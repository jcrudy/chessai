from chessai.ai.bitboard import BitBoardState, TimePlayer

def test_bratko_kopec():
    positions = [
                 ('1k1r4/pp1b1R2/3q2pp/4p3/2B5/4Q3/PPP2B2/2K5 b - -', 'Qd1+', 'BK.01')
                 ]
    score = 0
    player = TimePlayer(5000000, 6., False)
    for fen, best_move, q_id in positions:
        board = BitBoardState.from_fen(fen)
        move = player.movesearch(board)
        print(move.to_)
        
    

if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])