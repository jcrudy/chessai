import time
from nose.tools import assert_almost_equal, assert_greater_equal
from chessai.ai.bitboard import BitBoardState, ThresholdPlayer, TimePlayer

def test_quiescence_efficiency():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(starting_fen)
    quiescent = ThresholdPlayer(0, .000001, True)
    mundane = ThresholdPlayer(0, .000001, False)
    t0 = time.time()
    n = 1
    for _ in range(n):
        mundane.movesearch(board)
    t1 = time.time()
    print('Mundane player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))
    for _ in range(n):
        quiescent.movesearch(board)
    t1 = time.time()
    print('Quiescent player took %fs for %d search%s.' % (t1-t0, n, 'es' if n>1 else ''))


if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])