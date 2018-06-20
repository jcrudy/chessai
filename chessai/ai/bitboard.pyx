# distutils: language=c++
from libc.stdint cimport uint64_t, uint8_t
from cpython.object cimport Py_EQ, Py_NE
from cpython.mem cimport PyMem_Malloc, PyMem_Realloc, PyMem_Free
from toolz import partition
from operator import methodcaller
from libcpp.vector cimport vector
import time
cimport numpy as np
import numpy as np
from cython.operator cimport dereference
from tqdm import tqdm
from libcpp.memory cimport shared_ptr
from libc.stdlib cimport malloc, free
from toolz import compose, first

cdef extern from "stdbool.h":
    ctypedef char bool

cdef extern from "bitboardlib.h":
    ctypedef uint64_t bitboard
    ctypedef uint64_t zobrist_int
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
    
    ctypedef struct BoardState:
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
        void extract_features(BoardFeatures *features)
    
    ctypedef struct record_entry:
        zobrist_int key
        BoardState board_state
    
    ctypedef struct GameState:
        BoardState board_state
        unsigned int halfmove_clock
        unsigned int fullmove_counter
        unsigned int halfmove_counter
        unsigned int threefold_repetition_clock
        piece piece_map[64]
        zobrist_int hash;
        record_entry record[10000]
        GameState();
    
    ctypedef struct move:
        brdidx from_square
        brdidx to_square
        piece promotion
    
    cdef const move nomove
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
    
    cdef bool draw_by_repetition(GameState *brd, int maxrep)
    cdef moverecord make_move(GameState *brd, move *mv)
    cdef void unmake_move(GameState *brd, moverecord *mv)
    cdef void set_hash(GameState *bs, zobrist_int value)
    cdef zobrist_int get_hash(GameState *bs)
    cdef bool get_white_castle_king(GameState *bs)
    cdef void set_white_castle_king(GameState *bs)
    cdef void unset_white_castle_king(GameState *bs)
    cdef bool get_white_castle_queen(GameState *bs)
    cdef void set_white_castle_queen(GameState *bs)
    cdef void unset_white_castle_queen(GameState *bs)
    cdef bool get_black_castle_king(GameState *bs)
    cdef void set_black_castle_king(GameState *bs)
    cdef void unset_black_castle_king(GameState *bs)
    cdef bool get_black_castle_queen(GameState *bs)
    cdef void set_black_castle_queen(GameState *bs)
    cdef void unset_black_castle_queen(GameState *bs)
    cdef bool get_whites_turn(GameState *bs)
    cdef void set_whites_turn(GameState *bs)
    cdef void unset_whites_turn(GameState *bs)
    cdef bool get_blacks_turn(GameState *bs)
    cdef void set_blacks_turn(GameState *bs)
    cdef void unset_blacks_turn(GameState *bs)
    cdef unsigned int get_halfmove_clock(GameState *bs)
    cdef void set_halfmove_clock(GameState *bs, unsigned int n)
    cdef unsigned int get_fullmove_counter(GameState *bs)
    cdef void set_fullmove_counter(GameState *bs, unsigned int n)
    cdef uint8_t get_enpassant(GameState *bs)
    cdef void set_enpassant(GameState *bs, uint8_t pos)
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
    cdef piece unplace_piece(GameState *bs, brdidx square_index)
    cdef void place_piece(GameState *bs, brdidx square_index, piece pc)
    cdef int quiet_queen_moves(GameState *brd, move *moves, bool whites_turn)
    cdef int all_queen_moves(GameState *brd, move *moves, bool whites_turn)
    cdef int queen_captures(GameState *brd, move *moves, bool whites_turn)
    cdef int all_moves(GameState *brd, move *moves, bool whites_turn)
    cdef int all_captures(GameState *brd, move *moves, bool whites_turn)
    cdef unsigned long long perft(GameState *brd, int depth)
    cdef bool own_check(GameState *brd)
    ctypedef struct movechoice:
        move mv
        double score
    cdef cppclass Zobrist:
        Zobrist()
        zobrist_int hash(GameState *brd)
        zobrist_int update(zobrist_int previous, GameState *brd, moverecord *mv)
    cdef Zobrist zobrist
#     cdef cppclass MoveHistoryTable:
#         MoveHistoryTable();
#         bool compare_moves(move &lhs, move &rhs);
#         void setitem(move mv, double value, double strength);
#         std::tuple<double, double> getitem(move mv);
    ctypedef struct BoardFeatures:
        double *white_pawn
        double *black_pawn
        double *white_knight
        double *black_knight
        double *white_rook
        double *black_rook
        double *white_bishop
        double *black_bishop
        double *white_queen
        double *black_queen
        double *white_king
        double *black_king
        double *white_en_passant
        double *black_en_passant
        double *white_all
        double *black_all
        double *white_queen_and_bishop
        double *black_queen_and_bishop
        double *white_queen_and_rook
        double *black_queen_and_rook
        double *turn
        double *castle_rights

cdef extern from "xnornet.h":
    cdef int convert_to_binary[T](T *input, int input_size, uint64_t *output, int output_size, int stride)
    cdef int convert_from_binary[T](uint64_t *input, int input_size, T *output, int output_size, int stride)
    cdef int binary_sum(uint64_t *x, int size)
    cdef int binary_tanh_dot(uint64_t *x, uint64_t *y, int size)
    cdef cppclass XNorEvaluator:
        XNorEvaluator(int *layer_sizes, int num_layers, int input_size)
        void set_weights[T](int layer, T *weights)
        int apply(uint64_t *input)

cpdef binary_tanh_dot_validation_function(np.ndarray[double, ndim=2, mode='c'] x, np.ndarray[double, ndim=2, mode='c'] y):
    cdef int x_size = x.shape[1]
    cdef int y_size = y.shape[1]
    cdef np.ndarray[double, ndim=2, mode='c'] output = np.empty(shape=(1,y_size))
    cdef uint64_t *x_b = <uint64_t*> malloc((x_size/64) * sizeof(uint64_t))
    cdef uint64_t *y_col_b = <uint64_t*> malloc((x_size/64) * sizeof(uint64_t))
    cdef int i
    convert_to_binary[double](&x[0,0], x_size, x_b, x_size / 64, 1)
    for i in range(y_size):
        convert_to_binary[double](&y[0,i], x_size, y_col_b, x_size / 64, y_size)
        output[0, i] = 1 if binary_tanh_dot(x_b, y_col_b, x_size/64) else -1
    free(x_b)
    free(y_col_b)
    return output
    
cpdef binary_sum_validation_function(np.ndarray[double, ndim=2, mode='c'] data):
    cdef int input_size = data.shape[1]
    cdef int output_size = input_size / 64;
    cdef double * input = &data[0, 0]
    cdef uint64_t *output = <uint64_t*> malloc(output_size * sizeof(uint64_t))
    if convert_to_binary[double](input, input_size, output, output_size, 1):
        result = False
    cdef int correct_value = data.sum()
    cdef int value = binary_sum(output, output_size)
    free(output)
    if correct_value != value:
        print '%d != %d' % (value, correct_value)
        return False
    print '%d == %d' % (value, correct_value)
    return True

cpdef double_binary_conversion_validation_function(np.ndarray[double, ndim=2, mode='c'] data):
    cdef input_size = data.shape[1]
    cdef int output_size = input_size / 64;
    cdef double * input = &data[0, 0]
    cdef uint64_t *output = <uint64_t*> malloc(output_size * sizeof(uint64_t))
    cdef double *copy = <double*> malloc(input_size * sizeof(double))
    cdef bool result = True
    if convert_to_binary[double](input, input_size, output, output_size, 1):
        result = False
    if convert_from_binary[double](output, output_size, copy, input_size, 1):
        result = False
    cdef int i
    for i in range(input_size):
        if not ((copy[i]>0) == (input[i]>0) and (copy[i]<=0) == (input[i]<=0)):
            print 'mismatch at position %d: %f != %f' % (i, input[i], copy[i])
            result = False
            break
    free(output)
    free(copy)
    return result
            

cdef extern from "movesearch.h":
    cdef cppclass MoveTable[ElementType]:
        MoveTable(int num_best)
        bool compare(move &lhs, move &rhs)
        void add(move &mv, ElementType amount)
        void set(move &mv, ElementType amount)
        int rank(move &mv)
        ElementType get(move &mv)
        void reset(ElementType amount)
        void increment(ElementType amount)
        int num_best
    
    cdef cppclass AlphaBetaValue:
        int ply
        int value
        move best_move
        AlphaBetaValue()
    
    cdef cppclass TranspositionEntry:
        zobrist_int key
        int depth
        AlphaBetaValue value
        BoardState brd
        TranspositionEntry()
    
    cdef cppclass TranspositionTable:
        void initialize(size_t size)
        TranspositionTable(size_t size)
        void setitem(GameState &game, const TranspositionEntry &entry)
        TranspositionEntry getitem(GameState &game)
        unsigned long int getindex(GameState &game)
        size_t size
        TranspositionEntry (*data)[2]
        
    cdef cppclass EvaluationEntry:
        zobrist_int key;
        BoardState brd;
        int value;
        EvaluationEntry()
        EvaluationEntry(GameState &game, int value)
    
    cdef cppclass EvaluationTable:
        EvaluationTable()
        void initialize(size_t size)
        EvaluationTable(size_t size)
        void setitem(GameState &game, const EvaluationEntry &entry)
        EvaluationEntry getitem(GameState &game)
        size_t getindex(GameState &game)
        
    cdef cppclass SimpleEvaluation:
        pass
    
    cdef cppclass LogisticEvaluation:
        pass
    
    cdef cppclass KillerTable:
        void initialize(int num_killers)
        KillerTable(int num_killers)
        void record_cutoff(GameState &game, move &mv)
        int score(GameState &game, move &mv)
        void clear(int ply)
    
    cdef cppclass HistoryTable:
        void initialize(int num_history)
        HistoryTable(int num_history)
        void record_cutoff(GameState &game, move &mv)
        int score(GameState &game, move &mv)
    
    cdef cppclass SearchMemory:
        SearchMemory()
        SearchMemory(size_t tt_size, int num_killers, int num_history, size_t ee_size)
        TranspositionTable *tt
        KillerTable *killers
        HistoryTable *hh
        EvaluationTable *ee

    cdef cppclass MoveManager:
        MoveManager()
        int getindex(int depth)
        void generate_all_opponent(GameState &game)
        void generate_all(GameState &game, int depth)
        void generate_noisy(GameState &game, int depth)
        void order_noisy(GameState &game, SearchMemory *memory, int depth)
        void order_all(GameState &game, SearchMemory *memory, int depth)
        moverecord make(GameState &game, move &mv)
        void unmake(GameState &game, moverecord &rec)
        move *get_moves(int depth)
        move *get_opponent_moves()
        int full_begin(int depth)
        int full_end(int depth)
        int pv_begin(int depth)
        int pv_end(int depth)
        int num_moves(int depth)
        int num_opponent_moves()
        
#         
#         
#         
#         void generate_all(GameState &game, int depth)
#         void generate_noisy(GameState &game, int depth)
#         void order_all(GameState &game, SearchMemory *memory, int depth)
#         moverecord make(GameState &game, move &mv)
#         void unmake(GameState &game, moverecord &rec)
#         move *get_moves(int depth)
#         int full_begin
#         int full_end
#         int pv_begin
#         int pv_end
#         int num_moves
    
    cdef AlphaBetaValue quiesce[Evaluation](GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int depth)
    cdef AlphaBetaValue alphabeta[Evaluation](GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int depth, bool *stop, int top, bool debug)
    cdef void calphabeta[Evaluation](GameState *game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, bool *stop, int *depth, AlphaBetaValue *result, bool debug)
    cdef AlphaBetaValue talphabeta[Evaluation](GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int time, int *depth, bool debug)
    cdef AlphaBetaValue mtdf[Evaluation](GameState &game, MoveManager *manager, SearchMemory *memory, int depth, bool *stop)
    cdef void extract_engineered_features(GameState &brd, move *own_moves, int num_own_moves, move *opponent_moves,
                                          int num_opponent_moves, int *output)
    
    cdef cppclass SimpleTimeManager:
        pass
    
    cdef cppclass Player[Evaluation, TimeManager]:
        Player(size_t tt_size, int num_killers, int num_history, size_t ee_size)
#         Player()
        void start_ponder(GameState &game) nogil
        void stop_ponder() nogil
        AlphaBetaValue movesearch(GameState &game, int time_remaining) nogil
        int get_depth()
        int get_pv(GameState &game, move *pv, moverecord *recs)
        TranspositionTable *get_tt()
    
#     cdef cppclass SearchMemory:
#         SearchMemory(int num_killers, int num_moves)
#         TranspositionTable tt
#         HistoryTable hh
#         KillerTable killers


cdef class XNor:
    cdef XNorEvaluator *evaluator
    def __cinit__(XNor self, list layer_sizes, int input_size):
        cdef int num_layers = len(layer_sizes)
        cdef int *sizes = <int *>malloc(num_layers * sizeof(int))
        cdef int i, size
        for i, size in enumerate(layer_sizes):
            sizes[i] = size
        self.evaluator = new XNorEvaluator(sizes, num_layers, input_size)
        free(sizes)
    
    def __dealloc__(XNor self):
        del self.evaluator
        
    cpdef set_weights(XNor self, int layer, np.ndarray[np.float32_t, ndim=2, mode='c'] weights):
        print 'X'
        self.evaluator[0].set_weights[float](layer, &weights[0,0])
        print 'Y'
    
    @classmethod
    def from_keras(cls, model):
        from chessai.xnornet.xnor_layers import XnorDense
        from keras.layers.core import Dropout, Lambda
        from keras.engine.topology import InputLayer
        cdef list layers = list(reversed(map(compose(first, model.layers_by_depth.__getitem__), range(len(model.layers)))))
        cdef list layer_sizes = []
        cdef int insize, outsize, input_size
        cdef bool got_input = False
        cdef list weight_list = []
        for layer in layers:
            if isinstance(layer, XnorDense):
                weights = layer.get_weights()[0]
                insize, outsize = weights.shape
                layer_sizes.append(outsize)
                weight_list.append(weights)
                if not got_input:
                    input_size = insize
                    got_input = True
        print 'layer_sizes = %s' % str(layer_sizes)
        print 'weight_list = %s' % str(layer_sizes)
        print 'A'
        cdef XNor result = XNor(layer_sizes, input_size)
        print 'A.5'
        for i, weights in enumerate(weight_list):
            print i
            result.set_weights(i, weights)
        print 'B'
        return result
    
    cpdef int evaluate_n_times(XNor self, np.ndarray[double, ndim=2, mode='c'] data, int n):
        if data.shape[1] % 64 != 0:
            raise ValueError('Data size %d not divisible by 64.' % data.shape[1])
        cdef uint64_t *converted_data = <uint64_t *>malloc((data.shape[1] / 64) * sizeof(uint64_t))
        cdef double *data_array = &data[0,0]
        convert_to_binary[double](data_array, data.shape[1], converted_data, data.shape[1] / 64, 1)
        cdef int i
        for i in range(n):
            result = self.evaluator[0].apply(converted_data)
        free(converted_data)
        return result
        
    cpdef int evaluate(XNor self, np.ndarray[double, ndim=2, mode='c'] data):
        '''
        Expects data to be 1 x n contiguous array
        Allocates a temporary array to store the binarized version of the data
        '''
        print data
        print data.shape[1]
        if data.shape[1] % 64 != 0:
            raise ValueError('Data size %d not divisible by 64.' % data.shape[1])
        cdef uint64_t *converted_data = <uint64_t *>malloc((data.shape[1] / 64) * sizeof(uint64_t))
        cdef double *data_array = &data[0,0]
        convert_to_binary[double](data_array, data.shape[1], converted_data, data.shape[1] / 64, 1)
        cdef int result
        result = self.evaluator[0].apply(converted_data)
        free(converted_data)
        return result

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
        if not isinstance(other, BitBoard):
            return NotImplemented()
        if op == Py_EQ:
            if self.bb == other.bb:
                return True
            else:
                return False
        elif op == Py_NE:
            return not (self == other)
        else:
            return NotImplemented

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
    
    def to_uci(Move self):
        return (
                int_to_algebraic(self.from_square) + 
                int_to_algebraic(self.to_square) +
                (self.promotion.lower() if self.promotion != 'no' else '')
                )
    
    def to_long_form(Move self):
        return (
                int_to_algebraic(self.from_square) + '-' +
                int_to_algebraic(self.to_square) +
                (('=' + self.promotion.lower()) if self.promotion != 'no' else '')
                )
    
    @classmethod
    def from_long_form(cls, white, rep):
        from_square, to_square = rep.split('-')
        if '=' in to_square:
            to_square, promotion = to_square.split('=')
        else:
            promotion = 'no'
        if white:
            promotion = promotion.upper()
        else:
            promotion = promotion.lower()
        return cls(algebraic_to_int(from_square), algebraic_to_int(to_square), promotion)
    
    cpdef nomove(Move self):
        if self.mv == nomove:
            return True
        else:
            return False
    
    def __bool__(Move self):
        return not self.nomove()
    
    def __richcmp__(Move self, other, op):
        if not isinstance(other, Move):
            return NotImplemented
        cdef Move other_ = other
        if op == Py_EQ:
            if (self.mv.from_square == other_.mv.from_square and 
                self.mv.to_square == other_.mv.to_square and 
                self.mv.promotion == other_.mv.promotion):
                return True
            else:
                return False
        elif op == Py_NE:
            return not (self == other)
        else:
            return NotImplemented
    
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

cdef class ZobristHash:
    cdef readonly zobrist_int value
    def __richcmp__(ZobristHash self, other, int op):
        if not isinstance(other, ZobristHash):
            return NotImplemented
        cdef ZobristHash other_ = other
        if op == Py_EQ:
            if self.value == other_.value:
                return True
            else:
                return False
        elif not (op == Py_NE):
            return not (self == other)
        else:
            return NotImplemented
            

    cpdef ZobristHash update(ZobristHash self, BitBoardState brd, MoveRecord mv):
        cdef ZobristHash result = ZobristHash()
        result.value = zobrist.update(self.value, &(brd.bs), &(mv.rec))
        return result

cdef class LogisticOfficialPlayer:
    cdef Player[LogisticEvaluation, SimpleTimeManager] *player
    cdef bool pondering
    def __cinit__(LogisticOfficialPlayer self, size_t tt_size, int num_killers, int num_history, size_t ee_size):
        self.player = new Player[LogisticEvaluation, SimpleTimeManager](tt_size, num_killers, num_history, ee_size)
        self.pondering = False
        
    def __dealloc__(LogisticOfficialPlayer self):
        del self.player
    
    cpdef start_ponder(LogisticOfficialPlayer self, BitBoardState game):
        if not self.pondering:
            self.player[0].start_ponder(game.bs)
            self.pondering = True
    
    cpdef stop_ponder(LogisticOfficialPlayer self):
        if self.pondering:
            self.player[0].stop_ponder()
            self.pondering = False
    
    cpdef movesearch(LogisticOfficialPlayer self, BitBoardState game, int time_remaining):
        if self.pondering:
            self.stop_ponder()
        cdef AlphaBetaValue search_result
        search_result = self.player[0].movesearch(game.bs, time_remaining)
        cdef Move result = Move()
        result.mv = search_result.best_move
        return result, search_result.value, self.player[0].get_depth()
    
    def get_pv(LogisticOfficialPlayer self, BitBoardState game):
        cdef move pv[100];
        cdef moverecord recs[100];
        cdef int pv_length = self.player[0].get_pv(game.bs, pv, recs)
        cdef int i
        cdef list result = []
        cdef Move mv
        for i in range(pv_length):
            mv = Move()
            mv.mv = pv[i]
            result.append(mv)
        return result

cdef class LogisticPlayer:
    cdef SearchMemory *memory
    cdef MoveManager *manager
    def __init__(Player self, size_t tt_size, int num_killers, int num_history, size_t ee_size=2000000):
        self.memory = new SearchMemory(tt_size, num_killers, num_history, ee_size)
        self.manager = new MoveManager()
    
    def alphabeta(Player self, BitBoardState board, int depth):
        cdef AlphaBetaValue search_result
        cdef bool stop = False
        search_result = alphabeta[LogisticEvaluation](board.bs, self.manager, self.memory, -10000000, 10000000, depth, &stop, depth, False)
        cdef Move result = Move()
        result.mv = search_result.best_move
        return result, search_result.value
    
    def movesearch(Player self, BitBoardState board, int depth, bool debug=False):
        cdef AlphaBetaValue search_result
        cdef bool stop = False
        search_result = alphabeta[LogisticEvaluation](board.bs, self.manager, self.memory, -10000000, 10000000, depth, &stop, depth, debug)
        print search_result.ply
        cdef Move result = Move()
        result.mv = search_result.best_move
        return result, search_result.value
    
    def tmovesearch(Player self, BitBoardState board, int time, bool debug=False):
        '''
        time : time limit in milliseconds
        '''
        cdef AlphaBetaValue search_result
        cdef int depth
        search_result = talphabeta[LogisticEvaluation](board.bs, self.manager, self.memory, -10000000, 10000000, time, &depth, debug)
        cdef Move result = Move()
        result.mv = search_result.best_move
        return result, search_result.value, depth

    def mtdf(Player self, BitBoardState board, int depth):
        cdef AlphaBetaValue search_result
        cdef bool stop = False
        search_result = mtdf[LogisticEvaluation](board.bs, self.manager, self.memory, depth, &stop)
        cdef Move result = Move()
        result.mv = search_result.best_move
        return result, search_result.value

cdef class SimplePlayer:
    cdef SearchMemory *memory
    cdef MoveManager *manager
    def __init__(Player self, size_t tt_size, int num_killers, int num_history, size_t ee_size=2000000):
        self.memory = new SearchMemory(tt_size, num_killers, num_history, ee_size)
        self.manager = new MoveManager()
    
    def alphabeta(Player self, BitBoardState board, int depth):
        cdef AlphaBetaValue search_result
        cdef bool stop = False
        search_result = alphabeta[SimpleEvaluation](board.bs, self.manager, self.memory, -1000000, 1000000, depth, &stop, depth, False)
        cdef Move result = Move()
        result.mv = search_result.best_move
        return result, search_result.value
    
    def movesearch(Player self, BitBoardState board, int depth, bool debug=False):
        cdef AlphaBetaValue search_result
        cdef bool stop = False
        search_result = alphabeta[SimpleEvaluation](board.bs, self.manager, self.memory, -1000000, 1000000, depth, &stop, depth, debug)
        cdef Move result = Move()
        result.mv = search_result.best_move
        return result, search_result.value
    
    def tmovesearch(Player self, BitBoardState board, int time, bool debug=False):
        '''
        time : time limit in milliseconds
        '''
        cdef AlphaBetaValue search_result
        cdef int depth
        search_result = talphabeta[SimpleEvaluation](board.bs, self.manager, self.memory, -1000000, 1000000, time, &depth, debug)
        cdef Move result = Move()
        result.mv = search_result.best_move
        return result, search_result.value, depth

    def mtdf(Player self, BitBoardState board, int depth):
        cdef AlphaBetaValue search_result
        cdef bool stop = False
        search_result = mtdf[SimpleEvaluation](board.bs, self.manager, self.memory, depth, &stop)
        cdef Move result = Move()
        result.mv = search_result.best_move
        return result, search_result.value
    
# cdef class TimePlayer:
#     cdef MoveSearchMemory *msm
#     cdef readonly double time_per_move
#     cdef readonly bool quiesce
#     def __init__(TimePlayer self, unsigned long int size, double time_per_move, bool quiesce):
#         self.msm = new MoveSearchMemory(size)
#         self.time_per_move = time_per_move
#         self.quiesce = quiesce
#     
#     cpdef Move movesearch(TimePlayer self, BitBoardState board):
#         cdef double thresh
#         cdef move mv = movesearch_time(&(board.bs), self.time_per_move, &thresh, self.msm, self.quiesce)
#         cdef Move result = Move()  # @DuplicatedSignature
#         result.mv = mv
#         print('Reached threshold %f' % thresh)
#         return result
# 
# cdef class ThresholdPlayer:
#     cdef MoveSearchMemory *msm
#     cdef readonly double threshold
#     cdef readonly bool quiesce
#     def __init__(ThresholdPlayer self, unsigned long int size, double threshold, bool quiesce):
#         self.msm = new MoveSearchMemory(size)
#         self.threshold = threshold
#         self.quiesce = quiesce
#     
#     cpdef Move movesearch(ThresholdPlayer self, BitBoardState board):
#         cdef move mv = movesearch_threshold(&(board.bs), self.threshold, self.msm, self.quiesce)
#         cdef Move result = Move()  # @DuplicatedSignature
#         result.mv = mv
#         return result

cdef class FeatureExtractor:
    cdef MoveManager *manager
    def __init__(FeatureExtractor self):
        self.manager = new MoveManager()
        
    def engineered_features(FeatureExtractor self, fens):
        cdef BitBoardState board;
        
        cdef move *moves
        cdef int num_moves
    
        cdef move *opponent_moves
        cdef int num_opponent_moves
        
        cdef np.ndarray[int, ndim=1, mode='c'] output = np.empty(shape=15*15 + 29, dtype='i')
        cdef list features = []
        for fen in tqdm(fens):
            board = BitBoardState.from_fen(fen)
            self.manager.generate_all(board.bs, 1)
            moves = self.manager.get_moves(1)
            num_moves = self.manager.num_moves(1)
        
            self.manager.generate_all_opponent(board.bs)
            opponent_moves = self.manager.get_opponent_moves()
            num_opponent_moves = self.manager.num_opponent_moves()
            board = BitBoardState.from_fen(fen)
            extract_engineered_features(board.bs, moves, num_moves, opponent_moves, 
                                        num_opponent_moves, &(output[0]))
            features.append(output.copy())
            
        return features
            
            



cdef class BitBoardState:
    cdef GameState bs
    
    cpdef int get_threefold_repetition_clock(BitBoardState self):
        return self.bs.threefold_repetition_clock
    
    cpdef bool check(BitBoardState self):
        if own_check(&(self.bs)):
            return True
        else:
            return False
    
    property halfmove_clock:
        def __get__(MoveRecord self):  # @DuplicatedSignature
            return self.bs.halfmove_clock
            
    cpdef bool draw(BitBoardState self):
        moves = self.all_moves()
        if not moves:
            if not self.check():
                return True
            else:
                return False
        if self.bs.halfmove_clock >= 50:
            return True
        if draw_by_repetition(&(self.bs), 3):
            return True
        return False
    
    cpdef bool repetition(BitBoardState self, int maxrep):
        if draw_by_repetition(&(self.bs), maxrep):
            return True
        return False
    
    def extract_flat_raw_features(BitBoardState self):
        cdef np.ndarray[double, ndim=2, mode="c"] vec = np.zeros(shape=(1, 20*8*8 + 64,), order='C')
        cdef BoardFeatures features
        features.white_pawn = &vec[0, 0*64]
        features.black_pawn = &vec[0, 1*64]
        features.white_knight = &vec[0, 2*64]
        features.black_knight = &vec[0, 3*64]
        features.white_rook = &vec[0, 4*64]
        features.black_rook = &vec[0, 5*64]
        features.white_bishop = &vec[0, 6*64]
        features.black_bishop = &vec[0, 7*64]
        features.white_queen = &vec[0, 8*64]
        features.black_queen = &vec[0, 9*64]
        features.white_king = &vec[0, 10*64]
        features.black_king = &vec[0, 11*64]
        features.white_en_passant = &vec[0, 12*64]
        features.black_en_passant = &vec[0, 13*64]
        features.white_all = &vec[0, 14*64]
        features.black_all = &vec[0, 15*64]
        features.white_queen_and_bishop = &vec[0, 16*64]
        features.black_queen_and_bishop = &vec[0, 17*64]
        features.white_queen_and_rook = &vec[0, 18*64]
        features.black_queen_and_rook = &vec[0, 19*64]
        features.turn = &vec[0, 20*64]
        features.castle_rights = &vec[0, 20*64 + 2]
        self.bs.board_state.extract_features(&features)
        vec[0, 20*64 + 1] = -1 * min(vec[0, 20*64], 0)
        vec[0, 20*64] = max(vec[0, 20*64], 0)
        vec[0, 20*64 + 63] = 1
        vec[0, 20*64 + 2] *= vec[0, 20*64 + 2]
        vec[0, 20*64 + 3] *= vec[0, 20*64 + 3]
        vec[0, 20*64 + 4] *= vec[0, 20*64 + 4]
        vec[0, 20*64 + 5] *= vec[0, 20*64 + 5]
        vec *= 2
        vec -= 1
        return vec

    def extract_features(BitBoardState self):
        cdef np.ndarray[double, ndim=3, mode="c"] pieces = np.empty(shape=(20,8,8), order='C')
#         cdef np.ndarray[double, ndim=3, mode="c"] knight = np.empty(shape=(8,8,2), order='C')  # @DuplicatedSignature
#         cdef np.ndarray[double, ndim=3, mode="c"] rook = np.empty(shape=(8,8,2), order='C')  # @DuplicatedSignature
#         cdef np.ndarray[double, ndim=3, mode="c"] bishop = np.empty(shape=(8,8,2), order='C')  # @DuplicatedSignature
#         cdef np.ndarray[double, ndim=3, mode="c"] queen = np.empty(shape=(8,8,2), order='C')  # @DuplicatedSignature
#         cdef np.ndarray[double, ndim=3, mode="c"] king = np.empty(shape=(8,8,2), order='C')  # @DuplicatedSignature
#         cdef np.ndarray[double, ndim=3, mode="c"] en_passant = np.empty(shape=(8,8,2), order='C')  # @DuplicatedSignature
#         cdef np.ndarray[double, ndim=3, mode="c"] all = np.empty(shape=(8,8,2), order='C')  # @DuplicatedSignature
#         cdef np.ndarray[double, ndim=3, mode="c"] queen_and_bishop = np.empty(shape=(8,8,2), order='C')  # @DuplicatedSignature
#         cdef np.ndarray[double, ndim=3, mode="c"] queen_and_rook = np.empty(shape=(8,8,2), order='C')  # @DuplicatedSignature
        cdef np.ndarray[double, ndim=1, mode="c"] turn = np.empty(shape=1, order='C')  # @DuplicatedSignature
        cdef np.ndarray[double, ndim=1, mode="c"] castle_rights = np.empty(shape=4, order='C')  # @DuplicatedSignature
        cdef BoardFeatures features
        features.white_pawn = &pieces[0,0,0]
        features.black_pawn = &pieces[1,0,0]
        features.white_knight = &pieces[2,0,0]
        features.black_knight = &pieces[3,0,0]
        features.white_rook = &pieces[4,0,0]
        features.black_rook = &pieces[5,0,0]
        features.white_bishop = &pieces[6,0,0]
        features.black_bishop = &pieces[7,0,0]
        features.white_queen = &pieces[8,0,0]
        features.black_queen = &pieces[9,0,0]
        features.white_king = &pieces[10,0,0]
        features.black_king = &pieces[11,0,0]
        features.white_en_passant = &pieces[12,0,0]
        features.black_en_passant = &pieces[13,0,0]
        features.white_all = &pieces[14,0,0]
        features.black_all = &pieces[15,0,0]
        features.white_queen_and_bishop = &pieces[16,0,0]
        features.black_queen_and_bishop = &pieces[17,0,0]
        features.white_queen_and_rook = &pieces[18,0,0]
        features.black_queen_and_rook = &pieces[19,0,0]
        features.turn = &turn[0]
        features.castle_rights = &castle_rights[0]
        self.bs.board_state.extract_features(&features)
        return dict(pieces=pieces, turn=turn, castle_rights=castle_rights)
    
    cpdef checkmate(BitBoardState self):
        return self.check() and not self.all_moves()
    
    cpdef ZobristHash zobrist_hash(BitBoardState self):
        cdef ZobristHash result = ZobristHash()
        result.value = zobrist.hash(&(self.bs))
        return result
    
    cpdef ZobristHash get_zobrist_hash(BitBoardState self):
        cdef ZobristHash result = ZobristHash()  # @DuplicatedSignature
        result.value = self.bs.hash
        return result
    
    cpdef str get_piece_at_square_index(BitBoardState self, int i):
        cdef brdidx square = <brdidx> i
        return piece_to_str(self.bs.piece_map[square])
    
    property whites_turn:
        def __get__(BitBoardState self):  # @DuplicatedSignature
            if self.bs.board_state.whites_turn:
                return True
            else:
                return False
    
    def __richcmp__(BitBoardState self, other, int op):
        if not isinstance(other, BitBoardState):
            return NotImplemented
        cdef BitBoardState other_ = other
        if op == Py_EQ:
            if not (self.bs == other_.bs):
                return False
            for i in range(64):
                if self.bs.piece_map[i] != other_.bs.piece_map[i]:
                    return False
            return True
        elif op == Py_NE:
            return not (self == other)
        else:
            return NotImplemented
    
#     cpdef tuple movesearch(BitBoardState self, double time_limit):
#         cdef int depth = 0;
#         cdef move mv = movesearch(&(self.bs), time_limit, &depth)
#         cdef Move result = Move()
#         result.mv = mv
#         return result, depth
#     
#     cpdef tuple movesearch_threshold(BitBoardState self, double threshold):
#         t0 = time.time()
#         cdef move mv = movesearch_threshold(&(self.bs), threshold)  # @DuplicatedSignature
#         t1 = time.time()
#         cdef Move result = Move()  # @DuplicatedSignature
#         result.mv = mv
#         return result, t1 - t0
    
    cpdef unsigned long long perft(BitBoardState self, int depth):
        return perft(&(self.bs), depth)
    
    cpdef all_moves(BitBoardState self, whites_turn=None):
        cdef move mvs[300]
        cdef bool whites_turn_
        if whites_turn is None:
            whites_turn_ = self.bs.board_state.whites_turn
        else:
            whites_turn_ = whites_turn
        cdef int num_moves = all_moves(&(self.bs), mvs, whites_turn_)
#         print "num_moves = %d" % num_moves
        cdef list result = []
        cdef move mv
        for i in range(num_moves):
            mv = mvs[i]
            result.append(Move(mv.from_square, mv.to_square, piece_to_str(mv.promotion)))
        return result
    
    cpdef all_captures(BitBoardState self):
        cdef move mvs[300];  # @DuplicatedSignature
        cdef int num_moves = all_captures(&(self.bs), mvs, self.bs.board_state.whites_turn)
        cdef list result = []  # @DuplicatedSignature
        cdef move mv  # @DuplicatedSignature
        for i in range(num_moves):
            mv = mvs[i]
            result.append(Move(mv.from_square, mv.to_square, piece_to_str(mv.promotion)))
        return result
    
    cpdef quiet_queen_moves(BitBoardState self):
        cdef move mvs[300];  # @DuplicatedSignature
        cdef int num_moves = quiet_queen_moves(&(self.bs), mvs, self.bs.board_state.whites_turn)
        cdef list result = []  # @DuplicatedSignature
        cdef move mv  # @DuplicatedSignature
        for i in range(num_moves):
            mv = mvs[i]
            result.append(Move(mv.from_square, mv.to_square, piece_to_str(mv.promotion)))
        return result
    
    cpdef all_queen_moves(BitBoardState self):
        cdef move mvs[300];  # @DuplicatedSignature
        cdef int num_moves = all_queen_moves(&(self.bs), mvs, self.bs.board_state.whites_turn)
        cdef list result = []  # @DuplicatedSignature
        cdef move mv  # @DuplicatedSignature
        for i in range(num_moves):
            mv = mvs[i]
            result.append(Move(mv.from_square, mv.to_square, piece_to_str(mv.promotion)))
        return result
    
    cpdef queen_captures(BitBoardState self):
        cdef move mvs[300];  # @DuplicatedSignature
        cdef int num_moves = queen_captures(&(self.bs), mvs, self.bs.board_state.whites_turn)
        cdef list result = []  # @DuplicatedSignature
        cdef move mv  # @DuplicatedSignature
        for i in range(num_moves):
            mv = mvs[i]
            result.append(Move(mv.from_square, mv.to_square, piece_to_str(mv.promotion)))
        return result
    
    cpdef place_piece(BitBoardState self, int idx, str pc):
        place_piece(&(self.bs), <brdidx> idx, str_to_piece(pc))

    @classmethod
    def from_fen(cls, str fen):
        cdef GameState bs
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
        result.bb =  self.bs.board_state.k
        return result

    cpdef BitBoard get_q(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.board_state.q
        return result

    cpdef BitBoard get_b(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.board_state.b
        return result

    cpdef BitBoard get_r(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.board_state.r
        return result

    cpdef BitBoard get_n(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.board_state.n
        return result

    cpdef BitBoard get_p(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.board_state.p
        return result

    cpdef BitBoard get_white(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.board_state.white
        return result

    cpdef BitBoard get_black(BitBoardState self):
        result = BitBoard()
        result.bb =  self.bs.board_state.black
        return result

    cpdef int get_enpassant(BitBoardState self):
        cdef int result = self.bs.board_state.enpassant
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

cdef GameState fen_to_bitboard(str fen):
    cdef GameState bs = GameState();
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
        if bs.board_state.whites_turn:
            bs.piece_map[algebraic_to_int(en_passant)] = ep
        else:
            bs.piece_map[algebraic_to_int(en_passant)] = EP
    set_halfmove_clock(&bs, int(halfmove_clock))
    set_fullmove_counter(&bs, int(move_number))
    set_hash(&bs, zobrist.hash(&bs))
    bs.record[0].board_state = bs.board_state
    bs.record[0].key = bs.hash
    return bs
