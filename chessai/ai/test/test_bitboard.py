from chessai.ai.bitboard import BitBoardState, BitBoard, Move, MoveRecord,\
    int_to_algebraic, algebraic_to_int
from nose.tools import assert_equal, assert_list_equal
import random
import chess

def chess_move_to_black_move(chess_move):
    promotion_dict = {5: 'q', 4:'r', 3:'b', 2:'n'}
    mv = Move(chess_move.from_square, chess_move.to_square, 
              promotion_dict[chess_move.promotion] if chess_move.promotion else 'no')
    return mv

def chess_move_to_white_move(chess_move):
    promotion_dict = {5: 'Q', 4:'R', 3:'B', 2:'N'}
    mv = Move(chess_move.from_square, chess_move.to_square, 
              promotion_dict[chess_move.promotion] if chess_move.promotion else 'no')
    return mv

def all_moves_from_chess_package(fen):
    board = chess.Board(fen)
    moves = board.legal_moves
    if board.turn:
        return list(map(chess_move_to_white_move, moves))
    else:
        return list(map(chess_move_to_black_move, moves))

def test_boardstate_to_grid():
    starting_fen = 'rnbqkbnr/pppppppr/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(starting_fen)
    expected_grid = '''
                    rnbqkbnr
                    pppppppr
                    --------
                    --------
                    --------
                    --------
                    PPPPPPPP
                    RNBQKBNR
                    '''.replace(' ','').strip()
    assert_equal(board.to_grid(), expected_grid)

def test_places():
    expected = BitBoard.from_grid('''
               00000000
               00000000
               00000000
               00000000
               00000000
               00000000
               00000000
               10000000
               ''').to_grid()
    got = BitBoard.from_square_index(0).to_grid()
    assert_equal(expected, got)

    expected = BitBoard.from_grid('''
               00000000
               00000000
               00000000
               00000000
               00000000
               00000000
               00000000
               01000000
               ''').to_grid()
    got = BitBoard.from_square_index(1).to_grid()
    assert_equal(expected, got)

    expected = BitBoard.from_grid('''
               00000000
               00000000
               00000000
               00000000
               00000000
               00000000
               10000000
               00000000
               ''').to_grid()
    got = BitBoard.from_square_index(8).to_grid()
    assert_equal(expected, got)

    expected = BitBoard.from_grid('''
               00000000
               00000000
               00000000
               00000000
               00000000
               00000000
               00001000
               00000000
               ''').to_grid()
    got = BitBoard.from_square_index(12).to_grid()
    assert_equal(expected, got)

    expected = BitBoard.from_grid('''
               00000000
               00000000
               00000000
               00000000
               00000000
               00001000
               00000000
               00000000
               ''').to_grid()
    got = BitBoard.from_square_index(20).to_grid()
    assert_equal(expected, got)

def test_algebraic():
    correct = {
               0: 'a1',
               1: 'b1',
               2: 'c1',
               3: 'd1',
               4: 'e1',
               5: 'f1',
               6: 'g1',
               7: 'h1',
               8: 'a2',
               9: 'b2',
               10: 'c2',
               11: 'd2',
               12: 'e2',
               13: 'f2',
               14: 'g2',
               15: 'h2',
               16: 'a3',
               17: 'b3',
               18: 'c3',
               19: 'd3',
               20: 'e3',
               21: 'f3',
               22: 'g3',
               23: 'h3',
               }
    for ind, alg in correct.items():
        assert_equal(int_to_algebraic(ind), alg)
        assert_equal(ind, algebraic_to_int(alg))

def test_promotion():
    fen = '4k3/P7/8/8/8/8/8/8 w - - 0 100'
    board = BitBoardState.from_fen(fen)
    move = Move(48, 56, 'Q')
    record = board.make_move(move)
    assert_equal(record.promoted_from, 'P')
    assert_equal(board.to_fen(), 'Q3k3/8/8/8/8/8/8/8 b - - 0 100')
    board.unmake_move(record)
    assert_equal(board.to_fen(), fen)

def test_queen_captures():
    fen = 'rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).queen_captures())
    assert_equal(moves, set())
    
    fen = 'rnbqkbnr/pppppppp/8/8/8/3p4/PPP1PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).queen_captures())
    assert_equal(moves, {Move(3, 19)})

    fen = 'rnbqkbnr/pppppppp/8/8/8/1pPP4/PP2PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).queen_captures())
    assert_equal(moves, {Move(3, 17)})
    
    # Make sure a pinned queen doesn't move out of the pin ray
    fen = 'rnb1kbnr/4q3/8/8/8/8/PPPPRPPP/RNBQKBNR b KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).queen_captures())
    assert_equal(moves, {Move(52, 52-40)})

def test_all_queen_moves():
    fen = 'rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).all_queen_moves())
    assert_equal(moves, {Move(3, 11)})
    
    fen = 'rnbqkbnr/pppppppp/8/8/8/3p4/PPP1PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).all_queen_moves())
    assert_equal(moves, {Move(3, 11), Move(3, 19)})

    fen = 'rnbqkbnr/pppppppp/8/8/8/1pPP4/PP2PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).all_queen_moves())
    assert_equal(moves, {Move(3, 11), Move(3, 10), Move(3, 17)})
                 
    # Make sure a pinned queen doesn't move out of the pin ray
    fen = 'rnb1kbnr/4q3/8/8/8/8/PPPPRPPP/RNBQKBNR b KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).all_queen_moves())
    assert_equal(moves, {Move(52, 52-8), Move(52, 52-16), Move(52, 52-24),
                         Move(52, 52-32), Move(52, 52-40)})

def test_all_moves():
    fen = 'rnbqkbnr/pppppppr/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    moves = BitBoardState.from_fen(fen).all_moves()
    expected_moves = all_moves_from_chess_package(fen)
    assert_equal(set(moves), set(expected_moves))

def test_quiet_queen_moves():
    fen = 'rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).quiet_queen_moves())
    assert_equal(moves, {Move(3, 11)})
     
    fen = 'rnbqkbnr/pppppppp/8/8/8/2PP4/PP2PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).quiet_queen_moves())
    assert_equal(moves, {Move(3, 11), Move(3, 10), Move(3, 17), Move(3, 24)})
     
    fen = 'rnbqkbnr/pppppppp/8/8/8/1pPP4/PP2PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).quiet_queen_moves())
    assert_equal(moves, {Move(3, 11), Move(3, 10)})
     
    fen = 'rnbqkbnQ/ppppppp1/8/8/8/1pPP4/PP2PPPP/RNBQKBNR w KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).quiet_queen_moves())
    assert_equal(moves, {Move(3, 11), Move(3, 10), Move(63, 63-8), Move(63, 63-16),
                         Move(63, 63-24), Move(63, 63-32), Move(63, 63-40)})
     
    fen = 'rnbqkbnr/ppp1pppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR b KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).quiet_queen_moves())
    assert_equal(moves, {Move(59, 59-8), Move(59, 59-16), Move(59, 59-24), 
                         Move(59, 59-32)})
    
    # Make sure a pinned queen doesn't move out of the pin ray
    fen = 'rnb1kbnr/4q3/8/8/8/8/PPPPRPPP/RNBQKBNR b KQkq - 0 1'
    moves = set(BitBoardState.from_fen(fen).quiet_queen_moves())
    assert_equal(moves, {Move(52, 52-8), Move(52, 52-16), Move(52, 52-24),
                         Move(52, 52-32)})
    
    
def test_make_move():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'

    # Try moving king's pawn one space
    board = BitBoardState.from_fen(starting_fen)
    record = board.make_move(Move(12, 20))
    assert_equal(board.to_fen(), 'rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1')
    board.unmake_move(record)
    assert_equal(board.to_fen(), starting_fen) 
    
    
    # Try moving king's pawn two spaces, thus invoking en passant
    board = BitBoardState.from_fen(starting_fen)
    record = board.make_move(Move(12, 28))
    assert_equal(board.get_enpassant(), 20)
    assert_equal(board.to_fen(), 'rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1')
    board.unmake_move(record)
    assert_equal(board.to_fen(), starting_fen) 
    
    # Attempt an en passant capture
    record_stack = []
    fen_stack = [starting_fen]
    board = BitBoardState.from_fen(starting_fen)
    move = Move(12, 28)
    record = board.make_move(move)
    record_stack.append(record)
    assert_equal(record.from_square, move.from_square)
    assert_equal(record.to_square, move.to_square)
    fen_stack.append(board.to_fen())
    assert_equal(
                 '''
                 rnbqkbnr
                 pppppppp
                 --------
                 --------
                 ----P---
                 ----*---
                 PPPP-PPP
                 RNBQKBNR
                 '''.replace(' ','').strip(),
                 board.to_grid()
                 )
    move = Move(48, 40)
    record = board.make_move(move)
    record_stack.append(record)
    assert_equal(record.from_square, move.from_square)
    assert_equal(record.to_square, move.to_square)
    fen_stack.append(board.to_fen())
    assert_equal(
                 '''
                 rnbqkbnr
                 -ppppppp
                 p-------
                 --------
                 ----P---
                 --------
                 PPPP-PPP
                 RNBQKBNR
                 '''.replace(' ','').strip(),
                 board.to_grid()
                 )
    move = Move(28, 36)
    record = board.make_move(move)
    record_stack.append(record)
    assert_equal(record.from_square, move.from_square)
    assert_equal(record.to_square, move.to_square)
    fen_stack.append(board.to_fen())
    assert_equal(
                 '''
                 rnbqkbnr
                 -ppppppp
                 p-------
                 ----P---
                 --------
                 --------
                 PPPP-PPP
                 RNBQKBNR
                 '''.replace(' ','').strip(),
                 board.to_grid()
                 )
    move = Move(51, 35)
    record = board.make_move(move)
    record_stack.append(record)
    assert_equal(record.from_square, move.from_square)
    assert_equal(record.to_square, move.to_square)
    fen_stack.append(board.to_fen())
    assert_equal(
                 '''
                 rnbqkbnr
                 -pp-pppp
                 p--*----
                 ---pP---
                 --------
                 --------
                 PPPP-PPP
                 RNBQKBNR
                 '''.replace(' ','').strip(),
                 board.to_grid()
                 )
    assert_equal(board.get_enpassant(), 43)
    move = Move(36, 43)
    record = board.make_move(move)
    record_stack.append(record)
    assert_equal(record.from_square, move.from_square)
    assert_equal(record.to_square, move.to_square)
    fen_stack.append(board.to_fen())
    assert_equal(
                 '''
                 rnbqkbnr
                 -pp-pppp
                 p--P----
                 --------
                 --------
                 --------
                 PPPP-PPP
                 RNBQKBNR
                 '''.replace(' ','').strip(),
                 board.to_grid()
                 )
    record_stack.append(board.make_move(Move(52, 36)))
    fen_stack.append(board.to_fen())
    assert_equal(
                 '''
                 rnbqkbnr
                 -pp--ppp
                 p--P*---
                 ----p---
                 --------
                 --------
                 PPPP-PPP
                 RNBQKBNR
                 '''.replace(' ','').strip(),
                 board.to_grid()
                 )
    fen = fen_stack.pop(-1)
    assert_equal(fen, board.to_fen())
    while record_stack:
        record = record_stack.pop(-1)
        board.unmake_move(record)
        fen = fen_stack.pop(-1)
        assert_equal(fen, board.to_fen())
    assert_equal(board.to_fen(), starting_fen) 
        
    # Try white castle king side
    board = BitBoardState.from_fen('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQK2R w KQkq - 0 1')
    record = board.make_move(Move(4, 6))
    assert_equal(board.to_fen(), 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQ1RK1 b kq - 1 1')
    board.unmake_move(record)
    assert_equal(board.to_fen(), 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQK2R w KQkq - 0 1')
    
    # Try white castle queen side
    board = BitBoardState.from_fen('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R3KBNR w KQkq - 0 1')
    record = board.make_move(Move(4, 2))
    assert_equal(board.to_fen(), 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/2KR1BNR b kq - 1 1')
    board.unmake_move(record)
    assert_equal(board.to_fen(), 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R3KBNR w KQkq - 0 1')
    
    # Try black castle king side
    board = BitBoardState.from_fen('rnbqk2r/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1')
    record = board.make_move(Move(60, 62))
    assert_equal(board.to_fen(), 'rnbq1rk1/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQ - 1 2')
    board.unmake_move(record)
    assert_equal(board.to_fen(), 'rnbqk2r/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1')
    
    # Try black castle queen side
    board = BitBoardState.from_fen('r3kbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1')
    record = board.make_move(Move(60, 58))
    assert_equal(board.to_fen(), '2kr1bnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQ - 1 2')
    board.unmake_move(record)
    assert_equal(board.to_fen(), 'r3kbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1')
    
    
def test_place_piece():
    fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    bb = BitBoardState.from_fen(fen)
    bb.place_piece(0, 'p')
    new_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/pNBQKBNR w KQkq - 0 1'
    assert_equal(bb.to_fen(), new_fen)

def test_from_fen():
    fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    bb = BitBoardState.from_fen(fen)
    assert_equal(bb.get_k().to_str(), '0001000000000000000000000000000000000000000000000000000000010000')
    assert_equal(bb.get_q().to_str(), '0000100000000000000000000000000000000000000000000000000000001000')
    assert_equal(bb.get_b().to_str(), '0010010000000000000000000000000000000000000000000000000000100100')
    assert_equal(bb.get_n().to_str(), '0100001000000000000000000000000000000000000000000000000001000010')
    assert_equal(bb.get_r().to_str(), '1000000100000000000000000000000000000000000000000000000010000001')
    assert_equal(bb.get_p().to_str(), '0000000011111111000000000000000000000000000000001111111100000000')
    assert_equal(bb.get_white().to_str(), '0000000000000000000000000000000000000000000000001111111111111111')
    assert_equal(bb.get_black().to_str(), '1111111111111111000000000000000000000000000000000000000000000000')

def test_to_grid():
    fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    grid = '''
           rnbqkbnr
           pppppppp
           --------
           --------
           --------
           --------
           PPPPPPPP
           RNBQKBNR
           '''.strip().replace(' ', '')
    bb = BitBoardState.from_fen(fen)
    assert_equal(bb.to_grid(), grid)
    
    fen = '8/5N2/4p2p/5p1k/1p4rP/1P2Q1P1/P4P1K/5q2 w - - 15 44'
    grid = '''
           --------
           -----N--
           ----p--p
           -----p-k
           -p----rP
           -P--Q-P-
           P----P-K
           -----q--
           '''.strip().replace(' ', '')
    bb = BitBoardState.from_fen(fen)
    assert_equal(bb.to_grid(), grid)
    
    fen = 'rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1'
    grid = '''
           rnbqkbnr
           pppppppp
           --------
           --------
           ----P---
           ----*---
           PPPP-PPP
           RNBQKBNR
           '''.strip().replace(' ', '')
    bb = BitBoardState.from_fen(fen)
    assert_equal(bb.to_grid(), grid)
    
    fen = 'rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2'
    grid = '''
           rnbqkbnr
           pp-ppppp
           --*-----
           --p-----
           ----P---
           --------
           PPPP-PPP
           RNBQKBNR
           '''.strip().replace(' ', '')
    bb = BitBoardState.from_fen(fen)
    assert_equal(bb.to_grid(), grid)
    
    fen = 'rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2'
    grid = '''
           rnbqkbnr
           pp-ppppp
           --------
           --p-----
           ----P---
           -----N--
           PPPP-PPP
           RNBQKB-R
           '''.strip().replace(' ', '')
    bb = BitBoardState.from_fen(fen)
    assert_equal(bb.to_grid(), grid)
    
    fen = 'R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1'
    grid = '''
           R------R
           ---Q----
           -Q----Q-
           ----Q---
           --Q----Q
           Q----Q--
           pp-Q----
           kBNN-KB-
           '''.strip().replace(' ', '')
    bb = BitBoardState.from_fen(fen)
    assert_equal(bb.to_grid(), grid)
    
    fen = '3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1'
    grid = '''
           ---Q----
           -Q----Q-
           ----Q---
           --Q----R
           Q----Q--
           ---Q----
           -Q----Rp
           -K-BBNNk
           '''.strip().replace(' ', '')
    bb = BitBoardState.from_fen(fen)
    assert_equal(bb.to_grid(), grid)

def test_negamax():
    starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    board = BitBoardState.from_fen(starting_fen)
    for _ in range(10):
        move = board.negamax(4)
        board.make_move(move)
        
        

def test_perft():
#     starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
#     def compute_perft(n):
#         return BitBoardState.from_fen(starting_fen).perft(n)
#      
#     perft_result = list(map(compute_perft, range(7)))
#     expected = [1,20,400,8902,197281,4865609,119060324]
#     assert_list_equal(perft_result, expected)
    # https://www.chessprogramming.net/perfect-perft/
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

def compare_to_python(fen, depth):
    board = BitBoardState.from_fen(fen)
    pyboard = chess.Board(fen)
    def _compare_to_python(board, pyboard, depth):
        fen = board.to_fen()
        moves = board.all_moves()
        pymoves_ = list(pyboard.legal_moves)
        if pyboard.turn:
            pymoves = list(map(chess_move_to_white_move, pymoves_))
        else:
            pymoves = list(map(chess_move_to_black_move, pymoves_))
        assert_equal(set(moves), set(pymoves))
        order = list(map(pymoves.index, moves))
        if depth <= 1:
            return
        for i, move in enumerate(moves):
            record = board.make_move(move)
            pyboard.push(pymoves_[order[i]])
            try:
                _compare_to_python(board, pyboard, depth-1)
            except AssertionError:
                print('depth = %d' % depth)
                print(board.to_fen())
                print(board.to_grid())
                print(pyboard.fen())
                print(pyboard)
                print(move)
                print(pymoves_[order[i]])
                print(i)
                record = board.unmake_move(record)
                pyboard.pop()
                raise
            board.unmake_move(record)
            pyboard.pop()
            assert_equal(board.to_fen(), fen)
    _compare_to_python(board, pyboard, depth)

def confirm_moves(fen, depth):
    moves = BitBoardState.from_fen(fen).all_moves()
    random.shuffle(moves)
    expected_moves = all_moves_from_chess_package(fen)
    try:
        assert_equal(set(moves), set(expected_moves))
    except AssertionError:
        print(fen)
        print(BitBoardState.from_fen(fen).to_grid())
        raise
    if depth <= 1:
        return len(moves)
    total = 0
    for move in moves:
        board = BitBoardState.from_fen(fen)
        record = board.make_move(move)
        total += confirm_moves(board.to_fen(), depth-1)
        board.unmake_move(record)
        try:
            assert_equal(board, BitBoardState.from_fen(fen))
        except AssertionError:
            print(board.to_fen())
            print(board.to_grid())
            print(BitBoardState.from_fen(fen).to_grid())
            raise
    return total

def test_move_tree_depth_6():
    fen = 'r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1'
    compare_to_python(fen, 6)

def test_a_position():
    fen = 'rnbq1bnr/pppkpppp/2P5/3p4/8/8/PP1PPPPP/RNBQKBNR b KQ - 0 3'
    fen = 'r3k2r/p1ppqp2/bn2pnpb/3PN3/1p2P3/2N2Q1p/PPP1BPPP/R3K2R w KQkq - 0 2'
    fen = 'r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2NQ4/PPPBBPpP/R4RK1 b kq - 1 2'
    fen = '8/8/3p4/1Pp4r/1K3p2/6k1/4P1P1/1R6 w - c6 0 3'
    fen = 'r3k2r/1ppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R1Q2R1K b k - 3 3'
    board = BitBoardState.from_fen(fen)
    moves = board.all_moves()
    expected_moves = all_moves_from_chess_package(fen)
    try:
        assert_equal(set(moves), set(expected_moves))
    except AssertionError:
        print(board.to_grid())
        raise
    
# def test_move_tree_depth_3():
#     starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
#     compare_to_python(starting_fen, 3)

# def test_move_tree_depth_4():
#     starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
#     compare_to_python(starting_fen, 4)
    
def test_white_castling():
    fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1'
    moves = BitBoardState.from_fen(fen).all_moves()
    expected_moves = all_moves_from_chess_package(fen)
    assert_equal(set(moves), set(expected_moves))
    
def test_black_castling():
    fen = 'r3k2r/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1'
    moves = BitBoardState.from_fen(fen).all_moves()
    expected_moves = all_moves_from_chess_package(fen)
    assert_equal(set(moves), set(expected_moves))
# 
# def test_move_tree_depth_5():
#     starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
#     confirm_moves(starting_fen, 5)
# #     
# def test_move_tree_depth_6():
#     starting_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
#     confirm_moves(starting_fen, 6)
    
def test_move_generation():
    # The following two positions should have 218 moves each.
    # See https://chessprogramming.wikispaces.com/Encoding+Moves
    positions_218 = [
                     'R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1',
                     '3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1',
                     ]
    for fen in positions_218:
        moves = BitBoardState.from_fen(fen).all_moves()
        expected_moves = all_moves_from_chess_package(fen)
        assert_equal(set(moves), set(expected_moves))
        assert_equal(len(moves), 218)

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

def test_step_north():
    pieces = BitBoard.from_grid('''
             00000000
             00000000
             00000000
             00000000
             00000000
             00100000
             00000000
             00000001
             ''')

    expected = BitBoard.from_grid('''
               00000000
               00000000
               00000000
               00000000
               00100000
               00000000
               00000001
               00000000
               ''')
    assert_equal(pieces.step_north(), expected)
    pieces = BitBoard.from_grid('''
             00010000
             00000000
             00000000
             00000000
             00000000
             00000000
             00000000
             00000000
             ''')

    expected = BitBoard.from_grid('''
               00000000
               00000000
               00000000
               00000000
               00000000
               00000000
               00000000
               00000000
               ''')
    assert_equal(pieces.step_north(), expected)


if __name__ == '__main__':
#     test_move_tree_depth_6()
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
