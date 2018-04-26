from chessai.locations import data_dir
import os
from toolz.functoolz import curry
import h5py
from bz2 import BZ2File
import chess.pgn
from chessai.ai.bitboard import BitBoardState, Move
from toolz.curried import keymap
from toolz.dicttoolz import merge
import time
import numpy as np
from _collections import defaultdict

def chess_move_to_black_move(chess_move):
    promotion_dict = {5: 'q', 4:'r', 3:'b', 2:'n'}
    mv = Move(chess_move.from_square, chess_move.to_square, 
              promotion_dict[chess_move.promotion] if chess_move.promotion else 'no')
    return mv

@curry
def move_is_capture(board, move):
    if board.get_piece_at_square_index(move.from_square).lower() != 'p':
        return board.get_piece_at_square_index(move.to_square).lower() not in {'no', 'ep'}
    else:
        return board.get_piece_at_square_index(move.to_square).lower() != 'no'
    
def chess_move_to_white_move(chess_move):
    promotion_dict = {5: 'Q', 4:'R', 3:'B', 2:'N'}
    mv = Move(chess_move.from_square, chess_move.to_square, 
              promotion_dict[chess_move.promotion] if chess_move.promotion else 'no')
    return mv

infilenames = [
               os.path.join(data_dir, 'ficsgamesdb_2017_standard2000_nomovetimes_1546835.pgn.bz2'),
               os.path.join(data_dir, 'ficsgamesdb_2016_standard2000_nomovetimes_1547869.pgn.bz2'),
               ]
# fields = ['pawn', 'knight', 'rook', 'bishop', 'queen', 'king', 'en_passant', 'all', 'queen_and_bishop',
#           'queen_and_rook', 'turn', 'castle_rights']
# fields += list(map(lambda x: x + '_selected', fields))

outfilename = os.path.join(data_dir, 'fics_features.h5')

def write_data(outfile, data):
    for k in sorted(data.keys()):
        arr = np.array(data[k])
        shape = arr.shape
        if k not in outfile:
            outfile.create_dataset(k, (0,) + shape[1:], maxshape=(None,) + shape[1:], chunks=True, compression='lzf')
        ds = outfile[k]
        s = ds.shape[0]
        ds.resize(s + shape[0], axis=0)
        ds.__setitem__((slice(s,None,None),) + (slice(None,None,None),) * (len(shape) - 1), arr)
#         if len(shape) == 3:
#             ds[s:,:,:] = arr
#         else:
#             ds[s:,:] = arr
            
def append_data(data, addition):
    for k in addition.keys():
        data[k].append(addition[k])

if __name__ == '__main__':
    raise
    t0 = time.time()
    results = defaultdict(list)
    
    with h5py.File(outfilename, 'w') as outfile:
        for infilename in infilenames:
            with BZ2File(infilename, 'r') as infile:
                state_id = 0
                games = 0
                write_count = 1
                while infile:
                    game = chess.pgn.read_game(infile)
                    if game is None:
                        break
                    pyboard = game.board()
                    board = BitBoardState.from_fen(pyboard.fen())
                    for pymove in game.main_line():
            #             print(pymove)
                        if pyboard.turn:
                            move = chess_move_to_white_move(pymove)
                        else:
                            move = chess_move_to_black_move(pymove)
                        legal_moves = board.all_moves()
                        rec = board.make_move(move)
                        selected_move_features = keymap(lambda x: x + '_selected', board.extract_features())
                        board.unmake_move(rec)
                        for legal_move in legal_moves:
                            rec = board.make_move(legal_move)
                            data = merge(board.extract_features(),
                                         selected_move_features,
                                         dict(white=np.array([1. if board.whites_turn else -1.])))
                            append_data(results, data)
                            board.unmake_move(rec)
                        board.make_move(move)
                    games += 1
                    if games % 10 == 0:
                        write_data(outfile, results)
                        
                        results = defaultdict(list)
                    t = time.time()
                    print('Completed %d game%s in %fs.' % (games, 's' if games > 1 else '', t - t0))
                    
            


