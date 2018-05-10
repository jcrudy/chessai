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
#     starting_fen = 'rn1q1bnr/pp1bk1pp/2p1pp2/8/3p4/BPP1PN2/P4PPP/RN2KB1R b KQ - 2 9'
#     starting_fen = 'rnbqkb1r/ppp1pppp/5n2/3p4/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq d6 0 3'
    board = BitBoardState.from_fen(starting_fen)
#     white = ThresholdPlayer(5000000, 1e-6)
#     black = ThresholdPlayer(5000000, 1e-9)

    print 1
    white = Player(5000000, 3, 3)
    print 2
    black = Player(5000000, 3, 3)
    print 3
    print('\n')
    print(board.to_grid())
    print 4
    while(True):
        t0 = time.time()
        print 5
        move = white.movesearch(board)
        print 6
        print(move)
        t1 = time.time()
        print('%s: Search took %fs.' % (board.to_fen(), t1-t0))
        if move:
            board.make_move(move)
        print('#'*10)
        print(board.to_grid())
        break
#         break
        if board.checkmate():
            print 'White wins!'
            break
        if not move:
            print 'Stalemate!'
            break
        t0 = time.time()
        move = black.movesearch(board)
        t1 = time.time()
        print('%s: Search took %fs.' % (board.to_fen(), t1-t0))
        if move:
            board.make_move(move)
        print('#'*10)
        print(board.to_grid())
        if board.checkmate():
            print 'Black wins!'
            break
        if not move:
            print 'Stalemate!'
            break
#         break
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