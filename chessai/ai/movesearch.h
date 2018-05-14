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

struct SimpleEvaluation{
	static const int infinity;
	static const int mate;
	static const int draw;
	static const int delta;
	static const int evaluate(GameState &brd){
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
		void record_cutoff(GameState &game, move &mv){
			MoveTable<int> *table;
			if(game.board_state.whites_turn){
				table = white_history;
			}else{
				table = black_history;
			}
			table->add(mv, 1);
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
		SearchMemory(size_t tt_size, int num_killers, int num_history){
			tt = new TranspositionTable(tt_size);
			killers = new KillerTable(num_killers);
			hh = new HistoryTable(num_history);
		}
		TranspositionTable *tt;
		KillerTable *killers;
		HistoryTable *hh;
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
		void generate_all(GameState &game, int depth){
			int index = getindex(depth);
			_num_moves[index] = all_moves(&game, buffer[index]);
		}
		void generate_noisy(GameState &game, int depth){
			int index = getindex(depth);
			_num_moves[index] = all_captures(&game, buffer[index]);
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
	private:
		// No search is likely to exceed 1000 ply, and
		// no position has more than 1000 possible moves
		static const int maxply = 1000;
		static const int maxmove = 1000;
		move buffer[maxply][maxmove];
		int _full_begin[maxply];
		int _full_end[maxply];
		int _pv_begin[maxply];
		int _pv_end[maxply];
		int _num_moves[maxply];
};

template<class Evaluation>
int quiesce(GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int depth){

	// Check whether maximizing or minimizing
	const bool maximize = game.board_state.whites_turn;

	// Get the current evaluation and possibly cut off immediately
	int result = Evaluation::evaluate(game);
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

	// Generate all legal moves.  Some of these will not be searched,
	// but we need to generate all moves to check for checkmate and
	// stalemate.
	manager->generate_all(game, depth);

	// Check for checkmates and draws
	if(manager->num_moves(depth) == 0){
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
	move *moves = manager->get_moves(depth);
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
AlphaBetaValue alphabeta(GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int depth, bool *stop, bool debug){
	// Not using negamax.  All scores will be from the perspective of white.  That is,
	// white seeks to maximize and black seeks to minimize.

	// Check whether maximizing or minimizing
	bool maximize = game.board_state.whites_turn;

	// Allocate the result
	AlphaBetaValue result;
	int value;

	// Check for draw by repetition or 50 move rule
	// This must be done before transposition table lookup
	// because the transposition table does not take the halfmove clock
	// or threefold clock and position record into account.
	if(game.halfmove_clock >= 50 || draw_by_repetition(&game, 2)){
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

	bool debug_ = depth==4?debug:false;
	moverecord rec;
	for(int i=(manager->full_begin(depth));i<(manager->pv_end(depth));i++){
		mv = moves[i];
		rec = manager->make(game, mv);
		if(i < manager->pv_begin(depth)){
			// Search full depth right away
			search_result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth-1, stop, debug_);
		}else{
			// Do a narrower search and make it larger if cutoff occurs
			if(maximize){
				search_result = alphabeta<Evaluation>(game, manager, memory, alpha, alpha, depth-1, stop, false);
				if(search_result.value > alpha && beta > alpha){
					// The narrow search returned a lower bound, so we must search again with full width
					search_result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth-1, stop, false);
				}
			}else{
				search_result = alphabeta<Evaluation>(game, manager, memory, beta, beta, depth-1, stop, false);
				if(search_result.value < beta && beta > alpha){
					// The narrow search returned an upper bound, so we must search again with full width
					search_result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth-1, stop, false);
				}
			}
		}
		manager->unmake(game, rec);
		if(maximize){
			if(search_result.value > beta){
				// Cut node.  Yay!
				memory->hh->record_cutoff(game, mv);
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
				memory->hh->record_cutoff(game, mv);
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

	// We checked everything.  Either it's an all node or a pv node.
	// Update transposition table and return.
	memory->tt->setitem(game, TranspositionEntry(game, result, depth, result.value < alpha, result.value > beta));
	return result;

}

template<class Evaluation>
AlphaBetaValue ialphabeta(GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int depth){
	bool stop = false;
	AlphaBetaValue result;
	for(int i=0;i<depth;i++){
		result = alphabeta<Evaluation>(game, manager, memory, alpha, beta, depth, stop, false);
	}
	return result;
}

template<class Evaluation>
void calphabeta(GameState *game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, bool *stop, int *depth, AlphaBetaValue *result){
	AlphaBetaValue search_result;
	int _depth = 0;
	while(true){
		if(*stop){
			break;
		}
		search_result = alphabeta<Evaluation>(*game, manager, memory, alpha, beta, _depth, stop, false);
		if(!(*stop)){
			// Don't take partial results
			*result = search_result;
			*depth = _depth;
		}
		_depth++;
	}
}

template<class Evaluation>
AlphaBetaValue talphabeta(GameState &game, MoveManager *manager, SearchMemory *memory, int alpha, int beta, int time, int *depth){
	// time in milliseconds
	AlphaBetaValue result;
	bool stop = false;
	std::thread t1 = std::thread(calphabeta<Evaluation>, &game, manager, memory, alpha, beta, &stop, depth, &result);
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



#endif // MOVESEARCH_H_
