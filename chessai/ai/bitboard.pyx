# distutils: language=c++
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
    cdef bitboard unplace(bitboard b, int p)
    ctypedef enum piece:
        no=0
        K
        Q
        B
        N
        R
        P
        EP
        k
        q
        b
        n
        r
        p
        ep
        
    ctypedef unsigned char brdidx
    
    ctypedef struct boardstate:
        bitboard k
        bitboard q
        bitboard b
        bitboard n
        bitboard r
        bitboard p
        bitboard white
        bitboard black
        brdidx enpassant;
        bool whites_turn;
        bool white_castle_king
        bool white_castle_queen
        bool black_castle_king
        bool black_castle_queen
        unsigned int halfmove_clock
        unsigned int fullmove_counter
        piece piece_map[64]
    
    ctypedef struct move:
        brdidx from_square
        brdidx to_square

    ctypedef struct moverecord:
        piece captured
        bool lost_castle_king
        bool lost_castle_queen
        brdidx from_square
        brdidx to_square
    
    cdef moverecord make_move(boardstate *brd, move *mv);
    cdef const boardstate emptyboardstate
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
    cdef const bitboard places[64]
    cdef const bitboard empty;
    cdef bitboard slide_north(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_south(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_east(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_west(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_northwest(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_northeast(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_southeast(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_southwest(bitboard pieces, bitboard unoccupied)
    cdef bitboard ls1b(bitboard b)
    cdef int greatest_square_index(bitboard b)
    cdef int greatest_rank_index(bitboard b)
    cdef int greatest_file_index(bitboard b)
    cdef int greatest_diag_index(bitboard b)
    cdef int greatest_antidiag_index(bitboard b)
    cdef bitboard bitboard_from_square_index(int i)
    cdef void unplace_piece(boardstate *bs, brdidx square_index)
    cdef void place_piece(boardstate *bs, brdidx square_index, piece pc)
    
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
    def from_square_index(cls, int idx):
        cdef bitboard bb = bitboard_from_square_index(idx)
        cdef BitBoard result = BitBoard()
        result.bb = bb
        return result
        
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
        return cls.from_str(s)
    
    def to_str(self):
        return bitboard_to_str(self.bb)
    
    def to_grid(self):
        return '\n'.join(reversed(map(''.join, partition(8, reversed(self.to_str())))))
    
    cpdef BitBoard ls1b(BitBoard self):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
        result.bb = ls1b(self.bb)
        return result
    
    cpdef BitBoard slide_north(BitBoard self, BitBoard unoccupied):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
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

cdef piece str_to_piece(str s):
    if s == 'K':
        return K
    if s == 'k':
        return k
    if s == 'Q':
        return Q
    if s == 'q':
        return q
    if s == 'B':
        return B
    if s == 'b':
        return b
    if s == 'N':
        return N
    if s == 'n':
        return n
    if s == 'R':
        return R
    if s == 'r':
        return r
    if s == 'P':
        return P
    if s == 'p':
        return p
    if s == 'EP':
        return EP
    if s == 'ep':
        return ep
    if s == 'no':
        return no

cdef str piece_to_str(piece pc):
    cdef str c
    if pc == K:
        c =  'K'
    elif pc == k:
        c = 'k'
    elif pc == Q:
        c = 'Q'
    elif pc == q:
        c = 'q'
    elif pc == B:
        c = 'B'
    elif pc == b:
        c = 'b'
    elif pc == N:
        c = 'N'
    elif pc == n:
        c = 'n'
    elif pc == R:
        c = 'R'
    elif pc == r:
        c = 'r'
    elif pc == P:
        c = 'P'
    elif pc == p:
        c = 'p'
    elif pc == EP:
        c = 'EP'
    elif pc == ep:
        c = 'ep'
    elif pc == no:
        c = 'no'
    return c

cdef class Move:
    cdef move mv
    def __init__(Move self, int from_square, int to_square):
        cdef move mv
        mv.from_square = from_square
        mv.to_square = to_square
        self.mv = mv
    
cdef class MoveRecord:
    cdef moverecord rec
    property from_square:
        def __get__(MoveRecord self):
            return self.rec.from_square
#         
#         def __set__(MoveRecord self, int square_index):
#             self.rec.from_square = square_index
        
    property to_square:
        def __get__(MoveRecord self):  # @DuplicatedSignature
            return self.rec.to_square
        
#         def __set__(MoveRecord self, int square_index):  # @DuplicatedSignature
#             self.rec.to_square = square_index
        
    property captured:
        def __get__(MoveRecord self):  # @DuplicatedSignature
            return piece_to_str(self.rec.captured)
        
    property lost_castle_king:
        def __get__(MoveRecord self):  # @DuplicatedSignature
            if self.rec.lost_castle_king:
                return True
            else:
                return False
    
    property lost_castle_queen:
        def __get__(MoveRecord self):  # @DuplicatedSignature
            if self.rec.lost_castle_queen:
                return True
            else:
                return False
        
cdef class BitBoardState:
    cdef boardstate bs
    
    cpdef place_piece(BitBoardState self, int idx, str pc):
        place_piece(&(self.bs), <brdidx> idx, str_to_piece(pc))
    
    @classmethod
    def from_fen(cls, str fen):
        cdef boardstate bs
        bs = fen_to_bitboard(fen)
        cdef BitBoardState result = BitBoardState()
        result.bs = bs
        return result
    
    cpdef MoveRecord make_move(BitBoardState self, Move mv):
        cdef moverecord rec
        rec = make_move(&(self.bs), &(mv.mv))
        cdef MoveRecord result
        result = MoveRecord()
        result.rec = rec
        return result
    
    cpdef to_grid_redundant(BitBoardState self):
        '''
        Use the redundant piece_map instead of the bitboards.
        '''
        cdef int i
        cdef piece pc
        result = ''
        for i in range(64):
            pc = self.bs.piece_map[i]
            c = piece_to_str(pc)
            if c == 'no':
                c = '-'
            if c.lower() == 'ep':
                c = '*'
            result = result + c
        return '\n'.join(reversed(map(''.join, partition(8, result))))
    
    cpdef str to_grid(BitBoardState self):
        # Get raw positions
        cdef char *arr = <char *>PyMem_Malloc(64 * sizeof(char))
        bitboard_to_arr(&(self.bs), arr)
        raw_positions = str(arr)
        PyMem_Free(arr)
        if self.bs.enpassant != 255:
            ins = '*'
            raw_positions = raw_positions[:(self.bs.enpassant)] + ins + raw_positions[(self.bs.enpassant+1):]
        return '\n'.join(reversed(map(''.join, partition(8, raw_positions))))
    
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
        fen_positions = '/'.join(reversed(rows))
        
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
    
    cpdef int get_enpassant(BitBoardState self):
        cdef int result = self.bs.enpassant
        return result
    
cpdef int algebraic_to_int(str alg):
    return ord(alg[0].lower()) - ord('a') + 8 * (int(alg[1]) - 1)

cpdef str int_to_algebraic(int n):
    return chr(ord('a') + (n % 8)) + str((n / 8) + 1)

cdef str bb_to_grid(bitboard bb):
    r = BitBoard()
    r.bb = bb
    return r.to_grid()

cdef boardstate fen_to_bitboard(str fen):
    cdef boardstate bs = emptyboardstate;
    cdef str pieces, turn, castles, en_passant, halfmove_clock, move_number 
    pieces, turn, castles, en_passant, halfmove_clock, move_number = fen.split(' ')
    
    cdef int pos = 0
    cdef str ch
    ranks = list(reversed(pieces.split('/')))
    for rank in ranks:
        for ch in rank:
            if ch.isdigit():
                pos += int(ch)
            else:
                place_piece(&bs, pos, str_to_piece(ch))
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
        if bs.whites_turn:
            bs.piece_map[algebraic_to_int(en_passant)] = ep
        else:
            bs.piece_map[algebraic_to_int(en_passant)] = EP
    set_halfmove_clock(&bs, int(halfmove_clock))
    set_fullmove_counter(&bs, int(move_number))
    
    return bs
            
