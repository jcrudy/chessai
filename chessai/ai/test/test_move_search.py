import time
from nose.tools import assert_almost_equal, assert_greater_equal, assert_equal,\
    assert_true, assert_false
from chessai.ai.bitboard import BitBoardState, SimplePlayer, LogisticPlayer, Move
import chess

def move_is_legal(board, move):
    promotion_dict = {'Q':5, 'R':4, 'B':3, 'N':2, 'NO':None}
    pyboard = chess.Board(board.to_fen())
    pymove = chess.Move(move.from_square, move.to_square, promotion_dict[move.promotion.upper()])
    return pyboard.is_legal(pymove)

def test_weird_position():
    fen = '2b5/8/rqp1kpr1/3p2p1/4P2p/p3Q2P/2PPKPP1/R1B3b1 w - - 12 41'
    board = BitBoardState.from_fen(fen)
    player = SimplePlayer(1000000, 3, 3)
    move, score, depth = player.tmovesearch(board, 100)
    print(score, depth)
    try:
        assert(move_is_legal(board, move))
    except:
        print(board.to_grid())
        print(move)
        raise

def test_fast_move_is_legal():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    player = SimplePlayer(1000000, 3, 3)
    board = BitBoardState.from_fen(starting_fen)
    move, _, _ = player.tmovesearch(board, 1)
    assert(move_is_legal(board, move))

def test_mtdf_vs_regular():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    player1 = SimplePlayer(1000000, 3, 3)
    player2 = SimplePlayer(1000000, 3, 3)
    board = BitBoardState.from_fen(starting_fen)
    depth = 6
    
    t0 = time.time()
    move, score = player1.mtdf(board, depth)
    t1 = time.time()
    print('Initial search to depth %d took %fs. Got %s with score %d.' % (depth, t1-t0, str(move), score))

    t0 = time.time()
    for d in range(depth+1):
        move, score = player2.mtdf(board, d)
    t1 = time.time()
    print('Iterative search to depth %d took %fs. Got %s with score %d.' % (depth, t1-t0, str(move), score))


def test_draw():
    starting_fen = 'Q1k5/7p/2p2r2/1p1p1p2/5qn1/P1N5/1PP4P/3R3K b - - 49 59'
    board = BitBoardState.from_fen(starting_fen)
    player = SimplePlayer(1000000, 3, 3)
    depth = 6
    t0 = time.time()
    move, score = player.movesearch(board, depth)
    t1 = time.time()
    print('Search to depth %d took %fs. Got %s with score %d.' % (depth, t1-t0, str(move), score))
    assert_equal(score, 0)

def test_logistic_iterative_speed_boost():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    player1 = LogisticPlayer(1000000, 3, 3)
    player2 = LogisticPlayer(1000000, 3, 3)
    board = BitBoardState.from_fen(starting_fen)
    depth = 6
    
    t0 = time.time()
    move, score = player1.movesearch(board, depth, True)
    t1 = time.time()
    print('Initial search to depth %d took %fs. Got %s with score %d.' % (depth, t1-t0, str(move), score))

    t0 = time.time()
    for d in range(depth+1):
        move, score = player2.movesearch(board, d)
    t1 = time.time()
    print('Iterative search to depth %d took %fs. Got %s with score %d.' % (depth, t1-t0, str(move), score))
 

def test_iterative_speed_boost():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    player1 = SimplePlayer(1000000, 3, 3)
    player2 = SimplePlayer(1000000, 3, 3)
    board = BitBoardState.from_fen(starting_fen)
    depth = 6
    
    t0 = time.time()
    move, score = player1.movesearch(board, depth, True)
    t1 = time.time()
    print('Initial search to depth %d took %fs. Got %s with score %d.' % (depth, t1-t0, str(move), score))

    t0 = time.time()
    for d in range(depth+1):
        move, score = player2.movesearch(board, d)
    t1 = time.time()
    print('Iterative search to depth %d took %fs. Got %s with score %d.' % (depth, t1-t0, str(move), score))
        
    
def test_movesearch():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(starting_fen)
    white = SimplePlayer(1000000, 3, 3)
    black = LogisticPlayer(1000000, 3, 3)
    while(True):
        before_grid = board.to_grid()
        before_fen = board.to_fen()
        print(board.to_grid())
        print(board.draw())
        print(board.repetition(2))
        print(board.repetition(3))
        if board.draw():
            print('Draw: %s' % board.to_fen())
            break
        elif board.checkmate():
            print('Checkmate! %s wins: %s' %('Black' if board.whites_turn else 'White', board.to_fen()))
            break
        if board.whites_turn:
            player = white
            player_string = 'White'
        else:
            player = black
            player_string = 'Black'
        
        t0 = time.time()
        if player_string == black:
            move, score, depth = player.tmovesearch(board, 1000)
        else:
            move, score, depth = player.tmovesearch(board, 1000)
        t1 = time.time()
        after_grid = board.to_grid()
        after_fen = board.to_fen()
        print('%s: Search took %fs and reached depth %d.' % (board.to_fen(), t1-t0, depth))
        
        if not move:
            raise ValueError('%s failed to generate a move: %s' % (player_string, board.to_fen()))
        else:
            print('%s chose move %s with score %d' % (player_string, str(move), score))
        try:
            assert_equal(before_fen, after_fen)
            assert_equal(before_grid, after_grid)
        except:
            print('Before:')
            print before_grid
            print before_fen
            print('After:')
            print after_grid
            print after_fen
            raise
        print 'board.white_castle_king =', board.get_white_castle_king()
        print 'board.white_castle_queen =', board.get_white_castle_queen()
        print 'board.black_castle_king =', board.get_black_castle_king()
        print 'board.black_castle_queen =', board.get_black_castle_queen()
        print 'threefold_repetition_clock =', board.get_threefold_repetition_clock()
        print 'board.zobrist_hash() =', board.zobrist_hash().value
        
        board.make_move(move)

def test_weird_situation():
    fen = '8/7P/4k3/2b5/2P1p2P/4p3/5q2/5K2 w - - 3 54'
    board = BitBoardState.from_fen(fen)
    player = LogisticPlayer(1000000, 3, 3)
#     board.make_move(Move(1, 18, "no"))
    player.tmovesearch(board, 1000)
    assert_equal(board.to_fen(), fen)

def test_draw_by_repetition():
#     fen = 'r1b1k2r/ppp2ppp/3p4/8/2Pn4/1PKBqP2/P5PP/3R2NR b kq - 0 16'
    fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(fen)
    player = LogisticPlayer(1000000, 3, 3)
    moves = [
        Move(12, 28, "no"),
        Move(51, 43, "no"),
        Move(5, 33, "no"),
        Move(50, 42, "no"),
        Move(33, 26, "no"),
        Move(57, 51, "no"),
        Move(11, 27, "no"),
        Move(62, 45, "no"),
        Move(26, 19, "no"),
        Move(43, 35, "no"),
        Move(28, 36, "no"),
        Move(45, 28, "no"),
        Move(4, 5, "no"),
        Move(42, 34, "no"),
        Move(2, 20, "no"),
        Move(34, 26, "no"),
        Move(19, 28, "no"),
        Move(35, 28, "no"),
        Move(1, 18, "no"),
        Move(59, 41, "no"),
        Move(9, 17, "no"),
        Move(41, 42, "no"),
        Move(6, 12, "no"),
        Move(52, 44, "no"),
        Move(17, 26, "no"),
        Move(51, 41, "no"),
        Move(27, 35, "no"),
        Move(42, 26, "no"),
        Move(35, 43, "no"),
        Move(41, 35, "no"),
        Move(3, 11, "no"),
        Move(58, 51, "no"),
        Move(18, 35, "no"),
        Move(26, 35, "no"),
        Move(11, 35, "no"),
        Move(44, 35, "no"),
        Move(0, 3, "no"),
        Move(56, 58, "no"),
        Move(10, 18, "no"),
        Move(51, 44, "no"),
        Move(3, 2, "no"),
        Move(53, 45, "no"),
        Move(12, 27, "no"),
        Move(60, 51, "no"),
        Move(2, 1, "no"),
        Move(45, 36, "no"),
        Move(27, 44, "no"),
        Move(51, 44, "no"),
        Move(43, 51, "no"),
        Move(44, 51, "no"),
        Move(1, 49, "no"),
        Move(51, 44, "no"),
        Move(20, 11, "no"),
        Move(61, 34, "no"),
        Move(49, 54, "no"),
        Move(58, 57, "no"),
        Move(5, 12, "no"),
        Move(57, 9, "no"),
        Move(8, 24, "no"),
        Move(63, 61, "no"),
        Move(7, 5, "no"),
        Move(28, 20, "no"),
        Move(13, 20, "no"),
        Move(9, 11, "no"),
        Move(12, 11, "no"),
        Move(61, 5, "no"),
        Move(11, 12, "no"),
        Move(5, 53, "no"),
        Move(54, 53, "no"),
        Move(44, 53, "no"),
        Move(15, 31, "no"),
        Move(48, 40, "no"),
        Move(24, 32, "no"),
        Move(55, 39, "no"),
        Move(12, 21, "no"),
        Move(36, 28, "no"),
        Move(21, 12, "no"),
        Move(34, 43, "no"),
        Move(12, 11, "no"),
        Move(43, 50, "no"),
        Move(11, 10, "no"),
        Move(50, 32, "no"),
        Move(10, 17, "no"),
        Move(53, 44, "no"),
        Move(18, 26, "no"),
        Move(35, 27, "no"),
        Move(17, 10, "no"),
        Move(27, 20, "no"),
        Move(10, 3, "no"),
        Move(32, 25, "no"),
        Move(3, 12, "no"),
        Move(25, 34, "no"),
        Move(12, 4, "no"),
        Move(40, 32, "no"),
        Move(14, 30, "no"),
        Move(32, 24, "no"),
        Move(30, 39, "no"),
        Move(24, 16, "no"),
        Move(4, 12, "no"),
        Move(16, 8, "no"),
        Move(39, 47, "no"),
        Move(8, 0, "q"),
        Move(47, 55, "no"),
        Move(0, 8, "no"),
        Move(12, 5, "no"),
        Move(8, 13, "no"),
        Move(1, 18, "no"),
        Move(57, 42, "no"),
        Move(12, 20, "no"),
        Move(52, 44, "no"),
        Move(6, 21, "no"),
        Move(62, 45, "no"),
        Move(5, 33, "no"),
        Move(48, 40, "no"),
        Move(33, 42, "no"),
        Move(51, 42, "no"),
        Move(21, 36, "no"),
        Move(61, 43, "no"),
        Move(13, 29, "no"),
        Move(54, 38, "no"),
        Move(7, 5, "no"),
        Move(38, 29, "no"),
        Move(20, 29, "no"),
        Move(63, 62, "no"),
        Move(3, 12, "no"),
        Move(55, 39, "no"),
        Move(14, 22, "no"),
        Move(60, 52, "no"),
        Move(8, 16, "no"),
        Move(62, 54, "no"),
        Move(11, 27, "no"),
        Move(42, 34, "no"),
        Move(27, 34, "no"),
        Move(43, 34, "no"),
        Move(29, 37, "no"),
        Move(59, 63, "no"),
        Move(5, 29, "no"),
        Move(34, 43, "no"),
        Move(2, 11, "no"),
        Move(63, 55, "no"),
        Move(4, 5, "no"),
        Move(44, 37, "no"),
        Move(36, 26, "no"),
        Move(58, 44, "no"),
        Move(5, 4, "no"),
        Move(43, 29, "no"),
        Move(11, 29, "no"),
        Move(49, 33, "no"),
        Move(26, 20, "no"),
        Move(50, 42, "no"),
        Move(29, 36, "no"),
        Move(54, 62, "no"),
        Move(0, 3, "no"),
        Move(45, 28, "no"),
        Move(18, 28, "no"),
        Move(37, 28, "no"),
        Move(3, 43, "no"),
        Move(53, 45, "no"),
        Move(36, 29, "no"),
        Move(56, 58, "no"),
        Move(15, 31, "no"),
        Move(62, 59, "no"),
        Move(12, 3, "no"),
        Move(59, 43, "no"),
        Move(3, 43, "no"),
        Move(52, 53, "no"),
        Move(10, 18, "no"),
        Move(40, 32, "no"),
        Move(4, 3, "no"),
        Move(32, 24, "no"),
        Move(3, 2, "no"),
        Move(55, 62, "no"),
        Move(43, 34, "no"),
        Move(53, 46, "no"),
        Move(34, 25, "no"),
        Move(44, 26, "no"),
        Move(25, 34, "no"),
        Move(62, 44, "no"),
        Move(22, 30, "no"),
        Move(39, 30, "no"),
        Move(20, 26, "no"),
        Move(33, 26, "no"),
        Move(31, 39, "no"),
        Move(46, 53, "no"),
        Move(34, 48, "no"),
        Move(58, 50, "no"),
        Move(48, 50, "no"),
        Move(53, 60, "no"),
        Move(39, 47, "no"),
        Move(44, 53, "no"),
        Move(47, 55, "no"),
        Move(53, 39, "no"),
        Move(50, 57, "no"),
        Move(60, 53, "no"),
        Move(57, 62, "no"),
        Move(53, 52, "no"),
        Move(55, 63, "Q"),
        Move(39, 63, "no"),
        Move(62, 63, "no"),
        Move(52, 44, "no"),
        Move(63, 58, "no"),
        Move(44, 52, "no"),
        Move(58, 42, "no"),
        Move(28, 20, "no"),
        Move(42, 26, "no"),
        Move(20, 12, "no"),
        Move(26, 12, "no"),
        Move(52, 51, "no"),
        Move(12, 30, "no"),
        Move(51, 52, "no"),
        Move(29, 15, "no"),
        Move(52, 53, "no"),
        Move(30, 24, "no"),
        Move(53, 46, "no"),
        Move(24, 30, "no"),
        Move(46, 53, "no"),
        Move(15, 43, "no"),
        Move(45, 37, "no"),
        Move(30, 37, "no"),
        Move(53, 54, "no"),
        Move(43, 36, "no"),
        Move(54, 62, "no"),
        Move(37, 45, "no"),
        Move(62, 55, "no"),
        Move(45, 54, "no"),
        Move(6, 21, "no"),
        Move(62, 45, "no"),
        Move(11, 27, "no"),
        Move(52, 44, "no"),
        Move(2, 38, "no"),
        Move(55, 47, "no"),
        Move(38, 45, "no"),
        Move(59, 45, "no"),
        Move(1, 18, "no"),
        Move(61, 25, "no"),
        Move(8, 16, "no"),
        Move(25, 18, "no"),
        Move(9, 18, "no"),
        Move(57, 42, "no"),
        Move(0, 1, "no"),
        Move(45, 37, "no"),
        Move(12, 20, "no"),
        Move(37, 32, "no"),
        Move(1, 17, "no"),
        Move(48, 40, "no"),
        Move(5, 19, "no"),
        Move(47, 39, "no"),
        Move(15, 31, "no"),
        Move(32, 24, "no"),
        Move(21, 36, "no"),
        Move(42, 32, "no"),
        Move(17, 1, "no"),
        Move(51, 43, "no"),
        Move(36, 53, "no"),
        Move(60, 53, "no"),
        Move(3, 21, "no"),
        Move(53, 60, "no"),
        Move(4, 11, "no"),
        Move(32, 42, "no"),
        Move(21, 22, "no"),
        Move(60, 53, "no"),
        Move(1, 0, "no"),
        Move(58, 51, "no"),
        Move(7, 1, "no"),
        Move(49, 41, "no"),
        Move(22, 38, "no"),
        Move(63, 47, "no"),
        Move(20, 28, "no"),
        Move(56, 63, "no"),
        Move(28, 36, "no"),
        Move(43, 36, "no"),
        Move(27, 36, "no"),
        Move(24, 30, "no"),
        Move(13, 21, "no"),
        Move(30, 38, "no"),
        Move(31, 38, "no"),
        Move(47, 46, "no"),
        Move(21, 29, "no"),
        Move(42, 36, "no"),
        Move(29, 36, "no"),
        Move(46, 38, "no"),
        Move(19, 40, "no"),
        Move(51, 42, "no"),
        Move(11, 20, "no"),
        Move(38, 36, "no"),
        Move(20, 13, "no"),
        Move(53, 52, "no"),
        Move(1, 25, "no"),
        Move(63, 56, "no"),
        Move(25, 26, "no"),
        Move(36, 34, "no"),
        Move(26, 34, "no"),
        Move(41, 34, "no"),
        Move(40, 26, "no"),
        Move(56, 61, "no"),
        Move(13, 6, "no"),
        Move(39, 31, "no"),
        Move(0, 4, "no"),
        Move(42, 51, "no"),
        Move(4, 28, "no"),
        Move(61, 63, "no"),
        Move(28, 36, "no"),
        Move(63, 57, "no"),
        Move(36, 34, "no"),
        Move(57, 56, "no"),
        Move(6, 5, "no"),
        Move(56, 16, "no"),
        Move(26, 19, "no"),
        Move(16, 0, "no"),
        Move(5, 13, "no"),
        Move(50, 42, "no"),
        Move(34, 38, "no"),
        Move(52, 53, "no"),
        Move(38, 30, "no"),
        Move(44, 36, "no"),
        Move(30, 31, "no"),
        Move(51, 44, "no"),
        Move(31, 28, "no"),
        Move(53, 45, "no"),
        Move(28, 20, "no"),
        Move(0, 24, "no"),
        Move(13, 6, "no"),
        Move(44, 35, "no"),
        Move(18, 26, "no"),
        Move(35, 26, "no"),
        Move(19, 26, "no"),
        Move(24, 26, "no"),
        Move(10, 18, "no"),
        Move(36, 28, "no"),
        Move(6, 7, "no"),
        Move(26, 24, "no"),
        Move(7, 15, "no"),
        Move(45, 37, "no"),
        Move(20, 4, "no"),
        Move(37, 36, "no"),
        Move(4, 5, "no"),
        Move(28, 20, "no"),
        Move(5, 53, "no"),
        Move(36, 44, "no"),
        Move(53, 21, "no"),
        Move(24, 28, "no"),
        Move(21, 61, "no"),
        Move(44, 35, "no"),
        Move(61, 59, "no"),
        Move(35, 26, "no"),
        Move(59, 57, "no"),
        Move(20, 12, "no"),
        Move(57, 25, "no"),
        Move(26, 19, "no"),
        Move(25, 1, "no"),
        Move(12, 4, "q"),
        Move(1, 4, "no"),
        Move(28, 4, "no"),
        Move(15, 22, "no"),
        Move(19, 18, "no"),
        Move(22, 29, "no"),
        Move(4, 5, "no"),
        Move(29, 20, "no"),
        Move(42, 34, "no"),
        Move(20, 12, "no"),
        Move(34, 26, "no"),
        Move(12, 5, "no"),
        Move(18, 9, "no"),
        Move(5, 12, "no"),
        Move(26, 18, "no"),
        Move(12, 4, "no"),
        Move(18, 10, "no"),
        Move(4, 5, "no"),
        Move(10, 2, "q"),
        Move(5, 13, "no"),
        Move(54, 38, "no"),
        Move(13, 12, "no"),
        Move(2, 29, "no"),
        Move(12, 19, "no"),
        Move(38, 30, "no"),
        Move(14, 22, "no"),
        Move(29, 36, "no"),
        Move(19, 11, "no"),
        Move(9, 0, "no"),
        Move(11, 2, "no"),
        Move(36, 4, "no"),
        Move(2, 10, "no"),
        Move(4, 20, "no"),
        Move(10, 3, "no"),
        Move(20, 13, "no"),
        Move(3, 2, "no"),
        Move(0, 8, "no"),
        Move(2, 3, "no"),
        Move(8, 17, "no"),
        Move(3, 2, "no"),
        Move(17, 8, "no"),
        Move(2, 3, "no"),
        Move(8, 17, "no"),
#         Move(3, 2, "no"),
#         Move(17, 8, "no")
        ]
    for i, move in enumerate(moves):
        print(i)
        f1 = board.to_fen()
        if i==107:
            chosen, score, depth =  player.tmovesearch(board, 1000, debug=True)
        else:
            chosen, score, depth =  player.tmovesearch(board, 1000)
        f2 = board.to_fen()
        try:
            assert_equal(f1, f2)
        except:
            print(board.to_grid())
            print(board.to_fen())
            raise
        print(move)
        board.make_move(move)
        print board.to_grid()
        print board.to_fen()
    
    print player.tmovesearch(board, 1000)
    
    
    
#     m1 = Move(0, 10)
#     m2 = Move(63, 53)
#     r1 = Move(10, 0)
#     r2 = Move(53, 63)
#     board.make_move(m1)
#     board.make_move(m2)
#     board.make_move(r1)
#     board.make_move(r2)
#     assert_false(board.draw())
#     assert_true(board.repetition(2))
#     board.make_move(m1)
#     board.make_move(m2)
#     board.make_move(r1)
#     board.make_move(r2)
#     assert_true(board.draw())
#     
#     fen = '8/4r3/8/2k5/5K2/8/8/8 w - - 36 99'
#     board = BitBoardState.from_fen(fen)
#     board.make_move(Move(29, 37, "no"))
#     board.make_move(Move(34, 25, "no"))
#     board.make_move(Move(37, 29, "no"))
#     board.make_move(Move(25, 34, "no"))
#     board.make_move(Move(29, 37, "no"))
#     board.make_move(Move(34, 25, "no"))
#     board.make_move(Move(37, 29, "no"))
#     board.make_move(Move(25, 34, "no"))
#     assert_true(board.repetition(2))
#     board.make_move(Move(29, 37, "no"))
#     board.make_move(Move(34, 25, "no"))
#     board.make_move(Move(37, 29, "no"))
#     board.make_move(Move(25, 34, "no"))
#     assert_true(board.repetition(3))
#     assert_true(board.draw())
#     
#     fen = '8/8/3p4/p1p5/P1P1r3/8/8/K2k4 b - - 20 118'
#     board = BitBoardState.from_fen(fen)
#     moves = [Move(3, 2, "no"), Move(0, 8, "no"), Move(2, 3, "no"), Move(8, 0, "no"),
#              Move(3, 2, "no"), Move(0, 8, "no"), Move(2, 3, "no"), Move(8, 0, "no"),
#              Move(3, 2, "no"), Move(0, 8, "no"), Move(2, 3, "no"), Move(8, 9, "no")]
#     print board.to_grid()
#     for move in moves:
#         board.make_move(move)
#         print board.to_grid()
#         print board.draw()


if __name__ == '__main__':
    test_weird_situation()
    exit()
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])