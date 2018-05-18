#ifndef BITBOARDLIB_H
#define BITBOARDLIB_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

typedef uint64_t bitboard;
typedef uint64_t zobrist_int;

extern const bitboard empty;
extern const bitboard full;
extern const bitboard p0;
extern const bitboard p1;
extern const bitboard p2;
extern const bitboard p3;
extern const bitboard p4;
extern const bitboard p5;
extern const bitboard p6;
extern const bitboard p7;
extern const bitboard p8;
extern const bitboard p9;
extern const bitboard p10;
extern const bitboard p11;
extern const bitboard p12;
extern const bitboard p13;
extern const bitboard p14;
extern const bitboard p15;
extern const bitboard p16;
extern const bitboard p17;
extern const bitboard p18;
extern const bitboard p19;
extern const bitboard p20;
extern const bitboard p21;
extern const bitboard p22;
extern const bitboard p23;
extern const bitboard p24;
extern const bitboard p25;
extern const bitboard p26;
extern const bitboard p27;
extern const bitboard p28;
extern const bitboard p29;
extern const bitboard p30;
extern const bitboard p31;
extern const bitboard p32;
extern const bitboard p33;
extern const bitboard p34;
extern const bitboard p35;
extern const bitboard p36;
extern const bitboard p37;
extern const bitboard p38;
extern const bitboard p39;
extern const bitboard p40;
extern const bitboard p41;
extern const bitboard p42;
extern const bitboard p43;
extern const bitboard p44;
extern const bitboard p45;
extern const bitboard p46;
extern const bitboard p47;
extern const bitboard p48;
extern const bitboard p49;
extern const bitboard p50;
extern const bitboard p51;
extern const bitboard p52;
extern const bitboard p53;
extern const bitboard p54;
extern const bitboard p55;
extern const bitboard p56;
extern const bitboard p57;
extern const bitboard p58;
extern const bitboard p59;
extern const bitboard p60;
extern const bitboard p61;
extern const bitboard p62;
extern const bitboard p63;
extern const bitboard places[64];

extern const bitboard file_a;
extern const bitboard file_b;
extern const bitboard file_c;
extern const bitboard file_d;
extern const bitboard file_e;
extern const bitboard file_f;
extern const bitboard file_g;
extern const bitboard file_h;
extern const bitboard files[8];

extern const bitboard rank_1;
extern const bitboard rank_2;
extern const bitboard rank_3;
extern const bitboard rank_4;
extern const bitboard rank_5;
extern const bitboard rank_6;
extern const bitboard rank_7;
extern const bitboard rank_8;
extern const bitboard ranks[8];

extern const bitboard white_castle_king_open;
extern const bitboard black_castle_king_open;
extern const bitboard castle_king_rook;
extern const bitboard white_castle_queen_open;
extern const bitboard black_castle_queen_open;
extern const bitboard castle_queen_rook;

extern const bitboard center4;
extern const bitboard center16;

extern const bitboard diag_0;
extern const bitboard diag_1;
extern const bitboard diag_2;
extern const bitboard diag_3;
extern const bitboard diag_4;
extern const bitboard diag_5;
extern const bitboard diag_6;
extern const bitboard diag_7;
extern const bitboard diag_15;
extern const bitboard diag_14;
extern const bitboard diag_13;
extern const bitboard diag_12;
extern const bitboard diag_11;
extern const bitboard diag_10;
extern const bitboard diag_9;
extern const bitboard diags[16];

extern const bitboard antidiag_0;
extern const bitboard antidiag_1;
extern const bitboard antidiag_2;
extern const bitboard antidiag_3;
extern const bitboard antidiag_4;
extern const bitboard antidiag_5;
extern const bitboard antidiag_6;
extern const bitboard antidiag_7;
extern const bitboard antidiag_15;
extern const bitboard antidiag_14;
extern const bitboard antidiag_13;
extern const bitboard antidiag_12;
extern const bitboard antidiag_11;
extern const bitboard antidiag_10;
extern const bitboard antidiag_9;
extern const bitboard antidiags[16];

typedef unsigned char brdidx;
extern const brdidx no_enpassant;

inline brdidx greatest_square_index(bitboard b){
	brdidx result = 0;
	while(b >>= 1){
		result++;
	}
	return(result);
}

inline bitboard bitboard_from_square_index(brdidx i){
	return(places[i]);
}

inline const char *bbstr(bitboard bb){
	// Just for debugging
	std::string str = std::string();
	for(int i=0;i<64;i++){
		if(bb & bitboard_from_square_index(i)){
			str.push_back('1');
		}else{
			str.push_back('0');
		}
	}
	std::string *str2 = new std::string();
	for(int j=1; j<=8; j++){
		(*str2) += str.substr(64 - 8*j, 8);
		if(j<8){
			str2->push_back(10);
		}
	}
	return str2->c_str();
}

inline brdidx square_index_to_file_index(brdidx i){
	return(i % 8);
}

inline brdidx square_index_to_rank_index(brdidx i){
	return(i / 8);
}

inline brdidx square_index_to_diag_index(brdidx i){
	return((square_index_to_rank_index(i) - square_index_to_file_index(i)) & 15);
//	return(7 + square_index_to_rank_index(i) - square_index_to_file_index(i));
}

inline brdidx square_index_to_antidiag_index(brdidx i){
	return(7 ^ (square_index_to_rank_index(i) + square_index_to_file_index(i)));
//	return(square_index_to_rank_index(i) + square_index_to_file_index(i));
}

inline brdidx greatest_rank_index(bitboard b){
	return(greatest_square_index(b) / 8);
}

inline brdidx greatest_file_index(bitboard b){
	return(greatest_square_index(b) % 8);
}

inline brdidx greatest_diag_index(bitboard b){
	return(greatest_rank_index(b) - greatest_file_index(b));
}

inline brdidx greatest_antidiag_index(bitboard b){
	return(greatest_rank_index(b) + greatest_file_index(b) - 7);
}

inline bitboard place(bitboard b, int p){
	return (b | places[p]);
}

inline bitboard unplace(bitboard b, int p){
	return (b & ~(places[p]));
}

inline bitboard ls1b(bitboard b){
	return(b & (-b));
}

inline int population_count(bitboard b){
	return __builtin_popcountll(b);
//	int result = 0;
//	while(b){
//		b ^= ls1b(b);
//		result++;
//	}
//	return(result);
}

inline bitboard step_north(bitboard b){
	return(b << 8);
}

inline bitboard step_south(bitboard b){
	return(b >> 8);
}

inline bitboard step_east(bitboard b){
	return((b & (~file_h)) << 1);
}

inline bitboard step_west(bitboard b){
	return((b & (~file_a)) >> 1);
}

inline bitboard step_northwest(bitboard b){
	return((b & (~file_a)) << 7);
}

inline bitboard step_northeast(bitboard b){
	return((b & (~file_h)) << 9);
}

inline bitboard step_southwest(bitboard b){
	return((b & (~file_a)) >> 9);
}

inline bitboard step_southeast(bitboard b){
	return((b & (~file_h)) >> 7);
}

inline bitboard slide_north(bitboard pieces, bitboard unoccupied){
	bitboard result = pieces;
	result |= ((result << 8) & unoccupied);
	unoccupied &= (unoccupied << 8);
	result |= ((result << 16) & unoccupied);
	unoccupied &= (unoccupied << 16);
	result |= ((result << 32) & unoccupied);
	return result;
}

//inline bitboard slide_capture_north(bitboard pieces, bitboard own, bitboard opponent){
//	bitboard result = pieces;
//	bitboard open = ~opponent;
//	bitboard unoccupied = ~own;
//	result |= (((result & open) << 8) & unoccupied);
//	unoccupied &= (unoccupied << 8);
//	result |= (((result & open) << 16) & unoccupied);
//	unoccupied &= (unoccupied << 16);
//	result |= (((result & open) << 32) & unoccupied);
//	return result & opponent;
//}

inline bitboard slide_south(bitboard pieces, bitboard unoccupied){
	bitboard result = pieces;
	result |= ((result >> 8) & unoccupied);
	unoccupied &= (unoccupied >> 8);
	result |= ((result >> 16) & unoccupied);
	unoccupied &= (unoccupied >> 16);
	result |= ((result >> 32) & unoccupied);
	return result;
}

inline bitboard slide_east(bitboard pieces, bitboard unoccupied){
	bitboard result = pieces;
	unoccupied &= (~file_a);
	result |= ((result << 1) & unoccupied);
	unoccupied &= (unoccupied << 1);
	result |= ((result << 2) & unoccupied);
	unoccupied &= (unoccupied << 2);
	result |= ((result << 4) & unoccupied);
	return result;
}

inline bitboard slide_west(bitboard pieces, bitboard unoccupied){
	bitboard result = pieces;
	unoccupied &= (~file_h);
	result |= ((result >> 1) & unoccupied);
	unoccupied &= (unoccupied >> 1);
	result |= ((result >> 2) & unoccupied);
	unoccupied &= (unoccupied >> 2);
	result |= ((result >> 4) & unoccupied);
	return result;
}

inline bitboard slide_northeast(bitboard pieces, bitboard unoccupied){
	bitboard result = pieces;
	unoccupied &= (~file_a);
	result |= ((result << 9) & unoccupied);
	unoccupied &= (unoccupied << 9);
	result |= ((result << 18) & unoccupied);
	unoccupied &= (unoccupied << 18);
	result |= ((result << 36) & unoccupied);
	return result;
}

inline bitboard slide_northwest(bitboard pieces, bitboard unoccupied){
	bitboard result = pieces;
	unoccupied &= (~file_h);
	result |= ((result << 7) & unoccupied);
	unoccupied &= (unoccupied << 7);
	result |= ((result << 14) & unoccupied);
	unoccupied &= (unoccupied << 14);
	result |= ((result << 28) & unoccupied);
	return result;
}

inline bitboard slide_southeast(bitboard pieces, bitboard unoccupied){
	bitboard result = pieces;
	unoccupied &= (~file_a);
	result |= ((result >> 7) & unoccupied);
	unoccupied &= (unoccupied >> 7);
	result |= ((result >> 14) & unoccupied);
	unoccupied &= (unoccupied >> 14);
	result |= ((result >> 28) & unoccupied);
	return result;
}

inline bitboard slide_southwest(bitboard pieces, bitboard unoccupied){
	bitboard result = pieces;
	unoccupied &= (~file_h);
	result |= ((result >> 9) & unoccupied);
	unoccupied &= (unoccupied >> 9);
	result |= ((result >> 18) & unoccupied);
	unoccupied &= (unoccupied >> 18);
	result |= ((result >> 36) & unoccupied);
	return result;
}

inline bitboard compute_knight_moves_from_square_index(brdidx s){
	bitboard knight_square = bitboard_from_square_index(s);
	bitboard nee = step_north(step_east(step_east(knight_square)));
	bitboard nne = step_north(step_north(step_east(knight_square)));
	bitboard nww = step_north(step_west(step_west(knight_square)));
	bitboard nnw = step_north(step_north(step_west(knight_square)));
	bitboard see = step_south(step_east(step_east(knight_square)));
	bitboard sse = step_south(step_south(step_east(knight_square)));
	bitboard sww = step_south(step_west(step_west(knight_square)));
	bitboard ssw = step_south(step_south(step_west(knight_square)));
	return(nee | nne | nww | nnw | see | sse | sww | ssw);
}

// TODO: Change to lookup
inline bitboard knight_moves_from_square_index(brdidx s){
	return(compute_knight_moves_from_square_index(s));
}

inline bitboard compute_white_pawn_push_moves_from_square_index(brdidx s){
	bitboard pawn_square = bitboard_from_square_index(s);
	return(step_north(pawn_square) | (step_north(step_north(pawn_square & rank_2))));
}

// TODO: Change to lookup
inline bitboard white_pawn_push_moves_from_square_index(brdidx s){
	return(compute_white_pawn_push_moves_from_square_index(s));
}

inline bitboard compute_white_pawn_inverse_push_moves_from_square_index(brdidx s){
	bitboard pawn_square = bitboard_from_square_index(s);
	return((step_south(pawn_square) | (step_south(step_south(pawn_square)) & rank_2)) & (~rank_1));
}

// TODO: Change to lookup
inline bitboard white_pawn_inverse_push_moves_from_square_index(brdidx s){
	return(compute_white_pawn_inverse_push_moves_from_square_index(s));
}

inline bitboard compute_white_pawn_capture_moves_from_square_index(brdidx s){
	bitboard pawn_square = bitboard_from_square_index(s);
	return(step_east(step_north(pawn_square)) | step_west(step_north(pawn_square)));
}

// TODO: Change to lookup
inline bitboard white_pawn_capture_moves_from_square_index(brdidx s){
	return(compute_white_pawn_capture_moves_from_square_index(s));
}

inline bitboard compute_white_pawn_inverse_capture_moves_from_square_index(brdidx s){
	bitboard pawn_square = bitboard_from_square_index(s);
	return((step_east(step_south(pawn_square)) | step_west(step_south(pawn_square))) &(~rank_1));
}

// TODO: Change to lookup
inline bitboard white_pawn_inverse_capture_moves_from_square_index(brdidx s){
	return(compute_white_pawn_inverse_capture_moves_from_square_index(s));
}

inline bitboard compute_black_pawn_push_moves_from_square_index(brdidx s){
	bitboard pawn_square = bitboard_from_square_index(s);
	return(step_south(pawn_square) | (step_south(step_south(pawn_square & rank_7))));
}

// TODO: Change to lookup
inline bitboard black_pawn_push_moves_from_square_index(brdidx s){
	return(compute_black_pawn_push_moves_from_square_index(s));
}

inline bitboard compute_black_pawn_inverse_push_moves_from_square_index(brdidx s){
	bitboard pawn_square = bitboard_from_square_index(s);
	return((step_north(pawn_square) | (step_north(step_north(pawn_square)) & rank_7)) & (~rank_8));
}

// TODO: Change to lookup
inline bitboard black_pawn_inverse_push_moves_from_square_index(brdidx s){
	return(compute_black_pawn_inverse_push_moves_from_square_index(s));
}

inline bitboard compute_black_pawn_capture_moves_from_square_index(brdidx s){
	bitboard pawn_square = bitboard_from_square_index(s);
	return(step_east(step_south(pawn_square)) | step_west(step_south(pawn_square)));
}

// TODO: Change to lookup
inline bitboard black_pawn_capture_moves_from_square_index(brdidx s){
	return(compute_black_pawn_capture_moves_from_square_index(s));
}

inline bitboard compute_black_pawn_inverse_capture_moves_from_square_index(brdidx s){
	bitboard pawn_square = bitboard_from_square_index(s);
	return((step_east(step_north(pawn_square)) | step_west(step_north(pawn_square))) & (~rank_8));
}

// TODO: Change to lookup
inline bitboard black_pawn_inverse_capture_moves_from_square_index(brdidx s){
	return(compute_black_pawn_inverse_capture_moves_from_square_index(s));
}

inline bitboard compute_king_moves_from_square_index(brdidx s){
	bitboard king_square = bitboard_from_square_index(s);
	return(step_east(king_square) | step_northeast(king_square) | 
	       step_north(king_square) | step_northwest(king_square) | step_west(king_square) |
	       step_southwest(king_square) | step_south(king_square) | step_southeast(king_square));
}

// TODO: replace with lookup
inline bitboard king_moves_from_square_index(brdidx s){
	return(compute_king_moves_from_square_index(s));
}

inline bitboard compute_queen_moves_from_square_index(brdidx s){
	brdidx rank, file, diag, antidiag;
	rank = square_index_to_rank_index(s);
	file = square_index_to_file_index(s);
	diag = square_index_to_diag_index(s);
	antidiag = square_index_to_antidiag_index(s);
	return((ranks[rank] | files[file] | diags[diag] | antidiags[antidiag]) ^ bitboard_from_square_index(s));
}

// TODO: replace with lookup
inline bitboard queen_moves_from_square_index(brdidx s){
	return(compute_queen_moves_from_square_index(s));
}

inline bitboard compute_rook_moves_from_square_index(brdidx s){
	brdidx rank, file;
	rank = square_index_to_rank_index(s);
	file = square_index_to_file_index(s);
	return((ranks[rank] | files[file]) ^ bitboard_from_square_index(s));
}

// TODO: replace with lookup
inline bitboard rook_moves_from_square_index(brdidx s){
	return(compute_rook_moves_from_square_index(s));
}

inline bitboard compute_bishop_moves_from_square_index(brdidx s){
	brdidx diag, antidiag;
	diag = square_index_to_diag_index(s);
	antidiag = square_index_to_antidiag_index(s);
	return((diags[diag] | antidiags[antidiag]) ^ bitboard_from_square_index(s));
}

// TODO: replace with lookup
inline bitboard bishop_moves_from_square_index(brdidx s){
	return(compute_bishop_moves_from_square_index(s));
}


typedef enum {no=0,K,Q,B,N,R,P,EP,k,q,b,n,r,p,ep} piece;

struct BoardFeatures{
	double *white_pawn;//[64];
	double *black_pawn;//[64];
	double *white_knight;//[64];
	double *black_knight;//[64];
	double *white_rook;//[64];
	double *black_rook;//[64];
	double *white_bishop;//[64];
	double *black_bishop;//[64];
	double *white_queen;//[64];
	double *black_queen;//[64];
	double *white_king;//[64];
	double *black_king;//[64];
	double *white_en_passant;//[64];
	double *black_en_passant;//[64];
	double *white_all;//[64];
	double *black_all;//[64];
	double *white_queen_and_bishop;//[64];
	double *black_queen_and_bishop;//[64];
	double *white_queen_and_rook;//[64];
	double *black_queen_and_rook;//[64];
	double *turn;//[1];
	double *castle_rights;//[4];
	BoardFeatures() = default;
//	BoardFeatures(double *white_pawn, double *black_pawn, double *white_knight, 
//				double *black_knight, double *white_rook, double *black_rook, 
//				double *white_bishop, double *black_bishop, double *white_queen, 
//				double *black_queen, double *white_king, double *black_king, 
//				double *white_en_passant, double *black_en_passant, double *white_all,
//				double *black_all, double *white_queen_and_bishop, double *black_queen_and_bishop, 
//				double *white_queen_and_rook, double *black_queen_and_rook,
//				double *turn, double *castle_rights);
};

inline void bitboard_to_array(bitboard bb, double *arr){
	for(int i=0;i<64;i++){
		if(bb & bitboard_from_square_index(i)){
			arr[i] = 1;
		}else{
			arr[i] = 0;
		}
	}
}

// Just the parts needed to have same legal moves (ignoring clock)
struct BoardState{
	BoardState(){
		k = empty;
		q = empty;
		b = empty;
		n = empty;
		r = empty;
		p = empty;
		white = empty;
		black = empty;
		enpassant = empty;
		whites_turn = false;
		white_castle_king = false;
		white_castle_queen = false;
		black_castle_king = false;
		black_castle_queen = false;
	}
	bitboard k;
	bitboard q;
	bitboard b;
	bitboard n;
	bitboard r;
	bitboard p;
	bitboard white;
	bitboard black;
	brdidx enpassant;
	bool whites_turn;
	bool white_castle_king;
	bool white_castle_queen;
	bool black_castle_king;
	bool black_castle_queen;
	bool empty;
	void extract_features(BoardFeatures *features);
};

extern const BoardState empty_board_state;

/*
struct PositionCountHasher {
	std::size_t operator()(const std::tuple<zobrist_int, BoardState> &k) const {
		return (std::size_t) std::get<0>(k);
	}
};

typedef std::unordered_map<std::tuple<zobrist_int, BoardState>, int, PositionCountHasher> PositionCounter;
*/

struct record_entry {
	zobrist_int key;
	BoardState board_state;
};

struct move{
	brdidx from_square;
	brdidx to_square;
	piece promotion;
	int sort_score;
};

extern const move nomove;

class TargetTable{
	public:
		TargetTable(){
			clear();
		}
		void clear(){
			for(int i=0;i<64;i++){
				this->targets[i] = empty;
			}
		}
		void add_moves(move *moves, int num_moves, bool reverse){
			move mv;
			brdidx from_square, to_square;
			for(int i=0;i<num_moves;i++){
				mv = moves[i];
				if(reverse){
					from_square = mv.to_square;
					to_square = mv.from_square;
				}else{
					to_square = mv.to_square;
					from_square = mv.from_square;
				}
				this->targets[from_square] |= bitboard_from_square_index(to_square);
			}
		}
		void set_moves(move *moves, int num_moves, bool reverse){
			clear();
			add_moves(moves, num_moves, reverse);
		}
		bitboard targets[64];
	
};

struct GameState{
	BoardState board_state;
	static const int maxrecord = 10000;
	unsigned int halfmove_clock;
	unsigned int fullmove_counter;
	unsigned int halfmove_counter;
	unsigned int threefold_repetition_clock;
	piece piece_map[64];
	zobrist_int hash;
	record_entry record[maxrecord];
	TargetTable moves_from;
	TargetTable moves_to;
//	PositionCounter *position_count;
//	int current_position_count;
	GameState();
	~GameState();
};

inline int game_record_index(int ply){
	int result = ply % (GameState::maxrecord);
	if(result < 0){
		result += (GameState::maxrecord);
	}
	return result;
}

inline bool operator==(const BoardState& lhs, const BoardState& rhs)
{
	if (lhs.k == rhs.k &&
      	lhs.q == rhs.q &&
       	lhs.b == rhs.b &&
       	lhs.r == rhs.r &&
       	lhs.k == rhs.k &&
       	lhs.p == rhs.p &&
       	lhs.white == rhs.white &&
       	lhs.black == rhs.black &&
       	lhs.enpassant == rhs.enpassant &&
       	lhs.whites_turn == rhs.whites_turn &&
       	lhs.white_castle_king == rhs.white_castle_king &&
       	lhs.white_castle_queen == rhs.white_castle_queen &&
       	lhs.black_castle_king == rhs.black_castle_king &&
       	lhs.black_castle_queen == rhs.black_castle_queen){
		return true;
	} else {
		return false;
	}
}

inline bool operator==(const record_entry& lhs, const record_entry& rhs)
{
	if (lhs.key == rhs.key && lhs.board_state == rhs.board_state){
		return true;
	} else {
		return false;
	}
}

inline bool operator==(const GameState& lhs, const GameState& rhs)
{
    if (!(
           lhs.board_state == rhs.board_state &&
           lhs.halfmove_clock == rhs.halfmove_clock &&
           lhs.threefold_repetition_clock == rhs.threefold_repetition_clock &&
           lhs.fullmove_counter == rhs.fullmove_counter &&
           lhs.halfmove_counter == rhs.halfmove_counter
           )){
 		return(false);
 	}
 	
    for(int i=0; i<64; i++){
    	if(lhs.piece_map[i] != rhs.piece_map[i]){
    		return(false);
    	}
    }
    return(true);
}

inline bool draw_by_repetition(GameState *brd, int maxrep){
	int repetition_count=0;
	int repetition_check;
	record_entry rep_entry;
	if(brd->threefold_repetition_clock >= 2 * maxrep){
		for(repetition_check = brd->halfmove_counter;
			repetition_check <= brd->threefold_repetition_clock;
			repetition_check -= 2){
			rep_entry = brd->record[game_record_index(repetition_check)];
			if(brd->hash == rep_entry.key && brd->board_state == rep_entry.board_state){
				repetition_count++;
			}
			if(repetition_count>=maxrep){
				return true;
			}
		}
	}
	return false;
}

inline piece piece_from_square_index(GameState *bs, brdidx square_index){
	// May return no (=0), meaning not occupied.  Check for this before using the piece.
	return(bs->piece_map[square_index]);
}

inline void unsafe_place_piece(GameState *bs, brdidx square_index, piece pc){
	bitboard bb = bitboard_from_square_index(square_index);
	(bs->piece_map)[square_index] = pc;
	switch(pc){
		case K:
			(bs->board_state.k) |= bb;
			(bs->board_state.white) |= bb;
			break;
		case k:
			(bs->board_state.k) |= bb;
			(bs->board_state.black) |= bb;
			break;
		case Q:
			(bs->board_state.q) |= bb;
			(bs->board_state.white) |= bb;
			break;
		case q:
			(bs->board_state.q) |= bb;
			(bs->board_state.black) |= bb;
			break;
		case B:
			(bs->board_state.b) |= bb;
			(bs->board_state.white) |= bb;
			break;
		case b:
			(bs->board_state.b) |= bb;
			(bs->board_state.black) |= bb;
			break;
		case N:
			(bs->board_state.n) |= bb;
			(bs->board_state.white) |= bb;
			break;
		case n:
			(bs->board_state.n) |= bb;
			(bs->board_state.black) |= bb;
			break;
		case R:
			(bs->board_state.r) |= bb;
			(bs->board_state.white) |= bb;
			break;
		case r:
			(bs->board_state.r) |= bb;
			(bs->board_state.black) |= bb;
			break;
		case P:
			(bs->board_state.p) |= bb;
			(bs->board_state.white) |= bb;
			break;
		case p:
			(bs->board_state.p) |= bb;
			(bs->board_state.black) |= bb;
			break;
		case EP:
			(bs->board_state.enpassant) = square_index;
			break;
		case ep:
			(bs->board_state.enpassant) = square_index;
			break;
		case no:
			{}
	}
}

inline piece unplace_piece(GameState *bs, brdidx square_index){
	bitboard bb = ~bitboard_from_square_index(square_index);
	piece pc = (bs->piece_map)[square_index];
	bs->piece_map[square_index] = no;
	switch(pc){
		case K:
			(bs->board_state.k) &= bb;
			(bs->board_state.white) &= bb;
			break;
		case k:
			(bs->board_state.k) &= bb;
			(bs->board_state.black) &= bb;
			break;
		case Q:
			(bs->board_state.q) &= bb;
			(bs->board_state.white) &= bb;
			break;
		case q:
			(bs->board_state.q) &= bb;
			(bs->board_state.black) &= bb;
			break;
		case B:
			(bs->board_state.b) &= bb;
			(bs->board_state.white) &= bb;
			break;
		case b:
			(bs->board_state.b) &= bb;
			(bs->board_state.black) &= bb;
			break;
		case N:
			(bs->board_state.n) &= bb;
			(bs->board_state.white) &= bb;
			break;
		case n:
			(bs->board_state.n) &= bb;
			(bs->board_state.black) &= bb;
			break;
		case R:
			(bs->board_state.r) &= bb;
			(bs->board_state.white) &= bb;
			break;
		case r:
			(bs->board_state.r) &= bb;
			(bs->board_state.black) &= bb;
			break;
		case P:
			(bs->board_state.p) &= bb;
			(bs->board_state.white) &= bb;
			break;
		case p:
			(bs->board_state.p) &= bb;
			(bs->board_state.black) &= bb;
			break;
		case EP:
			(bs->board_state.enpassant) = no_enpassant;
			break;
		case ep:
			(bs->board_state.enpassant) = no_enpassant;
			break;
		case no:
			{}
	}
	return(pc);
}

inline void place_piece(GameState *bs, brdidx square_index, piece pc){
	if(pc != no){
		unplace_piece(bs, square_index);
		unsafe_place_piece(bs, square_index, pc);
	}
}

inline bitboard piece_bitboard_from_piece(GameState *bs, piece pc){
	switch(pc){
		case K:
			return(bs->board_state.k);
		case k:
			return(bs->board_state.k);
		case Q:
			return(bs->board_state.q);
		case q:
			return(bs->board_state.q);
		case B:
			return(bs->board_state.b);
		case b:
			return(bs->board_state.b);
		case N:
			return(bs->board_state.n);
		case n:
			return(bs->board_state.n);
		case R:
			return(bs->board_state.r);
		case r:
			return(bs->board_state.r);
		case P:
			return(bs->board_state.p);
		case p:
			return(bs->board_state.p);
		case EP:
			return(bitboard_from_square_index(bs->board_state.enpassant));
		case ep:
			return(bitboard_from_square_index(bs->board_state.enpassant));
		case no:
			return(empty);
	}
}

inline bitboard color_bitboard_from_piece(GameState *bs, piece pc){
	switch(pc){
		case K:
			return(bs->board_state.white);
		case k:
			return(bs->board_state.black);
		case Q:
			return(bs->board_state.white);
		case q:
			return(bs->board_state.black);
		case B:
			return(bs->board_state.white);
		case b:
			return(bs->board_state.black);
		case N:
			return(bs->board_state.white);
		case n:
			return(bs->board_state.black);
		case R:
			return(bs->board_state.white);
		case r:
			return(bs->board_state.black);
		case P:
			return(bs->board_state.white);
		case p:
			return(bs->board_state.black);
		case EP:
			return(bs->board_state.white);
		case ep:
			return(bs->board_state.black);
		case no:
			return(empty);
	}
}

inline bitboard bitboard_from_piece(GameState *bs, piece pc){
	return(piece_bitboard_from_piece(bs, pc) & color_bitboard_from_piece(bs, pc));
}

inline void printmove(move mv){
	// For debugging
	printf("move(%d, %d, %d)\n", mv.from_square, mv.to_square, mv.promotion);
}

inline bool operator==(const move& lhs, const move& rhs){
	// Note that sort_score is not considered for equality
	if(lhs.from_square == rhs.from_square && lhs.to_square == rhs.to_square &&
		lhs.promotion == rhs.promotion){
		return true;
	} else {
		return false;
	}
}

inline bool operator<(const move& lhs, const move& rhs){
	// Only consider sort_score.  Used for move ordering.  Higher scores
	// go first.
	if(lhs.sort_score > rhs.sort_score){
		return true;
	}
	return false;
}

typedef struct {
	piece captured;
	bool lost_own_castle_king;
	bool lost_own_castle_queen;
	bool lost_opponent_castle_king;
	bool lost_opponent_castle_queen;
	brdidx enpassant;
	unsigned int previous_halfmove_clock;
	unsigned int previous_threefold_repetition_clock;
	brdidx from_square;
	brdidx to_square;
	piece promoted_from;
} moverecord;

inline void set_hash(GameState *bs, zobrist_int value){
	bs->hash = value;
}

inline zobrist_int get_hash(GameState *bs){
	return bs->hash;
}

inline brdidx get_enpassant(GameState *bs){
	return(bs->board_state.enpassant);
}

inline bitboard get_enpassant_bitboard(GameState *bs){
	brdidx enpassant = get_enpassant(bs);
	if(enpassant != no_enpassant){
		return(bitboard_from_square_index(enpassant));
	}else{
		return(empty);
	}
}

inline void set_enpassant(GameState *bs, uint8_t pos){
	// Should be called after flip_turn
	if(bs->board_state.enpassant != no_enpassant){
		(bs->piece_map)[bs->board_state.enpassant] = no;
	}
	bs->board_state.enpassant = pos;
	if(bs->board_state.enpassant != no_enpassant){
		if(bs->board_state.whites_turn){
			(bs->piece_map)[pos] = ep;
		}else{
			(bs->piece_map)[pos] = EP;
		}
	}
};

inline unsigned int get_halfmove_clock(GameState *bs){
	return(bs->halfmove_clock);
};

inline void set_halfmove_clock(GameState *bs, unsigned int n){
	(bs->halfmove_clock) = n;
};

inline unsigned int get_fullmove_counter(GameState *bs){
	return(bs->fullmove_counter);
};

inline void set_fullmove_counter(GameState *bs, unsigned int n){
	bs->fullmove_counter = n;
};

inline bool get_white_castle_king(GameState *bs){
	return(bs->board_state.white_castle_king);
};

inline void set_white_castle_king(GameState *bs){
	bs->board_state.white_castle_king = true;
};

inline void unset_white_castle_king(GameState *bs){
	bs->board_state.white_castle_king = false;
};

inline bool get_white_castle_queen(GameState *bs){
	return(bs->board_state.white_castle_queen);
};

inline void set_white_castle_queen(GameState *bs){
	bs->board_state.white_castle_queen = true;
};

inline void unset_white_castle_queen(GameState *bs){
	bs->board_state.white_castle_queen = false;
};

inline bool get_black_castle_king(GameState *bs){
	return(bs->board_state.black_castle_king);
};

inline void set_black_castle_king(GameState *bs){
	bs->board_state.black_castle_king = true;
};

inline void unset_black_castle_king(GameState *bs){
	bs->board_state.black_castle_king = false;
};

inline bool get_black_castle_queen(GameState *bs){
	return(bs->board_state.black_castle_queen);
};

inline void set_black_castle_queen(GameState *bs){
	bs->board_state.black_castle_queen = true;
};

inline void unset_black_castle_queen(GameState *bs){
	(bs->board_state.black_castle_queen) = false;
};

inline void flip_turn(GameState *bs){
	(bs->board_state.whites_turn) = !(bs->board_state.whites_turn);
}

inline bool get_whites_turn(GameState *bs){
	return(bs->board_state.whites_turn);
};

inline void set_whites_turn(GameState *bs){
	(bs->board_state.whites_turn) = true;
};

inline void unset_whites_turn(GameState *bs){
	(bs->board_state.whites_turn) = false;
};

inline bool get_blacks_turn(GameState *bs){
	return(!get_whites_turn(bs));
};

inline void set_blacks_turn(GameState *bs){
	unset_whites_turn(bs);
};

inline void unset_blacks_turn(GameState *bs){
	set_whites_turn(bs);
};

inline bitboard get_current_movers_bitboard(GameState *bs){
	if(get_whites_turn(bs)){
		return(bs->board_state.white);
	}else{
		return(bs->board_state.black);
	}
}

inline bitboard get_player_bitboard(GameState *bs, bool white){
	if(white){
		return(bs->board_state.white);
	}else{
		return(bs->board_state.black);
	}
}

inline bitboard get_opposing_movers_bitboard(GameState *bs){
	if(get_whites_turn(bs)){
		return(bs->board_state.black);
	}else{
		return(bs->board_state.white);
	}
}

/*
inline void increment_fullmove_counter(GameState *bs){
	(bs->fullmove_counter)++;
}

inline void decrement_fullmove_counter(GameState *bs){
	(bs->fullmove_counter)--;
}

inline void increment_halfmove_clock(GameState *bs){
	(bs->halfmove_clock)++;
}

inline void reset_halfmove_clock(GameState *bs){
	(bs->halfmove_clock) = 0;
}
*/

class Zobrist {
	public:
		Zobrist();
		zobrist_int hash(GameState *brd) const;
		zobrist_int hash(BoardState brd) const;
		zobrist_int update(zobrist_int previous, GameState *brd, moverecord *mv) const;
	private:
		zobrist_int zobrist_table[8][8][14];
		zobrist_int zobrist_white_castle_king;
		zobrist_int zobrist_white_castle_queen;
		zobrist_int zobrist_black_castle_king;
		zobrist_int zobrist_black_castle_queen;
		zobrist_int zobrist_blacks_turn;
};

extern const Zobrist zobrist;

inline void unmake_move(GameState *brd, moverecord *mv){
	
	// downdate position count
//	std::tuple<zobrist_int, BoardState> key;
//	key = std::make_tuple(brd->hash, smallify(brd));
//	((*(brd->position_count))[key])--;
	
	
	// downdate zobrist hash value
	set_hash(brd, zobrist.update(get_hash(brd), brd, mv));

	// switch back whose turn it is
	flip_turn(brd);
	
	// check for promotion
	piece from_piece = brd->piece_map[mv->to_square];
	if (mv->promoted_from != from_piece){
		unplace_piece(brd, mv->to_square);
		place_piece(brd, mv->to_square, mv->promoted_from);
		from_piece = mv->promoted_from;
	}
	
	// change halfmove clock back
	brd->halfmove_clock = mv->previous_halfmove_clock;
	brd->threefold_repetition_clock = mv->previous_threefold_repetition_clock;
	
	// fulllmove counter and castle rights
	(brd->halfmove_counter)--;
	if(brd->board_state.whites_turn){
		if(mv->lost_own_castle_king){
			set_white_castle_king(brd);
		}
		if(mv->lost_own_castle_queen){
			set_white_castle_queen(brd);
		}
		if(mv->lost_opponent_castle_king){
			set_black_castle_king(brd);
		}
		if(mv->lost_opponent_castle_queen){
			set_black_castle_queen(brd);
		}
	}else{
		brd->fullmove_counter--;
		if(mv->lost_own_castle_king){
			set_black_castle_king(brd);
		}
		if(mv->lost_own_castle_queen){
			set_black_castle_queen(brd);
		}
		if(mv->lost_opponent_castle_king){
			set_white_castle_king(brd);
		}
		if(mv->lost_opponent_castle_queen){
			set_white_castle_queen(brd);
		}
	}
	
	// undo the actual move
	unplace_piece(brd, mv->to_square);
	place_piece(brd, mv->from_square, from_piece);
	// check for castling
	if(from_piece==K && (mv->to_square - mv->from_square == 2)){
		//white castle king side
		unplace_piece(brd, 5);
		place_piece(brd, 7, R);
	}else if(from_piece==K && (mv->from_square - mv->to_square == 2)){
		//white castle queen side
		unplace_piece(brd, 3);
		place_piece(brd, 0, R);
	}else if(from_piece==k && (mv->to_square - mv->from_square == 2)){
		//black castle king side
		unplace_piece(brd, 61);
		place_piece(brd, 63, r);
	}else if(from_piece==k && (mv->from_square - mv->to_square == 2)){
		//black castle queen side
		unplace_piece(brd, 59);
		place_piece(brd, 56, r);
	}
	
	// undo capture, checking for en passant
	if(mv->captured==ep){
		place_piece(brd, (mv->to_square) - 8, p);
	}else if(mv->captured==EP){
		place_piece(brd, (mv->to_square) + 8, P);
	}else{
		place_piece(brd, mv->to_square, mv->captured);
	}
	
	// reset en passant status
	set_enpassant(brd, mv->enpassant);
	
	// set current position count (can only be done at end of unmake)
//	key = std::make_tuple(brd->hash, smallify(brd));
//	brd->current_position_count = (*(brd->position_count))[key];
}


inline bitboard checking_rays_intersection(GameState *brd, const bool pin_check_only){
	// Return the intersection of all rays by which the current mover's king is in check
	// by sliding pieces.  If no such rays, return the set of all squares (the empty intersection).
	// If pin_check_only, this is being used to detect an absolute pin and, under the 
	// assumption that there is no king capture available (which there should never be),
	// there is at most one possible pinning ray and we can terminate once we find it.
	
	BoardState bs = brd->board_state;
	bitboard king_board = bs.k & get_current_movers_bitboard(brd);
	bitboard propagator = ~(bs.white | bs.black);
	brdidx king_square = greatest_square_index(king_board);
	brdidx king_rank = square_index_to_rank_index(king_square);
	//brdidx king_file = square_index_to_file_index(king_square);
	brdidx king_diag = square_index_to_diag_index(king_square);
	//brdidx king_antidiag = square_index_to_antidiag_index(king_square);
	
	bitboard slide;
	bitboard current_attacker;
	brdidx current_attacker_square;
	brdidx attacker_file, attacker_rank, attacker_diag, attacker_antidiag;
	bitboard attackers;
	bitboard result = full;
	
	// Check for attacking rooks and queens
	attackers = rook_moves_from_square_index(king_square) & get_opposing_movers_bitboard(brd) & (bs.r | bs.q);
	while(attackers){
		current_attacker = ls1b(attackers);
		attackers &= ~current_attacker;
		current_attacker_square = greatest_square_index(current_attacker);
		attacker_rank = square_index_to_rank_index(current_attacker_square);
		attacker_file = square_index_to_file_index(current_attacker_square);
		if(current_attacker < king_board){
			if(king_rank == attacker_rank){
				slide = slide_east(current_attacker, propagator);
				slide |= step_east(slide) & king_board;
				if(slide & king_board){
					if(pin_check_only){
						return(slide);
					}else{
						result &= slide;
					}
				}
			}else{//king_file == attacker_file
				slide = slide_north(current_attacker, propagator);
				slide |= step_north(slide) & king_board;
				if(slide & king_board){
					if(pin_check_only){
						return(slide);
					}else{
						result &= slide;
					}
				}
			}
		}else{//current_attacker > king_board
			if(king_rank == attacker_rank){
				slide = slide_west(current_attacker, propagator);
				slide |= step_west(slide) & king_board;
				if(slide & king_board){
					if(pin_check_only){
						return(slide);
					}else{
						result &= slide;
					}
				}
			}else{//king_file == attacker_file
				slide = slide_south(current_attacker, propagator);
				slide |= step_south(slide) & king_board;
				if(slide & king_board){
					if(pin_check_only){
						return(slide);
					}else{
						result &= slide;
					}
				}
			}
		}
	}
	// Check for attacking bishops and queens
	attackers = bishop_moves_from_square_index(king_square) & get_opposing_movers_bitboard(brd) & (bs.b | bs.q);
	while(attackers){
		current_attacker = ls1b(attackers);
		attackers &= ~current_attacker;
		current_attacker_square = greatest_square_index(current_attacker);
		attacker_diag = square_index_to_diag_index(current_attacker_square);
		attacker_antidiag = square_index_to_antidiag_index(current_attacker_square);
		if(current_attacker < king_board){
			if(king_diag == attacker_diag){
				slide = slide_northeast(current_attacker, propagator);
				slide |= step_northeast(slide) & king_board;
				if(slide & king_board){
					if(pin_check_only){
						return(slide);
					}else{
						result &= slide;
					}
				}
			}else{//king_antidiag == attacker_antidiag
				slide = slide_northwest(current_attacker, propagator);
				slide |= step_northwest(slide) & king_board;
				if(slide & king_board){
					if(pin_check_only){
						return(slide);
					}else{
						result &= slide;
					}
				}
			}
		}else{//current_attacker > king_board
			if(king_diag == attacker_diag){
				slide = slide_southwest(current_attacker, propagator);
				slide |= step_southwest(slide) & king_board;
				if(slide & king_board){
					if(pin_check_only){
						return(slide);
					}else{
						result &= slide;
					}
				}
			}else{//king_antidiag == attacker_antidiag
				slide = slide_southeast(current_attacker, propagator);
				slide |= step_southeast(slide) & king_board;
				if(slide & king_board){
					if(pin_check_only){
						return(slide);
					}else{
						result &= slide;
					}
				}
			}
		}
	}
	
	// Check for attacking knights
	attackers = knight_moves_from_square_index(king_square) & get_opposing_movers_bitboard(brd) & (bs.n);
	if(attackers){
		result &= attackers;
	}
	
	// Check for attacking pawns
	if(get_whites_turn(brd)){
		attackers = black_pawn_inverse_capture_moves_from_square_index(king_square) & get_opposing_movers_bitboard(brd) & (bs.p);
	}else{
		attackers = white_pawn_inverse_capture_moves_from_square_index(king_square) & get_opposing_movers_bitboard(brd) & (bs.p);
	}
	if(attackers){
		result &= attackers;
	}
	return(result);
}

inline moverecord make_move(GameState *brd, move *mv){
	piece from_piece, to_piece;
	bool lost_own_castle_king = false;
	bool lost_own_castle_queen = false;
	bool lost_opponent_castle_king = false;
	bool lost_opponent_castle_queen = false;
	from_piece = brd->piece_map[mv->from_square];
	to_piece = brd->piece_map[mv->to_square];
	brdidx old_enpassant = brd->board_state.enpassant;
	
	// check for castle loss
	if(from_piece == K){
		lost_own_castle_king = get_white_castle_king(brd);
		lost_own_castle_queen = get_white_castle_queen(brd);
	}else if(from_piece == R){
		if((mv->from_square) == 7){
			lost_own_castle_king = get_white_castle_king(brd);
			lost_own_castle_queen = false;
		}
		if((mv->from_square) == 0){
			lost_own_castle_queen = get_white_castle_queen(brd);
			lost_own_castle_king = false;
		}
	}else if(from_piece == k){
		lost_own_castle_king = get_black_castle_king(brd);
		lost_own_castle_queen = get_black_castle_queen(brd);
	}else if(from_piece == r){
		if((mv->from_square) == 63){
			lost_own_castle_king = get_black_castle_king(brd);
			lost_own_castle_queen = false;
		}
		if((mv->from_square) == 56){
			lost_own_castle_queen = get_black_castle_queen(brd);
			lost_own_castle_king = false;
		}
	}else if(to_piece == R){
		if((mv->to_square) == 7){
			lost_opponent_castle_king = get_white_castle_king(brd);
			lost_opponent_castle_queen = false;
		}
		if((mv->to_square) == 0){
			lost_opponent_castle_queen = get_white_castle_queen(brd);
			lost_opponent_castle_king = false;
		}
	}else if(to_piece == r){
		if((mv->to_square) == 63){
			lost_opponent_castle_king = get_black_castle_king(brd);
			lost_opponent_castle_queen = false;
		}
		if((mv->to_square) == 56){
			lost_opponent_castle_queen = get_black_castle_queen(brd);
			lost_opponent_castle_king = false;
		}
	}

	// check for new en passant
	brdidx new_enpassant;
	if((from_piece == P) &&
		(square_index_to_rank_index(mv->from_square) == 1) &&
		(square_index_to_rank_index(mv->to_square) == 3)){
		new_enpassant = (mv->to_square) - 8;
	}else if((from_piece == p) &&
		(square_index_to_rank_index(mv->from_square) == 6) &&
		(square_index_to_rank_index(mv->to_square) == 4)){
		new_enpassant = (mv->to_square) + 8;
	}else{
		new_enpassant = no_enpassant;
	}

	// update board state
	unplace_piece(brd, mv->from_square);
	//perform en passant
	if(to_piece==ep && from_piece == P){
		//remove black pawn for en_passant capture
		unplace_piece(brd, (mv->to_square) - 8);
	}else if(to_piece==EP && from_piece == p){
		//remove white pawn for en_passant capture
		unplace_piece(brd, (mv->to_square) + 8);
	}
	//perform castling
	if(from_piece==K && (mv->to_square - mv->from_square == 2)){
		//white castle king side
		unplace_piece(brd, 7);
		place_piece(brd, 5, R);
	}else if(from_piece==K && (mv->from_square - mv->to_square == 2)){
		//white castle queen side
		unplace_piece(brd, 0);
		place_piece(brd, 3, R);
	}else if(from_piece==k && (mv->to_square - mv->from_square == 2)){
		//black castle king side
		unplace_piece(brd, 63);
		place_piece(brd, 61, r);
	}else if(from_piece==k && (mv->from_square - mv->to_square == 2)){
		//black castle queen side
		unplace_piece(brd, 56);
		place_piece(brd, 59, r);
	}
	//continue regular move stuff
	place_piece(brd, mv->to_square, from_piece);
	(brd->halfmove_counter)++;
	if(brd->board_state.whites_turn){
		if(lost_own_castle_king){
			unset_white_castle_king(brd);
		}
		if(lost_own_castle_queen){
			unset_white_castle_queen(brd);
		}
		if(lost_opponent_castle_king){
			unset_black_castle_king(brd);
		}
		if(lost_opponent_castle_queen){
			unset_black_castle_queen(brd);
		}
	}else{
		(brd->fullmove_counter)++;
		if(lost_own_castle_king){
			unset_black_castle_king(brd);
		}
		if(lost_own_castle_queen){
			unset_black_castle_queen(brd);
		}
		if(lost_opponent_castle_king){
			unset_white_castle_king(brd);
		}
		if(lost_opponent_castle_queen){
			unset_white_castle_queen(brd);
		}
	}
	unsigned int previous_halfmove_clock = brd->halfmove_clock;
	unsigned int previous_threefold_repetition_clock = brd->threefold_repetition_clock;
	if((to_piece != no) || (from_piece == p) || (from_piece == P)){
		brd->halfmove_clock = 0;
		brd->threefold_repetition_clock = 0;
	}else if(lost_own_castle_king || lost_own_castle_queen ||
			lost_opponent_castle_king || lost_opponent_castle_queen){
		brd->threefold_repetition_clock = 0;
		brd->halfmove_clock++;
	}else{
		brd->halfmove_clock++;
		brd->threefold_repetition_clock++;
	}
	
	// check for promotion
	if (mv->promotion != no){
		unplace_piece(brd, mv->to_square);
		place_piece(brd, mv->to_square, mv->promotion);
	}
	
	// Take turns, people
	flip_turn(brd);
	
//	if(new_enpassant != no_enpassant){
//		potential_capturers = black_pawn_inverse_capture_moves_from_square_index(new_enpassant);
//		
//	}
	
	// Set en_passant
	set_enpassant(brd, new_enpassant);
	
	// Remember what we did
	moverecord record = {to_piece, lost_own_castle_king, lost_own_castle_queen,
						 lost_opponent_castle_king, lost_opponent_castle_queen,
						 old_enpassant, previous_halfmove_clock, 
						 previous_threefold_repetition_clock,
						 mv->from_square, mv->to_square, from_piece};

	// update zobrist hash value
	set_hash(brd, zobrist.update(get_hash(brd), brd, &record));
	
	// update position count
//	std::tuple<zobrist_int, BoardState> key;
//	key = std::make_tuple(brd->hash, smallify(brd));
//	if(brd->position_count->count(key)){
//		((*(brd->position_count))[key])++;
//	}else{
//		(*(brd->position_count))[key] = 1;
//	}
//	brd->current_position_count = (*(brd->position_count))[key];
	brd->record[game_record_index(brd->halfmove_counter)] = {brd->hash, brd->board_state};
	return(record);
}

inline bitboard attackers_from_square_index(GameState *brd, brdidx s){
	BoardState bs = brd->board_state;
	bitboard result = empty;
	bitboard rooks_and_queens = bs.r | bs.q;
	bitboard bishops_and_queens = bs.b | bs.q;
	
	bitboard tmp;
	bitboard unoccupied = ~(bs.white | bs.black);
	bitboard source = bitboard_from_square_index(s);
	tmp = slide_east(source, unoccupied);
	tmp |= step_east(tmp) & rooks_and_queens;
	result |= tmp;
	tmp = slide_northeast(source, unoccupied);
	tmp |= step_northeast(tmp) & bishops_and_queens;
	result |= tmp;
	tmp = slide_north(source, unoccupied);
	tmp |= step_north(tmp) & rooks_and_queens;
	result |= tmp;
	tmp = slide_northwest(source, unoccupied);
	tmp |= step_northwest(tmp) & bishops_and_queens;
	result |= tmp;
	tmp = slide_west(source, unoccupied);
	tmp |= step_west(tmp) & rooks_and_queens;
	result |= tmp;
	tmp = slide_southwest(source, unoccupied);
	tmp |= step_southwest(tmp) & bishops_and_queens;
	result |= tmp;
	tmp = slide_south(source, unoccupied);
	tmp |= step_south(tmp) & rooks_and_queens;
	result |= tmp;
	tmp = slide_southeast(source, unoccupied);
	tmp |= step_southeast(tmp) & bishops_and_queens;
	result |= tmp;
	result |= black_pawn_inverse_capture_moves_from_square_index(s) & (bs.black & bs.p);
	result |= white_pawn_inverse_capture_moves_from_square_index(s) & (bs.white & bs.p);
	result |= knight_moves_from_square_index(s) & bs.n;
	result |= king_moves_from_square_index(s) & bs.k;
	result ^= source;
	return(result);
}

inline bool own_check(GameState *brd){
	bitboard own = get_current_movers_bitboard(brd);
	bitboard opponent = get_opposing_movers_bitboard(brd);
	brdidx king_square = greatest_square_index(own & brd->board_state.k);
	bitboard attackers = attackers_from_square_index(brd, king_square) & opponent;
	if(attackers){
		return(true);
	}else{
		return(false);
	}
}

inline bool opponent_check(GameState *brd){
	bitboard own = get_current_movers_bitboard(brd);
	bitboard opponent = get_opposing_movers_bitboard(brd);
	brdidx king_square = greatest_square_index(opponent & brd->board_state.k);
	bitboard attackers = attackers_from_square_index(brd, king_square) & own;
	if(attackers){
		return(true);
	}else{
		return(false);
	}
}

inline bool player_check(GameState *brd, bool whites_turn){
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	brdidx king_square = greatest_square_index(opponent & brd->board_state.k);
	bitboard attackers = attackers_from_square_index(brd, king_square) & own;
	if(attackers){
		return(true);
	}else{
		return(false);
	}
}

inline int king_captures(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	brdidx king_square = greatest_square_index(brd->board_state.k & own); // there is only one king
	bitboard king_targets = king_moves_from_square_index(king_square);
	piece own_king;
	if(get_whites_turn(brd)){
		own_king = K;
	}else{
		own_king = k;
	}
	king_targets &= ~own;
	king_targets &= opponent;
	bitboard target;
	brdidx target_square;
	bitboard attackers;
	move mv;
	while(king_targets){
		target = ls1b(king_targets);
		king_targets ^= target;
		target_square = greatest_square_index(target);
		unplace_piece(brd, king_square);
		attackers = attackers_from_square_index(brd, target_square) & opponent;
		unsafe_place_piece(brd, king_square, own_king);
		if(!attackers){
			mv = move();
			mv.from_square = king_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
		
	}
	return num_moves;
}


inline int all_king_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	BoardState bs = brd->board_state;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	brdidx king_square = greatest_square_index(bs.k & own); // there is only one king
	bitboard king_targets = king_moves_from_square_index(king_square) & (~own);
	bitboard attackers;
	move mv;
	
	// Castling
	if(whites_turn){
		if(get_white_castle_king(brd)){
			if((bs.white & bs.r & castle_king_rook) && !((own | opponent) & white_castle_king_open)){
				attackers = attackers_from_square_index(brd, 4) & opponent;
				attackers |= attackers_from_square_index(brd, 5) & opponent;
				attackers |= attackers_from_square_index(brd, 6) & opponent;
				if(!attackers){
					mv = move();
					mv.from_square = king_square;
					mv.to_square = king_square + 2;
					mv.promotion = no;
					moves[num_moves] = mv;
					num_moves++;
				}
			}
		}
		if(get_white_castle_queen(brd)){
			if((bs.white & bs.r & castle_queen_rook) && !((own | opponent) & white_castle_queen_open)){
				attackers = attackers_from_square_index(brd, 2) & opponent;
				attackers |= attackers_from_square_index(brd, 3) & opponent;
				attackers |= attackers_from_square_index(brd, 4) & opponent;
				if(!attackers){
					mv = move();
					mv.from_square = king_square;
					mv.to_square = king_square - 2;
					mv.promotion = no;
					moves[num_moves] = mv;
					num_moves++;
				}
			}
		}
	}else{
		if(get_black_castle_king(brd)){
			if((bs.black & bs.r & castle_king_rook) && !((own | opponent) & black_castle_king_open)){
				attackers = attackers_from_square_index(brd, 60) & opponent;
				attackers |= attackers_from_square_index(brd, 61) & opponent;
				attackers |= attackers_from_square_index(brd, 62) & opponent;
				if(!attackers){
					mv = move();
					mv.from_square = king_square;
					mv.to_square = king_square + 2;
					mv.promotion = no;
					moves[num_moves] = mv;
					num_moves++;
				}
			}
		}
		if(get_black_castle_queen(brd)){
			if((bs.black & bs.r & castle_queen_rook) && !((own | opponent) & black_castle_queen_open)){
				attackers = attackers_from_square_index(brd, 58) & opponent;
				attackers |= attackers_from_square_index(brd, 59) & opponent;
				attackers |= attackers_from_square_index(brd, 60) & opponent;
				if(!attackers){
					mv = move();
					mv.from_square = king_square;
					mv.to_square = king_square - 2;
					mv.promotion = no;
					moves[num_moves] = mv;
					num_moves++;
				}
			}
		}
	
	}
	
	piece own_king, captured;
	if(whites_turn){
		own_king = K;
	}else{
		own_king = k;
	}
	king_targets &= ~own;
	bitboard target;
	brdidx target_square;
	while(king_targets){
		target = ls1b(king_targets);
		king_targets ^= target;
		target_square = greatest_square_index(target);
		unplace_piece(brd, king_square);
		captured = unplace_piece(brd, target_square);
		attackers = attackers_from_square_index(brd, target_square) & opponent;
		if(captured != no){
			unsafe_place_piece(brd, target_square, captured);
		}
		unsafe_place_piece(brd, king_square, own_king);
		if(!attackers){
			mv = move();
			mv.from_square = king_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
		
	}
	return num_moves;
}

inline int quiet_king_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	BoardState bs = brd->board_state;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	brdidx king_square = greatest_square_index(bs.k & own); // there is only one king
	bitboard king_targets = king_moves_from_square_index(king_square);
	bitboard attackers;
	move mv;
	
	// Castling
	if(whites_turn){
		if(get_white_castle_king(brd)){
			if((bs.white & bs.r & castle_king_rook) && !((own | opponent) & white_castle_king_open)){
				attackers = attackers_from_square_index(brd, 4) & opponent;
				attackers |= attackers_from_square_index(brd, 5) & opponent;
				attackers |= attackers_from_square_index(brd, 6) & opponent;
				if(!attackers){
					mv = move();
					mv.from_square = king_square;
					mv.to_square = king_square + 2;
					mv.promotion = no;
					moves[num_moves] = mv;
					num_moves++;
				}
			}
		}
		if(get_white_castle_queen(brd)){
			if((bs.white & bs.r & castle_queen_rook) && !((own | opponent) & white_castle_queen_open)){
				attackers = attackers_from_square_index(brd, 2) & opponent;
				attackers |= attackers_from_square_index(brd, 3) & opponent;
				attackers |= attackers_from_square_index(brd, 4) & opponent;
				if(!attackers){
					mv = move();
					mv.from_square = king_square;
					mv.to_square = king_square - 2;
					mv.promotion = no;
					moves[num_moves] = mv;
					num_moves++;
				}
			}
		}
	}else{
		if(get_black_castle_king(brd)){
			if((bs.black & bs.r & castle_king_rook) && !((own | opponent) & black_castle_king_open)){
				attackers = attackers_from_square_index(brd, 60) & opponent;
				attackers |= attackers_from_square_index(brd, 61) & opponent;
				attackers |= attackers_from_square_index(brd, 62) & opponent;
				if(!attackers){
					mv = move();
					mv.from_square = king_square;
					mv.to_square = king_square + 2;
					mv.promotion = no;
					moves[num_moves] = mv;
					num_moves++;
				}
			}
		}
		if(get_black_castle_queen(brd)){
			
			if((bs.black & bs.r & castle_queen_rook) && !((own | opponent) & black_castle_queen_open)){
				attackers = attackers_from_square_index(brd, 58) & opponent;
				attackers |= attackers_from_square_index(brd, 59) & opponent;
				attackers |= attackers_from_square_index(brd, 60) & opponent;
				if(!attackers){
					mv = move();
					mv.from_square = king_square;
					mv.to_square = king_square - 2;
					mv.promotion = no;
					moves[num_moves] = mv;
					num_moves++;
				}
			}
		}
	
	}
	
	piece own_king;
	if(whites_turn){
		own_king = K;
	}else{
		own_king = k;
	}
	king_targets &= ~own;
	king_targets &= ~opponent;
	bitboard target;
	bitboard target_square;
	while(king_targets){
		target = ls1b(king_targets);
		king_targets ^= target;
		target_square = ls1b(target);
		unplace_piece(brd, king_square);
		attackers = attackers_from_square_index(brd, target_square) & opponent;
		unsafe_place_piece(brd, king_square, own_king);
		if(!attackers){
			mv = move();
			mv.from_square = king_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
		
	}
	return num_moves;
		
}

inline int knight_captures(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	BoardState bs = brd->board_state;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	
	bitboard targets, current_source, current_target, propagator;
	brdidx source_square, target_square;
	move mv;
	
	bitboard knights = own & (bs.n);
	while(knights){
		current_source = ls1b(knights);
		knights ^= current_source;
		source_square = greatest_square_index(current_source);
		
		// propagator takes care of pinning
		propagator = full;
		unplace_piece(brd, source_square);
		propagator &= checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, N);
		}else{
			unsafe_place_piece(brd, source_square, n);
		}
		
		targets = empty;
		targets |= step_north(step_north(step_east(current_source)));
		targets |= step_north(step_north(step_west(current_source)));
		targets |= step_south(step_south(step_east(current_source)));
		targets |= step_south(step_south(step_west(current_source)));
		
		targets |= step_east(step_east(step_south(current_source)));
		targets |= step_east(step_east(step_north(current_source)));
		targets |= step_west(step_west(step_south(current_source)));
		targets |= step_west(step_west(step_north(current_source)));
		
		targets &= opponent & propagator;
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}

inline int all_knight_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	BoardState bs = brd->board_state;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard targets, current_source, current_target, propagator;
	brdidx source_square, target_square;
	move mv;
	
	bitboard knights = own & (bs.n);
	while(knights){
		current_source = ls1b(knights);
		knights ^= current_source;
		source_square = greatest_square_index(current_source);
		
		// propagator takes care of pinning
		propagator = full;
		unplace_piece(brd, source_square);
		propagator &= checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, N);
		}else{
			unsafe_place_piece(brd, source_square, n);
		}
		
		targets = empty;
		targets |= step_north(step_north(step_east(current_source)));
		targets |= step_north(step_north(step_west(current_source)));
		targets |= step_south(step_south(step_east(current_source)));
		targets |= step_south(step_south(step_west(current_source)));
		
		targets |= step_east(step_east(step_south(current_source)));
		targets |= step_east(step_east(step_north(current_source)));
		targets |= step_west(step_west(step_south(current_source)));
		targets |= step_west(step_west(step_north(current_source)));
		
		targets &= (~own) & propagator;
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}

inline int quiet_knight_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	BoardState bs = brd->board_state;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	
	bitboard targets, current_source, current_target, propagator;
	brdidx source_square, target_square;
	move mv;
	
	bitboard knights = own & (bs.n);
	while(knights){
		current_source = ls1b(knights);
		knights ^= current_source;
		source_square = greatest_square_index(current_source);
		
		// propagator takes care of pinning
		propagator = full;
		unplace_piece(brd, source_square);
		propagator &= checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, N);
		}else{
			unsafe_place_piece(brd, source_square, n);
		}
		
		targets = empty;
		targets |= step_north(step_north(step_east(current_source)));
		targets |= step_north(step_north(step_west(current_source)));
		targets |= step_south(step_south(step_east(current_source)));
		targets |= step_south(step_south(step_west(current_source)));
		
		targets |= step_east(step_east(step_south(current_source)));
		targets |= step_east(step_east(step_north(current_source)));
		targets |= step_west(step_west(step_south(current_source)));
		targets |= step_west(step_west(step_north(current_source)));
		
		targets &= unoccupied & propagator;
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}

inline int pawn_captures(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	BoardState bs = brd->board_state;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard potential_targets = opponent | get_enpassant_bitboard(brd);
	bitboard targets, current_source, pinboard, current_target;
	brdidx source_square, target_square;
	piece target_piece;
	moverecord rec;
	
	move mv;
	brdidx rank;
	brdidx end_rank;
	if(whites_turn){
		end_rank = 7;
	}else{
		end_rank = 0;
	}
	
	bitboard pawns = own & (bs.p);
	while(pawns){
		current_source = ls1b(pawns);
		pawns ^= current_source;
		source_square = greatest_square_index(current_source);
		
		// propagator takes care of pinning
		unplace_piece(brd, source_square);
		pinboard = checking_rays_intersection(brd, false);
		if(bs.enpassant != no_enpassant){
			pinboard |= get_enpassant_bitboard(brd);
		}
		if(whites_turn){
			unsafe_place_piece(brd, source_square, P);
		}else{
			unsafe_place_piece(brd, source_square, p);
		}
		
		targets = empty;
		if(whites_turn){
			targets |= ((step_northeast(current_source) | step_northwest(current_source)) & pinboard & potential_targets);
		}else{
			targets |= ((step_southeast(current_source) | step_southwest(current_source)) & pinboard & potential_targets);
		}
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			target_piece = brd->piece_map[target_square];
			rank = square_index_to_rank_index(target_square);
			if(rank == end_rank){
				if(whites_turn){
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = R;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = N;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = B;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = Q;
					moves[num_moves] = mv;
					num_moves++;
				}else{
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = r;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = n;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = b;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = q;
					moves[num_moves] = mv;
					num_moves++;
				}
			}else if(target_piece == ep || target_piece == EP){
				// check whether the en passant capture puts the king in check
				mv = move();
				mv.from_square = source_square;
				mv.to_square = target_square;
				mv.promotion = no;
				rec = make_move(brd, &mv);
				if(!player_check(brd, whites_turn)){
					moves[num_moves] = mv;
					num_moves++;
				}
				unmake_move(brd, &rec);
			}else{
				mv = move();
				mv.from_square = source_square;
				mv.to_square = target_square;
				mv.promotion = no;
				moves[num_moves] = mv;
				num_moves++;
			}
			
		}
	}
	return num_moves;
}

inline int all_pawn_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	BoardState bs = brd->board_state;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard potential_targets = opponent | get_enpassant_bitboard(brd);
	bitboard targets, current_source, current_target;
	bitboard pinboard;
	brdidx source_square, target_square;
	piece target_piece;
	moverecord rec;
	
	move mv;
	piece pc;
	brdidx rank;
	brdidx end_rank;
	if(whites_turn){
		end_rank = 7;
	}else{
		end_rank = 0;
	}
	
	bitboard pawns = own & (bs.p);
	while(pawns){
		current_source = ls1b(pawns);
		pawns ^= current_source;
		source_square = greatest_square_index(current_source);
		
		// take care of pinning
		pc = unplace_piece(brd, source_square);
		pinboard = checking_rays_intersection(brd, false);
		if(bs.enpassant != no_enpassant){
			pinboard |= get_enpassant_bitboard(brd);
		}
		unsafe_place_piece(brd, source_square, pc);
		targets = empty;
		if(whites_turn){
			// single step push
			targets |= (step_north(current_source) & unoccupied & pinboard);
			// double step push
			targets |= step_north(step_north(rank_2 & current_source)) & unoccupied & step_north(unoccupied) & pinboard;
			targets |= ((step_northeast(current_source) | step_northwest(current_source)) & pinboard & potential_targets);
		}else{
			// single step push
			targets |= (step_south(current_source) & unoccupied & pinboard);
			// double step push
			targets |= step_south(step_south(rank_7 & current_source)) & unoccupied & step_south(unoccupied) & pinboard;
			targets |= ((step_southeast(current_source) | step_southwest(current_source)) & pinboard & potential_targets);
		}
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			target_piece = brd->piece_map[target_square];
			rank = square_index_to_rank_index(target_square);
			if(rank == end_rank){
				if(whites_turn){
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = R;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = N;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = B;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = Q;
					moves[num_moves] = mv;
					num_moves++;
				}else{
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = r;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = n;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = b;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = q;
					moves[num_moves] = mv;
					num_moves++;
				}
			}else if(target_piece == ep || target_piece == EP){
				// check whether the en passant capture puts the king in check
				mv = move();
				mv.from_square = source_square;
				mv.to_square = target_square;
				mv.promotion = no;
				rec = make_move(brd, &mv);
				if(!player_check(brd, whites_turn)){
					moves[num_moves] = mv;
					num_moves++;
				}
				unmake_move(brd, &rec);
			}else{
				mv = move();
				mv.from_square = source_square;
				mv.to_square = target_square;
				mv.promotion = no;
				moves[num_moves] = mv;
				num_moves++;
			}
			
		}
	}
	return num_moves;
}

inline int quiet_pawn_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard targets, current_source, propagator, current_target;
	brdidx source_square, target_square;
	move mv;
	brdidx rank;
	brdidx end_rank;
	if(whites_turn){
		end_rank = 8;
	}else{
		end_rank = 1;
	}
	
	bitboard pawns = own & (brd->board_state.p);
	while(pawns){
		current_source = ls1b(pawns);
		pawns ^= current_source;
		source_square = greatest_square_index(current_source);
		
		// propagator takes care of pinning
		propagator = unoccupied;
		unplace_piece(brd, source_square);
		propagator &= checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, P);
		}else{
			unsafe_place_piece(brd, source_square, p);
		}
		
		targets = empty;
		if(whites_turn){
			// single step push
			targets |= (step_north(current_source) & propagator);
			// double step push
			targets |= step_north(step_north(rank_2 & current_source)) & propagator & step_north(propagator);
		}else{
			// single step push
			targets |= (step_south(current_source) & propagator);
			// double step push
			targets |= step_south(step_south(rank_7 & current_source)) & propagator & step_south(propagator);
		}
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			rank = square_index_to_rank_index(target_square);
			if(rank == end_rank){
				if(whites_turn){
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = P;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = R;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = N;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = B;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = Q;
					moves[num_moves] = mv;
					num_moves++;
				}else{
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = p;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = r;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = n;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = b;
					moves[num_moves] = mv;
					num_moves++;
					
					mv = move();
					mv.from_square = source_square;
					mv.to_square = target_square;
					mv.promotion = q;
					moves[num_moves] = mv;
					num_moves++;
				}
			}else{
				mv = move();
				mv.from_square = source_square;
				mv.to_square = target_square;
				mv.promotion = no;
				moves[num_moves] = mv;
				num_moves++;
			}
			
		}
	}
	return num_moves;
}

inline int bishop_captures(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard pinboard;
	bitboard bishops;
	bishops = own & brd->board_state.b;
	bitboard targets;
	bitboard current_target, current_source;
	brdidx target_square, source_square;
	bitboard tmp;
	
	move mv;
	while(bishops){
		current_source = ls1b(bishops);
		bishops &= (~current_source);
		source_square = greatest_square_index(current_source);
		
		// take care of pinning
		unplace_piece(brd, source_square);
		pinboard = checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, B);
		}else{
			unsafe_place_piece(brd, source_square, b);
		}
		
		targets = empty;
		tmp = slide_northeast(current_source, unoccupied);
		tmp = (step_northeast(tmp) & opponent);
		targets |= tmp;
		tmp = slide_northwest(current_source, unoccupied);
		tmp = (step_northwest(tmp) & opponent);
		targets |= tmp;
		tmp = slide_southwest(current_source, unoccupied);
		tmp = (step_southwest(tmp) & opponent);
		targets |= tmp;
		tmp = slide_southeast(current_source, unoccupied);
		tmp = (step_southeast(tmp) & opponent);
		targets |= tmp;
		targets &= (~current_source) & pinboard;
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}

inline int all_bishop_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard pinboard;
	bitboard bishops;
	bishops = own & brd->board_state.b;
	bitboard targets;
	bitboard current_target, current_source;
	brdidx target_square, source_square;
	bitboard tmp;
	
	move mv;
	while(bishops){
		current_source = ls1b(bishops);
		bishops &= (~current_source);
		source_square = greatest_square_index(current_source);
		
		// take care of pinning
		unplace_piece(brd, source_square);
		pinboard = checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, B);
		}else{
			unsafe_place_piece(brd, source_square, b);
		}
		targets = empty;
		tmp = slide_northeast(current_source, unoccupied);
		tmp |= (step_northeast(tmp) & opponent);
		targets |= tmp;
		tmp = slide_northwest(current_source, unoccupied);
		tmp |= (step_northwest(tmp) & opponent);
		targets |= tmp;
		tmp = slide_southwest(current_source, unoccupied);
		tmp |= (step_southwest(tmp) & opponent);
		targets |= tmp;
		tmp = slide_southeast(current_source, unoccupied);
		tmp |= (step_southeast(tmp) & opponent);
		targets |= tmp;
		targets &= (~current_source) & pinboard;
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}


inline int quiet_bishop_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard propagator;
	bitboard bishops;
	bishops = own & brd->board_state.b;
	bitboard targets;
	bitboard current_target, current_source;
	brdidx target_square, source_square;
	
	move mv;
	while(bishops){
		current_source = ls1b(bishops);
		bishops &= (~current_source);
		source_square = greatest_square_index(current_source);
		
		// propagator takes care of pinning
		propagator = unoccupied;
		unplace_piece(brd, source_square);
		propagator &= checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, B);
		}else{
			unsafe_place_piece(brd, source_square, b);
		}
		
		targets = empty;
		targets |= slide_northeast(current_source, propagator);
		targets |= slide_northwest(current_source, propagator);
		targets |= slide_southwest(current_source, propagator);
		targets |= slide_southeast(current_source, propagator);
		targets &= (~current_source);
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}

inline int rook_captures(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard pinboard;
	bitboard rooks;
	rooks = own & brd->board_state.r;
	bitboard targets;
	bitboard current_target, current_source;
	brdidx target_square, source_square;
	bitboard tmp;
	
	move mv;
	while(rooks){
		current_source = ls1b(rooks);
		rooks &= (~current_source);
		source_square = greatest_square_index(current_source);
		
		// take care of pinning
		unplace_piece(brd, source_square);
		pinboard = checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, R);
		}else{
			unsafe_place_piece(brd, source_square, r);
		}
		
		targets = empty;
		tmp = slide_east(current_source, unoccupied);
		tmp = (step_east(tmp) & opponent);
		targets |= tmp;
		tmp = slide_north(current_source, unoccupied);
		tmp = (step_north(tmp) & opponent);
		targets |= tmp;
		tmp = slide_west(current_source, unoccupied);
		tmp = (step_west(tmp) & opponent);
		targets |= tmp;
		tmp = slide_south(current_source, unoccupied);
		tmp = (step_south(tmp) & opponent);
		targets |= tmp;
		targets &= (~current_source) & pinboard;
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}

inline int all_rook_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard pinboard;
	bitboard rooks;
	rooks = own & brd->board_state.r;
	bitboard targets;
	bitboard current_target, current_source;
	brdidx target_square, source_square;
	bitboard tmp;
	
	move mv;
	while(rooks){
		current_source = ls1b(rooks);
		rooks &= (~current_source);
		source_square = greatest_square_index(current_source);
		
		// take care of pinning
		unplace_piece(brd, source_square);
		pinboard = checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, R);
		}else{
			unsafe_place_piece(brd, source_square, r);
		}
		
		targets = empty;
		tmp = slide_east(current_source, unoccupied);
		tmp |= (step_east(tmp) & opponent);
		targets |= tmp;
		tmp = slide_north(current_source, unoccupied);
		tmp |= (step_north(tmp) & opponent);
		targets |= tmp;
		tmp = slide_west(current_source, unoccupied);
		tmp |= (step_west(tmp) & opponent);
		targets |= tmp;
		tmp = slide_south(current_source, unoccupied);
		tmp |= (step_south(tmp) & opponent);
		targets |= tmp;
		targets &= (~current_source) & pinboard;
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}


inline int quiet_rook_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard propagator;
	bitboard rooks;
	rooks = own & brd->board_state.r;
	bitboard targets;
	bitboard current_target, current_source;
	brdidx target_square, source_square;
	
	move mv;
	while(rooks){
		current_source = ls1b(rooks);
		rooks &= (~current_source);
		source_square = greatest_square_index(current_source);
		
		// propagator takes care of pinning
		propagator = unoccupied;
		unplace_piece(brd, source_square);
		propagator &= checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, R);
		}else{
			unsafe_place_piece(brd, source_square, r);
		}
		
		targets = empty;
		targets |= slide_east(current_source, propagator);
		targets |= slide_north(current_source, propagator);
		targets |= slide_west(current_source, propagator);
		targets |= slide_south(current_source, propagator);
		targets &= (~current_source);
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}

inline int queen_captures(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard pinboard;
	bitboard queens;
	queens = own & brd->board_state.q;
	bitboard targets;
	bitboard current_target, current_source;
	brdidx target_square, source_square;
	bitboard tmp;
	
	move mv;
	while(queens){
		current_source = ls1b(queens);
		queens &= (~current_source);
		source_square = greatest_square_index(current_source);
		
		// take care of pinning
		unplace_piece(brd, source_square);
		pinboard = checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, Q);
		}else{
			unsafe_place_piece(brd, source_square, q);
		}
		
		targets = empty;
		tmp = slide_east(current_source, unoccupied);
		tmp = (step_east(tmp) & opponent);
		targets |= tmp;
		tmp = slide_northeast(current_source, unoccupied);
		tmp = (step_northeast(tmp) & opponent);
		targets |= tmp;
		tmp = slide_north(current_source, unoccupied);
		tmp = (step_north(tmp) & opponent);
		targets |= tmp;
		tmp = slide_northwest(current_source, unoccupied);
		tmp = (step_northwest(tmp) & opponent);
		targets |= tmp;
		tmp = slide_west(current_source, unoccupied);
		tmp = (step_west(tmp) & opponent);
		targets |= tmp;
		tmp = slide_southwest(current_source, unoccupied);
		tmp = (step_southwest(tmp) & opponent);
		targets |= tmp;
		tmp = slide_south(current_source, unoccupied);
		tmp = (step_south(tmp) & opponent);
		targets |= tmp;
		tmp = slide_southeast(current_source, unoccupied);
		tmp = (step_southeast(tmp) & opponent);
		targets |= tmp;
		targets &= (~current_source) & pinboard;
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}

inline int all_queen_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard own = get_player_bitboard(brd, whites_turn);
	bitboard opponent = get_player_bitboard(brd, !whites_turn);
	bitboard unoccupied = ~(own | opponent);
	bitboard pinboard;
	bitboard queens;
	queens = own & brd->board_state.q;
	bitboard targets;
	bitboard current_target, current_source;
	brdidx target_square, source_square;
	bitboard tmp;
	
	move mv;
	while(queens){
		current_source = ls1b(queens);
		queens &= (~current_source);
		source_square = greatest_square_index(current_source);
		
		// take care of pinning
		unplace_piece(brd, source_square);
		pinboard = checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, Q);
		}else{
			unsafe_place_piece(brd, source_square, q);
		}
		
		targets = empty;
		tmp = slide_east(current_source, unoccupied);
		tmp |= (step_east(tmp) & opponent);
		targets |= tmp;
		tmp = slide_northeast(current_source, unoccupied);
		tmp |= (step_northeast(tmp) & opponent);
		targets |= tmp;
		tmp = slide_north(current_source, unoccupied);
		tmp |= (step_north(tmp) & opponent);
		targets |= tmp;
		tmp = slide_northwest(current_source, unoccupied);
		tmp |= (step_northwest(tmp) & opponent);
		targets |= tmp;
		tmp = slide_west(current_source, unoccupied);
		tmp |= (step_west(tmp) & opponent);
		targets |= tmp;
		tmp = slide_southwest(current_source, unoccupied);
		tmp |= (step_southwest(tmp) & opponent);
		targets |= tmp;
		tmp = slide_south(current_source, unoccupied);
		tmp |= (step_south(tmp) & opponent);
		targets |= tmp;
		tmp = slide_southeast(current_source, unoccupied);
		tmp |= (step_southeast(tmp) & opponent);
		targets |= tmp;
		targets &= (~current_source) & pinboard;
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves ++;
		}
	}
	return num_moves;
}


inline int quiet_queen_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	bitboard unoccupied = ~(brd->board_state.white | brd->board_state.black);
	bitboard propagator;
	bitboard queens;
	if(whites_turn){
		queens = brd->board_state.white & brd->board_state.q;
	}else{
		queens = brd->board_state.black & brd->board_state.q;
	}
	bitboard targets;
	bitboard current_target, current_source;
	brdidx target_square, source_square;
	
	move mv;
	while(queens){
		current_source = ls1b(queens);
		queens &= (~current_source);
		source_square = greatest_square_index(current_source);
		
		// propagator takes care of pinning
		propagator = unoccupied;
		unplace_piece(brd, source_square);
		propagator &= checking_rays_intersection(brd, false);
		if(whites_turn){
			unsafe_place_piece(brd, source_square, Q);
		}else{
			unsafe_place_piece(brd, source_square, q);
		}
		
		targets = empty;
		targets |= slide_east(current_source, propagator);
		targets |= slide_northeast(current_source, propagator);
		targets |= slide_north(current_source, propagator);
		targets |= slide_northwest(current_source, propagator);
		targets |= slide_west(current_source, propagator);
		targets |= slide_southwest(current_source, propagator);
		targets |= slide_south(current_source, propagator);
		targets |= slide_southeast(current_source, propagator);
		targets &= (~current_source);
		
		while(targets){
			current_target = ls1b(targets);
			targets &= (~current_target);
			target_square = greatest_square_index(current_target);
			mv = move();
			mv.from_square = source_square;
			mv.to_square = target_square;
			mv.promotion = no;
			moves[num_moves] = mv;
			num_moves++;
		}
	}
	return num_moves;
}

inline int all_captures(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	num_moves += king_captures(brd, moves + num_moves, whites_turn);
	num_moves += queen_captures(brd, moves + num_moves, whites_turn);
	num_moves += bishop_captures(brd, moves + num_moves, whites_turn);
	num_moves += rook_captures(brd, moves + num_moves, whites_turn);
	num_moves += pawn_captures(brd, moves + num_moves, whites_turn);
	num_moves += knight_captures(brd, moves + num_moves, whites_turn);
	return num_moves;
}

inline int all_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	num_moves += all_king_moves(brd, moves + num_moves, whites_turn);
	num_moves += all_queen_moves(brd, moves + num_moves, whites_turn);
	num_moves += all_bishop_moves(brd, moves + num_moves, whites_turn);
	num_moves += all_rook_moves(brd, moves + num_moves, whites_turn);
	num_moves += all_pawn_moves(brd, moves + num_moves, whites_turn);
	num_moves += all_knight_moves(brd, moves + num_moves, whites_turn);
	return num_moves;
}

inline int all_quiet_moves(GameState *brd, move *moves, bool whites_turn){
	int num_moves = 0;
	num_moves += quiet_king_moves(brd, moves + num_moves, whites_turn);
	num_moves += quiet_queen_moves(brd, moves + num_moves, whites_turn);
	num_moves += quiet_bishop_moves(brd, moves + num_moves, whites_turn);
	num_moves += quiet_rook_moves(brd, moves + num_moves, whites_turn);
	num_moves += quiet_pawn_moves(brd, moves + num_moves, whites_turn);
	num_moves += quiet_knight_moves(brd, moves + num_moves, whites_turn);
	return num_moves;
}

unsigned long long perft(GameState *brd, int depth);

inline int piece_to_zobrist_index(piece pc){
	switch(pc){
		case K:
			return(0);
		case k:
			return(1);
		case Q:
			return(2);
		case q:
			return(3);
		case B:
			return(4);
		case b:
			return(5);
		case N:
			return(6);
		case n:
			return(7);
		case R:
			return(8);
		case r:
			return(9);
		case P:
			return(10);
		case p:
			return(11);
		case EP:
			return(12);
		case ep:
			return(13);
	}
}

inline int piece_to_search_order(piece pc){
	// Higher means more valuable
	// Start with low attacking high
	switch(pc){
		case K:
			return(6);
		case k:
			return(6);
		case Q:
			return(5);
		case q:
			return(5);
		case B:
			return(3);
		case b:
			return(3);
		case N:
			return(2);
		case n:
			return(2);
		case R:
			return(4);
		case r:
			return(4);
		case P:
			return(1);
		case p:
			return(1);
		case EP:
			return(1);
		case ep:
			return(1);
		case no:
			return(0);
	}
}



typedef struct {
	// If it's not a lower_bound then it's exact.
	// If lower_bound, the negamax call that returned this
	// result returned a lower bound from its perspective.
	// From the caller's perspective this is an 
	// upper bound and the value is negative value.
	double value;
	bool lower_bound;
	bool upper_bound;
} negamax_result;

inline bool operator==(const negamax_result& lhs, const negamax_result& rhs){
	if(lhs.value == rhs.value && lhs.lower_bound == rhs.lower_bound){
		return true;
	} else {
		return false;
	}
}

class MoveHistoryTable {
	public:
		MoveHistoryTable();
		bool compare_moves(move &lhs, move &rhs);
		void setitem(move mv, double value, double strength);
		std::tuple<double, double> getitem(move mv);
	private:
		std::tuple<double, double> data[64][64];
};

typedef struct {
	zobrist_int key;
	double strength;
	negamax_result value;
	move best_move;
	BoardState brd;
} transposition_entry;

extern const transposition_entry empty_transposition_entry;

inline bool operator==(const transposition_entry& lhs, const transposition_entry& rhs){
	if (lhs.key == rhs.key && lhs.strength == rhs.strength && lhs.value == rhs.value &&
	    lhs.best_move == rhs.best_move){
		return true;
	} else {
		return false;
	}
}

#endif
