import time
from nose.tools import assert_almost_equal, assert_greater_equal
from chessai.ai.bitboard import BitBoardState, Player

# def test_movesearch_depth():
#     starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
#     board = BitBoardState.from_fen(starting_fen)
#     for _ in range(10):
#         print(board.to_grid())
#         move, t = board.movesearch_depth(5)
#         board.make_move(move)
#         print(t)

def test_movesearch():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(starting_fen)
    white = Player(5000000, .00001)
    black = Player(5000000, .00001)
    print('\n')
    print(board.to_grid())
    for _ in range(1000):
        t0 = time.time()
        move = white.movesearch(board)
        t1 = time.time()
        move = white.movesearch(board)
        t2 = time.time()
        print('%s: First search took %fs and second took %fs.' % (board.to_fen(), t1-t0, t2-t1))
        board.make_move(move)
        print('#'*10)
        print(board.to_grid())
        if board.checkmate():
            print 'White wins!'
        t3 = time.time()
        move = black.movesearch(board)
        t4 = time.time()
        move = black.movesearch(board)
        t5 = time.time()
        print('%s: First search took %fs and second took %fs.' % (board.to_fen(), t4-t3, t5-t4))
        board.make_move(move)
        print('#'*10)
        print(board.to_grid())
        if board.checkmate():
            print 'Black wins!'
#         t0 = time.time()
#         if i % 2 == 0:#white
#             thresh = .00000001
#         else: #black
#             thresh = .000001
#         move, depth = board.movesearch_threshold(thresh)
#         t1 = time.time()
#         assert_almost_equal(t1 - t0, 2., places=1)
#         assert_greater_equal(depth, 5)
#         board.make_move(move)
#         print('#'*10)
#         print(board.to_grid())

if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])