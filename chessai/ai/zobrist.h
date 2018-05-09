#ifndef ZOBRIST_H
#define ZOBRIST_H

#include "bitboardlib.h"
#include <boost/multiprecision/cpp_int.hpp>

typedef uint64_t zobrist_int;

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

#endif
