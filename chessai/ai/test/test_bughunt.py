from chessai.ai.bitboard import BitBoardState, Move, LogisticOfficialPlayer, LogisticPlayer
from nose.tools import assert_in, assert_not_equal

def test_checkmate_preference_bug():
    board = BitBoardState.from_fen('8/6p1/2p2b2/7p/6p1/4K3/k6r/1q6 b - - 13 50')
    player = LogisticPlayer(5000000, 3, 3)
    for i in range(8):
        print player.alphabeta(board, i)
    

def test_for_bug():
    board = BitBoardState.from_fen('rnbqkbnr/pppppppr/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1')
    moves = [
                Move(12, 28, "no"),
                Move(52, 36, "no"),
                Move(6, 21, "no"),
                Move(57, 42, "no"),
                Move(1, 18, "no"),
                Move(62, 45, "no"),
                Move(3, 12, "no"),
                Move(51, 43, "no"),
                Move(18, 35, "no"),
                Move(58, 44, "no"),
                Move(35, 45, "no"),
                Move(59, 45, "no"),
                Move(12, 33, "no"),
                Move(60, 58, "no"),
                Move(5, 19, "no"),
                Move(43, 35, "no"),
                Move(15, 31, "no"),
                Move(58, 57, "no"),
                Move(33, 24, "no"),
                Move(42, 25, "no"),
                Move(4, 12, "no"),
                Move(44, 30, "no"),
                Move(24, 17, "no"),
                Move(45, 29, "no"),
                Move(28, 35, "no"),
                Move(61, 34, "no"),
                Move(19, 26, "no"),
                Move(36, 28, "no"),
                Move(11, 27, "no"),
                Move(28, 21, "no"),
                Move(14, 21, "no"),
                Move(29, 27, "no"),
                Move(2, 20, "no"),
                Move(27, 28, "no"),
                Move(21, 30, "no"),
                Move(25, 10, "no"),
                Move(12, 11, "no"),
                Move(34, 25, "no"),
                Move(11, 3, "no"),
                Move(10, 20, "no"),
                Move(13, 20, "no"),
                Move(28, 7, "no"),
                Move(3, 12, "no"),
                Move(7, 0, "no"),
                Move(17, 25, "no"),
                Move(0, 7, "no"),
                Move(25, 52, "no"),
                Move(7, 14, "no"),
                Move(12, 19, "no"),
                Move(14, 30, "no"),
                Move(19, 18, "no"),
                Move(53, 45, "no"),
                Move(8, 16, "no"),
                Move(30, 31, "no"),
                Move(52, 54, "no"),
                Move(63, 60, "no"),
                Move(54, 6, "no"),
                Move(31, 47, "no"),
                Move(18, 19, "no"),
                Move(45, 37, "no"),
                Move(9, 25, "no"),
                Move(60, 28, "no"),
                Move(16, 24, "no"),
                Move(48, 32, "no"),
                Move(25, 32, "no"),
                Move(47, 42, "no"),
                Move(26, 17, "no"),
                Move(42, 24, "no"),
                Move(17, 24, "no"),
                Move(28, 24, "no"),
                Move(19, 11, "no"),
                Move(24, 32, "no"),
                Move(11, 18, "no"),
                Move(57, 56, "no"),
                Move(6, 54, "no"),
                Move(32, 34, "no"),
                Move(18, 17, "no"),
                Move(55, 39, "no"),
                Move(17, 25, "no"),
                Move(59, 35, "no"),
                Move(54, 63, "no"),
                Move(56, 48, "no"),
                Move(63, 39, "no"),
                Move(34, 42, "no"),
                Move(39, 7, "no"),
                Move(42, 43, "no"),
                Move(7, 0, "no"),
                Move(43, 40, "no"),
                Move(0, 54, "no"),
                Move(40, 41, "no"),
                Move(25, 26, "no"),
                Move(35, 19, "no"),
                Move(26, 19, "no"),
                Move(41, 43, "no"),
                Move(19, 12, "no"),
                Move(43, 42, "no"),
                Move(54, 36, "no"),
                Move(48, 41, "no"),
                Move(36, 37, "no"),
                Move(42, 43, "no"),
                Move(37, 29, "no"),
                Move(43, 35, "no"),
                Move(29, 25, "no"),
                Move(41, 42, "no"),
                Move(25, 26, "no"),
                Move(42, 43, "no"),
                Move(26, 29, "no"),
                Move(43, 42, "no"),
                Move(29, 21, "no"),
                Move(42, 43, "no"),
                Move(21, 45, "no"),
                Move(43, 51, "no"),
                Move(20, 28, "no"),
                Move(35, 32, "no"),
                Move(12, 3, "no"),
                Move(51, 58, "no"),
                Move(28, 36, "no"),
                Move(32, 36, "no"),
                Move(45, 36, "no"),
                Move(49, 41, "no"),
                Move(36, 35, "no"),
                Move(58, 57, "no"),
                Move(3, 10, "no"),
                Move(57, 58, "no"),
                Move(10, 17, "no"),
                Move(58, 57, "no"),
                Move(17, 24, "no"),
                Move(57, 58, "no"),
                Move(24, 33, "no"),
                Move(58, 57, "no"),
                Move(35, 42, "no"),
                Move(57, 48, "no"),
                Move(42, 50, "no"),
                Move(48, 56, "no"),
                Move(33, 24, "no"),
                Move(41, 33, "no"),
                Move(24, 16, "no"),
                Move(33, 25, "no"),
                Move(16, 8, "no"),
                Move(25, 17, "no"),
                Move(8, 1, "no"),
                Move(17, 9, "no"),
                Move(50, 10, "no"),
                Move(56, 48, "no"),
                Move(10, 34, "no"),
            ]
    more_moves = [
                Move(48, 40, "no"),
                Move(1, 8, "no"),
                Move(40, 49, "no"),
                Move(8, 9, "no"),
                Move(49, 40, "no"),
                Move(34, 36, "no"),
                Move(40, 41, "no"),
                Move(9, 0, "no"),
                Move(41, 40, "no"),
                Move(0, 1, "no"),
                Move(40, 41, "no"),
                Move(36, 27, "no"),
                Move(41, 32, "no"),
#                 Move(1, 0, "no"),
#                 Move(32, 33, "no"),
#                 Move(0, 1, "no"),
#                 Move(33, 32, "no"),
#                 Move(1, 2, "no"),
#                 Move(32, 33, "no"),
#                 Move(2, 1, "no"),
#                 Move(33, 32, "no")
            ]
    player = LogisticOfficialPlayer(5000000, 3, 3, 5000000)
    print(board.to_grid())
    for move in moves:
        assert_in(move, board.all_moves())
        print(player.movesearch(board, 600000))
        board.make_move(move)
        print(board.to_grid())
    for move in more_moves:
        assert_in(move, board.all_moves())
        print(player.movesearch(board, 10000))
        board.make_move(move)
        print(board.to_grid())
    
    mv, _, _ = player.movesearch(board, 10000)
    assert_not_equal(mv, Move(1, 0, "no"))
    
    
    1+1

if __name__ == '__main__':
    test_checkmate_preference_bug()
    exit()
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])