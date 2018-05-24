#ifndef MOVESEARCH_H_
#define MOVESEARCH_H_
#include "bitboardlib.h"
#include <chrono>
#include <thread>

template <typename ElementType>
class MoveTable{
	public:
		MoveTable(){
			this->initialize(0);
		}
		void initialize(int num_best){
			this->num_best = num_best;
			if(num_best>0){
				best_scores = new ElementType[num_best]();
				best_moves = new move[num_best]();
			}
		}
		MoveTable(int num_best) : MoveTable(){
			this->initialize(num_best);
		}
		~MoveTable(){
			if(num_best>0){
				delete[] best_scores;
				delete[] best_moves;
			}
		}
		void add(move &mv, ElementType amount){
			elements[mv.from_square][mv.to_square] += amount;
			ElementType current = elements[mv.from_square][mv.to_square];
			for(int i=0;i<num_best;i++){
				if(current > best_scores[i]){
					for(int j=0;j<i;j++){
						best_scores[j] = best_scores[j+1];
						best_moves[j] = best_moves[j+1];
					}
					best_moves[i] = mv;
					best_scores[i] = current;
				}
			}
		}
		void set(move &mv, ElementType amount){
			elements[mv.from_square][mv.to_square] = amount;
			ElementType current = elements[mv.from_square][mv.to_square];
			for(int i=0;i<num_best;i++){
				if(current > best_scores[i]){
					for(int j=0;j<i;j++){
						best_scores[j] = best_scores[j+1];
						best_moves[j] = best_moves[j+1];
					}
					best_moves[i] = mv;
					best_scores[i] = current;
				}
			}
		}
		int rank(move &mv){

			int rank = -1;

			for(int i=0;i<num_best;i++){
				if(mv == best_moves[i]){
					rank = i;
					break;
				}
			}
			return rank;
		}
		ElementType get(move &mv){
			return elements[mv.from_square][mv.to_square];
		}
		void reset(ElementType amount){
			for(int i=0;i<64;i++){
				for(int j=0;j<64;j++){
					elements[i][j] = amount;
				}
			}
			for(int i=0;i<num_best;i++){
				best_scores[i] = amount;
			}
		}
		void increment(ElementType amount){
			for(int i=0;i<64;i++){
				for(int j=0;j<64;j++){
					elements[i][j] += amount;
				}
			}
			for(int i=0;i<num_best;i++){
				best_scores[i] += amount;
			}
		}
		int num_best;
	private:
		ElementType elements[64][64];
		ElementType *best_scores;
		move *best_moves;
};

struct AlphaBetaValue{
	// In alpha-beta search, treat alpha and beta as inclusive (closed) bounds.
	// If fail_low, value is a closed upper bound.
	// If fail_high, value is a closed lower bound.
	// Note that these are fail-soft values.
	int ply;
	int value;
	move best_move;
	AlphaBetaValue(){
		ply = 0;
		value = 0;
		move best_move = nomove;
	}
	bool operator==(const AlphaBetaValue &other) const{
		if(ply == other.ply && value == other.value && best_move == other.best_move){
			return true;
		}else{
			return false;
		}
	}
};
extern const AlphaBetaValue empty_alpha_beta_value;


struct TranspositionEntry{
	zobrist_int key;
	int depth;
	bool fail_low;
	bool fail_high;
	int halfmove_clock;
	BoardState brd;
	AlphaBetaValue value;
	TranspositionEntry(){
		this->key = 0;
		this->depth = 0;
		this->fail_low = false;
		this->fail_high = false;
		this->halfmove_clock = 0;
		this->value = empty_alpha_beta_value;
		this->brd = empty_board_state;
	}
	TranspositionEntry(GameState &game, AlphaBetaValue &value, int &depth, bool fail_low, bool fail_high){
		this->key = game.hash;
		this->depth = depth;
		this->fail_low = fail_low;
		this->fail_high = fail_high;
		this->halfmove_clock = game.halfmove_clock;
		this->value = value;
		this->brd = game.board_state;
	}
	bool operator==(const TranspositionEntry &other) const{
		if(key == other.key && depth == other.depth &&
			fail_low == other.fail_low && fail_high == other.fail_high &&
			value == other.value && brd == other.brd && halfmove_clock == other.halfmove_clock){
			return true;
		}else{
			return false;
		}
	}
	bool operator!=(const TranspositionEntry &other) const{
		return !((*this) == other);
	}
};

class TranspositionTable {
	public:
		TranspositionTable(){}
		void initialize(size_t size);
		TranspositionTable(size_t size);
		~TranspositionTable(){
			if(size>0){
				delete[] this->data;
			}
		}
		void setitem(GameState &game, const TranspositionEntry &entry);
		TranspositionEntry getitem(GameState &game);
		unsigned long int getindex(GameState &game){
			return (game.hash % size);
		}
	private:
		size_t size;
		TranspositionEntry (*data)[2];//Stores best and most recent

};

extern const TranspositionEntry null_te;

struct EvaluationEntry{
	zobrist_int key;
	BoardState brd;
	int value;
	EvaluationEntry(){
		key = 0;
		brd = empty_board_state;
		value = 0;
	}
	EvaluationEntry(GameState &game, int value){
		key = game.hash;
		brd = game.board_state;
		this->value = value;
	}
	bool operator==(const EvaluationEntry &other) const{
		if(key == other.key && value == other.value && brd == other.brd){
			return true;
		}else{
			return false;
		}
	}
	bool operator!=(const EvaluationEntry &other) const{
		return !((*this) == other);
	}
};

extern const EvaluationEntry null_ee;

class EvaluationTable {
	public:
		EvaluationTable(){}
		void initialize(size_t size);
		EvaluationTable(size_t size);
		~EvaluationTable(){
			if(size>0){
				delete[] this->data;
			}
		}
		void setitem(GameState &game, const EvaluationEntry &entry);
		EvaluationEntry getitem(GameState &game);
		size_t getindex(GameState &game){
			return (game.hash % size);
		}
	private:
		size_t size;
		EvaluationEntry *data;//Stores best and most recent

};


inline void extract_engineered_features(GameState &brd, move *own_moves, int num_own_moves, move *opponent_moves,
		                                int num_opponent_moves, int *output){
	// output should be at least 15*15 + 15
	int w_p, w_n, w_b, w_r, w_q, b_p, b_n, b_b, b_r, b_q;
	int w_center_4, w_center_16, w_rank_7, w_rank_6, w_rank_5, b_center_4, b_center_16, b_rank_2,
		b_rank_3, b_rank_4;

	// attack_count_diff[from][to];
	// use piece_to_target_type_index to index
	int attack_count[15][15];
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			attack_count[i][j] = 0;
		}
	}
//
//	int w_king_mobility, b_king_mobility;
//	int w_doubled_pawns, b_doubled_pawns;

	w_p = population_count(brd.board_state.white & brd.board_state.p);
	w_n = population_count(brd.board_state.white & brd.board_state.n);
	w_b = population_count(brd.board_state.white & brd.board_state.b);
	w_r = population_count(brd.board_state.white & brd.board_state.r);
	w_q = population_count(brd.board_state.white & brd.board_state.q);
	b_p = population_count(brd.board_state.black & brd.board_state.p);
	b_n = population_count(brd.board_state.black & brd.board_state.n);
	b_b = population_count(brd.board_state.black & brd.board_state.b);
	b_r = population_count(brd.board_state.black & brd.board_state.r);
	b_q = population_count(brd.board_state.black & brd.board_state.q);

	w_center_4 = population_count(brd.board_state.white & center4);
	w_center_16 = population_count(brd.board_state.white & center16);
	w_rank_7 = population_count(brd.board_state.white & brd.board_state.p & rank_7);
	w_rank_6 = population_count(brd.board_state.white & brd.board_state.p & rank_6);
	w_rank_5 = population_count(brd.board_state.white & brd.board_state.p & rank_5);

	b_center_4 = population_count(brd.board_state.black & center4);
	b_center_16 = population_count(brd.board_state.black & center16);
	b_rank_2 = population_count(brd.board_state.black & brd.board_state.p & rank_2);
	b_rank_3 = population_count(brd.board_state.black & brd.board_state.p & rank_3);
	b_rank_4 = population_count(brd.board_state.black & brd.board_state.p & rank_4);

	brd.moves_from.set_moves(own_moves, num_own_moves, true);
	brd.moves_to.set_moves(own_moves, num_own_moves, false);
	brd.moves_from.add_moves(opponent_moves, num_opponent_moves, true);
	brd.moves_to.add_moves(opponent_moves, num_opponent_moves, false);
	bitboard targets, tmp;

	bitboard w_king_area, b_king_area, w_king, b_king;
	w_king = brd.board_state.white & brd.board_state.k;
	b_king = brd.board_state.black & brd.board_state.k;
	w_king_area = empty;
	w_king_area |= step_north(w_king);
	w_king_area |= step_west(w_king);
	w_king_area |= step_south(w_king);
	w_king_area |= step_east(w_king);
	w_king_area |= step_northeast(w_king);
	w_king_area |= step_northwest(w_king);
	w_king_area |= step_southwest(w_king);
	w_king_area |= step_southeast(w_king);
	int w_king_area_attack = 0;
	int b_king_area_attack = 0;

	b_king_area = empty;
	b_king_area |= step_north(b_king);
	b_king_area |= step_west(b_king);
	b_king_area |= step_south(b_king);
	b_king_area |= step_east(b_king);
	b_king_area |= step_northeast(b_king);
	b_king_area |= step_northwest(b_king);
	b_king_area |= step_southwest(b_king);
	b_king_area |= step_southeast(b_king);


	int from_target_index, to_target_index;
	piece to_pc, from_pc;
	for(int i=0;i<64;i++){
		targets = brd.moves_from.targets[i];
		from_pc = brd.piece_map[i];
		from_target_index = piece_to_target_index(from_pc);
		if(piece_is_white(from_pc)){
			b_king_area_attack += population_count(b_king_area & targets);
		}else if(piece_is_black(from_pc)){
			w_king_area_attack += population_count(w_king_area & targets);
		}
		while(targets){
			tmp = ls1b(targets);
			to_pc = brd.piece_map[greatest_square_index(tmp)];
			to_target_index = piece_to_target_index(to_pc);
			attack_count[from_target_index][to_target_index] += 1;
			targets ^= tmp;
		}
	}


	output[0] = w_p;
	output[1] = b_p;
	output[2] = w_n;
	output[3] = b_n;
	output[4] = w_b;
	output[5] = b_b;
	output[6] = w_r;
	output[7] = b_r;
	output[8] = w_q;
	output[9] = b_q;
	output[10] = brd.board_state.whites_turn;
	output[11] = brd.board_state.white_castle_queen;
	output[12] = brd.board_state.white_castle_king;
	output[13] = brd.board_state.black_castle_queen;
	output[14] = brd.board_state.black_castle_queen;
	output[15] = w_center_4;
	output[16] = b_center_4;
	output[17] = w_center_16;
	output[18] = b_center_16;
	output[19] = w_rank_7;
	output[20] = b_rank_2;
	output[21] = w_rank_6;
	output[22] = b_rank_3;
	output[23] = w_rank_5;
	output[24] = b_rank_4;
	output[25] = brd.board_state.whites_turn?num_own_moves:num_opponent_moves;
	output[26] = brd.board_state.whites_turn?num_opponent_moves:num_own_moves;
	output[27] = w_king_area_attack;
	output[28] = b_king_area_attack;

	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			output[29 + i*15 + j] = attack_count[i][j];
		}
	}

}

struct LogisticEvaluation{
	static const int infinity;
	static const int mate;
	static const int draw;
	static const int delta;
	static const int evaluate(GameState &brd, move *own_moves, int num_own_moves, move *opponent_moves, int num_opponent_moves){
		int w_p, w_n, w_b, w_r, w_q, b_p, b_n, b_b, b_r, b_q;
		int w_center_4, w_center_16, w_rank_7, w_rank_6, w_rank_5, b_center_4, b_center_16, b_rank_2,
				b_rank_3, b_rank_4;

		// attack_count_diff[from][to];
		// use piece_to_target_type_index to index
		int attack_count[15][15];
		for(int i=0;i<15;i++){
			for(int j=0;j<15;j++){
				attack_count[i][j] = 0;
			}
		}
		w_p = population_count(brd.board_state.white & brd.board_state.p);
		w_n = population_count(brd.board_state.white & brd.board_state.n);
		w_b = population_count(brd.board_state.white & brd.board_state.b);
		w_r = population_count(brd.board_state.white & brd.board_state.r);
		w_q = population_count(brd.board_state.white & brd.board_state.q);
		b_p = population_count(brd.board_state.black & brd.board_state.p);
		b_n = population_count(brd.board_state.black & brd.board_state.n);
		b_b = population_count(brd.board_state.black & brd.board_state.b);
		b_r = population_count(brd.board_state.black & brd.board_state.r);
		b_q = population_count(brd.board_state.black & brd.board_state.q);


		w_center_4 = population_count(brd.board_state.white & center4);
		w_center_16 = population_count(brd.board_state.white & center16);
		w_rank_7 = population_count(brd.board_state.white & brd.board_state.p & rank_7);
		w_rank_6 = population_count(brd.board_state.white & brd.board_state.p & rank_6);
		w_rank_5 = population_count(brd.board_state.white & brd.board_state.p & rank_5);

		b_center_4 = population_count(brd.board_state.black & center4);
		b_center_16 = population_count(brd.board_state.black & center16);
		b_rank_2 = population_count(brd.board_state.black & brd.board_state.p & rank_2);
		b_rank_3 = population_count(brd.board_state.black & brd.board_state.p & rank_3);
		b_rank_4 = population_count(brd.board_state.black & brd.board_state.p & rank_4);

		brd.moves_from.set_moves(own_moves, num_own_moves, true);
		brd.moves_to.set_moves(own_moves, num_own_moves, false);
		brd.moves_from.add_moves(opponent_moves, num_opponent_moves, true);
		brd.moves_to.add_moves(opponent_moves, num_opponent_moves, false);
		bitboard targets, tmp;

		bitboard w_king_area, b_king_area, w_king, b_king;
		w_king = brd.board_state.white & brd.board_state.k;
		b_king = brd.board_state.black & brd.board_state.k;
		w_king_area = empty;
		w_king_area |= step_north(w_king);
		w_king_area |= step_west(w_king);
		w_king_area |= step_south(w_king);
		w_king_area |= step_east(w_king);
		w_king_area |= step_northeast(w_king);
		w_king_area |= step_northwest(w_king);
		w_king_area |= step_southwest(w_king);
		w_king_area |= step_southeast(w_king);
		int w_king_area_attack = 0, b_king_area_attack = 0;

		b_king_area = empty;
		b_king_area |= step_north(b_king);
		b_king_area |= step_west(b_king);
		b_king_area |= step_south(b_king);
		b_king_area |= step_east(b_king);
		b_king_area |= step_northeast(b_king);
		b_king_area |= step_northwest(b_king);
		b_king_area |= step_southwest(b_king);
		b_king_area |= step_southeast(b_king);


		int from_target_index, to_target_index;
		piece to_pc, from_pc;
		for(int i=0;i<64;i++){
			targets = brd.moves_from.targets[i];
			from_pc = brd.piece_map[i];
			from_target_index = piece_to_target_index(from_pc);
			if(piece_is_white(from_pc)){
				b_king_area_attack += population_count(b_king_area & targets);
			}else if(piece_is_black(from_pc)){
				w_king_area_attack += population_count(w_king_area & targets);
			}
			while(targets){
				tmp = ls1b(targets);
				to_pc = brd.piece_map[greatest_square_index(tmp)];
				to_target_index = piece_to_target_index(to_pc);
				attack_count[from_target_index][to_target_index] += 1;
				targets ^= tmp;
			}
		}

//		int coef[240] = {3519, -3671, 7275, -7292, 8093, -9000, 12604, -12925, 25405, -23569, 3209, -1107, 488, -94, -585, 0, 0, 0, 50, 162, -259, 200, -333, 162, -121, 167, -210, 168, -311, 5, 0, 0, 0, -2322, 4384, -6450, 0, -28, 1004, -6856, -1407, 6598, 0, 0, 0, 0, 0, 0, 1777, -450, 0, 1018, 1879, -438, 0, 4041, -4994, -2947, 0, 6267, 0, 0, 0, 0, 119, 0, 270, 0, 619, 0, 267, 0, -325, 0, 1601, 0, 0, 0, 90, 0, -960, 0, 0, 0, -89, 0, 196, 0, 11, 0, 0, 0, 0, 0, 2988, 0, 0, 0, 3236, 0, 3449, 0, 585, 0, 5830, 0, 0, 0, -3841, 0, 1152, 0, -1328, 0, -1595, 0, -824, 0, -3542, 0, 0, 0, 0, 0, 2484, 0, 1734, 0, -1182, 0, 565, 0, 126, 0, 4229, 0, 0, 0, -3801, 0, -2070, 0, 1180, 0, -1435, 0, -23, 0, -1482, 0, 0, 0, 0, 0, 2098, 0, 1399, 0, 2278, 0, -265, 0, -105, 0, 5532, 0, 0, 0, -2402, 0, -1628, 0, -1091, 0, 0, 0, -336, 0, -3584, 0, 0, 0, 0, 0, 4255, 0, 5376, 0, 6603, 0, 5069, 0, 0, 0, 12742, 0, 0, 0, -6199, 0, -3254, 0, -3958, 0, -5631, 0, 2612, 0, -11757, 0, 0, 0, 0, 0, -955, 0, 0, 0, 1683, 0, 2054, 0, 119, 0, 0, 0, 0, 0, -2641, 0, 330, 0, -347, 0, -3686, 0, -840, 0, 0, 0};
//		int coef[250] = {3025, -3187, 7289, -7168, 8098, -9081, 12896, -13281, 25474, -23751, 3353, -1133, 552, -577, -4, 231, 119, 295, -47, 5945, -5144, 1495, -1817, 351, -1226, 0, 0, 0, -28, 220, -231, 168, -320, 108, -100, 139, -198, 157, -237, -84, 0, 0, 0, -2470, 4199, -6551, 0, -59, 785, -6935, -1211, 6720, 0, 0, 0, 0, 0, 0, 2640, -399, 0, 1023, 1903, -375, 0, 4005, -6350, -3066, 0, 5945, 0, 0, 0, 0, 0, 0, 400, 0, 704, 0, 265, 0, -251, 0, 2755, 0, 0, 0, 214, 0, -1039, 0, -141, 0, -64, 0, 143, 0, -308, 0, 0, 0, 0, 0, 2373, 0, 0, 0, 3565, 0, 3631, 0, 766, 0, 5533, 0, 0, 0, -3224, 0, 1098, 0, -1344, 0, -1855, 0, -943, 0, -3759, 0, 0, 0, 0, 0, 2356, 0, 1665, 0, -1544, 0, 564, 0, 33, 0, 3911, 0, 0, 0, -3534, 0, -2011, 0, 1345, 0, -1496, 0, -102, 0, -983, 0, 0, 0, 0, 0, 1880, 0, 1380, 0, 2262, 0, -328, 0, -38, 0, 5387, 0, 0, 0, -2310, 0, -1628, 0, -1156, 0, 0, 0, -439, 0, -3029, 0, 0, 0, 0, 0, 4267, 0, 5472, 0, 6697, 0, 5163, 0, 0, 0, 12402, 0, 0, 0, -6178, 0, -3182, 0, -4022, 0, -5759, 0, 2601, 0, -11954, 0, 0, 0, 0, 0, -1608, 0, 0, 0, 1521, 0, 2077, 0, 138, 0, 0, 0, 0, 0, -2242, 0, 0, 0, -1029, 0, -4604, 0, -1540, 0, 0, 0};
//		int coef[252] = {3039, -3202, 7282, -7165, 8102, -9071, 12891, -13304, 25460, -23742, 3390, -1147, 555, -582, 0, 233, 121, 289, -39, 5528, -3614, 1508, -1827, 357, -1230, 218, -810, 0, 0, 0, 794, -5, 581, -49, 487, -108, 709, -79, 613, -61, 570, -301, 0, 0, 0, -1591, 4069, -5616, 0, 0, 588, -6075, -1454, 7482, 0, 0, 0, 0, 0, 0, 3473, -600, 0, 827, 2730, -542, 0, 3808, -5563, -3292, 0, 5758, 0, 0, 0, 0, 0, 0, 161, 0, 487, 0, 60, 0, -480, 0, 2590, 0, 0, 0, 812, 0, -228, 0, 653, 0, 714, 0, 956, 0, 357, 0, 0, 0, 0, 0, 2022, 0, 0, 0, 3357, 0, 3418, 0, 553, 0, 5385, 0, 0, 0, -2077, 0, 1701, 0, -540, 0, -1053, 0, -126, 0, -2983, 0, 0, 0, 0, 0, 2123, 0, 1449, 0, -1796, 0, 358, 0, -124, 0, 3700, 0, 0, 0, -2676, 0, -1199, 0, 2183, 0, -701, 0, 657, 0, -170, 0, 0, 0, 0, 0, 1668, 0, 1168, 0, 2047, 0, 0, 0, -234, 0, 5153, 0, 0, 0, -1423, 0, -815, 0, -352, 0, 230, 0, 245, 0, -2203, 0, 0, 0, 0, 0, 4042, 0, 5253, 0, 6485, 0, 5103, 0, 0, 0, 12260, 0, 0, 0, -5288, 0, -2422, 0, -3190, 0, -4987, 0, 3181, 0, -11221, 0, 0, 0, 0, 0, -1828, 0, 0, 0, 1298, 0, 1838, 0, 0, 0, 0, 0, 0, 0, -922, 0, 443, 0, -230, 0, -3812, 0, -716, 0, 0, 0};
//		int coef[252] = {2785, -2990, 6608, -6414, 8919, -8729, 12629, -12722, 26442, -25038, 3367, -313, -434, 0, -388, 75, 8, 158, -256, 4183, -4955, 1753, -1658, 443, -625, 641, -366, 0, 0, 0, 294, -512, 104, -463, 25, -347, 223, -592, 200, -534, 246, -757, 0, 0, 0, -804, -1452, -1450, 9347, 1429, -2159, 529, -798, 1767, -3844, 62, 0, 0, 0, 0, 621, -1113, 0, 1108, -1312, 887, 0, -819, -254, 1716, 0, 1082, 0, 0, 0, 0, -830, 0, -115, 0, -63, 0, -446, 0, -702, 0, 1694, 0, 0, 0, 898, 0, -176, 0, -112, 0, 88, 0, 613, 0, -1221, 0, 0, 0, 0, 0, 2655, 0, -131, 0, 2020, 0, 2053, 0, 578, 0, 4336, 0, 0, 0, -3401, 0, 0, 0, -2771, 0, -2585, 0, -999, 0, -3327, 0, 0, 0, 0, 0, 1241, 0, 577, 0, 560, 0, 312, 0, -630, 0, 1758, 0, 0, 0, -1832, 0, -1009, 0, -782, 0, -504, 0, 594, 0, -3662, 0, 0, 0, 0, 0, 1543, 0, 955, 0, 1413, 0, 518, 0, 168, 0, 3562, 0, 0, 0, -1953, 0, -1310, 0, -1444, 0, -1050, 0, 175, 0, -3875, 0, 0, 0, 0, 0, 4064, 0, 4382, 0, 4680, 0, 3577, 0, 1492, 0, 17761, 0, 0, 0, -5193, 0, -5051, 0, -4042, 0, -4135, 0, -2255, 0, -19813, 0, 0, 0, 0, 0, 588, 0, 195, 0, 520, 0, 1246, 0, 706, 0, 0, 0, 0, 0, -1586, 0, -1966, 0, -1456, 0, -2592, 0, -3209, 0, 0, 0};
		int coef[254] = {2791, -2990, 6606, -6419, 8913, -8730, 12629, -12724, 26424, -25041, 3367, -297, -422, -388, 0, 77, 7, 153, -257, 4108, -4911, 1750, -1668, 440, -632, 675, -390, 213, 32, 0, 0, 0, 316, -547, 127, -500, 49, -383, 247, -626, 223, -569, 267, -788, 0, 0, 0, -786, -1508, -1439, 9331, 1453, -2207, 555, -864, 1791, -3862, 67, 0, 0, 0, 0, 641, -1154, 0, 1083, -1305, 856, 0, -875, -236, 1696, 0, 1002, 0, 0, 0, 0, -898, 0, -162, 0, -119, 0, -517, 0, -746, 0, 1644, 0, 0, 0, 930, 0, -155, 0, -92, 0, 103, 0, 632, 0, -1204, 0, 0, 0, 0, 0, 2592, 0, -178, 0, 1968, 0, 1999, 0, 541, 0, 4314, 0, 0, 0, -3361, 0, 0, 0, -2746, 0, -2564, 0, -973, 0, -3286, 0, 0, 0, 0, 0, 1183, 0, 530, 0, 486, 0, 253, 0, -665, 0, 1716, 0, 0, 0, -1802, 0, -988, 0, -752, 0, -483, 0, 623, 0, -3629, 0, 0, 0, 0, 0, 1480, 0, 903, 0, 1356, 0, 434, 0, 127, 0, 3515, 0, 0, 0, -1907, 0, -1291, 0, -1421, 0, -1021, 0, 196, 0, -3835, 0, 0, 0, 0, 0, 4001, 0, 4300, 0, 4626, 0, 3502, 0, 1484, 0, 17708, 0, 0, 0, -5174, 0, -5038, 0, -4011, 0, -4131, 0, -2298, 0, -19770, 0, 0, 0, 0, 0, 550, 0, 153, 0, 480, 0, 1199, 0, 667, 0, 0, 0, 0, 0, -1543, 0, -1926, 0, -1447, 0, -2556, 0, -3161, 0, 0, 0};

		int output = 0;

		output += coef[0]*w_p;
		output += coef[1]*b_p;
		output += coef[2]*w_n;
		output += coef[3]*b_n;
		output += coef[4]*w_b;
		output += coef[5]*b_b;
		output += coef[6]*w_r;
		output += coef[7]*b_r;
		output += coef[8]*w_q;
		output += coef[9]*b_q;
		output += coef[10]*brd.board_state.whites_turn;
		output += coef[11]*brd.board_state.white_castle_queen;
		output += coef[12]*brd.board_state.white_castle_king;
		output += coef[13]*brd.board_state.black_castle_queen;
		output += coef[14]*brd.board_state.black_castle_queen;
		output += coef[15]*w_center_4;
		output += coef[16]*b_center_4;
		output += coef[17]*w_center_16;
		output += coef[18]*b_center_16;
		output += coef[19]*w_rank_7;
		output += coef[20]*b_rank_2;
		output += coef[21]*w_rank_6;
		output += coef[22]*b_rank_3;
		output += coef[23]*w_rank_5;
		output += coef[24]*b_rank_4;
		output += coef[25]*(brd.board_state.whites_turn?num_own_moves:num_opponent_moves);
		output += coef[26]*(brd.board_state.whites_turn?num_opponent_moves:num_own_moves);
		output += coef[27]*w_king_area_attack;
		output += coef[28]*b_king_area_attack;

		for(int i=0;i<15;i++){
			for(int j=0;j<15;j++){
				output += coef[29 + i*15 + j]*attack_count[i][j];
			}
		}

		return output;
	}
};

struct SimpleEvaluation{
	static const int infinity;
	static const int mate;
	static const int draw;
	static const int delta;
	static const int evaluate(GameState &brd, move *own_moves, int num_own_moves, move *opponent_moves, int num_opponent_moves){
		int white_score, black_score;
		white_score = 0;
		black_score = 0;
		white_score += 100 * population_count(brd.board_state.white & brd.board_state.p);
		white_score += 320 * population_count(brd.board_state.white & brd.board_state.n);
		white_score += 330 * population_count(brd.board_state.white & brd.board_state.b);
		white_score += 500 * population_count(brd.board_state.white & brd.board_state.r);
		white_score += 900 * population_count(brd.board_state.white & brd.board_state.q);

		white_score += 1 * population_count(brd.board_state.white & center4);
		white_score += 1 * population_count(brd.board_state.white & center16);
		white_score += 5 * population_count(brd.board_state.white & brd.board_state.p & rank_7);
		white_score += 4 * population_count(brd.board_state.white & brd.board_state.p & rank_6);
		white_score += 3 * population_count(brd.board_state.white & brd.board_state.p & rank_5);

		black_score += 100 * population_count(brd.board_state.black & brd.board_state.p);
		black_score += 320 * population_count(brd.board_state.black & brd.board_state.n);
		black_score += 330 * population_count(brd.board_state.black & brd.board_state.b);
		black_score += 500 * population_count(brd.board_state.black & brd.board_state.r);
		black_score += 900 * population_count(brd.board_state.black & brd.board_state.q);

		black_score += 1 * population_count(brd.board_state.black & center4);
		black_score += 1 * population_count(brd.board_state.black & center16);
		black_score += 5 * population_count(brd.board_state.black & brd.board_state.p & rank_2);
		black_score += 4 * population_count(brd.board_state.black & brd.board_state.p & rank_3);
		black_score += 3 * population_count(brd.board_state.black & brd.board_state.p & rank_4);
		
		return white_score - black_score;

	}

};

class KillerTable{
	// Tracks the most recent num_killers cutoff moves
	// by ply.
	public:
		KillerTable(int num_killers){
			highest_ply_seen = 0;
			this->num_killers = num_killers;
			if(num_killers > 0){
				killers = new move*[num_ply];
				starts = new int[num_ply];
				for(int i=0;i<num_ply;i++){
					killers[i] = new move[num_killers];
					for(int j=0;j<num_killers;j++){
						killers[i][j] = nomove;
					}
					starts[i] = num_killers - 1;
				}
			}
		}
		KillerTable() : KillerTable(0) {}
		~KillerTable(){
			if(num_killers > 0){
				for(int i=0;i<num_ply;i++){
					delete[] killers[i];
				}
				delete[] killers;
				delete[] starts;
			}
		}
		void record_cutoff(GameState &game, move &mv){
			if(num_killers == 0){
				return;
			}
			int ply = game.halfmove_counter;
			int index = ply % num_ply;
			move *moves = killers[index];
			if(ply > highest_ply_seen){
				// Clear the killers at this index
				for(int i=0;i<num_killers;i++){
					moves[i] = nomove;
				}
				starts[index] = num_killers-1;
				highest_ply_seen = ply;
			}
			int start = starts[index];
			int new_start = start - 1;
			if(new_start < 0){
				new_start += num_killers;
			}
			moves[new_start] = mv;
			starts[index] = new_start;
		}

		int score(GameState &game, move &mv){
			// The score is num_killers for the most recent killer,
			// num_killers - 1 for the next most, and so on.  If none
			// of the most recent num_killers is a match, the score is
			// 0.
			if(num_killers == 0){
				return 0;
			}
			int ply = game.halfmove_counter;
			if(ply > highest_ply_seen){
				return 0;
			}
			int index = ply % num_ply;
			int start = starts[index];
			int rank = num_killers;
			int killer_index;
			move *moves = killers[index];
			for(int i=0;i<num_killers;i++){
				killer_index = i % (num_killers + start);
				if(mv == moves[killer_index]){
					rank = i;
					break;
				}
			}
			return num_killers - rank;
		}
	private:
		static const int num_ply;
		int highest_ply_seen;
		move **killers;
		int *starts;
		int num_killers;

};

class HistoryTable{
	public:
		HistoryTable(){
			initialize(0);
		}
		void initialize(int num_history){
			this->num_history = num_history;
			if(num_history>0){
				white_history = new MoveTable<int>(num_history);
				black_history = new MoveTable<int>(num_history);
				white_history->reset(0);
				black_history->reset(0);
			}
		}
		HistoryTable(int num_history) : HistoryTable() {
			initialize(num_history);
		}
		~HistoryTable(){
			if(num_history>0){
				delete white_history;
				delete black_history;
			}
		}
		void record_cutoff(GameState &game, move &mv, int depth){
			MoveTable<int> *table;
			if(game.board_state.whites_turn){
				table = white_history;
			}else{
				table = black_history;
			}
			table->add(mv, depth*depth);
		}
		int score(GameState &game, move &mv){
			MoveTable<int> *table;
			if(game.board_state.whites_turn){
				table = white_history;
			}else{
				table = black_history;
			}
			int rank = table->rank(mv);
			if(rank == -1){
				return 0;
			}
			return num_history - rank;
		}
	private:
		MoveTable<int> *white_history;
		MoveTable<int> *black_history;
		int num_history;
};

class SearchMemory{
	public:
		SearchMemory(){
		}
		~SearchMemory(){
			delete tt;
			delete killers;
			delete hh;
		}
		SearchMemory(size_t tt_size, int num_killers, int num_history, size_t ee_size){
			tt = new TranspositionTable(tt_size);
			killers = new KillerTable(num_killers);
			hh = new HistoryTable(num_history);
			ee = new EvaluationTable(ee_size);
		}
		TranspositionTable *tt;
		KillerTable *killers;
		HistoryTable *hh;
		EvaluationTable *ee;
};

class MoveManager{
	// Responsible for move ordering
	public:
		MoveManager(){}
		int getindex(int depth){
			int index = depth % maxply;
			if(index < 0){
				index += maxply;
			}
			return index;
		}
		void generate_all_opponent(GameState &game){
			_num_opponent_moves = all_moves(&game, opponent_buffer, !game.board_state.whites_turn);
		}
		void generate_all(GameState &game, int depth){
			int index = getindex(depth);
			_num_moves[index] = all_moves(&game, buffer[index], game.board_state.whites_turn);
		}
		void generate_noisy(GameState &game, int depth){
			int index = getindex(depth);
			_num_moves[index] = all_captures(&game, buffer[index], game.board_state.whites_turn);
		}
		void order_noisy(GameState &game, SearchMemory *memory, int depth){
			// Determine best move from transposition table
			TranspositionEntry entry = memory->tt->getitem(game);
			move best_move = nomove;
			if(entry != null_te){
				best_move = entry.value.best_move;
			}

			// Score all moves based on where they will be in the order
			int index = getindex(depth);
			move *current_buffer = buffer[index];
			int capture_count = 0;
			piece capture_target;
			piece capturer;
			move *mv;
			int killer_score;
			int history_score;
			int capture_score;
			int tmp;
			for(int i=0;i<_num_moves[index];i++){
				mv = &(current_buffer[i]);
				mv->sort_score = 0;
				if((*mv) == best_move){
					mv->sort_score += 100000;
				}

				// If there are any killer moves, they will be just below the best move
				// from the transposition table
				tmp = 1000 * (memory->killers->score(game, *mv));
				mv->sort_score += tmp;

				// Use history heuristic for any moves that remain
				if(game.board_state.whites_turn){
					mv->sort_score += memory->hh->score(game, *mv);
				}else{
					mv->sort_score += memory->hh->score(game, *mv);
				}

				// Capture score is at most 560
				// Prefer to capture the biggest piece, then prefer to use the smallest
				capture_target = game.piece_map[mv->to_square];
				capturer = game.piece_map[mv->from_square];
				if(capture_target != no){
					capture_count += 1;
					mv->sort_score += 10 * ((10 * piece_to_search_order(capture_target))) + (6 - piece_to_search_order(capturer));
					if(mv->promotion != no){
						// If it's a promotion and a capture
						mv->sort_score += 100 * piece_to_search_order(mv->promotion);
					}
				}else if(mv->promotion != no){
					// If it's a promotion,
					capture_count += 1;
					mv->sort_score += 100 * piece_to_search_order(mv->promotion)  + (6 - piece_to_search_order(capturer));
				}else{
					// This move is quiet, so it will go at the end and ultimately not be used.
					mv->sort_score = -1;
				}
			}

			// Sort moves based on sort_score.  Highest to lowest.
			std::stable_sort(current_buffer, current_buffer + _num_moves[index]);

			// Keep track of this stuff
			// We will only consider the captures.  All non-captures were set to -1,
			// and so strictly get sorted after captures.
			_full_begin[index] = 0;
			_full_end[index] = capture_count > 3?3:capture_count;
			_pv_begin[index] = _full_end[index];
			_pv_end[index] = capture_count;
		}
		void order_all(GameState &game, SearchMemory *memory, int depth){
			int index = getindex(depth);

			// Determine best move from transposition table
			TranspositionEntry entry = memory->tt->getitem(game);
			move best_move = nomove;
			if(entry != null_te){
				best_move = entry.value.best_move;
			}

			// Score all moves based on where they will be in the order

			move *current_buffer = buffer[index];
			int capture_count = 0;
			piece capture_target;
			piece capturer;
			move *mv;
			int tmp;
			for(int i=0;i<_num_moves[index];i++){
				mv = &(current_buffer[i]);
				mv->sort_score = 0;
				if((*mv) == best_move){
					mv->sort_score += 100000;
				}

				// If there are any killer moves, they will be just below the best move
				// from the transposition table
				tmp = 1000 * (memory->killers->score(game, *mv));
				mv->sort_score += tmp;

				// Capture score is at most 560
				// Prefer to capture the biggest piece, then prefer to use the smallest
				capture_target = game.piece_map[mv->from_square];
				capturer = game.piece_map[mv->from_square];
				if(capture_target != no){
					capture_count += 1;
					mv->sort_score += 10 * ((10 * piece_to_search_order(capture_target))) + (6 - piece_to_search_order(capturer));
				}

				// Use history heuristic for any moves that remain
				if(game.board_state.whites_turn){
					mv->sort_score += memory->hh->score(game, *mv);
				}else{
					mv->sort_score += memory->hh->score(game, *mv);
				}
			}

			// Sort moves based on sort_score.  Highest to lowest.
			std::stable_sort(current_buffer, current_buffer + _num_moves[index]);

			// Keep track of this stuff
			_full_begin[index] = 0;
			_full_end[index] = _num_moves[index] > 3?3:_num_moves[index]; // TODO: Experiment with this.
			_pv_begin[index] = _full_end[index];
			_pv_end[index] = _num_moves[index];

		}
		moverecord make(GameState &game, move &mv){
			return make_move(&game, &mv);
		}
		void unmake(GameState &game, moverecord &rec){
			unmake_move(&game, &rec);
		}
		move *get_moves(int depth){
			int index = getindex(depth);
			return buffer[index];
		}
		move *get_opponent_moves(){
			return opponent_buffer;
		}
		int full_begin(int depth){
			int index = getindex(depth);
			return _full_begin[index];
		}
		int full_end(int depth){
			int index = getindex(depth);
			return _full_end[index];
		}
		int pv_begin(int depth){
			int index = getindex(depth);
			return _pv_begin[index];
		}
		int pv_end(int depth){
			int index = getindex(depth);
			return _pv_end[index];
		}
		int num_moves(int depth){
			int index = getindex(depth);
			return _num_moves[index];
		}
		int num_opponent_moves(){
			return _num_opponent_moves;
		}
	private:
		// No search is likely to exceed 1000 ply, and
		// no position has more than 1000 possible moves
		static const int maxply = 1000;
		static const int maxmove = 1000;
		move buffer[maxply][maxmove];
		move opponent_buffer[maxmove];
		int _full_begin[maxply];
		int _full_end[maxply];
		int _pv_begin[maxply];
		int _pv_end[maxply];
		int _num_moves[maxply];
		int _num_opponent_moves;
};

template<class Evaluation>
int quiesce(GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int depth){

	// Check whether maximizing or minimizing
	const bool maximize = game.board_state.whites_turn;
	
	// Generate all legal moves.  Some of these will not be searched,
	// but we need to generate all moves to check for checkmate and
	// stalemate and for evaluation.
	manager->generate_all(game, depth);
	move *moves = manager->get_moves(depth);
	int num_moves = manager->num_moves(depth);
	
	manager->generate_all_opponent(game);
	move *opponent_moves = manager->get_opponent_moves();
	int num_opponent_moves = manager->num_opponent_moves();

	int result;
	// Check for checkmates and draws
	if(num_moves == 0){
		if(own_check(&game)){
			// Checkmate.  We lose.
			result = maximize?(-(Evaluation::mate)):(Evaluation::mate);
		}else{
			// Stalemate
			result = Evaluation::draw;
		}
		return result;
	}

	// Check for draw by repetition or 50 move rule
	// A maxrep of 2 is used because, in principal, if we repeat once,
	// we will repeat again, and this is faster to check.
	if(game.halfmove_clock >= 50 || draw_by_repetition(&game, 2)){
		// Draw
		result = Evaluation::draw;
		return result;
	}

	// Get the current evaluation and possibly cut off immediately
	EvaluationEntry entry = memory->ee->getitem(game);
	if(entry != null_ee){
		result = entry.value;
	}else{
		result = Evaluation::evaluate(game, moves, num_moves, opponent_moves, num_opponent_moves);
		entry = EvaluationEntry(game, result);
		memory->ee->setitem(game, entry);
	}
	if(maximize){
		if(result > beta){
			return result;
		}else if(result > alpha){
			alpha = result;
		}else if(result < alpha){
			if(result < alpha - Evaluation::delta){
				// Delta prune
				return result;
			}else{
			}
		}
	}else{
		if(result < alpha){
			return result;
		}else if(result < beta){
			beta = result;
		}else if(result > beta){
			if(result > beta + Evaluation::delta){
				// Delta prune
				return result;
			}else{
			}
		}//else value == beta
	}
	// At this point result is the stand pat value, and matches alpha (if maximizing) or beta (otherwise).

	// Order moves
	bool in_check = own_check(&game) || opponent_check(&game);
	if(in_check){
		manager->order_all(game, memory, depth);
	}else{
		// Order noisy will trim any quiet moves
		manager->order_noisy(game, memory, depth);
	}

	// Recurse
	int search_result;
	move mv;
	moverecord rec;
	for(int i=manager->full_begin(depth);i<manager->pv_end(depth);i++){
		mv = moves[i];
		rec = manager->make(game, mv);
		if(i < manager->pv_begin(depth)){
			// Search full depth right away
			search_result = quiesce<Evaluation>(game, manager, memory, alpha, beta, depth-1);
		}else{
			// Do a narrower search and make it larger if no cutoff occurs
			if(maximize){
				search_result = quiesce<Evaluation>(game, manager, memory, alpha, alpha, depth-1);
				if(search_result > alpha && beta > alpha){
					// The narrow search returned a lower bound, so we must search again with full width
					search_result = quiesce<Evaluation>(game, manager, memory, alpha, beta, depth-1);
				}
			}else{
				search_result = quiesce<Evaluation>(game, manager, memory, beta, beta, depth-1);
				if(search_result < beta && beta > alpha){
					// The narrow search returned an upper bound, so we must search again with full width
					search_result = quiesce<Evaluation>(game, manager, memory, alpha, beta, depth-1);
				}
			}
		}
		manager->unmake(game, rec);
		if(maximize){
			if(search_result > beta){
				return search_result;
			}else if (search_result > result){
				if(search_result > alpha){
					alpha = search_result;
				}
				result = search_result;
			}
		}else{
			if(search_result < alpha){
				return search_result;
			}else if (search_result < result){
				if(search_result < beta){
					beta = search_result;
				}
				result = search_result;
			}
		}

	}

	// Update transposition table and return.
	return result;

}

template<class Evaluation>
AlphaBetaValue alphabeta(GameState &game, MoveManager *manager, SearchMemory *memory, int alpha,
		                 int beta, int depth, bool *stop, int top, bool debug){
	// Not using negamax.  All scores will be from the perspective of white.  That is,
	// white seeks to maximize and black seeks to minimize.
	bool true_before = game.board_state.k & 1;
	// Check whether maximizing or minimizing
	bool maximize = game.board_state.whites_turn;

	// Allocate the result
	AlphaBetaValue result;
	int value;

	// Check for draw by repetition or 50 move rule
	// This must be done before transposition table lookup
	// because the transposition table does not take the halfmove clock
	// or threefold clock and position record into account.
	if(game.halfmove_clock >= 50 || (draw_by_repetition(&game, 2) && !(top == depth))){
		// Draw
		result.value = Evaluation::draw;
		result.ply = game.halfmove_counter;
		result.best_move = nomove;
//		memory->tt->setitem(game, TranspositionEntry(game, result, depth, result.value < alpha, result.value > beta));
		return result;
	}

	// Check transposition table.  Can update alpha or beta or simply return.
	TranspositionEntry entry = memory->tt->getitem(game);
	if(entry != null_te && (entry.depth >= depth)){
		// TODO: Put this halfmove logic in the TranspositionTable getitem and setitem methods
		// instead of here.  Would also allow to store the same position with two different
		// clocks in some cases.
		if(game.halfmove_clock >= 50 - depth && game.halfmove_clock != entry.halfmove_clock){
			// In this case, we are in range of a draw by 50 move rule and the entry does
			// not match the current halfmove clock, so we can't use it.
		}else if(entry.halfmove_clock >= 50 - entry.depth && game.halfmove_clock != entry.halfmove_clock){
			// In this case, the entry was in range of a draw by the fifty move rule and
			// again the halfmove clocks don't match, so we can't use it.
		}else{
			if(entry.fail_low){
				// This transposition entry is an upper bound
				beta = (entry.value.value < beta)?(entry.value.value):beta;
				if(alpha > beta){
					result.value = entry.value.value;
					result.ply = entry.value.ply;
					result.best_move = nomove;
					return result;
				}
			}else if(entry.fail_high){
				// This transposition entry is a lower bound
				alpha = (entry.value.value > alpha)?(entry.value.value):alpha;
				if(alpha > beta){
					result.value = entry.value.value;
					result.ply = entry.value.ply;
					result.best_move = nomove;
					return result;
				}
			}else{
				// The transposition entry is exact
				value = entry.value.value;
				if(value < alpha){
					result.ply = entry.value.ply;
					result.value = entry.value.value;
					result.best_move = nomove;
				}else if(value > beta){
					result.ply = entry.value.ply;
					result.value = entry.value.value;
					result.best_move = nomove;
				}else{
					result = entry.value;
				}
				return result;
			}
		}
	}

	// If this is a leaf node, call quiescence search
	if(depth <= 0){
		result.value = quiesce<Evaluation>(game, manager, memory, alpha, beta, depth - 1);
		result.ply = game.halfmove_counter;
		result.best_move = nomove;
		memory->tt->setitem(game, TranspositionEntry(game, result, depth, result.value < alpha, result.value > beta));
		return result;
	}

	// Generate moves
	manager->generate_all(game, depth);
	bool true_after = game.board_state.k & 1;

	// Check for checkmates and stalemates
	if(manager->num_moves(depth) == 0){
		if(own_check(&game)){
			// Checkmate.  We lose.
			result.value = maximize?(-(Evaluation::mate)):(Evaluation::mate);
			result.ply = game.halfmove_counter;
		}else{
			// Stalemate
			result.value = Evaluation::draw;
			result.ply = game.halfmove_counter;
		}
		result.best_move = nomove;
		memory->tt->setitem(game, TranspositionEntry(game, result, depth, result.value < alpha, result.value > beta));
		return result;
	}

	int k;
	// Order moves
	manager->order_all(game, memory, depth);
	move *moves = manager->get_moves(depth);

	// Iterate over full moves
	move mv;
	AlphaBetaValue search_result;
	if(maximize){
		result.ply = 0;
		result.value = -Evaluation::infinity;
		result.best_move = nomove;
	}else{
		result.ply = 0;
		result.value = Evaluation::infinity;
		result.best_move = nomove;
	}
	bool fail_soft_hit;

	bool debug_ = false;
	moverecord rec;
	for(int i=(manager->full_begin(depth));i<(manager->pv_end(depth));i++){
		mv = moves[i];
//		if(depth == top){
//			printf("depth=%d, mv.from_square = %d, mv.to_square = %d, mv.sort_score = %d, stop = %d\n", depth, mv.from_square, mv.to_square, mv.sort_score, *stop);
//		}
		rec = manager->make(game, mv);
		if(i < manager->pv_begin(depth)){
			// Search full depth right away
			search_result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth-1, stop, top, debug_);
		}else{
			// Do a narrower search and make it larger if cutoff occurs
			if(maximize){
				search_result = alphabeta<Evaluation>(game, manager, memory, alpha, alpha, depth-1, stop, top, false);
				if(search_result.value > alpha && beta > alpha){
					// The narrow search returned a lower bound, so we must search again with full width
					search_result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth-1, stop, top, false);
				}
			}else{
				search_result = alphabeta<Evaluation>(game, manager, memory, beta, beta, depth-1, stop, top, false);
				if(search_result.value < beta && beta > alpha){
					// The narrow search returned an upper bound, so we must search again with full width
					search_result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth-1, stop, top, false);
				}
			}
		}
		manager->unmake(game, rec);
		true_after = game.board_state.k & 1;

		if(maximize){
			if(search_result.value > beta){
				// Cut node.  Yay!
				memory->hh->record_cutoff(game, mv, depth);
				memory->killers->record_cutoff(game, mv);
				search_result.best_move = nomove;
				memory->tt->setitem(game, TranspositionEntry(game, search_result, depth, false, true));
				return search_result;
			}else if(search_result.value > result.value){
				if(search_result.value > alpha ||
					(search_result.value == alpha && (result.best_move == nomove || result.ply < search_result.ply))){
					// New best move.  Note that in the case of equal scores, we keep the
					// old best move unless the new one has a lower ply (which favors sooner checkmates).
					// This is just an heuristic.
					result.best_move = mv;
					result.ply = search_result.ply;
					alpha = search_result.value;
				}
				result.value = search_result.value;
			}
		}else{
			if(search_result.value < alpha){
				// Cut node.  Yay!
				memory->hh->record_cutoff(game, mv, depth);
				memory->killers->record_cutoff(game, mv);
				search_result.best_move = nomove;
				memory->tt->setitem(game, TranspositionEntry(game, search_result, depth, true, false));
				return search_result;
			}else if(search_result.value < result.value){
				if(search_result.value < beta ||
					(search_result.value == beta && (result.best_move == nomove || result.ply < search_result.ply))){
					// New best move.  Note that in the case of equal scores, we keep the
					// old best move unless the new one has a lower ply (which favors sooner checkmates).
					// This is just an heuristic.
					result.best_move = mv;
					result.ply = search_result.ply;
					beta = search_result.value;
				}
				result.value = search_result.value;
			}

		}
		if(*stop){
			// The caller has asked us to stop.  We stop here, and the current result is returned.
			break;
		}
	}
	true_after = game.board_state.k & 1;

	if(debug){
		printf("END\n");
	}
	// We checked everything.  Either it's an all node or a pv node.
	// Update transposition table and return.
	memory->tt->setitem(game, TranspositionEntry(game, result, depth, result.value < alpha, result.value > beta));
	return result;

}

template<class Evaluation>
AlphaBetaValue mtdf(GameState &game, MoveManager *manager, SearchMemory *memory, int depth, bool *stop){
	bool maximize = game.board_state.whites_turn;
	int f;
	TranspositionEntry te = memory->tt->getitem(game);
	int g;
	if(te != null_te){
		g = te.value.value;
	}else{
		g = Evaluation::draw;
	}
	int alpha = -(Evaluation::infinity);
	int beta = Evaluation::infinity;
	AlphaBetaValue result;
	while(alpha < beta){
		f = g;
		result = alphabeta<Evaluation>(game, manager, memory, f, f, depth, stop, depth, false);
		g = result.value;
		if(g == f){
			break;
		}
		if(g < f){
			beta = g;
		}else{
			alpha = g;
		}
	}
	return result;
}

template<class Evaluation>
AlphaBetaValue ialphabeta(GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int depth){
	bool stop = false;
	AlphaBetaValue result;
	for(int i=0;i<depth;i++){
		result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth, stop, depth, false);
	}
	return result;
}

template<class Evaluation>
void calphabeta(GameState *game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, bool *stop, int *depth, AlphaBetaValue *result, bool debug){
	AlphaBetaValue search_result;
	int _depth = 0;
	while(true){
		if(*stop){
			break;
		}
		search_result = alphabeta<Evaluation>(*game, manager, memory, alpha, beta, _depth, stop, _depth, debug);
		if(!(*stop)){
			// Don't take partial results
			*result = search_result;
			*depth = _depth;
		}
		_depth++;
	}
}

template<class Evaluation>
void salphabeta(GameState *game, std::shared_ptr<MoveManager> manager, std::shared_ptr<SearchMemory> memory, int alpha, int beta, std::shared_ptr<bool> stop, std::shared_ptr<int> depth, std::shared_ptr<AlphaBetaValue> result, bool debug){
	AlphaBetaValue search_result;
	int _depth = 0;
	while(true){
		if(*stop){
			break;
		}
		search_result = alphabeta<Evaluation>(*game, manager.get(), memory.get(), alpha, beta, _depth, stop.get(), _depth, debug);
		if(!(*stop)){
			// Don't take partial results
			(*result) = search_result;
			(*depth) = _depth;
		}
		_depth++;
	}
}

template<class Evaluation>
AlphaBetaValue talphabeta(GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int time, int *depth, bool debug){
	// time in milliseconds
	AlphaBetaValue result;
	if(debug){
		printf("debug talphabeta\n");
	}
	bool stop = false;
	std::thread t1 = std::thread(calphabeta<Evaluation>, &game, manager, memory, alpha, beta, &stop, depth, &result, debug);
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
	stop = true;
	t1.join();
	return result;
}


//template<class Evaluation>
//AlphaBetaValue mtdf(GameState &game, MoveManager &manager, SearchMemory &memory, float alpha, float beta, int depth){
//	// Check whether maximizing or minimizing
//	const bool maximize = game.whites_turn;
//	AlphaBetaValue result;
//	float orig_alpha = alpha;
//	float orig_beta = beta;
//	result.fail_low = false;
//	result.fail_high = false;
//	result.value = 0;
//	result.checkmate = false;
//	result.checkmate_maximize = false;
//	result.draw = false;
//	result.ply = 0;
//	result.best_move = nomove;
//
//	// Check the transposition table
//	TranspositionEntry entry = memory->tt->getitem(game);
//	if(entry != null_te && (entry.depth >= depth || (entry.value.checkmate && entry.depth >= 0))){
//		// The transposition entry is valid at this depth
//
//		if(entry.value.fail_low){
//			// This transposition entry is an upper bound
//			beta = (entry.value.value < beta)?(entry.value.value):beta;
//			if(alpha > beta){
//				result.fail_low = true;
//				result.fail_high = false;
//				result.value = alpha;
//				result.checkmate = false;
//				result.checkmate_maximize = false;
//				result.draw = false;
//				result.ply = 0;
//				result.best_move = nomove;
//				return result;
//			}
//		}else if(entry.value.fail_high){
//			// This transposition entry is a lower bound
//			alpha = (entry.value.value > alpha)?(entry.value.value):alpha;
//			if(alpha > beta){
//				result.fail_low = false;
//				result.fail_high = true;
//				result.value = beta;
//				result.checkmate = false;
//				result.checkmate_maximize = false;
//				result.draw = false;
//				result.ply = 0;
//				result.best_move = nomove;
//				return result;
//			}
//		}else{
//			// The transposition entry is exact
//			value = entry.value.value;
//			if(value < alpha){
//				result.fail_low = true;
//				result.fail_high = false;
//				result.checkmate = false;
//				result.draw = false;
//				result.ply = entry.value.ply;
//				result.value = alpha;
//				result.best_move = nomove;
//				return result;
//			}else if(value > beta){
//				result.fail_low = false;
//				result.fail_high = true;
//				result.checkmate = false;
//				result.draw = false;
//				result.ply = entry.value.ply;
//				result.value = beta;
//				result.best_move = nomove;
//				return result;
//			}else{
//				return entry.value;
//			}
//		}
//	}else if(entry != null_te){
//		guess = entry.value.value;
//	}
//
//
//	// Do mtdf
//	float proposal;
//	AlphaBetaValue search_result;
//	if(maximize){
//		while(alpha < beta){
//			proposal = lower_bound-(Evaluation::zero_window);
//			beta = (guess > proposal)?guess:proposal;
//			search_result = alphabeta<Evaluation>(game, manager, memory, beta-(Evaluation::zero_window), beta, depth);
//			if(search_result.fail_low){
//				// It's bad to fail low because the zero-window search is slower, so take a bigger step.
//
//			}
//
//		}
//
//	}
//
//
//
//}
//template<class Evaluation>
//AlphaBetaValue imtdf(GameState &game, MoveManager &manager, SearchMemory &memory, float alpha,
//					 float beta, double time_limit){
//	// Iterative deepening of mtdf with a time limit (in seconds)
//}

struct SimpleTimeManager{
	static std::chrono::milliseconds time_to_use(GameState &game, std::chrono::milliseconds ponder_time_used, std::chrono::milliseconds time_remaining){
		std::chrono::milliseconds result;
		int estimated_remaining_moves = 61 - game.fullmove_counter;
		if(estimated_remaining_moves < 5){
			estimated_remaining_moves = 5;
		}
		result = time_remaining / (2*estimated_remaining_moves);
		if(result > std::chrono::milliseconds(10000)){
			result = std::chrono::milliseconds(10000);
		}
//		result = ponder_time_used > std::chrono::milliseconds(10)?ponder_time_used:(std::chrono::milliseconds(1000));
//		result = (result > (time_remaining / 2))?(time_remaining / 2):result;
//		result = result>std::chrono::milliseconds(10)?result:std::chrono::milliseconds(10);
		return result;
	}
};

template <class Evaluation, class TimeManager>
class Player{
	public:
		Player(size_t tt_size, int num_killers, int num_history, size_t ee_size){
			printf("constructor 4\n");
			ponder_time_used = std::chrono::milliseconds(0);
			depth = std::make_shared<int>(0);
			*depth = 0;
			memory = std::shared_ptr<SearchMemory>(new SearchMemory(tt_size, num_killers, num_history, ee_size));
			manager = std::shared_ptr<MoveManager>(new MoveManager());
			stop = std::make_shared<bool>(true);
			result = std::shared_ptr<AlphaBetaValue>(new AlphaBetaValue());

		}
//		Player(){
//			printf("constructor 1\n");
//			ponder_time_used = std::chrono::milliseconds(0);
//			depth = std::shared_ptr<int>(0);
//			stop = shared_ptr<bool>(true);
//		}
		~Player(){
			if(search_thread->joinable()){
				*stop = true;
				search_thread->join();
				delete search_thread;
			}

		}
		void start_ponder(GameState &game){
			printf("start_ponder\n");
			if(!(*stop)){
				return;//Already pondering
			}
			*stop = false;
			ponder_start_time = std::chrono::high_resolution_clock::now();
			search_thread = new std::thread(salphabeta<Evaluation>, &game, manager, memory, -(Evaluation::infinity), Evaluation::infinity, stop, depth, result, false);
			printf("end start_ponder\n");
		}
		void stop_ponder(){
			printf("stop_ponder\n");
			*stop = true;
			search_thread->join();
			delete search_thread;
			ponder_stop_time = std::chrono::high_resolution_clock::now();
			ponder_time_used = std::chrono::duration_cast<std::chrono::milliseconds>(ponder_stop_time - ponder_start_time);
			printf("end stop_ponder\n");
		}
		AlphaBetaValue movesearch(GameState &game, int time_remaining){
			std::chrono::milliseconds time_to_use = TimeManager::time_to_use(game, ponder_time_used, std::chrono::milliseconds(time_remaining));
			*stop = false;
			search_thread = new std::thread(salphabeta<Evaluation>, &game, manager, memory, -(Evaluation::infinity), Evaluation::infinity, stop, depth, result, false);
			std::this_thread::sleep_for(time_to_use);
			*stop = true;
			search_thread->join();
			delete search_thread;
			return *result;
		}
		int get_depth(){
			return *depth;
		}
	private:
		std::shared_ptr<int> depth;
		std::shared_ptr<AlphaBetaValue> result;
		std::chrono::high_resolution_clock::time_point ponder_start_time;
		std::chrono::high_resolution_clock::time_point ponder_stop_time;
		std::chrono::milliseconds ponder_time_used;
		std::shared_ptr<bool> stop;
		std::thread *search_thread;
		std::shared_ptr<SearchMemory> memory;
		std::shared_ptr<MoveManager> manager;
};



#endif // MOVESEARCH_H_
