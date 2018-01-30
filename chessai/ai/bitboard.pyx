from libc.stdint cimport uint64_t, uint8_t
from cpython cimport bool

cdef extern from "bitboardlib.h":
    ctypedef uint64_t bitboard
    cdef bitboard place(bitboard b, int p)
    ctypedef uint8_t stateflags
    ctypedef struct boardstate:
        bitboard k
        bitboard q
        bitboard b
        bitboard n
        bitboard r
        bitboard p
        bitboard white
        bitboard black
        uint8_t enpassant
        stateflags flags
        unsigned int halfmove_clock
        unsigned int fullmove_counter
        
    cdef boardstate emptyboardstate
    cdef bool get_white_castle_king(boardstate *bs)
    cdef void set_white_castle_king(boardstate *bs)
    cdef void unset_white_castle_king(boardstate *bs)
    cdef bool get_white_castle_queen(boardstate *bs)
    cdef void set_white_castle_queen(boardstate *bs)
    cdef void unset_white_castle_queen(boardstate *bs)
    cdef bool black_castle_king(boardstate *bs)
    cdef void set_black_castle_king(boardstate *bs)
    cdef void unset_black_castle_king(boardstate *bs)
    cdef bool black_castle_queen(boardstate *bs)
    cdef void set_black_castle_queen(boardstate *bs)
    cdef void unset_black_castle_queen(boardstate *bs)
    cdef bool get_whites_turn(boardstate *bs)
    cdef void set_whites_turn(boardstate *bs)
    cdef void unset_whites_turn(boardstate *bs)
    cdef bool get_blacks_turn(boardstate *bs)
    cdef void set_blacks_turn(boardstate *bs)
    cdef void unset_blacks_turn(boardstate *bs)
    cdef unsigned int get_halfmove_clock(boardstate *bs)
    cdef void set_halfmove_clock(boardstate *bs, unsigned int n)
    cdef unsigned int get_fullmove_counter(boardstate *bs)
    cdef void set_fullmove_counter(boardstate *bs, unsigned int n)
    cdef uint8_t get_enpassant(boardstate *bs)
    cdef void set_enpassant(boardstate *bs, uint8_t pos)

cdef class BitBoardState:
    cdef boardstate *bs
    
    @classmethod
    def from_fen(cls, str fen):
        cdef boardstate *bs
        bs = fen_to_bitboard(fen)
        cdef BitBoardState result = BitBoardState()
        result.bs = bs
        return result
    
#     def to_lol(BitBoardState self):
#         result = [list() for _ in range(8)]
#         cdef bitboard white_kings = (self.bs.k & self.bs.w)
    
#     def render_fen(BitBoardState self):
#         '''
#         Not fast.
#         '''
#         board
        
cpdef int algebraic_to_int(str alg):
    return int(alg[1]) + 8 * (ord(alg[0].lower()) - ord('a'))
    
cdef boardstate *fen_to_bitboard(str fen):
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
            bs.white = place(bs.white, pos)
        else:
            bs.black = place(bs.black, pos)
        if ch.lower() == 'k':
            bs.k = place(bs.k, pos)
        elif ch.lower() == 'q':
            bs.q = place(bs.q, pos)
        elif ch.lower() == 'b':
            bs.b = place(bs.b, pos) 
        elif ch.lower() == 'n':
            bs.n = place(bs.n, pos) 
        elif ch.lower() == 'r':
            bs.r = place(bs.r, pos) 
        elif ch.lower() == 'p':
            bs.p = place(bs.p, pos)
    
    if turn.lower() == 'w':
        set_whites_turn(&bs)
    else:
        set_blacks_turn(&bs)
    
    if 'K' in castles:
        set_white_castle_king(&bs)
    if 'k' in castles:
        set_black_castle_king(&bs)
    if 'Q' in castles:
        set_white_castle_queen(&bs)
    if 'q' in castles:
        set_black_castle_queen(&bs)
    
    if en_passant != '-':
        set_enpassant(&bs, algebraic_to_int(en_passant))
    set_halfmove_clock(&bs, int(halfmove_clock))
    set_fullmove_counter(&bs, int(move_number))
    
    return &bs
            
