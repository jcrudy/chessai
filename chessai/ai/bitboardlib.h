#ifndef BITBOARDLIB_H
#define BITBOARDLIB_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <queue>
#include <string>

typedef uint64_t bitboard;

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
	std::string str2 = std::string();
	for(int j=1; j<=8; j++){
		str2 += str.substr(64 - 8*j, 8);
		if(j<8){
			str2.push_back(10);
		}
	}
	return str2.c_str();
}

inline brdidx square_index_to_file_index(brdidx i){
	return(i % 8);
}

inline brdidx square_index_to_rank_index(brdidx i){
	return(i / 8);
}

inline brdidx square_index_to_diag_index(brdidx i){
	return(square_index_to_rank_index(i) - square_index_to_file_index(i));
}

inline brdidx square_index_to_antidiag_index(brdidx i){
	return(square_index_to_rank_index(i) + square_index_to_file_index(i) - 7);
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

inline bitboard compute_queen_moves_from_square_index(brdidx s){
	bitboard rank, file, diag, antidiag;
	rank = square_index_to_rank_index(s);
	file = square_index_to_file_index(s);
	diag = square_index_to_diag_index(s);
	antidiag = square_index_to_antidiag_index(s);
	return(ranks[rank] | files[file] | diags[diag] | antidiags[antidiag]);
}

// TODO: replace with lookup
inline bitboard queen_moves_from_square_index(brdidx s){
	return(compute_queen_moves_from_square_index(s));
}

inline bitboard compute_rook_moves_from_square_index(brdidx s){
	bitboard rank, file;
	rank = square_index_to_rank_index(s);
	file = square_index_to_file_index(s);
	return(ranks[rank] | files[file]);
}

// TODO: replace with lookup
inline bitboard rook_moves_from_square_index(brdidx s){
	return(compute_rook_moves_from_square_index(s));
}

inline bitboard compute_bishop_moves_from_square_index(brdidx s){
	bitboard diag, antidiag;
	diag = square_index_to_diag_index(s);
	antidiag = square_index_to_antidiag_index(s);
	return(diags[diag] | antidiags[antidiag]);
}

// TODO: replace with lookup
inline bitboard bishop_moves_from_square_index(brdidx s){
	return(compute_bishop_moves_from_square_index(s));
}

inline bitboard step_north(bitboard b){
	return(b << 8);
}

inline bitboard step_south(bitboard b){
	return(b >> 8);
}

inline bitboard step_east(bitboard b){
	return((b << 1) & (~file_a));
}

inline bitboard step_west(bitboard b){
	return((b >> 1) & (~file_h));
}

inline bitboard step_northwest(bitboard b){
	return((b << 9) & (~file_a));
}

inline bitboard step_northeast(bitboard b){
	return((b << 7) & (~file_a));
}

inline bitboard step_southwest(bitboard b){
	return((b >> 7) & (~file_h));
}

inline bitboard step_southeast(bitboard b){
	return((b >> 9) & (~file_h));
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

typedef enum {no=0,K,Q,B,N,R,P,EP,k,q,b,n,r,p,ep} piece;

typedef struct {
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
	unsigned int halfmove_clock;
	unsigned int fullmove_counter;
	piece piece_map[64];
} boardstate;


inline piece piece_from_square_index(boardstate *bs, brdidx square_index){
	// May return no (=0), meaning not occupied.  Check for this before using the piece.
	return(bs->piece_map[square_index]);
}

inline void unsafe_place_piece(boardstate *bs, brdidx square_index, piece pc){
	bitboard bb = bitboard_from_square_index(square_index);
	(bs->piece_map)[square_index] = pc;
	switch(pc){
		case K:
			(bs->k) |= bb;
			(bs->white) |= bb;
			break;
		case k:
			(bs->k) |= bb;
			(bs->black) |= bb;
			break;
		case Q:
			(bs->q) |= bb;
			(bs->white) |= bb;
			break;
		case q:
			(bs->q) |= bb;
			(bs->black) |= bb;
			break;
		case B:
			(bs->b) |= bb;
			(bs->white) |= bb;
			break;
		case b:
			(bs->b) |= bb;
			(bs->black) |= bb;
			break;
		case N:
			(bs->n) |= bb;
			(bs->white) |= bb;
			break;
		case n:
			(bs->n) |= bb;
			(bs->black) |= bb;
			break;
		case R:
			(bs->r) |= bb;
			(bs->white) |= bb;
			break;
		case r:
			(bs->r) |= bb;
			(bs->black) |= bb;
			break;
		case P:
			(bs->p) |= bb;
			(bs->white) |= bb;
			break;
		case p:
			(bs->p) |= bb;
			(bs->black) |= bb;
			break;
		case EP:
			(bs->enpassant) = square_index;
			break;
		case ep:
			(bs->enpassant) = square_index;
			break;
		case no:
			{}
	}
}

inline void unplace_piece(boardstate *bs, brdidx square_index){
	bitboard bb = ~bitboard_from_square_index(square_index);
	piece pc = (bs->piece_map)[square_index];
	bs->piece_map[square_index] = no;
	switch(pc){
		case K:
			(bs->k) &= bb;
			(bs->white) &= bb;
			break;
		case k:
			(bs->k) &= bb;
			(bs->black) &= bb;
			break;
		case Q:
			(bs->q) &= bb;
			(bs->white) &= bb;
			break;
		case q:
			(bs->q) &= bb;
			(bs->black) &= bb;
			break;
		case B:
			(bs->b) &= bb;
			(bs->white) &= bb;
			break;
		case b:
			(bs->b) &= bb;
			(bs->black) &= bb;
			break;
		case N:
			(bs->n) &= bb;
			(bs->white) &= bb;
			break;
		case n:
			(bs->n) &= bb;
			(bs->black) &= bb;
			break;
		case R:
			(bs->r) &= bb;
			(bs->white) &= bb;
			break;
		case r:
			(bs->r) &= bb;
			(bs->black) &= bb;
			break;
		case P:
			(bs->p) &= bb;
			(bs->white) &= bb;
			break;
		case p:
			(bs->p) &= bb;
			(bs->black) &= bb;
			break;
		case EP:
			(bs->enpassant) = no_enpassant;
			break;
		case ep:
			(bs->enpassant) = no_enpassant;
			break;
		case no:
			{}
	}
}

inline void place_piece(boardstate *bs, brdidx square_index, piece pc){
	unplace_piece(bs, square_index);
	unsafe_place_piece(bs, square_index, pc);
}

inline bitboard piece_bitboard_from_piece(boardstate *bs, piece pc){
	switch(pc){
		case K:
			return(bs->k);
		case k:
			return(bs->k);
		case Q:
			return(bs->q);
		case q:
			return(bs->q);
		case B:
			return(bs->b);
		case b:
			return(bs->b);
		case N:
			return(bs->n);
		case n:
			return(bs->n);
		case R:
			return(bs->r);
		case r:
			return(bs->r);
		case P:
			return(bs->p);
		case p:
			return(bs->p);
		case EP:
			return(bitboard_from_square_index(bs->enpassant));
		case ep:
			return(bitboard_from_square_index(bs->enpassant));
		case no:
			return(empty);
	}
}

inline bitboard color_bitboard_from_piece(boardstate *bs, piece pc){
	switch(pc){
		case K:
			return(bs->white);
		case k:
			return(bs->black);
		case Q:
			return(bs->white);
		case q:
			return(bs->black);
		case B:
			return(bs->white);
		case b:
			return(bs->black);
		case N:
			return(bs->white);
		case n:
			return(bs->black);
		case R:
			return(bs->white);
		case r:
			return(bs->black);
		case P:
			return(bs->white);
		case p:
			return(bs->black);
		case EP:
			return(bs->white);
		case ep:
			return(bs->black);
		case no:
			return(empty);
	}
}

inline bitboard bitboard_from_piece(boardstate *bs, piece pc){
	return(piece_bitboard_from_piece(bs, pc) & color_bitboard_from_piece(bs, pc));
}

extern const boardstate emptyboardstate;

typedef struct {
	brdidx from_square;
	brdidx to_square;
	piece promotion;
} move;

typedef struct {
	piece captured;
	bool lost_castle_king;
	bool lost_castle_queen;
	brdidx enpassant;
	int previous_halfmove_clock;
	brdidx from_square;
	brdidx to_square;
	piece promoted_from;
} moverecord;

inline uint8_t get_enpassant(boardstate *bs){
	return(bs->enpassant);
}

inline void set_enpassant(boardstate *bs, uint8_t pos){
	// Should be called before flip_turn
	bs->enpassant = pos;
	if(bs->whites_turn){
		(bs->piece_map)[pos] = EP;
	}else{
		(bs->piece_map)[pos] = ep;
	}
};

inline unsigned int get_halfmove_clock(boardstate *bs){
	return(bs->halfmove_clock);
};

inline void set_halfmove_clock(boardstate *bs, unsigned int n){
	(bs->halfmove_clock) = n;
};

inline unsigned int get_fullmove_counter(boardstate *bs){
	return(bs->fullmove_counter);
};

inline void set_fullmove_counter(boardstate *bs, unsigned int n){
	bs->fullmove_counter = n;
};

inline bool get_white_castle_king(boardstate *bs){
	return(bs->white_castle_king);
};

inline void set_white_castle_king(boardstate *bs){
	bs->white_castle_king = true;
};

inline void unset_white_castle_king(boardstate *bs){
	bs->white_castle_king = false;
};

inline bool get_white_castle_queen(boardstate *bs){
	return(bs->white_castle_queen);
};

inline void set_white_castle_queen(boardstate *bs){
	bs->white_castle_queen = true;
};

inline void unset_white_castle_queen(boardstate *bs){
	bs->white_castle_queen = false;
};

inline bool get_black_castle_king(boardstate *bs){
	return(bs->black_castle_king);
};

inline void set_black_castle_king(boardstate *bs){
	bs->black_castle_king = true;
};

inline void unset_black_castle_king(boardstate *bs){
	bs->black_castle_king = false;
};

inline bool get_black_castle_queen(boardstate *bs){
	return(bs->black_castle_queen);
};

inline void set_black_castle_queen(boardstate *bs){
	bs->black_castle_queen = true;
};

inline void unset_black_castle_queen(boardstate *bs){
	(bs->black_castle_queen) = false;
};

inline void flip_turn(boardstate *bs){
	(bs->whites_turn) = !(bs->whites_turn);
}

inline bool get_whites_turn(boardstate *bs){
	return(bs->whites_turn);
};

inline void set_whites_turn(boardstate *bs){
	(bs->whites_turn) = true;
};

inline void unset_whites_turn(boardstate *bs){
	(bs->whites_turn) = false;
};

inline bool get_blacks_turn(boardstate *bs){
	return(~get_whites_turn(bs));
};

inline void set_blacks_turn(boardstate *bs){
	unset_whites_turn(bs);
};

inline void unset_blacks_turn(boardstate *bs){
	set_whites_turn(bs);
};

inline bitboard get_current_movers_bitboard(boardstate *bs){
	if(get_whites_turn(bs)){
		return(bs->white);
	}else{
		return(bs->black);
	}
}

inline bitboard get_opposing_movers_bitboard(boardstate *bs){
	if(get_whites_turn(bs)){
		return(bs->black);
	}else{
		return(bs->white);
	}
}

inline void increment_fullmove_counter(boardstate *bs){
	(bs->fullmove_counter)++;
}

inline void decrement_fullmove_counter(boardstate *bs){
	(bs->fullmove_counter)--;
}

inline void increment_halfmove_clock(boardstate *bs){
	(bs->halfmove_clock)++;
}

inline void reset_halfmove_clock(boardstate *bs){
	(bs->halfmove_clock) = 0;
}

inline void unmake_move(boardstate *brd, moverecord *mv){
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
	set_halfmove_clock(brd, mv->previous_halfmove_clock);
	
	// fulllmove counter and castle rights
	if(brd->whites_turn){
		if(mv->lost_castle_king){
			set_white_castle_king(brd);
		}
		if(mv->lost_castle_queen){
			set_white_castle_queen(brd);
		}
	}else{
		decrement_fullmove_counter(brd);
		if(mv->lost_castle_king){
			set_black_castle_king(brd);
		}
		if(mv->lost_castle_queen){
			set_black_castle_queen(brd);
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
	
}

inline moverecord make_move(boardstate *brd, move *mv){
	piece from_piece, to_piece;
	bool lost_castle_king = false;
	bool lost_castle_queen = false;
	from_piece = brd->piece_map[mv->from_square];
	to_piece = brd->piece_map[mv->to_square];
	brdidx old_enpassant = brd->enpassant;

	// check for castle loss
	switch(from_piece){
		case K:
			lost_castle_king = get_white_castle_king(brd);
			lost_castle_queen = get_white_castle_queen(brd);
			break;
		case R:
			if((mv->from_square) == 7){
				lost_castle_king = get_white_castle_king(brd);
				lost_castle_queen = false;
			}
			if((mv->from_square) == 0){
				lost_castle_queen = get_white_castle_queen(brd);
				lost_castle_king = false;
			}
			break;
		case k:
			lost_castle_king = get_black_castle_king(brd);
			lost_castle_queen = get_black_castle_queen(brd);
			break;
		case r:
			if((mv->from_square) == 63){
				lost_castle_king = get_black_castle_king(brd);
				lost_castle_queen = false;
			}
			if((mv->from_square) == 55){
				lost_castle_queen = get_black_castle_queen(brd);
				lost_castle_king = false;
			}
			break;
		default:
			break;

	}// end check for castle loss

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
	if(to_piece==ep){
		//remove black pawn for en_passant capture
		unplace_piece(brd, (mv->to_square) - 8);
	}else if(to_piece==EP){
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
	set_enpassant(brd, new_enpassant);
	if(brd->whites_turn){
		if(lost_castle_king){
			unset_white_castle_king(brd);
		}
		if(lost_castle_queen){
			unset_white_castle_queen(brd);
		}
	}else{
		increment_fullmove_counter(brd);
		if(lost_castle_king){
			unset_black_castle_king(brd);
		}
		if(lost_castle_queen){
			unset_black_castle_queen(brd);
		}
	}
	int previous_halfmove_clock = get_halfmove_clock(brd);
	if((to_piece != no) || (from_piece == p) || (from_piece == P)){
		reset_halfmove_clock(brd);
	}else{
		increment_halfmove_clock(brd);
	}
	
	// check for promotion
	if (mv->promotion != no){
		unplace_piece(brd, mv->to_square);
		place_piece(brd, mv->to_square, mv->promotion);
	}
	
	// Take turns, people
	flip_turn(brd);
	
	// Remember what we did
	moverecord record = {to_piece, lost_castle_king, lost_castle_queen,
						 old_enpassant, previous_halfmove_clock, 
						 mv->from_square, mv->to_square, from_piece};
	return(record);
}

inline bitboard checking_rays_intersection(boardstate *brd){
	// Return the intersection of all rays by which the current mover's king is in check
	// by sliding pieces.  If no such rays, return the set of all squares (the empty intersection).
	bitboard king_board = brd->k & get_current_movers_bitboard(brd);
	bitboard all_but_king_prop = ~((brd->white | brd->black) & (~(brd->k)));
	brdidx king_square = greatest_square_index(king_board);
	brdidx king_rank = square_index_to_rank_index(king_square);
	//brdidx king_file = square_index_to_file_index(king_square);
	brdidx king_diag = square_index_to_diag_index(king_square);
	//brdidx king_antidiag = square_index_to_antidiag_index(king_square);
	
	bitboard result = full;
	bitboard slide;
	bitboard current_attacker;
	brdidx current_attacker_square;
	brdidx attacker_file, attacker_rank, attacker_diag, attacker_antidiag;
	bitboard attackers;
	
	// Check for attacking rooks and queens
	attackers = rook_moves_from_square_index(king_square) & get_opposing_movers_bitboard(brd) & (brd->r | brd->q);
	while(attackers){
		current_attacker = ls1b(attackers);
		attackers &= ~current_attacker;
		current_attacker_square = greatest_square_index(current_attacker);
		attacker_rank = square_index_to_rank_index(current_attacker_square);
		attacker_file = square_index_to_file_index(current_attacker_square);
		if(current_attacker < king_board){
			if(king_rank == attacker_rank){
				slide = slide_east(current_attacker, all_but_king_prop);
				if(slide & king_board){
					result &= slide;
				}
			}else{//king_file == attacker_file
				slide = slide_north(current_attacker, all_but_king_prop);
				if(slide & king_board){
					result &= slide;
				}
			}
		}else{//current_attacker > king_board
			if(king_rank == attacker_rank){
				slide = slide_west(current_attacker, all_but_king_prop);
				if(slide & king_board){
					result &= slide;
				}
			}else{//king_file == attacker_file
				slide = slide_south(current_attacker, all_but_king_prop);
				if(slide & king_board){
					result &= slide;
				}
			}
		}
	}
	// Check for attacking bishops and queens
	attackers = bishop_moves_from_square_index(king_square) & get_opposing_movers_bitboard(brd) & (brd->r | brd->q);
	while(attackers){
		current_attacker = ls1b(attackers);
		attackers &= ~current_attacker;
		current_attacker_square = greatest_square_index(current_attacker);
		attacker_diag = square_index_to_diag_index(current_attacker_square);
		attacker_antidiag = square_index_to_antidiag_index(current_attacker_square);
		if(current_attacker < king_board){
			if(king_diag == attacker_diag){
				slide = slide_northeast(current_attacker, all_but_king_prop);
				if(slide & king_board){
					result &= slide;
				}
			}else{//king_antidiag == attacker_antidiag
				slide = slide_northwest(current_attacker, all_but_king_prop);
				if(slide & king_board){
					result &= slide;
				}
			}
		}else{//current_attacker > king_board
			if(king_diag == attacker_diag){
				slide = slide_southeast(current_attacker, all_but_king_prop);
				if(slide & king_board){
					result &= slide;
				}
			}else{//king_antidiag == attacker_antidiag
				slide = slide_southeast(current_attacker, all_but_king_prop);
				if(slide & king_board){
					result &= slide;
				}
			}
		}
	if(result == king_board){
		break;
	}
	}
	return(result);
}


inline void quiet_queen_moves(boardstate *brd, std::queue<move> &moves){
	bitboard unoccupied = ~(brd->white | brd->black);
	bitboard propagator;
	bitboard queens;
	if(get_whites_turn(brd)){
		queens = brd->white & brd->q;
	}else{
		queens = brd->black & brd->q;
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
		propagator &= checking_rays_intersection(brd);
		if(get_whites_turn(brd)){
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
			moves.push(mv);
		}
	}
}


void bitboard_to_arr(boardstate *bb, char* arr);


#endif
