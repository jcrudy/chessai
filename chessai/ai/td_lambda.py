from chessai.ai.bitboard import BitBoardState
from infinity import inf
import numpy as np
import random
from chessai.ai.flat_network import create_net
import time
import h5py
from keras.models import save_model, load_model
import pickle
import os
from chessai.xnornet.xnor_layers import XnorDense
from chessai.xnornet.binary_ops import binary_tanh
from tempfile import mkstemp
from chessai.binarynet.binary_layers import Clip

class GameBlock(object):
    def __init__(self):
        self.states = []
        self.vectors = []
        self.scores = []
    
    def store(self, board, vector, score):
        self.states.append(board.to_fen())
        self.vectors.append(vector)
        self.scores.append(score)
    
    def train_data(self, lambd):
        n = len(self.states)
        if n <= 1:
            return None, None, None
        X = []
        y = []
        w = []
        # i is current, j is earlier
        # we always want earlier states to predict same as 
        # current, but discount based on number of steps in between
        for i in range(n):
            for j in range(i):
                X.append(self.vectors[j])
                y.append(self.scores[i])
                w.append(np.array([lambd ** (i - j - 1)]))
        if n == 2:
            return X[0], y[0], w[0]
        else:
            try:
                return np.concatenate(X, axis=0), np.concatenate(y, axis=0), np.concatenate(w, axis=0)
            except:
                return np.concatenate(X, axis=0), np.concatenate(y, axis=0), np.concatenate(w, axis=0)
    
class GameRecord():       
    def __init__(self):
        self.blocks = []
        self.current_block = None
        self.new_block()
        
    def new_block(self):
        if self.current_block is not None:
            self.blocks.append(self.current_block)
        self.current_block = GameBlock()
    
    def store(self, board, vector, score):
        self.current_block.store(board, vector, score)
    
    def train_data(self, lambd):
        self.new_block()
        X = []
        y = []
        w = []
        for i, block in enumerate(self.blocks):
            if i == len(self.blocks) - 1:
                1+1
            X_, y_, w_ = block.train_data(lambd)
            if y_ is not None:
                X.append(X_)
                y.append(y_)
                w.append(w_)
        if X:
            return np.concatenate(X, axis=0), np.concatenate(y, axis=0), np.concatenate(w, axis=0)
        else:
            return None, None, None

def basic_extractor(board):
    return board.extract_flat_raw_features()

def play_game(trainer, starting_fen, epsilon):
    return trainer.play_game(starting_fen, epsilon)

class TDLambdaPlayer(object):
    def __init__(self, extractor, model, win_score=2048, draw_score=0):
        self.extractor = extractor
        self.model = model
        self.win_score = win_score
        self.draw_score = draw_score
        self.reset_record()
        
    def reset_record(self):
        self.record = GameRecord()
    
    def _move(self, board):
        '''Choose move.  Return move, vector, score'''
        raise NotImplementedError
    
    def move(self, board):
        move, vector, score = self._move(board)
        self.record.store(board, vector, score)
        return move
    
    def learn(self):
        raise NotImplementedError
    
    def record_white_win(self):
        self.record.store(None, None, self.win_score)
    
    def record_black_win(self):
        self.record.store(None, None, -self.win_score)
        
    def record_draw(self):
        self.record.store(None, None, self.draw_score)
    
    
    
    
    
    

class TDLambdaTrainer(object):
    def __init__(self, lambd, extractor, model, win_score=2048., draw_score=0.):
        self.lam = lambd
        self.extractor = extractor
        self.model = model
        self.win_score = win_score
        self.draw_score = draw_score
    
    def __getstate__(self):
        with h5py.File('does not matter', driver='core', backing_store=False) as h5file:
            save_model(self.model, h5file)
            h5file.flush()
            binary_data = h5file.fid.get_file_image()
        return {
                'lam': self.lam,
                'extractor': self.extractor,
                'model': binary_data,
                'win_score': self.win_score,
                'draw_score': self.draw_score
                }
    
    def __setstate__(self, state):
        self.lam = state['lam']
        self.extractor = state['extractor']
        fapl = h5py.h5p.create(h5py.h5p.FILE_ACCESS)
        fapl.set_fapl_core()
        fapl.set_file_image(state['model'])
        tmfile, tmfilename = mkstemp()
        os.remove(tmfilename)
#         tmfile.close()
        fid = h5py.h5f.open(tmfilename, h5py.h5f.ACC_RDONLY, fapl=fapl)
        with h5py.File(fid) as h5file:
            loaded_model = load_model(h5file, custom_objects={'XnorDense': XnorDense,
                                                              'binary_tanh': binary_tanh,
                                                              'Clip': Clip})
        os.remove(tmfilename)
        self.model = loaded_model
        self.win_score = state['win_score']
        self.draw_score = state['draw_score']
    
    def save(self, path):
        with open(path, 'wb') as outfile:
            pickle.dump(self, outfile)
    
    @classmethod
    def load(cls, path):
        with open(path, 'rb') as infile:
            result = pickle.load(infile)
        return result
    
    def train(self, n_epochs, games_per_epoch=lambda i: 10, 
              starting_position=lambda i, j:'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1',
              epsilon=lambda i, j: .5,
              lambda_=lambda i, j: .5,
              batch_size=1024):
        X = []
        y = []
        w = []
        for i in range(n_epochs):
            for j in range(games_per_epoch(i)):
                start_pos = starting_position(i,j)
                eps = epsilon(i,j)
                record = self.play_game(start_pos, eps)
                lambd = lambda_(i, j)
                X_, y_, w_ = record.train_data(lambd)
                X.append(X_)
                y.append(y_)
                w.append(w_)
        
        if X is None or len(X) == 0:
            return
        elif len(X) == 1:
            X = X[0]
            y = y[0]
            w = w[0]
        else:
            X = np.concatenate(X, axis=0)
            y = np.concatenate(y, axis=0)
            w = np.concatenate(w, axis=0)
        if X is None:
            return
        try:
            print(y)
            self.model.fit(X, y, sample_weight=w, batch_size=batch_size, epochs=10)
        except:
            print(X)
            print(y)
            print(w)
            raise
    
    def play_game(self, starting_fen, epsilon):
        record = GameRecord()
        board = BitBoardState.from_fen(starting_fen)
        
        # Store starting position
        vec = self.extractor(board)
        d = vec.shape[-1]
        record.store(board, vec, self.model.predict(vec))
        
        # Play a game
        t0 = time.time()
        move_count = 0
        while True:
            whites_turn = board.whites_turn
            moves = board.all_moves()
            best_move = None
            if whites_turn:
                best_score = -inf
            else:
                best_score = inf
            
            # We are using an epsilon-greedy training algorithm
            explore = random.random() < epsilon
            if explore:
                record.new_block()
                best_move = random.choice(moves)
                board.make_move(best_move)
                best_vec = self.extractor(board)
                best_score = self.model.predict(best_vec)
                print 'Random move score: %d' % best_score
            else: #Exploit
                X = np.zeros(shape=(len(moves), d))
#                 y = np.empty(shape=(len(moves), 1))
#                 w = np.empty(shape=(len(moves), 1))
                draws = []
                mates = []
                for i, move in enumerate(moves):
                    rec = board.make_move(move)
                    if board.draw():
                        draws.append(i)
                    if board.checkmate():
                        mates.append(i)
                    X[i,:] = self.extractor(board)[0,:]
                    board.unmake_move(rec)
                y = self.model.predict(X)
                if draws:
                    y[np.array(draws)] = self.draw_score
                if mates:
                    y[np.array(mates)] = self.win_score if whites_turn else -self.win_score
                if whites_turn:
                    best_score_idx = np.argmax(y, 0)[0]
                else:
                    best_score_idx = np.argmin(y, 0)[0]
                best_score = y[best_score_idx:(best_score_idx+1), 0]
                best_move = moves[best_score_idx]
                best_vec = X[best_score_idx:(best_score_idx+1),:]
                print 'Selected move score: %d' % best_score
#                     score = self.model.predict(vec)
#                     if whites_turn:
#                         if score > best_score:
#                             best_score = score
#                             best_move = move
#                             best_vec = vec
#                     else:
#                         if score < best_score:
#                             best_score = score
#                             best_move = move
#                             best_vec = vec
                    
                    
                
                board.make_move(best_move)
            move_count += 1
            
            if board.draw():
                print("Draw!")
                record.store(board, best_vec, np.array([self.draw_score]))
                break
            if board.checkmate():
                print("Checkmate!  %s wins!" % ('Black' if board.whites_turn else 'White'))
                record.store(board, best_vec, np.array([self.win_score if not board.whites_turn else -self.win_score]))
                break
#             print(move_count, move_count / (time.time() - t0))
            record.store(board, best_vec, best_score)
            
        t1 = time.time()
        print('Played %d moves in %fs.' % (move_count, t1-t0))
        return record
    

if __name__ == '__main__':
    filename = 'saved_trainer.pkl'
    if os.path.exists(filename):
        print('Loading from file')
        trainer = TDLambdaTrainer.load(filename)
    else:
        print('Creating')
        model = create_net()
        model.compile(optimizer='adadelta', loss='mae')
        trainer = TDLambdaTrainer(.5, basic_extractor, model)
    k = 0
    while True:
        epsilon = .25#1. - (1/(1 + math.exp(-k / 100.)))
        print('epsilon = %f' % epsilon)
        trainer.train(1, 
                     epsilon=lambda i, j: epsilon,
                     lambda_=lambda i, j: .8,)
        
        trainer.save(filename)
        save_model(trainer.model, 'trained_model.h5')
        k += 1
#     
#     trainer.save('test_saved_trainer.pkl')
#     trainer2 = TDLambdaTrainer.load('test_saved_trainer.pkl')
#     record = trainer2.play_game('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1', .5)
#     print record.train_data(.5)
#     trainer2.train(1)
#     
#     trainer.train(1)
#     if os.path.exists('test_saved_trainer.pkl'):
#         os.remove('test_saved_trainer.pkl')
#                     
        
        
        