from chessai.ai.bitboard import LogisticOfficialPlayer, BitBoardState
from chessai.ai.tournament_ai import TournamentAI

def test_player():
    white = LogisticOfficialPlayer(1000000, 3, 3, 1000000)
    
    board = BitBoardState.from_fen('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1')
    print white.movesearch(board, 60000)
    
def test_tournament_ai():
    ai = TournamentAI()
    ai.start('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1')
    print ai.move(10000)
    
if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])