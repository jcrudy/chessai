from chessai.ai.base import ChessAI
from operator import __and__, __or__
from itertools import starmap

K = 'K'
Q = 'Q'
R = 'R'
P = 'P'
N = 'N'
B = 'B'

class BitBoard(object):
    def __init__(self):
        self.board = [False] * 64
    
    @classmethod
    def from_arr(cls, arr):
        result = BitBoard()
        result.board = arr
        return result
    
    def __getitem__(self, key):
        return self.board[key]
    
    def __setitem__(self, key, value):
        self.board[key] = bool(value)
    
    def __and__(self, other):
        return BitBoard.from_arr(list(starmap(__and__, zip(self.board, other.board))))
    
    def __or__(self, other):
        return BitBoard.from_arr(list(starmap(__or__, zip(self.board, other.board))))

class BoardState(object):
    '''
    This is a highly inefficient version of a bitboard
    '''
    def __init__(self):
        self.my_pieces = {
                         K: BitBoard(),
                         Q: BitBoard(),
                         B: BitBoard(),
                         R: BitBoard(),
                         K: BitBoard(),
                         P: BitBoard(),
                         }
        self.their_pieces = {
                             K: BitBoard(),
                             Q: BitBoard(),
                             B: BitBoard(),
                             R: BitBoard(),
                             K: BitBoard(),
                             P: BitBoard(),
                             }
        


class PythonMinimaxAI(ChessAI):
    pass