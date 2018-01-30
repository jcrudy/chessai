import random

class ChessAI(object):
    def update(self, move):
        raise NotImplementedError()
    
    def start(self, side):
        raise NotImplementedError()
    
    def move(self):
        raise NotImplementedError()