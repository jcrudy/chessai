import time
from nose.tools import assert_almost_equal, assert_greater_equal
from chessai.ai.bitboard import BitBoardState, Player

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
    white = Player(5000000, 3, 3)
    black = Player(5000000, 3, 3)
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
        move, score = player.movesearch(board, 5)
        t1 = time.time()
        print('%s: Search took %fs.' % (board.to_fen(), t1-t0))
        
        if not move:
            raise ValueError('%s failed to generate a move: %s' % (player_string, board.to_fen()))
        else:
            print('%s chose move %s with score %d' % (player_string, str(move), score))
        board.make_move(move)

if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])