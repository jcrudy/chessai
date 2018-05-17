from chessai.ai.bitboard import BitBoardState, Player, Move
import random
import numpy as np
import csv
from chessai.locations import data_dir
import os
from tqdm import tqdm
import chess


def move_is_legal(board, move):
    promotion_dict = {'Q':5, 'R':4, 'B':3, 'N':2, 'NO':None}
    pyboard = chess.Board(board.to_fen())
    if move.promotion.upper() not in promotion_dict:
        print('%s not legal promotion' % move.promotion)
        return False
    pymove = chess.Move(move.from_square, move.to_square, promotion_dict[move.promotion.upper()])
    return pyboard.is_legal(pymove)

def random_fen(random_ply, smart_ply=0, player=None, time=10, start='rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'):
#     print('random_fen')
    success = False
    if player is None and smart_ply > 0:
        player = Player(4000000, 3, 3)
    i = 0
    while not success:
#         print('i = %d' % i)
        i += 1
        board = BitBoardState.from_fen(start)
        success = True
        for _ in range(random_ply):
            moves = board.all_moves()
            if not moves:
                success = False
                break
            move = random.choice(moves)
            try:
                assert(move_is_legal(board, move))
            except:
                raise
            board.make_move(move)
        if board.draw() or board.checkmate():
            success = False
            continue
        if smart_ply > 0:
            for _ in range(smart_ply):
                move = Move(0, 0)
                t  = time
                while not move_is_legal(board, move):
                    move, _, _ = player.tmovesearch(board, t)
                    if not move_is_legal(board, move):
#                         print 1, move
                        t += 100
                try:
                    assert(move_is_legal(board, move))
                except:
                    raise
                board.make_move(move)
                if board.draw() or board.checkmate():
                    success = False
                    break
#     print('end random_fen')
    return board.to_fen()

def score_position(position, time=100, player=None):
#     print('score_position')
    board = BitBoardState.from_fen(position)
    if player is None:
        player = Player(4000000, 3, 3)
    while not (board.draw() or board.checkmate()):
        move = Move(0, 0)
        t = time
        while not move_is_legal(board, move):
            move, _, _ = player.tmovesearch(board, t)
            if not move_is_legal(board, move):
                print 2, move
                t *= 2
            if t > 10000:
#                 print(board.to_fen())
                move, _, _ = player.tmovesearch(board, t, True)
#                 raise ValueError()
        try:
            assert(move_is_legal(board, move))
        except:
            raise
        board.make_move(move)
    
#     print('end score_position')
    if board.draw():
        return 0
    elif board.whites_turn:
        return -1
    else:
        return 1
    
def generate_data(filename, n, player=None, lower=1, upper=100., smart_lower=0, smart_upper=50, time=100, start='rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'):
    with open(filename, 'w', 0) as outfile:
        writer = csv.writer(outfile)
        for _ in tqdm(range(n)):
            random_ply = np.random.randint(lower, upper)
#             print('random_ply =', random_ply)
            smart_ply = np.random.randint(smart_lower, smart_upper)
#             print('smart_ply =', smart_ply)
            fen = random_fen(random_ply, smart_ply=smart_ply, player=player, start=start, time=time)
#             print(fen)
            score = score_position(fen, time=time, player=player)
#             print(score)
            writer.writerow([fen, random_ply, str(score)])

if __name__ == '__main__':
#     fen = 'rnbqkb1r/pppppppp/7n/8/8/PP6/2PPPPPP/RNBQKBNR b KQkq - 0 2'
#     board = BitBoardState.from_fen(fen)
#     player = Player(4000000, 3, 3)
#     while not (board.draw() or board.checkmate()):
#         print(board.to_grid())
#         move, _ = player.mtdf(board, 3)
#         board.make_move(move)
    
#     print random_fen(100)
    outfilename = os.path.join(data_dir, 'random_positions_100k.csv')
    player = Player(4000000, 3, 3)
    generate_data(outfilename, 100000, player=player, time=10)
#     fen = random_fen(40)
#     board = BitBoardState.from_fen(fen)
#     print(board.to_grid())
#     print(score_position(fen))
    
    
    
    