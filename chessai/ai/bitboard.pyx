from libc.stdint cimport uint64_t, uint8_t

from cpython.mem cimport PyMem_Malloc, PyMem_Realloc, PyMem_Free
from toolz import partition

cdef extern from "stdbool.h":
    ctypedef char bool

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
        uint8_t enpassant;
        bool whites_turn;
        bool white_castle_king
        bool white_castle_queen
        bool black_castle_king
        bool black_castle_queen
        unsigned int halfmove_clock
        unsigned int fullmove_counter
        
    cdef boardstate emptyboardstate
    cdef bool get_white_castle_king(boardstate *bs)
    cdef void set_white_castle_king(boardstate *bs)
    cdef void unset_white_castle_king(boardstate *bs)
    cdef bool get_white_castle_queen(boardstate *bs)
    cdef void set_white_castle_queen(boardstate *bs)
    cdef void unset_white_castle_queen(boardstate *bs)
    cdef bool get_black_castle_king(boardstate *bs)
    cdef void set_black_castle_king(boardstate *bs)
    cdef void unset_black_castle_king(boardstate *bs)
    cdef bool get_black_castle_queen(boardstate *bs)
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
    cdef void bitboard_to_arr(boardstate *bb, char* arr)
    cdef bitboard places[64]
    cdef bitboard empty;
    
cpdef bitboard_to_str(bitboard bb):
    cdef int i
    result = ''
    for i in range(64):
        if bb & places[i]:
            result = '1' + result
        else:
            result = '0' + result
    return result

cdef class BitBoard:
    cdef bitboard bb
    
    @classmethod
    def from_str(cls, str s):
        cdef bitboard bb = empty
        for i, c in enumerate(reversed(s)):
            if c == '1':
                bb = place(bb, i)
            else:
                assert c == '0'
        cdef BitBoard result = BitBoard()
        result.bb = bb
        return result
    
#     @classmethod
#     def from_k(cls, BitBoardState bs):
#         cdef bitboard bb = bs.get_k()
#         cdef BitBoard result = BitBoard()
#         result.bb = bb
#         return result
    
    def to_str(self):
        return bitboard_to_str(self.bb)

def compress_row(row):
    result = ''
    count = 0
    for c in row:
        if c == '-':
            count += 1
        else:
            if count != 0:
                result += str(count)
                count = 0
            result += c
    if count != 0:
        result += str(count)
    return result

 
cdef class BitBoardState:
    cdef boardstate bs
    
    @classmethod
    def from_fen(cls, str fen):
        cdef boardstate bs
        bs = fen_to_bitboard(fen)
        cdef BitBoardState result = BitBoardState()
        result.bs = bs
#         cdef BitBoard bb = BitBoard.from_k(result)
#         print('bs.k =', result.get_k().to_str())
#         print('bs.q =', result.get_q().to_str())
#         print('bs.b =', result.get_b().to_str())
#         print('bs.n =', result.get_n().to_str())
#         print('bs.r =', result.get_r().to_str())
#         print('bs.p =', result.get_p().to_str())
        return result
    
    cpdef str to_fen(BitBoardState self):
        
        # Get raw positions
        cdef char *arr = <char *>PyMem_Malloc(64 * sizeof(char))
        bitboard_to_arr(&(self.bs), arr)
        raw_positions = str(arr)
        PyMem_Free(arr)
        
        # Compress positions into fen format
        rows = list(map(''.join, partition(8, raw_positions)))
        for i in range(len(rows)):
            rows[i] = compress_row(rows[i])
        fen_positions = '/'.join(rows)
        
        # Get turn
        cdef bool whites_turn = get_whites_turn(&(self.bs))
        turn = 'w' if whites_turn else 'b'
        
        # Get castles
        cdef bool white_castle_king = get_white_castle_king(&(self.bs))
        cdef bool white_castle_queen = get_white_castle_queen(&(self.bs))
        cdef bool black_castle_king = get_black_castle_king(&(self.bs))
        cdef bool black_castle_queen = get_black_castle_queen(&(self.bs))
        castles = ''
        castles += 'K' if white_castle_king else ''
        castles += 'Q' if white_castle_queen else ''
        castles += 'k' if black_castle_king else ''
        castles += 'q' if black_castle_queen else ''
        if not castles:
            castles = '-'
        
        # Get en passant
        cdef int en_passant_int = get_enpassant(&(self.bs))
        en_passant = int_to_algebraic(en_passant_int) if en_passant_int != 255 else '-'
        
        # Get clocks and counts
        cdef int halfmove_clock = get_halfmove_clock(&(self.bs))
        cdef int fullmove_count = get_fullmove_counter(&(self.bs))
        
        return ' '.join([fen_positions, turn, castles, en_passant, str(halfmove_clock), str(fullmove_count)])
    
    cpdef BitBoard get_k(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.k
        return result
        
    cpdef BitBoard get_q(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.q
        return result
    
    cpdef BitBoard get_b(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.b
        return result
    
    cpdef BitBoard get_r(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.r
        return result
    
    cpdef BitBoard get_n(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.n
        return result
    
    cpdef BitBoard get_p(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.p
        return result
    
    cpdef BitBoard get_white(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.white
        return result
    
    cpdef BitBoard get_black(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.black
        return result
    
    cpdef int k_to_int(BitBoardState self):
        return <int> self.bs.k
    
    cpdef int q_to_int(BitBoardState self):
        return <int> self.bs.q
    
    cpdef int b_to_int(BitBoardState self):
        return <int> self.bs.b
    
    cpdef int r_to_int(BitBoardState self):
        return <int> self.bs.r
    
    cpdef int n_to_int(BitBoardState self):
        return <int> self.bs.n
    
    cpdef int p_to_int(BitBoardState self):
        return <int> self.bs.p
    
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

cpdef str int_to_algebraic(int n):
    return chr(ord('a') + (n / 8)) + str(n % 8)

cdef boardstate fen_to_bitboard(str fen):
    cdef boardstate bs = emptyboardstate;
    cdef str pieces, turn, castles, en_passant, halfmove_clock, move_number 
    pieces, turn, castles, en_passant, halfmove_clock, move_number = fen.split(' ')
    
    cdef int pos = 0
    cdef str ch
#     print('for ch in pieces:')
    for ch in pieces:
#         print(ch)
#         print('pos =', pos)
        if ch == '/':
#             print('found /')
            continue
        if ch.isdigit():
#             print('found digit')
            pos += int(ch)
            continue
        if ch.isupper():
#             print('found white')
            bs.white = place(bs.white, 63 - pos)
        else:
#             print('found black')
            bs.black = place(bs.black, 63 - pos)
        if ch.lower() == 'k':
#             print('found king')
            bs.k = place(bs.k, 63 - pos)
        elif ch.lower() == 'q':
#             print('found queen')
            bs.q = place(bs.q, 63 - pos)
        elif ch.lower() == 'b':
#             print('found bishop')
            bs.b = place(bs.b, 63 - pos) 
        elif ch.lower() == 'n':
#             print('found knight')
            bs.n = place(bs.n, 63 - pos) 
        elif ch.lower() == 'r':
#             print('found rook')
            bs.r = place(bs.r, 63 - pos) 
        elif ch.lower() == 'p':
#             print('found pawn')
            bs.p = place(bs.p, 63 - pos)
        pos += 1
    
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
    
    return bs
            
