#ifndef MOVESEARCH_H_
#define MOVESEARCH_H_
#include "zobrist.h"
#include "bitboardlib.h"

class MoveTable{
	public:
		MoveTable();
		~MoveTable();
		bool compare(move &lhs, move &rhs);
		void update(move &mv, float amount);
		void set(move &mv, float amount);
		void reset();
	private:
		float elements[64];
}

struct AlphaBetaValue{
	bool fail_low;
	bool fail_high;
	bool checkmate;
	bool draw;
	bool checkmate_maximize;
	int ply;
	float value;
	move best_move;
};


struct TranspositionEntry{
	zobrist_int key;
	int depth;
	AlphaBetaValue value;
	BoardState brd;
	TranspositionEntry(GameState &game, AlphaBetaValue value, int depth);
};

class TranspositionTable {
	public:
		TranspositionTable(size_t size);
		~TranspositionTable();
		void setitem(GameState &brd, TranspositionEntry &entry);
		unsigned long int getindex(GameState &game);
		bool exists(GameState &brd);
		TranspositionEntry getitem(GameState &game);
	private:

};

struct SimpleEvaluation{
	static const float aspiration = 50;
	static const float mate = 200000;
	static const float draw = 0;
	static float piece_value(GameState &brd, brdidx idx){
		// TODO:

	}
	static float evaluate(gamestate &brd){
		float white_score, black_score;
		white_score = 0;
		black_score = 0;
		white_score += 100 * population_count(brd->board_state.white & brd->board_state.p);
		white_score += 320 * population_count(brd->board_state.white & brd->board_state.n);
		white_score += 330 * population_count(brd->board_state.white & brd->board_state.b);
		white_score += 500 * population_count(brd->board_state.white & brd->board_state.r);
		white_score += 900 * population_count(brd->board_state.white & brd->board_state.q);
		//white_score += 200000 * population_count(brd->board_state.white & brd->board_state.k);

		white_score += 1 * population_count(brd->board_state.white & center4);
		white_score += 1 * population_count(brd->board_state.white & center16);
		white_score += 5 * population_count(brd->board_state.white & brd->board_state.p & rank_7);
		white_score += 4 * population_count(brd->board_state.white & brd->board_state.p & rank_6);
		white_score += 3 * population_count(brd->board_state.white & brd->board_state.p & rank_5);

		black_score += 100 * population_count(brd->board_state.black & brd->board_state.p);
		black_score += 320 * population_count(brd->board_state.black & brd->board_state.n);
		black_score += 330 * population_count(brd->board_state.black & brd->board_state.b);
		black_score += 500 * population_count(brd->board_state.black & brd->board_state.r);
		black_score += 900 * population_count(brd->board_state.black & brd->board_state.q);
		//black_score += 200000 * population_count(brd->board_state.black & brd->board_state.k);

		black_score += 1 * 100 * population_count(brd->board_state.black & center4);
		black_score += 1 * 100 * population_count(brd->board_state.black & center16);
		black_score += 5 * population_count(brd->board_state.black & brd->board_state.p & rank_1);
		black_score += 4 * population_count(brd->board_state.black & brd->board_state.p & rank_2);
		black_score += 3 * population_count(brd->board_state.black & brd->board_state.p & rank_3);

		return white_score - black_score;

	}

}

template <struct Evaluation>

struct SearchMemory{

};

struct AnnotatedMove{
	AnnotatedMove(move &mv);
	move mv;
	float guess;
	bool has_guess;
};



class MoveManager{
	// Responsible for move ordering
	public:
		MoveManager();
		~MoveManager();
		void generate_all(GameState &game, SearchMemory &memory);
		void generate_noisy(GameState &game, SearchMemory &memory); // For quiescence
		void order_all(GameState &game, SearchMemory &memory);
		void order_noisy(GameState &game, SearchMemory &memory);
		void make(GameState &game, AnnotatedMove &mv);
		void unmake(GameState &game, AnnotatedMove &mv);
		int full_begin;
		int full_end;
		int pv_begin;
		int pv_end;
	private:
		// No game is likely to exceed 1000 ply, and
		// no position has more than 1000 possible moves
		static const int maxply = 10000;
		static const int maxmove = 1000;
		AnnotatedMove buffer[maxply][maxmove];

};


void MoveManager::order_all(GameState &game, SearchMemory &memory){
	// Check transposition table and put the best move at the front
	// if there is one

	// Next do any killer moves

	// Now use captures in order by piece values

	// Now use history heuristic



}

AlphaBetaValue alphabeta(GameState &game, MoveManager &manager, SearchMemory &memory, float alpha, float beta, int depth){
	// Not using negamax.  All scores will be from the perspective of white.  That is,
	// white seeks to maximize and black seeks to minimize.

	// Check whether maximizing or minimizing
	const bool maximize = game.whites_turn;

	// Allocate the result
	AlphaBetaValue result;
	float value;
	float guess;
	bool did_guess = false;

	// Check transposition table.  Can update alpha or beta or simply return.
	TranspositionEntry entry = memory.tt.getitem(game);
	if(entry.depth >= depth || (entry.value.checkmate && entry.depth >= 0)){
		// The transposition entry is valid at this depth

		if(entry.value.fail_low){
			// This transposition entry is an upper bound
			beta = (entry.value.value < beta)?(entry.value.value):beta;
		}else if(entry.value.fail_high){
			// This transposition entry is a lower bound
			alpha = (entry.value.value > alpha)?(entry.value.value):alpha;
		}else{
			// The transposition entry is exact
			value = entry.value.value;
			if(value < alpha){
				result.fail_low = true;
				result.fail_high = false;
				result.checkmate = false;
				result.draw = false;
				result.ply = entry.value.ply;
				result.value = alpha;
				result.best_move = nomove;
				return result;
			}else if(value > beta){
				result.fail_low = false;
				result.fail_high = true;
				result.checkmate = false;
				result.draw = false;
				result.ply = entry.value.ply;
				result.value = beta;
				result.best_move = nomove;
				return result;
			}else{
				return entry.value;
			}
		}
	}

	// Generate moves
	manager.generate_all(game, memory);

	// Check for checkmates and draws
	if(manager.num_moves == 0){
		if(own_check(game)){
			// Checkmate.  We lose.
			result.value = maximize?(-(Evaluation::mate)):(Evaluation::mate);
			result.checkmate = true;
			result.draw = false;
			result.ply = game.halfmove_counter;
			result.checkmate_maximize = maximize;
		}else{
			// Stalemate
			result.value = Evaluation::draw;
			result.checkmate = false;
			result.draw = true;
			result.ply = game.halfmove_counter;
//			result.checkmate_maximize = maximize;
		}
		//
		result.fail_high = (result.value < beta);
		result.fail_low = (result.value > alpha);
		if(result.fail_low){
			result.value = alpha;
		}
		if(result.fail_high){
			result.value = beta;
		}
		result.best_move = nomove;
		memory.tt.setitem(game, TranspositionEntry(game, result, depth));
		return result;
	}

	// If this is a leaf node, call quiescence search
	if(depth <= 0){
		stand_pat = Evaluation::evaluate(game);
		result = quiesce(game, manager, memory, alpha, beta, stand_pat);
		memory.tt.setitem(game, TranspositionEntry(game, result, depth));
		return result
	}

	// Order moves
	manager.order_all(game, memory)

	// Do any internal iterative deepening or other scouting steps, and
	// possibly reorder

	// Iterate over full moves
	AnnotatedMove mv;
	AlphaBetaValue search_result;

	// Begin by assuming an all node
	if(maximize){
		result.fail_low = true;
		result.fail_high = false;
		result.terminal = false;
		result.value = alpha;
		result.best_move = nomove;
	}else{
		result.fail_low = false;
		result.fail_high = true;
		result.terminal = false;
		result.value = beta;
		result.best_move = nomove;
	}

	AnnotatedMove *moves = manager.get_moves(game);
	for(int i=manager.full_begin;i<manager.pv_end;i++){
		mv = moves[i];
		manager.make_move(game, mv);
		if(i < pv_begin){
			// Search full depth right away
			search_result = alphabeta(game, manager, memory, alpha, beta, depth-1)
		}else{
			// Do a narrower search and make it larger if no cutoff occurs
			if(maximize){
				search_result = alphabeta(game, manager, memory, alpha, alpha+1, depth-1)
				if(search_result.fail_high){
					// The narrow search returned a lower bound, so we must search again with full width
					search_result = alphabeta(game, manager, memory, alpha, beta, depth-1)
				}
			}else{
				search_result = alphabeta(game, manager, memory, beta-1, beta, depth-1)
				if(search_result.fail_low){
					// The narrow search returned an upper bound, so we must search again with full width
					search_result = alphabeta(game, manager, memory, alpha, beta, depth-1)
				}
			}
		}
		manager.unmake_move(game, mv);
		if((maximize && search_result.fail_high) || ((!maximize) &&& search_result.fail_low)){
			// Cut node.  Yay!
			memory.tt.setitem(game, TranspositionEntry(game, result, depth));
			return search_result;
		}else if(((!maximize) && search_result.fail_high) || (maximize &&& search_result.fail_low)){
			// Potential all node. Ugh.
		}
		else{
			// It's a potential PV node!
			if((maximize && (search_result.value >= result.value)) || ((!maximize) && (search_result.value <= result.value))){
				result = search_result;
				if(search_result.checkmate){
					// Prefer sooner checkmates if we win, later if we lose
					if((result.terminal_ply > search_result.terminal_ply) && (result.terminal_maximize != maximize)){
						result = search_result;
					}else if((result.terminal_ply < search_result.terminal_ply) && (result.terminal_maximize == maximize)){
						result = search_result;
					}
				}
				if(maximize){
					alpha = result.value;
				}else{
					beta = result.value;
				}
			}
		}


	}

	// We checked everything.  Either it's an all node or a pv node.
	// Update transposition table and return.
	memory.tt.setitem(game, TranspositionEntry(game, result, depth));
	return result;

}

//// TODO: Can this simply be replaced with mtdf?
//AlphaBetaValue pvsearch(GameState &game, MoveManager &manager, SearchMemory &memory, float alpha, float beta, int depth){
//	// Check whether maximizing or minimizing
//
//	// Look for a cutoff with a narrow window
//
//	// If there was no cuttoff, extend the window
//}

AlphaBetaValue mtdf(GameState &game, MoveManager &manager, SearchMemory &memory, float guess, int depth){
	// Check whether maximizing or minimizing
	const bool maximize = game.whites_turn;

}

AlphaBetaValue imtdf(GameState &game, MoveManager &manager, SearchMemory &memory, float alpha,
					 float beta, double time_limit){
	// Iterative deepening of mtdf with a time limit (in seconds)
}

bool is_quiet(GameState &game, AnnotatedMove &mv){
	game.piece_map[mv.to_square] == no;

}

AlphaBetaValue quiesce(GameState &game, MoveManager &manager, SearchMemory &memory, float alpha, float beta, int depth){
	// Note that the caller has already ensured that this is not a terminal node
	// The main difference between quiesce and alphabeta is that we stop searching early if the
	// current evaluation ever gets too good.

	AlphaBetaValue result;

	// Check whether maximizing or minimizing
	const bool maximize = game.whites_turn;

	// Get the current evaluation and possibly cut off immediately
	result.value = Evaluation::evaluate(game);
	result.fail_high = false;
	result.fail_low = false;
	result.checkmate = false;
	result.draw = false;
	result.ply = game.halfmove_counter;
	if(maximize){
		if(result.value > beta){
			result.value = beta;
			result.fail_high = true;
			return result;
		}else if(result.value > alpha){
			alpha = result.value;
		}
	}else{
		if(result.value < alpha){
			result.value = alpha;
			result.fail_low = true;
			return result;
		}else if(result.value < beta){
			beta = result.value;
		}
	}

	// Generate and order moves
	bool in_check = own_check(game);// TODO: The caller may have already evaluated this.
	if(in_check){
		manager.generate_all(game, memory);
		manager.order_all(game, memory);
	}else{
		manager.generate_noisy(game, memory);
		manager.order_noisy(game, memory);
	}

	// Recurse
	AnnotatedMove *moves = manager.get_moves(game);
	for(int i=manager.full_begin;i<manager.pv_end;i++){
		mv = moves[i];
		manager.make_move(game, mv);
		if(i < pv_begin){
			// Search full depth right away
			search_result = quiesce(game, manager, memory, alpha, beta, depth-1)
		}else{
			// Do a narrower search and make it larger if no cutoff occurs
			if(maximize){
				search_result = quiesce(game, manager, memory, alpha, alpha+1, depth-1)
				if(search_result.fail_high){
					// The narrow search returned a lower bound, so we must search again with full width
					search_result = quiesce(game, manager, memory, alpha, beta, depth-1)
				}
			}else{
				search_result = quiesce(game, manager, memory, beta-1, beta, depth-1)
				if(search_result.fail_low){
					// The narrow search returned an upper bound, so we must search again with full width
					search_result = quiesce(game, manager, memory, alpha, beta, depth-1)
				}
			}
		}
		manager.unmake_move(game, mv);
		if((maximize && search_result.fail_high) || ((!maximize) &&& search_result.fail_low)){
			// Cut node.  Yay!
			memory.tt.setitem(game, TranspositionEntry(game, result, depth));
			return search_result;
		}else if(((!maximize) && search_result.fail_high) || (maximize &&& search_result.fail_low)){
			// Potential all node. Ugh.
		}
		else{
			// It's a potential PV node!
			if((maximize && (search_result.value >= result.value)) || ((!maximize) && (search_result.value <= result.value))){
				result = search_result;
				if(search_result.checkmate){
					// Prefer sooner checkmates if we win, later if we lose
					if((result.terminal_ply > search_result.terminal_ply) && (result.terminal_maximize != maximize)){
						result = search_result;
					}else if((result.terminal_ply < search_result.terminal_ply) && (result.terminal_maximize == maximize)){
						result = search_result;
					}
				}
				if(maximize){
					alpha = result.value;
				}else{
					beta = result.value;
				}
			}
		}
	}

	// Update transposition table and return.
	memory.tt.setitem(game, TranspositionEntry(game, result, depth));
	return result;

}




#endif // MOVESEARCH_H_
