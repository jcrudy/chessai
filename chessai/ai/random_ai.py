import random
from chessai.ai.base import ChessAI

def random_square():
    f = "abcdefgh"[random.randint(0, 7)]
    r = random.randint(1, 8)
    return "%s%s" % (f, r)

class RandomChessAI(ChessAI):
    def update(self, move):
        pass
    
    def start(self, fen):
        pass
    
    def move(self):
        return "%s-%s" % (random_square(), random_square())
