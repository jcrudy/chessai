from libc.stdint cimport uint64_t, uint8_t
from cpython.object cimport Py_EQ
from cpython.mem cimport PyMem_Malloc, PyMem_Realloc, PyMem_Free
from toolz import partition
from operator import methodcaller

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
    cdef bitboard slide_north(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_south(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_east(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_west(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_northwest(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_northeast(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_southeast(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_southwest(bitboard pieces, bitboard unoccupied)
    
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
    
    def __richcmp__(BitBoard self, BitBoard other, int op):
        if op != Py_EQ:
            return NotImplemented()
        if self.bb == other.bb:
            return True
        else:
            return False
    
    @classmethod
    def from_str(cls, str s):
        cdef bitboard bb = empty
        for i, c in enumerate(reversed(s)):
            if c != '0':
                bb = place(bb, i)
        cdef BitBoard result = BitBoard()
        result.bb = bb
        return result
    
    @classmethod
    def from_grid(cls, str g):
        cdef list lines = list(map(methodcaller('strip'), g.strip().split()))
        cdef str s = ''.join(reversed(''.join(reversed(lines))))
                               
#         cdef str s = ''.join(reversed(g.replace('\n', '').replace('\t', '').replace(' ', '')))
        return cls.from_str(s)
    
    def to_str(self):
        return bitboard_to_str(self.bb)
    
    def to_grid(self):
        return '\n'.join(reversed(map(''.join, partition(8, reversed(self.to_str())))))
    
    cpdef BitBoard slide_north(BitBoard self, BitBoard unoccupied):
        cdef BitBoard result = BitBoard()
        result.bb = slide_north(self.bb, unoccupied.bb)
        return result
    
    cpdef BitBoard slide_south(BitBoard self, BitBoard unoccupied):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
        result.bb = slide_south(self.bb, unoccupied.bb)
        return result
    
    cpdef BitBoard slide_east(BitBoard self, BitBoard unoccupied):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
        result.bb = slide_east(self.bb, unoccupied.bb)
        return result
    
    cpdef BitBoard slide_west(BitBoard self, BitBoard unoccupied):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
        result.bb = slide_west(self.bb, unoccupied.bb)
        return result
    
    cpdef BitBoard slide_northeast(BitBoard self, BitBoard unoccupied):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
        result.bb = slide_northeast(self.bb, unoccupied.bb)
        return result
    
    cpdef BitBoard slide_northwest(BitBoard self, BitBoard unoccupied):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
        result.bb = slide_northwest(self.bb, unoccupied.bb)
        return result
    
    cpdef BitBoard slide_southeast(BitBoard self, BitBoard unoccupied):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
        result.bb = slide_southeast(self.bb, unoccupied.bb)
        return result
    
    cpdef BitBoard slide_southwest(BitBoard self, BitBoard unoccupied):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
        result.bb = slide_southwest(self.bb, unoccupied.bb)
        return result
    
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
        return result
    
    cpdef str to_grid(BitBoardState self):
        # Get raw positions
        cdef char *arr = <char *>PyMem_Malloc(64 * sizeof(char))
        bitboard_to_arr(&(self.bs), arr)
        raw_positions = str(arr)
        PyMem_Free(arr)
        return '\n'.join(list(map(''.join, partition(8, raw_positions))))
    
    cpdef str to_fen(BitBoardState self):
        
        # Get raw positions
        cdef char *arr = <char *>PyMem_Malloc(64 * sizeof(char))  # @DuplicatedSignature
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
            
