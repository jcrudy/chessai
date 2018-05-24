from chessai.ai.base import ChessAI
from chessai.ai.bitboard import BitBoardState, LogisticOfficialPlayer, Move

class TournamentAI(ChessAI):
    default_fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
    def __init__(self):
        self.player = LogisticOfficialPlayer(5000000, 3, 3, 5000000)
        self.board = BitBoardState.from_fen(self.default_fen)
        self.moves = []
#         self.player.start_ponder(self.board)
    
    def print_diagnostic(self):
#         pass
        print self.board.to_grid()
        print self.board.to_fen()
        print self.moves
#         
    def update(self, move):
        self.player.stop_ponder()
        print '%s moves %s' % ('White' if self.board.whites_turn else 'Black', move)
        move = Move.from_long_form(self.board.whites_turn, move)
        print move
        assert move in self.board.all_moves()
        self.moves.append(move)
        self.board.make_move(move)
        print 'After %s move:' % ('White' if not self.board.whites_turn else 'Black')
        print self.board.to_grid()
        self.player.start_ponder(self.board)
    
    def start(self, fen):
        self.player.stop_ponder()
        self.board = BitBoardState.from_fen(fen)
        self.player.start_ponder(self.board)
    
    def move(self, time_remaining):
        self.player.stop_ponder()
        move, score, depth = self.player.movesearch(self.board, time_remaining)
        long_form_move = move.to_long_form()
        print('Selected %s with score %d at depth %d.' % (long_form_move, score, depth))
        self.player.start_ponder(self.board)
        return long_form_move
