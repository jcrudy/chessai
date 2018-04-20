import time
from nose.tools import assert_almost_equal, assert_greater_equal
from chessai.ai.bitboard import BitBoardState, ThresholdPlayer, TimePlayer

def test_quiescence_efficiency():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(starting_fen)
    quiescent = ThresholdPlayer(5000000, .0000001, True)
    mundane = ThresholdPlayer(5000000, .0000001, False)
    n = 1
    t0 = time.time()
    for _ in range(n):
        print(mundane.movesearch(board))
    t1 = time.time()
    print('Mundane player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))
    for _ in range(n):
        print(quiescent.movesearch(board))
    t1 = time.time()
    print('Quiescent player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))


def test_threshold_vs_time():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(starting_fen)
    threshold = ThresholdPlayer(0, .0000001, False)
    time_ = TimePlayer(0, 4.5, False)
    n = 1
    t0 = time.time()
    for _ in range(n):
        threshold.movesearch(board)
    t1 = time.time()
    print('Threshold player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))
    t0 = time.time()
    for _ in range(n):
        time_.movesearch(board)
    t1 = time.time()
    print('Time player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))

def test_transposition_vs_no_with_threshold():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(starting_fen)
    transposition = ThresholdPlayer(5000000, .0000001, False)
    no_transposition = ThresholdPlayer(0, .0000001, False)
    n = 1
    t0 = time.time()
    for _ in range(n):
        transposition.movesearch(board)
    t1 = time.time()
    print('Transposition player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))
    t0 = time.time()
    for _ in range(n):
        no_transposition.movesearch(board)
    t1 = time.time()
    print('No transposition player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))

def test_transposition_vs_no_with_time():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(starting_fen)
    transposition = TimePlayer(5000000, 4.5, False)
    no_transposition = TimePlayer(0, 4.5, False)
    n = 1
    t0 = time.time()
    for _ in range(n):
        transposition.movesearch(board)
    t1 = time.time()
    print('Transposition player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))
    t0 = time.time()
    for _ in range(n):
        no_transposition.movesearch(board)
    t1 = time.time()
    print('No transposition player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))


if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])