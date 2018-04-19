from chessai.ai.base import ChessAI
from chessai.ai.bitboard import BitBoardState, TimePlayer, Move

class MyAI(ChessAI):
    def __init__(self, tt_size, time_limit, use_quiescence):
        self.board = None
        self.tt_size = tt_size
        self.time_limit = time_limit
        self.use_quiescence = use_quiescence
    
    def update(self, move):
        print(move)
        print(Move.from_long_form(self.board.whites_turn, move))
        print(Move.from_long_form(self.board.whites_turn, move).to_long_form())
        self.board.make_move(Move.from_long_form(self.board.whites_turn, move))
    
    def start(self, fen):
        self.board = BitBoardState.from_fen(fen)
        self.player = TimePlayer(self.tt_size, self.time_limit, self.use_quiescence)
    
    def move(self):
        print('A')
        move = self.player.movesearch(self.board)
        print('B')
        return move.to_long_form()
