from chessai.ai.bitboard import BitBoardState, BitBoard
from nose.tools import assert_equal
import random

def test_place_piece():
    fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    bb = BitBoardState.from_fen(fen)
    bb.place_piece(0, 'p')
    new_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNp w KQkq - 0 1'
    assert_equal(bb.to_fen(), new_fen)
    
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

def test_to_grid():
    fens = [
            '8/5N2/4p2p/5p1k/1p4rP/1P2Q1P1/P4P1K/5q2 w - - 15 44',
            'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1',
            'rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1',
            'rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2',
            'rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2',
            'R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1',
            '3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1',
            ]
    for fen in fens:
        bb = BitBoardState.from_fen(fen)
        assert_equal(bb.to_grid(), bb.to_grid_redundant())

def test_move_generation():
    # The following two positions should have 218 moves each.
    # See https://chessprogramming.wikispaces.com/Encoding+Moves
    positions_218 = [
                     'R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1',
                     '3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1',
                     ]

def test_to_fen():
    fens = [
            '8/5N2/4p2p/5p1k/1p4rP/1P2Q1P1/P4P1K/5q2 w - - 15 44',
            'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1',
            'rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1',
            'rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2',
            'rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2',
            'R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1',
            '3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1',
            ]
    for fen in fens:
        bb = BitBoardState.from_fen(fen)
        new_fen = bb.to_fen()
        assert_equal(new_fen, fen)

def test_bitboard_io():
    s = '0000000000000000000000000000000100000011000010000111010000000000'
    bb = BitBoard.from_str(s)
    assert_equal(s, bb.to_str())
    for _ in range(1000):
        s = ''.join([random.choice(['0','1']) for _ in range(64)])
        bb = BitBoard.from_str(s)
        assert_equal(s, bb.to_str())
        assert_equal(bb.to_grid(), BitBoard.from_grid(bb.to_grid()).to_grid())
    
    s = '00000000000000000000000000000000000000000000000000000000000000001'
    
    g = '''
             00000000
             00000000
             00000000
             00000000
             00000000
             00000000
             00000000
             10000000
         '''
    
    assert_equal(BitBoard.from_str(s).to_grid(), BitBoard.from_grid(g).to_grid())
    
def test_bitboard_slide_north():
    pieces = BitBoard.from_grid('''
             00000000
             00000000
             00000000
             00000000
             00000000
             00001000
             00101000
             00000000
             ''')
    
    unoccupied = BitBoard.from_grid('''
                 11111111
                 11111111
                 11111101
                 11011111
                 11111111
                 11110111
                 11010111
                 11111101
                 ''')
    
    expected = BitBoard.from_grid('''
                 00001000
                 00001000
                 00001000
                 00001000
                 00101000
                 00101000
                 00101000
                 00000000
                 ''')
    assert_equal(pieces.slide_north(unoccupied), expected)
    
def test_bitboard_slide_south():
    pieces = BitBoard.from_grid('''
             00000000
             00001000
             00100000
             00000000
             00000000
             00000000
             00100000
             00000000
             ''')
    
    unoccupied = BitBoard.from_grid('''
                 11111111
                 11111111
                 11111101
                 11011111
                 11111111
                 11110111
                 11010111
                 11111101
                 ''')
    
    expected = BitBoard.from_grid('''
                 00000000
                 00001000
                 00101000
                 00001000
                 00001000
                 00000000
                 00100000
                 00100000
                 ''')
    assert_equal(pieces.slide_south(unoccupied), expected)

def test_bitboard_slide_east():
    pieces = BitBoard.from_grid('''
             00000000
             00001000
             00100000
             00000000
             00000000
             00000000
             00100000
             00000000
             ''')
    
    unoccupied = BitBoard.from_grid('''
                 11111111
                 11111111
                 11111101
                 11011111
                 11111111
                 11110111
                 11010111
                 11111101
                 ''')
    
    expected = BitBoard.from_grid('''
                 00000000
                 00001111
                 00111100
                 00000000
                 00000000
                 00000000
                 00110000
                 00000000
                 ''')
    assert_equal(pieces.slide_east(unoccupied), expected)

def test_bitboard_slide_west():
    pieces = BitBoard.from_grid('''
             00000000
             00001000
             00100000
             00000000
             00000000
             00000000
             00100000
             00000000
             ''')
    
    unoccupied = BitBoard.from_grid('''
                 11111111
                 11111111
                 10111101
                 11011111
                 11111111
                 11110111
                 11010111
                 11111101
                 ''')
    
    expected = BitBoard.from_grid('''
                 00000000
                 11111000
                 00100000
                 00000000
                 00000000
                 00000000
                 11100000
                 00000000
                 ''')
    assert_equal(pieces.slide_west(unoccupied), expected)

def test_bitboard_slide_northeast():
    pieces = BitBoard.from_grid('''
             00000000
             00001000
             00100000
             00000000
             00000000
             00000000
             00100000
             00000000
             ''')
    
    unoccupied = BitBoard.from_grid('''
                 11111111
                 11111111
                 10111101
                 11011111
                 11111111
                 11110111
                 11010111
                 11111101
                 ''')
    
    expected = BitBoard.from_grid('''
                 00001100
                 00011000
                 00100000
                 00000100
                 00001000
                 00010000
                 00100000
                 00000000
                 ''')
    assert_equal(pieces.slide_northeast(unoccupied), expected)

def test_bitboard_slide_northwest():
    pieces = BitBoard.from_grid('''
             00000000
             00001000
             00100000
             00000000
             00000000
             00000000
             00100000
             00000100
             ''')
    
    unoccupied = BitBoard.from_grid('''
                 11111111
                 11111111
                 10111101
                 11011111
                 11111111
                 11100111
                 11010111
                 11111101
                 ''')
    
    expected = BitBoard.from_grid('''
                 10010000
                 01001000
                 00100000
                 00000000
                 10000000
                 01000000
                 00100000
                 00000100
                 ''')
    assert_equal(pieces.slide_northwest(unoccupied), expected)

def test_bitboard_slide_southeast():
    pieces = BitBoard.from_grid('''
             00000000
             00001000
             00100000
             00000000
             00000000
             00000000
             00100000
             00000100
             ''')
    
    unoccupied = BitBoard.from_grid('''
                 11111111
                 11111111
                 10111101
                 11001111
                 11111111
                 11100111
                 11010111
                 11111101
                 ''')
    
    expected = BitBoard.from_grid('''
                 00000000
                 00001000
                 00100100
                 00000010
                 00000001
                 00000000
                 00100000
                 00010100
                 ''')
    assert_equal(pieces.slide_southeast(unoccupied), expected)

def test_bitboard_slide_southwest():
    pieces = BitBoard.from_grid('''
             00000000
             00001000
             00100000
             00000000
             00000000
             00000000
             00100000
             00000100
             ''')
    
    unoccupied = BitBoard.from_grid('''
                 11111111
                 11111111
                 10111101
                 11001111
                 11111111
                 11100111
                 11010111
                 11111101
                 ''')
    
    expected = BitBoard.from_grid('''
                 00000000
                 00001000
                 00110000
                 01000000
                 10000000
                 00000000
                 00100000
                 01000100
                 ''')
    assert_equal(pieces.slide_southwest(unoccupied), expected)

def test_bitboard_ls1b():
    s = '0000000000000000000000000000000100000011000010000111010000000000'
    e = '0000000000000000000000000000000000000000000000000000010000000000'
    bb = BitBoard.from_str(s)
    assert_equal(e, bb.ls1b().to_str())



if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])