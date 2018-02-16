from nose.tools import assert_equal
from chessai.ai.bitboard import BitBoardState

def test_perft():
    # https://www.chessprogramming.net/perfect-perft/
    print('')
    print('Running perft tests...')
    fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 119060324)
    print('%s perft passed' % fen)
    fen = 'r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(5), 193690690)
    print('%s perft passed' % fen)
    fen = '8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(7), 178633661)
    print('%s perft passed' % fen)
    fen = 'r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 706045033)
    print('%s perft passed' % fen)
    fen = '1k6/1b6/8/8/7R/8/8/4K2R b K - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(5), 1063513)
    print('%s perft passed' % fen)
    fen = '3k4/3p4/8/K1P4r/8/8/8/8 b - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 1134888)
    print('%s perft passed' % fen)
    fen = '8/8/4k3/8/2p5/8/B2P2K1/8 w - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 1015133)
    print('%s perft passed' % fen)
    fen = '8/8/1k6/2b5/2pP4/8/5K2/8 b - d3 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 1440467)
    print('%s perft passed' % fen)
    fen = '5k2/8/8/8/8/8/8/4K2R w K - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 661072)
    print('%s perft passed' % fen)
    fen = '3k4/8/8/8/8/8/8/R3K3 w Q - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 803711)
    print('%s perft passed' % fen)
    fen = 'r3k2r/1b4bq/8/8/8/8/7B/R3K2R w KQkq - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(4), 1274206)
    print('%s perft passed' % fen)
    fen = 'r3k2r/8/3Q4/8/8/5q2/8/R3K2R b KQkq - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(4), 1720476)
    print('%s perft passed' % fen)
    fen = '2K2r2/4P3/8/8/8/8/8/3k4 w - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 3821001)
    print('%s perft passed' % fen)
    fen = '8/8/1P2K3/8/2n5/1q6/8/5k2 b - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(5), 1004658)
    print('%s perft passed' % fen)
    fen = '4k3/1P6/8/8/8/8/K7/8 w - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 217342)
    print('%s perft passed' % fen)
    fen = '8/P1k5/K7/8/8/8/8/8 w - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 92683)
    print('%s perft passed' % fen)
    fen = 'K1k5/8/P7/8/8/8/8/8 w - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(6), 2217)
    print('%s perft passed' % fen)
    fen = '8/k1P5/8/1K6/8/8/8/8 w - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(7), 567584)
    print('%s perft passed' % fen)
    fen = '8/8/2k5/5q2/5n2/8/5K2/8 b - - 0 1'
    assert_equal(BitBoardState.from_fen(fen).perft(4), 23527)
    print('%s perft passed' % fen)
    print('All perft tests complete.')

if __name__ == '__main__':
#     test_move_tree_depth_5()
#     exit()
#     test_a_position()
#     exit()
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])