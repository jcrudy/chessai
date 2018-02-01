#ifndef BITBOARDLIB_H
#define BITBOARDLIB_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

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
	bitboard result = 1;
	return(result << i);
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
	brdidx from;
	brdidx to;
} move;

typedef struct {
	piece captured;
	bool lost_castle_king;
	bool lost_castle_queen;
} moverecord;

/*
inline moverecord make_move(boardstate *brd, move *mv){
	
}
*/

inline uint8_t get_enpassant(boardstate *bs){
	return(bs->enpassant);
}

inline void set_enpassant(boardstate *bs, uint8_t pos){
	bs->enpassant = pos;
};

inline unsigned int get_halfmove_clock(boardstate *bs){
	return(bs->halfmove_clock);
};

inline void set_halfmove_clock(boardstate *bs, unsigned int n){
	bs->halfmove_clock = n;
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
	return(bs->white_castle_king);
};

inline void set_black_castle_king(boardstate *bs){
	bs->white_castle_king = true;
};

inline void unset_black_castle_king(boardstate *bs){
	bs->white_castle_king = false;
};

inline bool get_black_castle_queen(boardstate *bs){
	return(bs->white_castle_queen);
};

inline void set_black_castle_queen(boardstate *bs){
	bs->white_castle_queen = true;
};

inline void unset_black_castle_queen(boardstate *bs){
	bs->white_castle_queen = false;
};



inline bool get_whites_turn(boardstate *bs){
	return(bs->whites_turn);
};

inline void set_whites_turn(boardstate *bs){
	bs->whites_turn = true;
};

inline void unset_whites_turn(boardstate *bs){
	bs->whites_turn = false;
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

void bitboard_to_arr(boardstate *bb, char* arr);



#endif
