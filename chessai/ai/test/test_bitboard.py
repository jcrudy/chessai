from chessai.ai.bitboard import BitBoardState, BitBoard
from nose.tools import assert_equal
import random

def test_from_fen():
    fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    bb = BitBoardState.from_fen(fen)
    assert_equal(bb.get_k().to_str(), '0000100000000000000000000000000000000000000000000000000000001000')
    assert_equal(bb.get_q().to_str(), '0001000000000000000000000000000000000000000000000000000000010000')
    assert_equal(bb.get_b().to_str(), '0010010000000000000000000000000000000000000000000000000000100100')
    assert_equal(bb.get_n().to_str(), '0100001000000000000000000000000000000000000000000000000001000010')
    assert_equal(bb.get_r().to_str(), '1000000100000000000000000000000000000000000000000000000010000001')
    assert_equal(bb.get_p().to_str(), '0000000011111111000000000000000000000000000000001111111100000000')
    assert_equal(bb.get_white().to_str(), '0000000000000000000000000000000000000000000000001111111111111111')
    assert_equal(bb.get_black().to_str(), '1111111111111111000000000000000000000000000000000000000000000000')

def test_to_fen():
    fens = ['8/5N2/4p2p/5p1k/1p4rP/1P2Q1P1/P4P1K/5q2 w - - 15 44',
            'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1',
            'rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1',
            'rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2',
            'rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2',
            ]
    for fen in fens:
        bb = BitBoardState.from_fen(fen)
        new_fen = bb.to_fen()
        assert_equal(new_fen, fen)

def test_bitboard():
    s = '0000000000000000000000000000000100000011000010000111010000000000'
    bb = BitBoard.from_str(s)
    assert_equal(s, bb.to_str())
    for _ in range(1000):
        s = ''.join([random.choice(['0','1']) for _ in range(64)])
        bb = BitBoard.from_str(s)
        assert_equal(s, bb.to_str())
        

if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])