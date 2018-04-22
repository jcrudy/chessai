import os
from chessai.data_dir import data_dir
from bz2 import BZ2File
import chess.pgn
from chessai.ai.bitboard import BitBoardState, Move
from toolz.functoolz import curry
import numpy as np
from toolz.curried import valmap
import csv
from toolz.dicttoolz import merge
import time
from gzip import GzipFile

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


infilename = os.path.join(data_dir, 'ficsgamesdb_2017_standard2000_nomovetimes_1546835.pgn.bz2')
fields = ['pawn', 'knight', 'rook', 'bishop', 'queen', 'king', 'en_passant', 'all', 'queen_and_bishop',
          'queen_and_rook', 'turn', 'castle_rights', 'choice', 'state_id']
filenames = dict(zip(fields, map(lambda name: os.path.join(data_dir, name + '.csv'), fields)))

compress = True
if compress:
    files = valmap(lambda fname: GzipFile(fname + '.gz', 'w'), filenames)
else:
    files = valmap(lambda fname: open(fname, 'w'), filenames)
writers = valmap(lambda fl: csv.writer(fl, lineterminator='\n'), files)

def append_data(data, addition):
    for k in set(data.keys()) & set(addition.keys()):
        data[k].writerow(addition[k])
        
t0 = time.time()
with BZ2File(infilename, 'r') as infile:
    state_id = 0
    games = 0
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
#             print(len(legal_moves))
            state_id += 1
            hit = False
            for legal_move in legal_moves:
                rec = board.make_move(legal_move)
                choice = np.array([0]) if legal_move != move else np.array([1]) if pyboard.turn else np.array([-1])
                if choice[0]:
                    hit = True
                append_data(writers, merge(board.extract_features(), dict(choice=choice, state_id=np.array([state_id]))))
                board.unmake_move(rec)
            pyboard.push(pymove)
            board.make_move(move)
#             assert hit
        games += 1
        print 'Completed %d game%s in %f seconds' % (games, 's' if games > 0 else '', time.time() - t0)

valmap(lambda fl: fl.close(), files)
t1 = time.time()
print(t1-t0)




