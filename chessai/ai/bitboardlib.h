#ifndef BITBOARDLIB_H
#define BITBOARDLIB_H

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t bitboard;
typedef uint8_t stateflags;

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

extern const stateflags empty_flags;
extern const stateflags white_castle_king_mask;
extern const stateflags white_castle_queen_mask;
extern const stateflags black_castle_king_mask;
extern const stateflags black_castle_queen_mask;
extern const stateflags turn_mask;

inline bitboard place(bitboard b, int p){
	return (b | places[p]);
}

typedef struct {
	bitboard k;
	bitboard q;
	bitboard b;
	bitboard n;
	bitboard r;
	bitboard p;
	bitboard white;
	bitboard black;
	uint8_t enpassant;
	bool whites_turn;
	bool white_castle_king;
	bool white_castle_queen;
	bool black_castle_king;
	bool black_castle_queen;
	unsigned int halfmove_clock;
	unsigned int fullmove_counter;
} boardstate;

extern const boardstate emptyboardstate;

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
