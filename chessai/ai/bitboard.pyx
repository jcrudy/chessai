# distutils: language=c++
from libc.stdint cimport uint64_t, uint8_t
from cpython.object cimport Py_EQ
from cpython.mem cimport PyMem_Malloc, PyMem_Realloc, PyMem_Free
from toolz import partition
from operator import methodcaller
from libcpp.queue cimport queue
import time

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
        piece promotion

    ctypedef struct moverecord:
        piece captured
        bool lost_own_castle_king
        bool lost_own_castle_queen
        bool lost_opponent_castle_king
        bool lost_opponent_castle_queen
        brdidx enpassant
        int previous_halfmove_clock
        brdidx from_square
        brdidx to_square
        piece promoted_from

    cdef moverecord make_move(boardstate *brd, move *mv);
    cdef void unmake_move(boardstate *brd, moverecord *mv);
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
    cdef const bitboard places[64]
    cdef const bitboard empty;
    cdef bitboard slide_north(bitboard pieces, bitboard unoccupied)
#     cdef bitboard slide_capture_north(bitboard pieces, bitboard own, bitboard opponent)
    cdef bitboard slide_south(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_east(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_west(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_northwest(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_northeast(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_southeast(bitboard pieces, bitboard unoccupied)
    cdef bitboard slide_southwest(bitboard pieces, bitboard unoccupied)
    cdef bitboard step_north(bitboard bb)
    cdef bitboard ls1b(bitboard b)
    cdef int greatest_square_index(bitboard b)
    cdef int greatest_rank_index(bitboard b)
    cdef int greatest_file_index(bitboard b)
    cdef int greatest_diag_index(bitboard b)
    cdef int greatest_antidiag_index(bitboard b)
    cdef bitboard bitboard_from_square_index(int i)
    cdef piece unplace_piece(boardstate *bs, brdidx square_index)
    cdef void place_piece(boardstate *bs, brdidx square_index, piece pc)
    cdef void quiet_queen_moves(boardstate *brd, queue[move] &moves)
    cdef void all_queen_moves(boardstate *brd, queue[move] &moves)
    cdef void queen_captures(boardstate *brd, queue[move] &moves)
    cdef void all_moves(boardstate *brd, queue[move] &moves)
    cdef void all_captures(boardstate *brd, queue[move] &moves)
    cdef unsigned long long perft(boardstate *brd, int depth)
    ctypedef struct movechoice:
        move mv
        double score
    cdef move movesearch(boardstate *brd, double time_limit, int *depth)
    cdef move movesearch_threshold(boardstate *brd, double threshold)

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
    
#     cpdef BitBoard slide_capture_north(BitBoard self, BitBoard own, BitBoard opponent):
#         cdef BitBoard result = BitBoard()  # @DuplicatedSignature
#         result.bb = slide_capture_north(self.bb, own.bb, opponent.bb)
#         return result

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

    cpdef BitBoard step_north(BitBoard self):
        cdef BitBoard result = BitBoard()  # @DuplicatedSignature
        result.bb = step_north(self.bb)
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
    cdef str c = 'error'
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
    cdef public move mv
    def __init__(Move self, int from_square=0, int to_square=0, str promotion='no'):
        cdef move mv
        mv.from_square = from_square
        mv.to_square = to_square
        mv.promotion = str_to_piece(promotion)
        self.mv = mv
        
    def __richcmp__(Move self, other, op):
        if (op != Py_EQ) or not isinstance(other, Move):
            return NotImplemented
        cdef Move other_ = other
        if (self.mv.from_square == other_.mv.from_square and 
            self.mv.to_square == other_.mv.to_square and 
            self.mv.promotion == other_.mv.promotion):
            return True
        else:
            return False
    
    def __hash__(Move self):
        return hash((self.from_square, self.to_square, self.promotion))
    
    def __repr__(Move self):
        return 'Move(%d, %d, "%s")' % (self.from_square, self.to_square, self.promotion)
    
    property from_square:
        def __get__(Move self):
            return self.mv.from_square
#
#         def __set__(MoveRecord self, int square_index):
#             self.rec.from_square = square_index

    property to_square:
        def __get__(Move self):  # @DuplicatedSignature
            return self.mv.to_square
        
    property promotion:
        def __get__(Move self):  # @DuplicatedSignature
            return piece_to_str(self.mv.promotion)

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

    property lost_own_castle_king:
        def __get__(MoveRecord self):  # @DuplicatedSignature
            if self.rec.lost_own_castle_king:
                return True
            else:
                return False

    property lost_own_castle_queen:
        def __get__(MoveRecord self):  # @DuplicatedSignature
            if self.rec.lost_own_castle_queen:
                return True
            else:
                return False
    
    property lost_opponent_castle_king:
        def __get__(MoveRecord self):  # @DuplicatedSignature
            if self.rec.lost_opponent_castle_king:
                return True
            else:
                return False

    property lost_opponent_castle_queen:
        def __get__(MoveRecord self):  # @DuplicatedSignature
            if self.rec.lost_opponent_castle_queen:
                return True
            else:
                return False
    
    property promoted_from:
        def __get__(Move self):  # @DuplicatedSignature
            return piece_to_str(self.rec.promoted_from)
        
cdef class BitBoardState:
    cdef readonly boardstate bs
    
    cpdef str get_piece_at_square_index(BitBoardState self, int i):
        cdef brdidx square = <brdidx> i
        return piece_to_str(self.bs.piece_map[square])
    
    property whites_turn:
        def __get__(BitBoardState self):  # @DuplicatedSignature
            if self.bs.whites_turn:
                return True
            else:
                return False
    
    def __richcmp__(BitBoardState self, other, int op):
        if not isinstance(other, BitBoardState) or op != Py_EQ:
            return NotImplemented
        cdef BitBoardState other_ = other
        if not (self.bs.k == other_.bs.k and
           self.bs.q == other_.bs.q and
           self.bs.b == other_.bs.b and
           self.bs.r == other_.bs.r and
           self.bs.k == other_.bs.k and
           self.bs.p == other_.bs.p and
           self.bs.white == other_.bs.white and
           self.bs.black == other_.bs.black and
           self.bs.enpassant == other_.bs.enpassant and
           self.bs.whites_turn == other_.bs.whites_turn and
           self.bs.white_castle_king == other_.bs.white_castle_king and
           self.bs.white_castle_queen == other_.bs.white_castle_queen and
           self.bs.black_castle_king == other_.bs.black_castle_king and
           self.bs.black_castle_queen == other_.bs.black_castle_queen and
           self.bs.halfmove_clock == other_.bs.halfmove_clock and
           self.bs.fullmove_counter == other_.bs.fullmove_counter):
            return False
        for i in range(64):
            if self.bs.piece_map[i] != other_.bs.piece_map[i]:
                return False
        return True
    
    cpdef tuple movesearch(BitBoardState self, double time_limit):
        cdef int depth = 0;
        cdef move mv = movesearch(&(self.bs), time_limit, &depth)
        cdef Move result = Move()
        result.mv = mv
        return result, depth
    
    cpdef tuple movesearch_threshold(BitBoardState self, double threshold):
        t0 = time.time()
        cdef move mv = movesearch_threshold(&(self.bs), threshold)  # @DuplicatedSignature
        t1 = time.time()
        cdef Move result = Move()  # @DuplicatedSignature
        result.mv = mv
        return result, t1 - t0
    
    cpdef unsigned long long perft(BitBoardState self, int depth):
        return perft(&(self.bs), depth)
    
    cpdef all_moves(BitBoardState self):
        cdef queue[move] mvs = queue[move]()
        all_moves(&(self.bs), mvs)
        cdef list result = []
        cdef move mv
        while not mvs.empty():
            mv = mvs.front()
            mvs.pop()
            result.append(Move(mv.from_square, mv.to_square, piece_to_str(mv.promotion)))
        return result
    
    cpdef all_captures(BitBoardState self):
        cdef queue[move] mvs = queue[move]()  # @DuplicatedSignature
        all_captures(&(self.bs), mvs)
        cdef list result = []  # @DuplicatedSignature
        cdef move mv  # @DuplicatedSignature
        while not mvs.empty():
            mv = mvs.front()
            mvs.pop()
            result.append(Move(mv.from_square, mv.to_square, piece_to_str(mv.promotion)))
        return result
    
    cpdef quiet_queen_moves(BitBoardState self):
        cdef queue[move] q = queue[move]()
        quiet_queen_moves(&(self.bs), q)
        cdef list result = []
        cdef move mv
        while not q.empty():
            mv = q.front()
            q.pop()
            result.append(Move(mv.from_square, mv.to_square))
        return result
    
    cpdef all_queen_moves(BitBoardState self):
        cdef queue[move] q = queue[move]()  # @DuplicatedSignature
        all_queen_moves(&(self.bs), q)
        cdef list result = []  # @DuplicatedSignature
        cdef move mv  # @DuplicatedSignature
        while not q.empty():
            mv = q.front()
            q.pop()
            result.append(Move(mv.from_square, mv.to_square))
        return result
    
    cpdef queen_captures(BitBoardState self):
        cdef queue[move] q = queue[move]()  # @DuplicatedSignature
        queen_captures(&(self.bs), q)
        cdef list result = []  # @DuplicatedSignature
        cdef move mv  # @DuplicatedSignature
        while not q.empty():
            mv = q.front()
            q.pop()
            result.append(Move(mv.from_square, mv.to_square))
        return result
    
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
    
    cpdef void unmake_move(BitBoardState self, MoveRecord mv):
        unmake_move(&(self.bs), &(mv.rec))
    
    cpdef str to_str(BitBoardState self):
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
        return result
    
    cpdef str to_grid(BitBoardState self):
        '''
        Use the redundant piece_map instead of the bitboards.
        '''
        return '\n'.join(reversed(map(''.join, partition(8, self.to_str()))))

    cpdef str to_fen(BitBoardState self):

        # Get raw positions
        raw_positions = self.to_str().replace('*', '-')

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
    
    cpdef bool get_white_castle_king(BitBoardState self):
        cdef bool result = get_white_castle_king(&(self.bs))
        return result
    
    cpdef bool get_white_castle_queen(BitBoardState self):
        cdef bool result = get_white_castle_queen(&(self.bs))
        return result
    
    cpdef bool get_black_castle_king(BitBoardState self):
        cdef bool result = get_black_castle_king(&(self.bs))
        return result
    
    cpdef bool get_black_castle_queen(BitBoardState self):
        cdef bool result = get_black_castle_queen(&(self.bs))
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
