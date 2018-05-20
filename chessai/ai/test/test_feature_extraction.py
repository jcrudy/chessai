from chessai.ai.bitboard import BitBoardState, FeatureExtractor

def test_feature_extraction():
    initial_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(initial_fen)
    for i in range(20):
        print board.extract_features()['pieces'][i,:,:]
#     print board.extract_features()['pieces'][1,:,:]

def test_engineered_feature_extraction():
    fens = [
            'rnbqkbnr/pppppppr/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1',
            'rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR w KQkq - 0 1',
            'rnbqk2r/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1',
            'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1',
            '8/5N2/4p2p/5p1k/1p4rP/1P2Q1P1/P4P1K/5q2 w - - 15 44',
            'rnbq1bnr/pppkpppp/2P5/3p4/8/8/PP1PPPPP/RNBQKBNR b KQ - 0 3', 
            'rnbq1bnr/pppkpppp/2P5/3p4/8/8/PP1PPPPP/RNBQKBNR b KQ - 0 3',
            'r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2NQ4/PPPBBPpP/R4RK1 b kq - 1 2',
            '8/8/3p4/1Pp4r/1K3p2/6k1/4P1P1/1R6 w - c6 0 3',
            'r3k2r/1ppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R1Q2R1K b k - 3 3',
            '8/5N2/4p2p/5p1k/1p4rP/1P2Q1P1/P4P1K/5q2 w - - 15 44',
            'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1',
            'rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1',
            'rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2',
            'rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2',
            'R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1',
            '3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1',
            'R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1',
            '3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1',
            ]
    
    extractor = FeatureExtractor()
    features = extractor.engineered_features(fens)
    print features
    
    

if __name__ == '__main__':
    test_engineered_feature_extraction()
    exit()
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])