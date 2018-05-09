#ifndef MOVESEARCH_H_
#define MOVESEARCH_H_
#include "bitboardlib.h"

template <typename ElementType>
class MoveTable{
	public:
		MoveTable(){
			this->num_best = 0;
		}
		void initialize(int num_best){
			this->num_best = num_best;
			best_scores = new ElementType[num_best];
			best_moves = new move[num_best];
		}
		MoveTable(int num_best) : MoveTable(){
			this->initialize(num_best);
		}
		~MoveTable(){
			delete[] best_scores;
			delete[] best_moves;
		}
		bool compare(move &lhs, move &rhs){
			// The higher the move's score, the lower the move (in search order)
			return (get(lhs) < get(rhs));

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
	bool fail_low;
	bool fail_high;
	bool checkmate;
	bool draw;
	bool checkmate_maximize;
	int ply;
	float value;
	move best_move;
	AlphaBetaValue(){
		fail_low = false;
		fail_high = false;
		checkmate = false;
		draw = false;
		checkmate_maximize = false;
		ply = 0;
		value = 0;
	}
	bool operator==(const AlphaBetaValue &other) const{
		if(fail_low == other.fail_low && fail_high == other.fail_high &&
			checkmate == other.checkmate && draw == other.draw &&
			checkmate_maximize == other.checkmate_maximize &&
			ply == other.ply && value == other.value && best_move == other.best_move){
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
	AlphaBetaValue value;
	BoardState brd;
	TranspositionEntry(){
		this->key = 0;
		this->depth = 0;
		this->value = empty_alpha_beta_value;
		this->brd = empty_board_state;
	}
	TranspositionEntry(GameState &game, AlphaBetaValue &value, int &depth){
		this->key = game.hash;
		this->depth = depth;
		this->value = value;
		this->brd = game.board_state;
	}
	bool operator==(const TranspositionEntry &other) const{
		if(key == other.key && depth == other.depth
			&& value == other.value && brd == other.brd){
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
		TranspositionTable(size_t size) : TranspositionTable() {
			initialize(size);
		}
		~TranspositionTable(){
			delete[] this->data;
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

struct SimpleEvaluation{
	static const float mate;
	static const float draw;
	static const float evaluate(GameState &brd){
		float white_score, black_score;
		white_score = 0;
		black_score = 0;
		white_score += 100 * population_count(brd.board_state.white & brd.board_state.p);
		white_score += 320 * population_count(brd.board_state.white & brd.board_state.n);
		white_score += 330 * population_count(brd.board_state.white & brd.board_state.b);
		white_score += 500 * population_count(brd.board_state.white & brd.board_state.r);
		white_score += 900 * population_count(brd.board_state.white & brd.board_state.q);
		//white_score += 200000 * population_count(brd.board_state.white & brd.board_state.k);

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
		//black_score += 200000 * population_count(brd.board_state.black & brd.board_state.k);

		black_score += 1 * 100 * population_count(brd.board_state.black & center4);
		black_score += 1 * 100 * population_count(brd.board_state.black & center16);
		black_score += 5 * population_count(brd.board_state.black & brd.board_state.p & rank_1);
		black_score += 4 * population_count(brd.board_state.black & brd.board_state.p & rank_2);
		black_score += 3 * population_count(brd.board_state.black & brd.board_state.p & rank_3);

		return white_score - black_score;

	}

};

class KillerTable{
	public:
		static const int num_ply;
		int highest_ply_seen;
		MoveTable<int> *killers;
		int num_killers;
		KillerTable(){
			highest_ply_seen = 0;
		}
		void initialize(int num_killers){
			killers = new MoveTable<int>[num_ply];
			this->num_killers = num_killers;
			for(int i=0;i<num_ply;i++){
				killers[i].initialize(num_killers);
			}
		}
		KillerTable(int num_killers) : KillerTable(){
			initialize(num_killers);
		}
		~KillerTable(){
			delete[] killers;
		}
		void record_cutoff(GameState &game, move &mv){
			int ply = game.halfmove_counter;
			if(ply > highest_ply_seen){
				clear(ply);
				highest_ply_seen = ply;
			}
			int index = ply % num_ply;
			MoveTable<int> table = killers[index];
			table.add(mv, 1);
		}
		int score(GameState &game, move &mv){
			int index = game.halfmove_counter % num_ply;
			MoveTable<int> table = killers[index];
			int rank = table.rank(mv);
			if(rank == -1){
				return 0;
			}
			return num_killers - rank;
		}
		void clear(int ply){
			// Clear the table for the ply
			int index = ply % num_ply;
			MoveTable<int> table = killers[index];
			table.reset(0);
		}
};

class HistoryTable{
	public:
		MoveTable<int> white_history;
		MoveTable<int> black_history;
		int num_history;
		HistoryTable(){}
		void initialize(int num_history){
			this->num_history = num_history;
			white_history = MoveTable<int>(num_history);
			black_history = MoveTable<int>(num_history);
		}
		HistoryTable(int num_history) : HistoryTable() {
			initialize(num_history);
		}
		void record_cutoff(GameState &game, move &mv){
			MoveTable<int> table;
			if(game.board_state.whites_turn){
				table = white_history;
			}else{
				table = black_history;
			}
			table.add(mv, 1);
		}
		int score(GameState &game, move &mv){
			MoveTable<int> table;
			if(game.board_state.whites_turn){
				table = white_history;
			}else{
				table = black_history;
			}
			int rank = table.rank(mv);
			if(rank == -1){
				return 0;
			}
			return num_history - rank;
		}
};

class SearchMemory{
	public:
		SearchMemory(size_t tt_size, int num_killers, int num_history){
			tt = TranspositionTable(tt_size);
			killers = KillerTable(num_killers);
			hh = HistoryTable(num_history);
		}
		TranspositionTable tt;
		KillerTable killers;
		HistoryTable hh;
};

//struct AnnotatedMove{
//	AnnotatedMove(move &mv){
//		this->mv = mv;
//		sort_score = 0;
//	}
//	move mv;
//	int sort_score;
//};

class MoveManager{
	// Responsible for move ordering
	public:
		void generate_all(GameState &game, int depth){
			num_moves = all_moves(&game, buffer[depth % maxply]);
		}
		void generate_noisy(GameState &game, int depth){
			num_moves = all_captures(&game, buffer[depth % maxply]);
		}
		void order_all(GameState &game, SearchMemory &memory, int depth){
			// Determine best move from transposition table
			TranspositionEntry entry = memory.tt.getitem(game);
			move best_move = nomove;
			if(entry != null_te){
				best_move = entry.value.best_move;
			}

			// Score all moves based on where they will be in the order
			move *current_buffer = buffer[depth % maxply];
			int capture_count = 0;
			piece capture_target;
			move mv;
			int killer_score;
			int history_score;
			int capture_score;
			for(int i=0;i<num_moves;i++){
				mv = current_buffer[i];
				mv.sort_score = 0;
				if(mv == best_move){
					mv.sort_score += 100000;
				}

				// If there are any killer moves, they will be just below the best move
				// from the transposition table
				mv.sort_score += 1000 * memory.killers.score(game, mv);

				// Capture score is at most 560
				// Prefer to capture the biggest piece, then prefer to use the smallest
				capture_target = game.piece_map[mv.from_square];
				if(capture_target != no){
					capture_count += 1;
				}
				mv.sort_score += 10 * ((10 * piece_to_search_order(game.piece_map[mv.to_square])) + (6 - piece_to_search_order(capture_target)));

				// Use history heuristic for any moves that remain
				if(game.board_state.whites_turn){
					mv.sort_score += memory.hh.score(game, mv);
				}else{
					mv.sort_score += memory.hh.score(game, mv);
				}

			}

			// Sort moves based on sort_score.  Highest to lowest.
			std::sort(current_buffer, current_buffer + num_moves);

			// Keep track of this stuff
			full_begin = 0;
			full_end = num_moves > 3?3:num_moves; // TODO: Experiment with this.
			pv_begin = full_end;
			pv_end = num_moves;

		}
//		void order_noisy(GameState &game, SearchMemory<num_killers, num_history> &memory) = order_all;
		moverecord make(GameState &game, move &mv){
			return make_move(&game, &mv);
		}
		void unmake(GameState &game, moverecord &rec){
			unmake_move(&game, &rec);
		}
		move *get_moves(int depth){
			return buffer[depth % maxply];
		}
		int full_begin;
		int full_end;
		int pv_begin;
		int pv_end;
		int num_moves;
	private:
		// No search is likely to exceed 1000 ply, and
		// no position has more than 1000 possible moves
		static const int maxply = 1000;
		static const int maxmove = 1000;
		move buffer[maxply][maxmove];


};



template<class Evaluation>
AlphaBetaValue quiesce(GameState &game, MoveManager &manager, SearchMemory &memory, float alpha, float beta, int depth){
	// Note that the caller has already ensured that this is not a terminal node
	// The main difference between quiesce and alphabeta is that we stop searching early if the
	// current evaluation ever gets too good.  We're only looking for obvious reasons not to do the move.

	AlphaBetaValue result;

	// Check whether maximizing or minimizing
	const bool maximize = game.board_state.whites_turn;

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
	bool in_check = own_check(&game);// TODO: The caller may have already evaluated this.
	if(in_check){
		manager.generate_all(game, depth);
		manager.order_all(game, memory, depth);
	}else{
		manager.generate_noisy(game, depth);
		manager.order_all(game, memory, depth); // TODO: Use order_noisy
	}

	// Recurse
	AlphaBetaValue search_result;
	move mv;
	moverecord rec;
	move *moves = manager.get_moves(depth);
	for(int i=manager.full_begin;i<manager.pv_end;i++){
		mv = moves[i];
		rec = manager.make(game, mv);
		if(i < manager.pv_begin){
			// Search full depth right away
			search_result = quiesce<Evaluation>(game, manager, memory, alpha, beta, depth-1);
		}else{
			// Do a narrower search and make it larger if no cutoff occurs
			if(maximize){
				search_result = quiesce<Evaluation>(game, manager, memory, alpha, alpha+1, depth-1);
				if(search_result.fail_high){
					// The narrow search returned a lower bound, so we must search again with full width
					search_result = quiesce<Evaluation>(game, manager, memory, alpha, beta, depth-1);
				}
			}else{
				search_result = quiesce<Evaluation>(game, manager, memory, beta-1, beta, depth-1);
				if(search_result.fail_low){
					// The narrow search returned an upper bound, so we must search again with full width
					search_result = quiesce<Evaluation>(game, manager, memory, alpha, beta, depth-1);
				}
			}
		}
		manager.unmake(game, rec);
		if((maximize && search_result.fail_high) || ((!maximize) && search_result.fail_low)){
			// Cut node.  Yay!
			memory.tt.setitem(game, TranspositionEntry(game, result, depth));
			return search_result;
		}else if(((!maximize) && search_result.fail_high) || (maximize && search_result.fail_low)){
			// Potential all node. Ugh.
		}
		else{
			// It's a potential PV node!
			if((maximize && (search_result.value >= result.value)) || ((!maximize) && (search_result.value <= result.value))){
				result = search_result;
				if(search_result.checkmate){
					// Prefer sooner checkmates if we win, later if we lose
					if((result.ply > search_result.ply) && (result.checkmate_maximize != maximize)){
						result = search_result;
					}else if((result.ply < search_result.ply) && (result.checkmate_maximize == maximize)){
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



template<class Evaluation>
AlphaBetaValue alphabeta(GameState &game, MoveManager &manager, SearchMemory &memory, float alpha, float beta, int depth){
	// Not using negamax.  All scores will be from the perspective of white.  That is,
	// white seeks to maximize and black seeks to minimize.

	// Check whether maximizing or minimizing
	const bool maximize = game.board_state.whites_turn;

	// Allocate the result
	AlphaBetaValue result;
	float value;
	float guess;
	bool did_guess = false;

	// Check transposition table.  Can update alpha or beta or simply return.
	TranspositionEntry entry = memory.tt.getitem(game);
	if(entry != null_te && (entry.depth >= depth || (entry.value.checkmate && entry.depth >= 0))){
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
	manager.generate_all(game, depth);

	// Check for checkmates and draws
	if(manager.num_moves == 0){
		if(own_check(&game)){
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
	float stand_pat;
	if(depth <= 0){
		stand_pat = Evaluation::evaluate(game);
		result = quiesce<Evaluation>(game, manager, memory, alpha, beta, stand_pat);
		memory.tt.setitem(game, TranspositionEntry(game, result, depth));
		return result;
	}

	// Order moves
	manager.order_all(game, memory, depth);

	// Do any internal iterative deepening or other scouting steps, and
	// possibly reorder

	// Iterate over full moves
	move mv;
	AlphaBetaValue search_result;

	// Begin by assuming an all node
	if(maximize){
		result.fail_low = true;
		result.fail_high = false;
		result.checkmate = false;
		result.draw = false;
		result.checkmate_maximize = false;
		result.ply = 0;
		result.value = alpha;
		result.best_move = nomove;
	}else{
		result.fail_low = false;
		result.fail_high = true;
		result.checkmate = false;
		result.draw = false;
		result.checkmate_maximize = false;
		result.ply = 0;
		result.value = beta;
		result.best_move = nomove;
	}

	move *moves = manager.get_moves(depth);
	moverecord rec;
	for(int i=manager.full_begin;i<manager.pv_end;i++){
		mv = moves[i];
		rec = manager.make(game, mv);
		if(i < manager.pv_begin){
			// Search full depth right away
			search_result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth-1);
		}else{
			// Do a narrower search and make it larger if cutoff occurs
			if(maximize){
				search_result = alphabeta<Evaluation>(game, manager, memory, alpha, alpha+1, depth-1);
				if(search_result.fail_high){
					// The narrow search returned a lower bound, so we must search again with full width
					search_result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth-1);
				}
			}else{
				search_result = alphabeta<Evaluation>(game, manager, memory, beta-1, beta, depth-1);
				if(search_result.fail_low){
					// The narrow search returned an upper bound, so we must search again with full width
					search_result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth-1);
				}
			}
		}
		manager.unmake(game, rec);
		if((maximize && search_result.fail_high) || ((!maximize) && search_result.fail_low)){
			// Cut node.  Yay!
			memory.hh.record_cutoff(game, mv);
			memory.killers.record_cutoff(game, mv);
			memory.tt.setitem(game, TranspositionEntry(game, result, depth));
			return search_result;
		}else if(((!maximize) && search_result.fail_high) || (maximize && search_result.fail_low)){
			// Potential all node. Ugh.
		}
		else{
			// It's a potential PV node!
			if((maximize && (search_result.value >= result.value)) || ((!maximize) && (search_result.value <= result.value))){
				result = search_result;
				if(search_result.checkmate){
					// Prefer sooner checkmates if we win, later if we lose
					if((result.ply > search_result.ply) && (result.checkmate_maximize != maximize)){
						result = search_result;
					}else if((result.ply < search_result.ply) && (result.checkmate_maximize == maximize)){
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
//template<class Evaluation>
//AlphaBetaValue mtdf(GameState &game, MoveManager &manager, SearchMemory &memory, float guess, int depth){
//	// Check whether maximizing or minimizing
//	const bool maximize = game.whites_turn;
//
//}
//template<class Evaluation>
//AlphaBetaValue imtdf(GameState &game, MoveManager &manager, SearchMemory &memory, float alpha,
//					 float beta, double time_limit){
//	// Iterative deepening of mtdf with a time limit (in seconds)
//}



#endif // MOVESEARCH_H_
