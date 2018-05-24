from chessai.ai.base import ChessAI
from chessai.ai.bitboard import BitBoardState, TimePlayer, Move

class MyAI(ChessAI):
    def __init__(self, tt_size, time_limit):
        self.board = None
        self.tt_size = tt_size
        self.time_limit = time_limit
    
    def update(self, move):
        self.board.make_move(Move.from_long_form(self.board.whites_turn, move))
    
    def start(self, fen):
        self.board = BitBoardState.from_fen(fen)
        self.player = TimePlayer(5000000, 3, 3)
    
    def move(self):
        move = self.player.tmovesearch(self.board, self.time_limit)
        return move.to_long_form()
