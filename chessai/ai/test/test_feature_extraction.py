from chessai.ai.bitboard import BitBoardState

def test_feature_extraction():
    initial_fen = 'rnbqkbnr/pppppppr/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(initial_fen)
    print board.extract_features()
    
    
if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])