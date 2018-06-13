from chessai.ai.bitboard import BitBoardState
from infinity import inf
import numpy as np
import random
from chessai.ai.flat_network import create_net

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
        X = []
        y = []
        w = []
        for block in self.blocks:
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

class TDLambdaTrainer(object):
    def __init__(self, lambd, extractor, model, win_score=2048., draw_score=0.):
        self.lam = lambd
        self.extractor = extractor
        self.model = model
        self.win_score = win_score
        self.draw_score = draw_score
    
    def train(self, n_epochs, games_per_epoch=lambda i: 1, 
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
        
        if len(X) == 0:
            return
        elif len(X) == 1:
            X = X[0]
            y = y[0]
            w = w[0]
        else:
            X = np.concatenate(X, axis=0)
            y = np.concatenate(y, axis=0)
            w = np.concatenate(w, axis=0)
        self.model.fit(X, y, sample_weight=w, batch_size=batch_size)
    
    def play_game(self, starting_fen, epsilon):
        record = GameRecord()
        board = BitBoardState.from_fen(starting_fen)
        
        # Store starting position
        vec = self.extractor(board)
        record.store(board, vec, self.model.predict(vec))
        
        # Play a game
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
            else: #Exploit
                for move in moves:
                    rec = board.make_move(move)
                    vec = self.extractor(board)
                    score = self.model.predict(vec)
                    if whites_turn:
                        if score > best_score:
                            best_score = score
                            best_move = move
                            best_vec = vec
                    else:
                        if score < best_score:
                            best_score = score
                            best_move = move
                            best_vec = vec
                    
                    board.unmake_move(rec)
                
                board.make_move(best_move)
            
            if board.draw():
                record.store(board, best_vec, self.draw_score)
                break
            if board.checkmate():
                record.store(board, best_vec, self.win_score if not board.whites_turn else -board.win_score)
                break
            record.store(board, best_vec, best_score)
        
        return record
    

if __name__ == '__main__':
    model = create_net()
    model.compile(optimizer='adadelta', loss='mse')
    trainer = TDLambdaTrainer(.5, basic_extractor, model)
    record = trainer.play_game('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1', .5)
    print record.train_data(.5)
    trainer.train(1)
    
                    
        
        
        