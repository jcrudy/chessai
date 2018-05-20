import time
from nose.tools import assert_almost_equal, assert_greater_equal, assert_equal
from chessai.ai.bitboard import BitBoardState, Player, LogisticPlayer
import chess

def move_is_legal(board, move):
    promotion_dict = {'Q':5, 'R':4, 'B':3, 'N':2, 'NO':None}
    pyboard = chess.Board(board.to_fen())
    pymove = chess.Move(move.from_square, move.to_square, promotion_dict[move.promotion.upper()])
    return pyboard.is_legal(pymove)

def test_weird_position():
    fen = '2b5/8/rqp1kpr1/3p2p1/4P2p/p3Q2P/2PPKPP1/R1B3b1 w - - 12 41'
    board = BitBoardState.from_fen(fen)
    player = Player(1000000, 3, 3)
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
    player = Player(1000000, 3, 3)
    board = BitBoardState.from_fen(starting_fen)
    move, _, _ = player.tmovesearch(board, 1)
    assert(move_is_legal(board, move))

def test_mtdf_vs_regular():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    player1 = Player(1000000, 3, 3)
    player2 = Player(1000000, 3, 3)
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
    player = Player(1000000, 3, 3)
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
    player1 = Player(1000000, 3, 3)
    player2 = Player(1000000, 3, 3)
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
    white = Player(1000000, 3, 3)
    black = Player(1000000, 3, 3)
    while(True):
        print(board.to_grid())
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
            move, score = player.movesearch(board, 4)
        else:
            move, score = player.movesearch(board, 4)
        t1 = time.time()
        print('%s: Search took %fs.' % (board.to_fen(), t1-t0))
        
        if not move:
            raise ValueError('%s failed to generate a move: %s' % (player_string, board.to_fen()))
        else:
            print('%s chose move %s with score %d' % (player_string, str(move), score))
        board.make_move(move)

if __name__ == '__main__':
    test_iterative_speed_boost()
    test_logistic_iterative_speed_boost()
    exit()
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])