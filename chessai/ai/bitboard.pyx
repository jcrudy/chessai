from libc.stdint cimport uint64_t

cdef extern from "bitboardlib.h":
    ctypedef uint64_t bitboard
    cdef bitboard place(bitboard b, int p)
    ctypedef struct boardstate:
        bitboard k
        bitboard q
        bitboard b
        bitboard n
        bitboard r
        bitboard p
        bitboard white
        bitboard black
    cdef boardstate emptyboardstate
        
cdef class BitBoardState:
    cdef boardstate bs
    
    def __cinit__(BitBoardState self, boardstate bs):
        self.bs = bs
    
    @classmethod
    def from_fen(cls, str fen):
        cdef boardstate bs
        bs = fen_to_bitboard(fen)
        return BitBoardState(bs)
    
    

cdef boardstate fen_to_bitboard(str fen):
    cdef boardstate bs = emptyboardstate;
    cdef str pieces, turn, castles, en_passant, halfmove_clock, move_number 
    pieces, turn, castles, en_passant, halfmove_clock, move_number = fen.split(' ')
    
    cdef int pos = 0
    cdef str ch
    for ch in pieces:
        if ch == '/':
            continue
        if ch.isdigit():
            pos += int(ch)
            continue
        if ch.isupper():
            bs.white = place(bs.white, 63 - pos)
        else:
            bs.black = place(bs.black, 63 - pos)
        if ch.lower() == 'k':
            bs.k = place(bs.k, 63 - pos)
        elif ch.lower() == 'q':
            bs.q = place(bs.q, 63 - pos)
        elif ch.lower() == 'b':
            bs.b = place(bs.b, 63 - pos) 
        elif ch.lower() == 'n':
            bs.n = place(bs.n, 63 - pos) 
        elif ch.lower() == 'r':
            bs.r = place(bs.r, 63 - pos) 
        elif ch.lower() == 'p':
            bs.p = place(bs.p, 63 - pos) 
    return bs
            
