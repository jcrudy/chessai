import chess
from chessai.ai.bitboard import TimePlayer, BitBoardState

class TextGame(object):
    def __init__(self, fen, white, black):
        self.board = chess.Board(fen)
        self.white = white
        self.black = black
    
    def play(self):
        while True:
            print(self.board)
            if self.board.is_checkmate():
                if self.board.turn == 1:
                    print('Black wins!')
                else:
                    print('White wins!')
                break
            tries = 100
            while True:
                if self.board.turn == 1:
                    move = self.white.choose_move(self.board)
                else:
                    move = self.black.choose_move(self.board)
                if tries <= 0 or self.board.is_legal(move):
                    break
                print('Selected move %s is illegal. Try again.' % move.uci())
                tries -= 1
            print(move)
            self.board.push(move)

class Player(object):
    def choose_move(self):
        raise NotImplementedError

class HumanPlayer(Player):
    def __init__(self, name):
        self.name = name
        
    def choose_move(self, board):
        while(True):
            try:
                user_input = raw_input('%s to move:' % self.name)
                move = chess.Move.from_uci(user_input.strip())
                break
            except:
                print 'Move "%s" could not be parsed. Try again.' % user_input
        return move


class AIPlayer(Player):
    def __init__(self, name, time_per_move):
        self.name = name
        self.player = TimePlayer(5000000, time_per_move, False)
    
    def choose_move(self, board):
        fen = board.fen()
        bitboard = BitBoardState.from_fen(fen)
        mv = self.player.movesearch(bitboard)
        return chess.Move.from_uci(mv.to_uci())

if __name__ == '__main__':
    game = TextGame('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1', 
                    HumanPlayer('White'),
                    AIPlayer('Black', 6))
    game.play()
        
    