#include "bitboardlib.h"
#include <stdio.h>
#include <tinythread.h>
#include <unistd.h>

using namespace tthread;

const bitboard empty = 0x0000000000000000ULL;
const bitboard full = 0xFFFFFFFFFFFFFFFFULL;
const bitboard p0 = (0x1ULL << 0);
const bitboard p1 = (0x1ULL << 1);
const bitboard p2 = (0x1ULL << 2);
const bitboard p3 = (0x1ULL << 3);
const bitboard p4 = (0x1ULL << 4);
const bitboard p5 = (0x1ULL << 5);
const bitboard p6 = (0x1ULL << 6);
const bitboard p7 = (0x1ULL << 7);
const bitboard p8 = (0x1ULL << 8);
const bitboard p9 = (0x1ULL << 9);
const bitboard p10 = (0x1ULL << 10);
const bitboard p11 = (0x1ULL << 11);
const bitboard p12 = (0x1ULL << 12);
const bitboard p13 = (0x1ULL << 13);
const bitboard p14 = (0x1ULL << 14);
const bitboard p15 = (0x1ULL << 15);
const bitboard p16 = (0x1ULL << 16);
const bitboard p17 = (0x1ULL << 17);
const bitboard p18 = (0x1ULL << 18);
const bitboard p19 = (0x1ULL << 19);
const bitboard p20 = (0x1ULL << 20);
const bitboard p21 = (0x1ULL << 21);
const bitboard p22 = (0x1ULL << 22);
const bitboard p23 = (0x1ULL << 23);
const bitboard p24 = (0x1ULL << 24);
const bitboard p25 = (0x1ULL << 25);
const bitboard p26 = (0x1ULL << 26);
const bitboard p27 = (0x1ULL << 27);
const bitboard p28 = (0x1ULL << 28);
const bitboard p29 = (0x1ULL << 29);
const bitboard p30 = (0x1ULL << 30);
const bitboard p31 = (0x1ULL << 31);
const bitboard p32 = (0x1ULL << 32);
const bitboard p33 = (0x1ULL << 33);
const bitboard p34 = (0x1ULL << 34);
const bitboard p35 = (0x1ULL << 35);
const bitboard p36 = (0x1ULL << 36);
const bitboard p37 = (0x1ULL << 37);
const bitboard p38 = (0x1ULL << 38);
const bitboard p39 = (0x1ULL << 39);
const bitboard p40 = (0x1ULL << 40);
const bitboard p41 = (0x1ULL << 41);
const bitboard p42 = (0x1ULL << 42);
const bitboard p43 = (0x1ULL << 43);
const bitboard p44 = (0x1ULL << 44);
const bitboard p45 = (0x1ULL << 45);
const bitboard p46 = (0x1ULL << 46);
const bitboard p47 = (0x1ULL << 47);
const bitboard p48 = (0x1ULL << 48);
const bitboard p49 = (0x1ULL << 49);
const bitboard p50 = (0x1ULL << 50);
const bitboard p51 = (0x1ULL << 51);
const bitboard p52 = (0x1ULL << 52);
const bitboard p53 = (0x1ULL << 53);
const bitboard p54 = (0x1ULL << 54);
const bitboard p55 = (0x1ULL << 55);
const bitboard p56 = (0x1ULL << 56);
const bitboard p57 = (0x1ULL << 57);
const bitboard p58 = (0x1ULL << 58);
const bitboard p59 = (0x1ULL << 59);
const bitboard p60 = (0x1ULL << 60);
const bitboard p61 = (0x1ULL << 61);
const bitboard p62 = (0x1ULL << 62);
const bitboard p63 = (0x1ULL << 63);
const bitboard places[64] = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16,
						  p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32,
						  p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, 
						  p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59, p60, p61, p62, p63};

const bitboard file_a = 0x0101010101010101ULL;
const bitboard file_b = 0x0202020202020202ULL;
const bitboard file_c = 0x0404040404040404ULL;
const bitboard file_d = 0x0808080808080808ULL;
const bitboard file_e = 0x1010101010101010ULL;
const bitboard file_f = 0x2020202020202020ULL;
const bitboard file_g = 0x4040404040404040ULL;
const bitboard file_h = 0x8080808080808080ULL;
const bitboard files[8] = {file_a, file_b, file_c, file_d, file_e, file_f, file_g, file_h};

const bitboard rank_1 = 0x00000000000000FFULL;
const bitboard rank_2 = 0x000000000000FF00ULL;
const bitboard rank_3 = 0x0000000000FF0000ULL;
const bitboard rank_4 = 0x00000000FF000000ULL;
const bitboard rank_5 = 0x000000FF00000000ULL;
const bitboard rank_6 = 0x0000FF0000000000ULL;
const bitboard rank_7 = 0x00FF000000000000ULL;
const bitboard rank_8 = 0xFF00000000000000ULL;
const bitboard ranks[8] = {rank_1, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8};

const bitboard white_castle_king_open = 0x0000000000000060ULL;
const bitboard black_castle_king_open = 0x6000000000000000ULL;
const bitboard castle_king_rook = 0x8000000000000080ULL;
const bitboard white_castle_queen_open = 0x000000000000000EULL;
const bitboard black_castle_queen_open = 0x0E00000000000000ULL;
const bitboard castle_queen_rook = 0x0100000000000001ULL;

const bitboard center4 = (rank_4 | rank_5) & (file_d | file_e);
const bitboard center16 = (rank_3 | rank_4 | rank_5 | rank_6) & (file_c | file_d | file_e | file_f);;

const bitboard diag_0 = 0x8040201008040201ULL;
const bitboard diag_1 = step_west(diag_0);
const bitboard diag_2 = step_west(diag_1);
const bitboard diag_3 = step_west(diag_2);
const bitboard diag_4 = step_west(diag_3);
const bitboard diag_5 = step_west(diag_4);
const bitboard diag_6 = step_west(diag_5);
const bitboard diag_7 = step_west(diag_6);
const bitboard diag_15 = step_east(diag_0);
const bitboard diag_14 = step_east(diag_15);
const bitboard diag_13 = step_east(diag_14);
const bitboard diag_12 = step_east(diag_13);
const bitboard diag_11 = step_east(diag_12);
const bitboard diag_10 = step_east(diag_11);
const bitboard diag_9 = step_east(diag_10);
const bitboard diags[16] = {diag_0, diag_1, diag_2, diag_3, diag_4, diag_5, diag_6, diag_7, 0,
							diag_9, diag_10, diag_11, diag_12, diag_13, diag_14, diag_15};

const bitboard antidiag_0 = 0x0102040810204080ULL;
const bitboard antidiag_1 = step_south(antidiag_0);
const bitboard antidiag_2 = step_south(antidiag_1);
const bitboard antidiag_3 = step_south(antidiag_2);
const bitboard antidiag_4 = step_south(antidiag_3);
const bitboard antidiag_5 = step_south(antidiag_4);
const bitboard antidiag_6 = step_south(antidiag_5);
const bitboard antidiag_7 = step_south(antidiag_6);
const bitboard antidiag_15 = step_north(antidiag_0);
const bitboard antidiag_14 = step_north(antidiag_15);
const bitboard antidiag_13 = step_north(antidiag_14);
const bitboard antidiag_12 = step_north(antidiag_13);
const bitboard antidiag_11 = step_north(antidiag_12);
const bitboard antidiag_10 = step_north(antidiag_11);
const bitboard antidiag_9 = step_north(antidiag_10);
const bitboard antidiags[16] = {antidiag_0, antidiag_1, antidiag_2, antidiag_3, antidiag_4, antidiag_5,
								antidiag_6, antidiag_7, 0, antidiag_9, antidiag_10, antidiag_11,
								antidiag_12, antidiag_13, antidiag_14, antidiag_15};

const brdidx no_enpassant = 0b11111111;

const move nomove = {0};

GameState::GameState(){
	this->board_state.k = empty;
	this->board_state.q = empty;
	this->board_state.b = empty;
	this->board_state.n = empty;
	this->board_state.r = empty;
	this->board_state.p = empty;
	this->board_state.white = empty;
	this->board_state.black = empty;
	this->board_state.enpassant = no_enpassant;
	this->board_state.whites_turn = false;
	this->board_state.white_castle_king = false;
	this->board_state.white_castle_queen = false;
	this->board_state.black_castle_king = false;
	this->board_state.black_castle_queen = false;
	this->halfmove_clock = 0;
	this->threefold_repetition_clock = 0;
	this->fullmove_counter = 0;
	this->halfmove_counter = 0;
	for(int i=0;i<64;i++){
		this->piece_map[i] = no;
	}
	this->hash = 0;
	this->record[0] = this->board_state;
	//this->position_count = new PositionCounter();
	//this->current_position_count = 1;
}

GameState::~GameState(){
	// TODO: Why does this cause a crash?
	//delete (this->position_count);
}

unsigned long long perft(GameState *brd, int depth){
    move moves[100];
    int n_moves = all_moves(brd, moves);
    moverecord rec;
    move mv;
    unsigned long long result = 0;
    if(depth == 0){
    	return(1);
    }
    if(depth == 1){
    	return(n_moves);
    }
    for(int i = 0; i<n_moves; i++){
    	mv = moves[i];
    	rec = make_move(brd, &mv);
    	result += perft(brd, depth - 1);
    	unmake_move(brd, &rec);
    }
    return(result);
}

double simple_evaluation(GameState *brd){
	double white_score, black_score;
	white_score = 0;
	black_score = 0;
	white_score += 100 * population_count(brd->board_state.white & brd->board_state.p);
	white_score += 320 * population_count(brd->board_state.white & brd->board_state.n);
	white_score += 330 * population_count(brd->board_state.white & brd->board_state.b);
	white_score += 500 * population_count(brd->board_state.white & brd->board_state.r);
	white_score += 900 * population_count(brd->board_state.white & brd->board_state.q);
	white_score += 200000 * population_count(brd->board_state.white & brd->board_state.k);
	/*
	if(population_count(brd->board_state.white & brd->board_state.q) == 0){
		printf("Q is dead\n");
	}
	*/
	
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
	black_score += 200000 * population_count(brd->board_state.black & brd->board_state.k);
	
	black_score += 1 * 100 * population_count(brd->board_state.black & center4);
	black_score += 1 * 100 * population_count(brd->board_state.black & center16);
	black_score += 5 * population_count(brd->board_state.black & brd->board_state.p & rank_1);
	black_score += 4 * population_count(brd->board_state.black & brd->board_state.p & rank_2);
	black_score += 3 * population_count(brd->board_state.black & brd->board_state.p & rank_3);
	
	
	if(get_whites_turn(brd)){
		return(white_score - black_score);
	}else{
		return(black_score - white_score);
	}
}

negamax_result negamax(GameState *brd, double prob, double threshold, double alpha, 
					double beta, move *best_move, bool *stop, MoveSearchMemory *msm,
					int depth, unsigned long long int *node_count, bool quiesce){
	//printf("depth = %d\n", depth);
	TranspositionTable *tt = msm->tt;
	//MoveHistoryTable *hh = msm->hh;
	
	negamax_result result;
	// Check for threefold repetition
//	if(brd->current_position_count >= 3){
//		result.value = 0;
//		result.lower_bound = false;
//		result.upper_bound = false;
//	}
	
	// This will store the moves
	move *moves = msm->move_buffer[depth];
	
	// First check transposition table
	double strength = prob / threshold;
	strength = strength>1?strength:1;
	transposition_entry entry;
	if(tt != NULL){
		entry = tt->getitem(brd);
		if(!(entry == empty_transposition_entry)){
			if(entry.strength >= strength){
				if(entry.value.lower_bound && entry.value.value > alpha){
					alpha = entry.value.value;
				}else if(entry.value.upper_bound && entry.value.value < beta){
					beta = entry.value.value;
				}else{
					(*best_move) = entry.best_move;
					return entry.value;
					// Search the best move first
					//moves.push(entry.best_move);
				}
			}
		}
	}
	
	// Consider the threshold and generate moves
	int num_moves;
	bool skip_recursion = false;
	
	// Generate all legal moves
	num_moves = all_moves(brd, moves);
//	num_moves = moves.size();
	//std::sort(moves.begin(), moves.end(), [hh](move lhs, move rhs){return hh->compare_moves(lhs, rhs);});

	// If there are no legal moves, this is either checkmate or stalemate
	if (num_moves == 0) {
		if (own_check(brd)){
			result.value = -200000.0 + depth; // checkmate!
			result.lower_bound = false;
			result.upper_bound = false;
			skip_recursion = true;
		} else {
			result.value = 0.0; // stalemate
			result.lower_bound = false;
			result.upper_bound = false;
			skip_recursion = true;
		}
	}
	
	
	// Now we're ready to recurse
	negamax_result subresult;
	moverecord rec;
	double quotient = prob / num_moves;
	move best_counter = nomove;
	double value;
	bool init = true;
	
	double this_eval = simple_evaluation(brd);
	move mv;
	for(int i=0; i<num_moves;i++){
		mv = moves[i];
		if(skip_recursion){
			break;
		}
	//while(!skip_recursion && !moves.empty()){
		// Make the move
		//mv = moves.front();
		//moves.pop();
		
		rec = make_move(brd, &mv);
		(*node_count)++;
		
		// Recurse
		if(quotient >= threshold){
			subresult = negamax(brd, quotient, threshold, -beta, -alpha, &best_counter, stop, msm, depth+1, node_count, quiesce);
			value = -subresult.value;
		}else{
			// This is a quiescence / stability search
			value = -simple_evaluation(brd);
			//printf("this_eval = %f, value = %f\n", this_eval, value);
			if(abs(this_eval - value) > 10. && quiesce){
				//printf("Quiesce: depth = %d, this_eval = %f, value = %f\n", depth, this_eval, value);
				subresult = negamax(brd, quotient, threshold, -beta, -value, &best_counter, stop, msm, depth+1, node_count, quiesce);
				//printf("subresult.value = %f\n", subresult.value);
				if(-subresult.value > value){
					value = -subresult.value;
				}
			}else{
				subresult.lower_bound = false;
				subresult.upper_bound = false;
			}
		}

		// Unmake the move
		unmake_move(brd, &rec);
		
		// Reconcile what we've learned
		if(value > beta || (*stop)){
			result.value = value;
			result.lower_bound = true;
			result.upper_bound = false;
			(*best_move) = mv;
			break;
		}else if(value >= result.value || init){
			result.value = value;
			result.lower_bound = false;
			if(subresult.lower_bound){
				result.upper_bound = true;
			}else{
				result.upper_bound = false;
			}
			(*best_move) = mv;
			init = false;
		}
		if(result.value >= alpha){
			alpha = value;
		}
	}

	// Store in transposition table
	if(tt != NULL){
		entry.strength = strength;
		entry.key = brd->hash;
		entry.value = result;
		entry.best_move = (*best_move);
		entry.brd = brd->board_state;
		tt->setitem(brd, entry);
	}
	
	// All done
	return result;
}

/*
void iterative_negamax(void *varg){
	searcharg *arg = (searcharg *) varg;
	int depth = 1;
	double result;
	while(!(*(arg->stop))){
		result = negamax(arg->brd, depth, -1000000.0, 1000000.0, 
						arg->best_move, arg->stop, arg->blank, 
						arg->quiesce);
		arg->blank = false;
		arg->depth = depth;
		depth++;
	}
}
*/

void iterative_negamax(void *varg){
	searcharg *arg = (searcharg *) varg;
	negamax_result result;
	double thresh = .0001;
	unsigned long long int node_count = 0;
	move best_move;
	double best_value;
	double value;
	//MoveHistoryTable *hh = new MoveHistoryTable();
	while(!(*(arg->stop))){
		result = negamax(arg->brd, 1.0, thresh, -1000000.0, 1000000.0,
						&best_move, arg->stop, arg->msm, 0, &node_count,
						arg->quiesce);
		value = result.value;
		*(arg->best_move) = best_move;
		if(!(*arg->stop)){
			arg->thresh = thresh;
		}
		thresh /= 2;
	}
}

move movesearch_threshold(GameState *brd, double threshold, MoveSearchMemory *msm, bool quiesce){
	EASY_PROFILER_ENABLE;
	EASY_BLOCK("movesearch_threshold");
	move best_move = nomove;
	bool blank = true;
	bool stop = false;
	unsigned long long int node_count = 0;
	int depth = 0;
	//MoveHistoryTable *hh = new MoveHistoryTable();
	negamax(brd, 1.0, threshold, -1000000.0, 
				1000000.0, &best_move, &stop, msm, depth, &node_count, quiesce);
	EASY_END_BLOCK;
	printf("Visited %llu nodes.\n", node_count);
	profiler::dumpBlocksToFile("test_profile.prof");
	return(best_move);
}

move movesearch_time(GameState *brd, double time_limit, double *thresh,
					MoveSearchMemory *msm, bool quiesce){
	move best_move = nomove;
	bool blank = true;
	bool stop = false;
	searcharg arg = {brd, &best_move, &stop, 1., msm, quiesce};
	thread * searcher = new thread(&iterative_negamax, (void *) &arg);
	usleep(time_limit * 1000000.0);
	stop = true;
	searcher->join();
	*thresh = arg.thresh;
	printf("Reached thresh=%e", *thresh);
	return(best_move);
}
/*
move movesearch(GameState *brd, double time_limit, int *depth){
	bool stop = false;
	move best_move;
	searcharg arg = {brd, &best_move, &stop, true, 0};
	thread * searcher = new thread(&iterative_negamax, (void *) &arg);
	usleep(time_limit * 1000000.0);
	stop = true;
	searcher->join();
	*depth = arg.depth;
	return(best_move);
}
*/
zobrist_int Zobrist::update(zobrist_int previous, GameState *brd, moverecord *mv) const{
	// Call after move has been made or before it is unmade
	zobrist_int result = previous;
	int from_square = (int) mv->from_square;
	int to_square = (int) mv->to_square;
	piece from_piece = mv->promoted_from;
	piece captured_piece = mv->captured;
	piece promoted_piece = brd->piece_map[mv->to_square];
	result ^= zobrist_table[from_square / 8][from_square % 8][piece_to_zobrist_index(from_piece)];
	if(captured_piece != no  && captured_piece != ep && captured_piece != EP){
		result ^= zobrist_table[to_square / 8][to_square % 8][piece_to_zobrist_index(captured_piece)];
	}
	if(captured_piece == ep){
		result ^= zobrist_table[(to_square - 8) / 8][(to_square - 8) % 8][piece_to_zobrist_index(p)];
	}else if(captured_piece == EP){
		result ^= zobrist_table[(to_square + 8) / 8][(to_square + 8) % 8][piece_to_zobrist_index(P)];
	}
	result ^= zobrist_table[to_square / 8][to_square % 8][piece_to_zobrist_index(promoted_piece)];
	
	if(mv->enpassant != no_enpassant){
		if(get_blacks_turn(brd)){
			result ^= zobrist_table[((int) (mv->enpassant)) / 8][((int) (mv->enpassant)) % 8][piece_to_zobrist_index(ep)];
		}else{
			result ^= zobrist_table[((int) (mv->enpassant)) / 8][((int) (mv->enpassant)) % 8][piece_to_zobrist_index(EP)];
		}
	}
	if(get_enpassant(brd) != no_enpassant){
		if(get_blacks_turn(brd)){
			result ^= zobrist_table[((int) (get_enpassant(brd))) / 8][((int) (get_enpassant(brd))) % 8][piece_to_zobrist_index(EP)];
		}else{
			result ^= zobrist_table[((int) (get_enpassant(brd))) / 8][((int) (get_enpassant(brd))) % 8][piece_to_zobrist_index(ep)];
		}
	}
	
	result ^= zobrist_blacks_turn;
	if(get_blacks_turn(brd)){
		if(mv->lost_own_castle_king){
			result ^= zobrist_white_castle_king;
		}
		if(mv->lost_own_castle_queen){
			result ^= zobrist_white_castle_queen;
		}
		if(mv->lost_opponent_castle_king){
			result ^= zobrist_black_castle_king;
		}
		if(mv->lost_opponent_castle_queen){
			result ^= zobrist_black_castle_queen;
		}
	}else{
		if(mv->lost_own_castle_king){
			result ^= zobrist_black_castle_king;
		}
		if(mv->lost_own_castle_queen){
			result ^= zobrist_black_castle_queen;
		}
		if(mv->lost_opponent_castle_king){
			result ^= zobrist_white_castle_king;
		}
		if(mv->lost_opponent_castle_queen){
			result ^= zobrist_white_castle_queen;
		}
	}
	
	if(from_piece==K && (mv->to_square - mv->from_square == 2)){
		//white castle king side
		result ^= zobrist_table[5 / 8][5 % 8][piece_to_zobrist_index(R)];
		result ^= zobrist_table[7 / 8][7 % 8][piece_to_zobrist_index(R)];
	}else if(from_piece==K && (mv->from_square - mv->to_square == 2)){
		//white castle queen side
		result ^= zobrist_table[3 / 8][3 % 8][piece_to_zobrist_index(R)];
		result ^= zobrist_table[0 / 8][0 % 8][piece_to_zobrist_index(R)];
	}else if(from_piece==k && (mv->to_square - mv->from_square == 2)){
		//black castle king side
		result ^= zobrist_table[61 / 8][61 % 8][piece_to_zobrist_index(r)];
		result ^= zobrist_table[63 / 8][63 % 8][piece_to_zobrist_index(r)];
	}else if(from_piece==k && (mv->from_square - mv->to_square == 2)){
		//black castle queen side
		result ^= zobrist_table[59 / 8][59 % 8][piece_to_zobrist_index(r)];
		result ^= zobrist_table[56 / 8][56 % 8][piece_to_zobrist_index(r)];
	}
	
	return result;
}

zobrist_int Zobrist::hash(GameState *brd) const{
	piece pc;
	zobrist_int result = 0;
	for(int i=0;i<64;i++){
		pc = brd->piece_map[i];
		if(pc != no){
			result ^= zobrist_table[i/8][i%8][piece_to_zobrist_index(pc)];
		}
	}
	if(get_blacks_turn(brd)){
		result ^= zobrist_blacks_turn;
	}
	if(get_white_castle_king(brd)){
		result ^= zobrist_white_castle_king;
	}
	if(get_white_castle_queen(brd)){
		result ^= zobrist_white_castle_queen;
	}
	if(get_black_castle_king(brd)){
		result ^= zobrist_black_castle_king;
	}
	if(get_black_castle_queen(brd)){
		result ^= zobrist_black_castle_queen;
	}
	return result;
}

Zobrist::Zobrist(void){
    zobrist_table[0][0][0] = 0x91B7584A2265B1F5ULL;
    zobrist_table[0][0][1] = 0xCD613E30D8F16ADFULL;
    zobrist_table[0][0][2] = 0x1027C4D1C386BBC4ULL;
    zobrist_table[0][0][3] = 0x1E2FEB89414C343CULL;
    zobrist_table[0][0][4] = 0xC2CE6F447ED4D57BULL;
    zobrist_table[0][0][5] = 0x78E510617311D8A3ULL;
    zobrist_table[0][0][6] = 0x612E7696A6CECC1BULL;
    zobrist_table[0][0][7] = 0x35BF992DC9E9C616ULL;
    zobrist_table[0][0][8] = 0x7CE42C8218072E8CULL;
    zobrist_table[0][0][9] = 0xE4B06CE60741C7A8ULL;
    zobrist_table[0][0][10] = 0x63CA828DD5F4B3B2ULL;
    zobrist_table[0][0][11] = 0x9B810E766EC9D286ULL;
    zobrist_table[0][0][12] = 0xC4647159C324C985ULL;
    zobrist_table[0][0][13] = 0xB2221A58008A05A6ULL;
    zobrist_table[0][1][0] = 0x442E3D437204E52DULL;
    zobrist_table[0][1][1] = 0xCD447E35B8B6D8FEULL;
    zobrist_table[0][1][2] = 0x9755D4C13A902931ULL;
    zobrist_table[0][1][3] = 0x1A2B8F1FF1FD42A2ULL;
    zobrist_table[0][1][4] = 0x51431193E6C3F339ULL;
    zobrist_table[0][1][5] = 0x5B6E6E307D4BEDCULL;
    zobrist_table[0][1][6] = 0xA648A7DD06839EB9ULL;
    zobrist_table[0][1][7] = 0x25B413F8A9A021EULL;
    zobrist_table[0][1][8] = 0xE1988AD9F06C144AULL;
    zobrist_table[0][1][9] = 0xAFBD67F9619699CFULL;
    zobrist_table[0][1][10] = 0xF8130C4237730EDFULL;
    zobrist_table[0][1][11] = 0xB9D179E06C0FD4F5ULL;
    zobrist_table[0][1][12] = 0x8712B8BC076F3787ULL;
    zobrist_table[0][1][13] = 0xC381E88F38C0C8FDULL;
    zobrist_table[0][2][0] = 0xF06D3FEF701966A0ULL;
    zobrist_table[0][2][1] = 0x8D88348A7EED8D14ULL;
    zobrist_table[0][2][2] = 0x587FD2803BAB6C39ULL;
    zobrist_table[0][2][3] = 0xAD45F23D3B1A11DFULL;
    zobrist_table[0][2][4] = 0xC2CD789A380208A9ULL;
    zobrist_table[0][2][5] = 0xF3C64AF775A89294ULL;
    zobrist_table[0][2][6] = 0xED2F89D94A2F20AAULL;
    zobrist_table[0][2][7] = 0x6A8AC4BA05805975ULL;
    zobrist_table[0][2][8] = 0xEA90A8F0D66B829EULL;
    zobrist_table[0][2][9] = 0xEC148CB48E73CA47ULL;
    zobrist_table[0][2][10] = 0x19999E3FA46D6753ULL;
    zobrist_table[0][2][11] = 0xA11D459A2F978D87ULL;
    zobrist_table[0][2][12] = 0xB94067EDFE175330ULL;
    zobrist_table[0][2][13] = 0x4BE03DB0DC2574BDULL;
    zobrist_table[0][3][0] = 0xBE3EDC0A1EF2A4F0ULL;
    zobrist_table[0][3][1] = 0xE5446DD4552B82F6ULL;
    zobrist_table[0][3][2] = 0xF9270F4EB8B333A8ULL;
    zobrist_table[0][3][3] = 0x803468B6B610A9F7ULL;
    zobrist_table[0][3][4] = 0xF79B17AEEFBA91FCULL;
    zobrist_table[0][3][5] = 0x81F9C1F66C0F3459ULL;
    zobrist_table[0][3][6] = 0xE901E35CD47D380DULL;
    zobrist_table[0][3][7] = 0x3099FDF5AB99254AULL;
    zobrist_table[0][3][8] = 0x48BEAB134DA98F1DULL;
    zobrist_table[0][3][9] = 0xF9341C68966BAEA1ULL;
    zobrist_table[0][3][10] = 0x7FD63116E1EA24C4ULL;
    zobrist_table[0][3][11] = 0xF0DFB4A5D8A064DFULL;
    zobrist_table[0][3][12] = 0x64B2D2BC815A47C5ULL;
    zobrist_table[0][3][13] = 0xDA71144896C8DA19ULL;
    zobrist_table[0][4][0] = 0x7AF027BC08D6AF57ULL;
    zobrist_table[0][4][1] = 0xBE6521CC3E2434E3ULL;
    zobrist_table[0][4][2] = 0x677F6CBDCC22AF58ULL;
    zobrist_table[0][4][3] = 0xAA2CA1AF6A107B75ULL;
    zobrist_table[0][4][4] = 0x5DFBD3D12C4A3698ULL;
    zobrist_table[0][4][5] = 0xE1FAB9D78C7E134FULL;
    zobrist_table[0][4][6] = 0xC69D4BD8B3FA7AA7ULL;
    zobrist_table[0][4][7] = 0xBCFBB050ACAB1A6BULL;
    zobrist_table[0][4][8] = 0x1622BD795FEC898FULL;
    zobrist_table[0][4][9] = 0xA9EC0806705FCA16ULL;
    zobrist_table[0][4][10] = 0x1BA1621582283D15ULL;
    zobrist_table[0][4][11] = 0x29E821A4C74803E3ULL;
    zobrist_table[0][4][12] = 0xD707107E855C3844ULL;
    zobrist_table[0][4][13] = 0x5EDA92D864AC5DB9ULL;
    zobrist_table[0][5][0] = 0xBB968A437D5C8DFCULL;
    zobrist_table[0][5][1] = 0x78255D6807923986ULL;
    zobrist_table[0][5][2] = 0x4EFBC8D60B21FBACULL;
    zobrist_table[0][5][3] = 0xD92A4AA2B410D93CULL;
    zobrist_table[0][5][4] = 0x9D643C25FBB230BBULL;
    zobrist_table[0][5][5] = 0x9403560D97DAE38DULL;
    zobrist_table[0][5][6] = 0xA5AC06D864C2F2E3ULL;
    zobrist_table[0][5][7] = 0x2B28FEF02B9C014EULL;
    zobrist_table[0][5][8] = 0x3A1890C78092B4D4ULL;
    zobrist_table[0][5][9] = 0x326324DFB695FFBULL;
    zobrist_table[0][5][10] = 0x33138131C541013DULL;
    zobrist_table[0][5][11] = 0xEB8AC8CE8A245E6BULL;
    zobrist_table[0][5][12] = 0x8C5FE8F8DC3BF364ULL;
    zobrist_table[0][5][13] = 0x678A5AA33B6FE507ULL;
    zobrist_table[0][6][0] = 0x5804F92283868A29ULL;
    zobrist_table[0][6][1] = 0xD8F33418F3D4E711ULL;
    zobrist_table[0][6][2] = 0x5A702CFA93EA5C4EULL;
    zobrist_table[0][6][3] = 0xE8E5B4617589A82BULL;
    zobrist_table[0][6][4] = 0xA8C24D4244EF7FEBULL;
    zobrist_table[0][6][5] = 0x9BE3CECB8C497C68ULL;
    zobrist_table[0][6][6] = 0xBAB9F87FF5059285ULL;
    zobrist_table[0][6][7] = 0x62397BC701762741ULL;
    zobrist_table[0][6][8] = 0xDB610487C89DA11BULL;
    zobrist_table[0][6][9] = 0xF463B337D20B5D59ULL;
    zobrist_table[0][6][10] = 0xF03EDCA7E2DCAA37ULL;
    zobrist_table[0][6][11] = 0x83333218BD91A1B7ULL;
    zobrist_table[0][6][12] = 0x21167D8FCF23CAE8ULL;
    zobrist_table[0][6][13] = 0xC703806984C81999ULL;
    zobrist_table[0][7][0] = 0x349AAE908FB5262CULL;
    zobrist_table[0][7][1] = 0xF320CD576D14475BULL;
    zobrist_table[0][7][2] = 0x7B297D0B0E5E18BAULL;
    zobrist_table[0][7][3] = 0x5D5F576CDEB8FC4CULL;
    zobrist_table[0][7][4] = 0x8DED3C9691EB79FAULL;
    zobrist_table[0][7][5] = 0xF0E642F43328AD08ULL;
    zobrist_table[0][7][6] = 0x69D495DD81355C53ULL;
    zobrist_table[0][7][7] = 0xD037CDFF7C240D49ULL;
    zobrist_table[0][7][8] = 0x6A17B9AF5B569643ULL;
    zobrist_table[0][7][9] = 0x67DBA858989008ULL;
    zobrist_table[0][7][10] = 0x8A449EBE89D9BF02ULL;
    zobrist_table[0][7][11] = 0xC9546B439F9D0129ULL;
    zobrist_table[0][7][12] = 0x54C56C9A9CC9AF4EULL;
    zobrist_table[0][7][13] = 0x99901C0475491BC3ULL;
    zobrist_table[1][0][0] = 0xCDF8440407295E42ULL;
    zobrist_table[1][0][1] = 0xA2A7AE1F3AC7652CULL;
    zobrist_table[1][0][2] = 0x8CFE5CD12D5DB79BULL;
    zobrist_table[1][0][3] = 0x2E47DC0E959F3A51ULL;
    zobrist_table[1][0][4] = 0x1773308CDC6B13ABULL;
    zobrist_table[1][0][5] = 0x8D103ED3CC667E97ULL;
    zobrist_table[1][0][6] = 0xD9ED17E3CC0E95EEULL;
    zobrist_table[1][0][7] = 0xEE52BDB6D1020A15ULL;
    zobrist_table[1][0][8] = 0x84F3DD6415AF341ULL;
    zobrist_table[1][0][9] = 0xF18DD1EED77C96C0ULL;
    zobrist_table[1][0][10] = 0x12093D26AC512B01ULL;
    zobrist_table[1][0][11] = 0xDE3A5DB5154ED512ULL;
    zobrist_table[1][0][12] = 0x73F7BA8E0445D656ULL;
    zobrist_table[1][0][13] = 0xC10FAA4003BA33DBULL;
    zobrist_table[1][1][0] = 0x47FC816AC16E2284ULL;
    zobrist_table[1][1][1] = 0x44C5B4763FE31D03ULL;
    zobrist_table[1][1][2] = 0xCC1B0C3E1C07724EULL;
    zobrist_table[1][1][3] = 0x2F429CE59FF3078FULL;
    zobrist_table[1][1][4] = 0x4A5012DC582C18C9ULL;
    zobrist_table[1][1][5] = 0x2ADF559A11CBC288ULL;
    zobrist_table[1][1][6] = 0x4155D7EF28DD37EBULL;
    zobrist_table[1][1][7] = 0xF3B37F32870266C4ULL;
    zobrist_table[1][1][8] = 0xA81AA40A2B0B8C12ULL;
    zobrist_table[1][1][9] = 0xA5F09E6345DDB87DULL;
    zobrist_table[1][1][10] = 0x4B63E0EFB62AC1FEULL;
    zobrist_table[1][1][11] = 0xB3DF44A47467537AULL;
    zobrist_table[1][1][12] = 0x7F1A355E526EB523ULL;
    zobrist_table[1][1][13] = 0x1D3B993F79490EABULL;
    zobrist_table[1][2][0] = 0x4FDF8E1A060CEA63ULL;
    zobrist_table[1][2][1] = 0x57E54ACC62F5680CULL;
    zobrist_table[1][2][2] = 0xCBD3F5E06BC15385ULL;
    zobrist_table[1][2][3] = 0x4227DE213023580CULL;
    zobrist_table[1][2][4] = 0x40E2A20A1BD7CE73ULL;
    zobrist_table[1][2][5] = 0xBAEB41A5E65A8149ULL;
    zobrist_table[1][2][6] = 0xFA0B85188296F5EAULL;
    zobrist_table[1][2][7] = 0xF72F2BB83586FCA7ULL;
    zobrist_table[1][2][8] = 0x6E80FA489B0BCA16ULL;
    zobrist_table[1][2][9] = 0xF9BDDEA5D12982E4ULL;
    zobrist_table[1][2][10] = 0x39B21C95055455E8ULL;
    zobrist_table[1][2][11] = 0x65B675CD0492C4F5ULL;
    zobrist_table[1][2][12] = 0x90B20BB257E8454ULL;
    zobrist_table[1][2][13] = 0xF5BB9188B80599E9ULL;
    zobrist_table[1][3][0] = 0x721754EF2904ACECULL;
    zobrist_table[1][3][1] = 0x819D7CA7B46108CCULL;
    zobrist_table[1][3][2] = 0x6D39EB43AD9CEDDEULL;
    zobrist_table[1][3][3] = 0xD50E00978B7199CDULL;
    zobrist_table[1][3][4] = 0xFA1B1BF13879399BULL;
    zobrist_table[1][3][5] = 0xA17A4340F9C08FEFULL;
    zobrist_table[1][3][6] = 0xB1EEDAFFCC3D5506ULL;
    zobrist_table[1][3][7] = 0x736A947A843FDDA7ULL;
    zobrist_table[1][3][8] = 0x861E02EC39235BC0ULL;
    zobrist_table[1][3][9] = 0x7DBF924A6048457ULL;
    zobrist_table[1][3][10] = 0xACC66A576518093DULL;
    zobrist_table[1][3][11] = 0xCDAAAC43936AA40CULL;
    zobrist_table[1][3][12] = 0xA8EA37F7523D2A54ULL;
    zobrist_table[1][3][13] = 0x6D21F4CDA185CC8EULL;
    zobrist_table[1][4][0] = 0xBCC99AE80F0C8A89ULL;
    zobrist_table[1][4][1] = 0x202CC8284C717095ULL;
    zobrist_table[1][4][2] = 0x364E433FF7C882F4ULL;
    zobrist_table[1][4][3] = 0xC250A03E023033DULL;
    zobrist_table[1][4][4] = 0x121B28004E6F5A94ULL;
    zobrist_table[1][4][5] = 0x1391F9B9DBC799B0ULL;
    zobrist_table[1][4][6] = 0xEACC110E4F73FD94ULL;
    zobrist_table[1][4][7] = 0x4C41D9C0F07534FEULL;
    zobrist_table[1][4][8] = 0x28804790BE6C6FE9ULL;
    zobrist_table[1][4][9] = 0x909FF4976A8A43EFULL;
    zobrist_table[1][4][10] = 0x21615022409A8A78ULL;
    zobrist_table[1][4][11] = 0x8F8B2B83022BC320ULL;
    zobrist_table[1][4][12] = 0xD9BC1D97E0F3A7EFULL;
    zobrist_table[1][4][13] = 0x973082D609B4E5D2ULL;
    zobrist_table[1][5][0] = 0x37B4000BD1C51F86ULL;
    zobrist_table[1][5][1] = 0xE69BAE29F652D008ULL;
    zobrist_table[1][5][2] = 0x75FA6DD891FDE85CULL;
    zobrist_table[1][5][3] = 0xD3F21DCC2BE88B46ULL;
    zobrist_table[1][5][4] = 0xDEB0E066DE26E655ULL;
    zobrist_table[1][5][5] = 0xC7AF3626F9495568ULL;
    zobrist_table[1][5][6] = 0x9F7A7DAFB43ADC4FULL;
    zobrist_table[1][5][7] = 0x994940E82458CC8ULL;
    zobrist_table[1][5][8] = 0x334DE73D60C290D0ULL;
    zobrist_table[1][5][9] = 0x1959B9EF58D07674ULL;
    zobrist_table[1][5][10] = 0x92C9357D34ACCD78ULL;
    zobrist_table[1][5][11] = 0xE585552FAC954AB5ULL;
    zobrist_table[1][5][12] = 0x976699CC6ED5D1BFULL;
    zobrist_table[1][5][13] = 0x7E0AB2ED31B1C27EULL;
    zobrist_table[1][6][0] = 0xF01DBF291ABB8BA3ULL;
    zobrist_table[1][6][1] = 0x63DB01FCAA7C314BULL;
    zobrist_table[1][6][2] = 0x810D2E304BCB6B22ULL;
    zobrist_table[1][6][3] = 0x4673B757FF2E341ULL;
    zobrist_table[1][6][4] = 0x9CB471A55349DA48ULL;
    zobrist_table[1][6][5] = 0x66FEC086DF229650ULL;
    zobrist_table[1][6][6] = 0x4806AA81E65150B5ULL;
    zobrist_table[1][6][7] = 0x282EE0BC04A1BDE4ULL;
    zobrist_table[1][6][8] = 0xDB87872D336B1A45ULL;
    zobrist_table[1][6][9] = 0xCFA6CF3E53E6D093ULL;
    zobrist_table[1][6][10] = 0x903715C8FCAF4A5AULL;
    zobrist_table[1][6][11] = 0x2298BDB1C85F0D46ULL;
    zobrist_table[1][6][12] = 0x6DE2B33B56CEF8ECULL;
    zobrist_table[1][6][13] = 0x443BAAC536891EEBULL;
    zobrist_table[1][7][0] = 0x18AE013EACA91679ULL;
    zobrist_table[1][7][1] = 0x611575C2D67393D6ULL;
    zobrist_table[1][7][2] = 0x8C31406DEEA3D685ULL;
    zobrist_table[1][7][3] = 0xEA190B2A58068A9DULL;
    zobrist_table[1][7][4] = 0xD6730839E1E48557ULL;
    zobrist_table[1][7][5] = 0x88C9DA8AAFE673F6ULL;
    zobrist_table[1][7][6] = 0xC49872C67C081BB7ULL;
    zobrist_table[1][7][7] = 0x88534206FC4A447EULL;
    zobrist_table[1][7][8] = 0x10B8FE223C116549ULL;
    zobrist_table[1][7][9] = 0xA57AF35B9B81635ULL;
    zobrist_table[1][7][10] = 0x220D672B15AD9A9DULL;
    zobrist_table[1][7][11] = 0x2AA3300B2B711343ULL;
    zobrist_table[1][7][12] = 0x89C80C4DE9367ED9ULL;
    zobrist_table[1][7][13] = 0x449C4CA23685156BULL;
    zobrist_table[2][0][0] = 0x550D40DDC2557035ULL;
    zobrist_table[2][0][1] = 0x8181E84D99A74924ULL;
    zobrist_table[2][0][2] = 0x415AC400D7547080ULL;
    zobrist_table[2][0][3] = 0x56BEFA395E3C536CULL;
    zobrist_table[2][0][4] = 0x1D296588571CEEEEULL;
    zobrist_table[2][0][5] = 0x3C35612E4A8D15D8ULL;
    zobrist_table[2][0][6] = 0xF1A9A658DE0F39A7ULL;
    zobrist_table[2][0][7] = 0xC78FEC459A9E994CULL;
    zobrist_table[2][0][8] = 0xB7115C02F44D7E40ULL;
    zobrist_table[2][0][9] = 0x7D2186D3E323CE54ULL;
    zobrist_table[2][0][10] = 0x947810D822A608BFULL;
    zobrist_table[2][0][11] = 0xC52F4FBE8D19821FULL;
    zobrist_table[2][0][12] = 0x521B18A91AB1C42FULL;
    zobrist_table[2][0][13] = 0x6816DE060A04EF48ULL;
    zobrist_table[2][1][0] = 0x6156C4DF12BCCDCBULL;
    zobrist_table[2][1][1] = 0xFDC1786BDDBD358FULL;
    zobrist_table[2][1][2] = 0x25B7501AC9C1FFEFULL;
    zobrist_table[2][1][3] = 0x20012170D418F7AFULL;
    zobrist_table[2][1][4] = 0x1D5C482557450E65ULL;
    zobrist_table[2][1][5] = 0x96605D959D7CD4F6ULL;
    zobrist_table[2][1][6] = 0xED192DA3C82AD589ULL;
    zobrist_table[2][1][7] = 0x139F711060C73494ULL;
    zobrist_table[2][1][8] = 0x8CDECE75921EBCE6ULL;
    zobrist_table[2][1][9] = 0x90E32E8239455353ULL;
    zobrist_table[2][1][10] = 0xF3C668B114ED2049ULL;
    zobrist_table[2][1][11] = 0x5D698C8B44480030ULL;
    zobrist_table[2][1][12] = 0x4BA955F3E4096150ULL;
    zobrist_table[2][1][13] = 0x88C780F6907F9669ULL;
    zobrist_table[2][2][0] = 0x1D43D1FFECD1345EULL;
    zobrist_table[2][2][1] = 0xE592067375305DB7ULL;
    zobrist_table[2][2][2] = 0x1B943CFC46F57327ULL;
    zobrist_table[2][2][3] = 0xBB662A8C979CB06ULL;
    zobrist_table[2][2][4] = 0x4BB57B5CD3E89D32ULL;
    zobrist_table[2][2][5] = 0x9D19EE45032B7328ULL;
    zobrist_table[2][2][6] = 0x3B96D91ABA018EAULL;
    zobrist_table[2][2][7] = 0x69DD649317788B95ULL;
    zobrist_table[2][2][8] = 0xD37C99611D775B7CULL;
    zobrist_table[2][2][9] = 0xCA357568E2934BF1ULL;
    zobrist_table[2][2][10] = 0x301BA9880A3EFB80ULL;
    zobrist_table[2][2][11] = 0xC91752A33D589CABULL;
    zobrist_table[2][2][12] = 0x96380ED6FCF7F49DULL;
    zobrist_table[2][2][13] = 0x297A21D76BC78BF5ULL;
    zobrist_table[2][3][0] = 0x736EBF511D95389BULL;
    zobrist_table[2][3][1] = 0xAE4ECF4B2AD9A40AULL;
    zobrist_table[2][3][2] = 0x28B09A933DCDB856ULL;
    zobrist_table[2][3][3] = 0xD85328B6BE773448ULL;
    zobrist_table[2][3][4] = 0x6F62E63A1A5356B5ULL;
    zobrist_table[2][3][5] = 0xF6F62C28E927DB48ULL;
    zobrist_table[2][3][6] = 0xCE75F4BA60D6C766ULL;
    zobrist_table[2][3][7] = 0x8AFD2973F8633958ULL;
    zobrist_table[2][3][8] = 0xD17F6494E8C2D219ULL;
    zobrist_table[2][3][9] = 0x8CDA80A34B452123ULL;
    zobrist_table[2][3][10] = 0xB62C228E40DF7C9AULL;
    zobrist_table[2][3][11] = 0x50806F017A1D556CULL;
    zobrist_table[2][3][12] = 0x35263B4519A2105CULL;
    zobrist_table[2][3][13] = 0x51423286A6ECC31FULL;
    zobrist_table[2][4][0] = 0x6FAADB10A248CFFULL;
    zobrist_table[2][4][1] = 0xC96FA75802B087F8ULL;
    zobrist_table[2][4][2] = 0xECF45CCBFB8A99A2ULL;
    zobrist_table[2][4][3] = 0xB9FAD67E4BA927C3ULL;
    zobrist_table[2][4][4] = 0x51FBFCC798B8DA9FULL;
    zobrist_table[2][4][5] = 0x642A357C732902F4ULL;
    zobrist_table[2][4][6] = 0x6607B61550332CB8ULL;
    zobrist_table[2][4][7] = 0x106EE2AB101E75EBULL;
    zobrist_table[2][4][8] = 0x513DD1A6E9D40F2BULL;
    zobrist_table[2][4][9] = 0x99F86C8DF845AED9ULL;
    zobrist_table[2][4][10] = 0x74B31BFBF8449560ULL;
    zobrist_table[2][4][11] = 0x40041E001C823D9EULL;
    zobrist_table[2][4][12] = 0xC8FEA5D73716E7EAULL;
    zobrist_table[2][4][13] = 0xC725BD979E289761ULL;
    zobrist_table[2][5][0] = 0xE4264C9FFADE312DULL;
    zobrist_table[2][5][1] = 0xDE1BF0CD8AFC5BEEULL;
    zobrist_table[2][5][2] = 0x780B25D9B02D3504ULL;
    zobrist_table[2][5][3] = 0x5B177A38A96DFB2CULL;
    zobrist_table[2][5][4] = 0x2EE7AF97425375BEULL;
    zobrist_table[2][5][5] = 0x3534CCAE8AA67235ULL;
    zobrist_table[2][5][6] = 0x32FFD03D4EAC98D6ULL;
    zobrist_table[2][5][7] = 0x5C47577B3F12D68EULL;
    zobrist_table[2][5][8] = 0xD1EA041814D4954EULL;
    zobrist_table[2][5][9] = 0x16E3E38047E1A38BULL;
    zobrist_table[2][5][10] = 0xC0D76560FBBE9381ULL;
    zobrist_table[2][5][11] = 0x172A401272A9B8A4ULL;
    zobrist_table[2][5][12] = 0x93090287A6EA2981ULL;
    zobrist_table[2][5][13] = 0x56C11669A4BA3161ULL;
    zobrist_table[2][6][0] = 0x3A389B09F0D3FA5CULL;
    zobrist_table[2][6][1] = 0xF772F8EA63F666E0ULL;
    zobrist_table[2][6][2] = 0xA8266954E896A65ULL;
    zobrist_table[2][6][3] = 0x2FD2F79253C617EBULL;
    zobrist_table[2][6][4] = 0xCAF078B051158DE5ULL;
    zobrist_table[2][6][5] = 0x9439C746D8DDD2EFULL;
    zobrist_table[2][6][6] = 0xEBDDB098E4BC6E82ULL;
    zobrist_table[2][6][7] = 0x3EEFE7344D84E990ULL;
    zobrist_table[2][6][8] = 0x19D7B4035596DFDEULL;
    zobrist_table[2][6][9] = 0x9C842B6A8B525B4FULL;
    zobrist_table[2][6][10] = 0xCEBCC1BA943863A5ULL;
    zobrist_table[2][6][11] = 0x179030DA98910052ULL;
    zobrist_table[2][6][12] = 0x385C1B333EBEBE3EULL;
    zobrist_table[2][6][13] = 0xCEEA590B05373B76ULL;
    zobrist_table[2][7][0] = 0x66DAA3653E67026CULL;
    zobrist_table[2][7][1] = 0x449FD49B12840EA1ULL;
    zobrist_table[2][7][2] = 0xDE1827478D1BC13AULL;
    zobrist_table[2][7][3] = 0xBAAAD6511227932FULL;
    zobrist_table[2][7][4] = 0x581F255133BB4C2ULL;
    zobrist_table[2][7][5] = 0x289EB06A2A866B4ULL;
    zobrist_table[2][7][6] = 0xC02FC22A4A7347FAULL;
    zobrist_table[2][7][7] = 0x5BF3F74DCACC9EC8ULL;
    zobrist_table[2][7][8] = 0x780587F07E465B19ULL;
    zobrist_table[2][7][9] = 0xDBEEF77ADCD69029ULL;
    zobrist_table[2][7][10] = 0x19D6D73B2778507CULL;
    zobrist_table[2][7][11] = 0xC71A5B11805DB06AULL;
    zobrist_table[2][7][12] = 0x53FDF07CCB8409D6ULL;
    zobrist_table[2][7][13] = 0x825F854213BD488EULL;
    zobrist_table[3][0][0] = 0xAA4DA822F3009A5CULL;
    zobrist_table[3][0][1] = 0x2DF810B92C599859ULL;
    zobrist_table[3][0][2] = 0x2649C1B0C6B5A1C6ULL;
    zobrist_table[3][0][3] = 0x243BD888FC2222D2ULL;
    zobrist_table[3][0][4] = 0xDD946658D2511C38ULL;
    zobrist_table[3][0][5] = 0x4E3D4D0F51DD5D5CULL;
    zobrist_table[3][0][6] = 0xB59641D21B5C56D3ULL;
    zobrist_table[3][0][7] = 0xD5AE305B83ACFB7EULL;
    zobrist_table[3][0][8] = 0x9A15A311EB5AF9F9ULL;
    zobrist_table[3][0][9] = 0x20552F5F4B2220A4ULL;
    zobrist_table[3][0][10] = 0x34ECF2EDE4CD6075ULL;
    zobrist_table[3][0][11] = 0x8BA56D3424452ECFULL;
    zobrist_table[3][0][12] = 0xB8FE2F4BE91553A9ULL;
    zobrist_table[3][0][13] = 0xC79D444008216B65ULL;
    zobrist_table[3][1][0] = 0xD22F02F350E9E079ULL;
    zobrist_table[3][1][1] = 0x9F9F80D0E730CB28ULL;
    zobrist_table[3][1][2] = 0xAC153076CDC98666ULL;
    zobrist_table[3][1][3] = 0x8D8E3B13E83B3AB1ULL;
    zobrist_table[3][1][4] = 0xF1878D5FD739543BULL;
    zobrist_table[3][1][5] = 0xFCA7CB5FBF05F8FAULL;
    zobrist_table[3][1][6] = 0x3497553CB0894F5AULL;
    zobrist_table[3][1][7] = 0x4C8670622D9B8EBFULL;
    zobrist_table[3][1][8] = 0x899918A76EC15D38ULL;
    zobrist_table[3][1][9] = 0xC6E5973286BEF29ULL;
    zobrist_table[3][1][10] = 0xDCB284F8B6FEBC3AULL;
    zobrist_table[3][1][11] = 0x3F4ED95AAAF38C2FULL;
    zobrist_table[3][1][12] = 0xC71C5CF140A980BDULL;
    zobrist_table[3][1][13] = 0xAE9C8563107D72D5ULL;
    zobrist_table[3][2][0] = 0x725A9A5BF6A07500ULL;
    zobrist_table[3][2][1] = 0x6E1FB6ADCEE9A4FDULL;
    zobrist_table[3][2][2] = 0x400E67ED8C9CF440ULL;
    zobrist_table[3][2][3] = 0x707C70B48A97B9D8ULL;
    zobrist_table[3][2][4] = 0x89BE4B4BD9EE50E2ULL;
    zobrist_table[3][2][5] = 0x2C8261B740C1A65ULL;
    zobrist_table[3][2][6] = 0xD6172ADF654D479AULL;
    zobrist_table[3][2][7] = 0x2BE893F456B30574ULL;
    zobrist_table[3][2][8] = 0x7C5C483D420A4323ULL;
    zobrist_table[3][2][9] = 0xCB06718C063FA2B6ULL;
    zobrist_table[3][2][10] = 0xEEC1754CA57D041EULL;
    zobrist_table[3][2][11] = 0xF9EF954E6AABCB78ULL;
    zobrist_table[3][2][12] = 0x4D759889213147BULL;
    zobrist_table[3][2][13] = 0xB11379A20FF44F65ULL;
    zobrist_table[3][3][0] = 0x947F81435ADD92D1ULL;
    zobrist_table[3][3][1] = 0x97F2A70223669676ULL;
    zobrist_table[3][3][2] = 0x237475E120087497ULL;
    zobrist_table[3][3][3] = 0xFBB41D1442553A33ULL;
    zobrist_table[3][3][4] = 0x46E3DB95D4350B28ULL;
    zobrist_table[3][3][5] = 0x906704C365D60B6EULL;
    zobrist_table[3][3][6] = 0x2C139C1966AD51FDULL;
    zobrist_table[3][3][7] = 0x16D8E80E9CC930D3ULL;
    zobrist_table[3][3][8] = 0x7C6A47A73BC8996BULL;
    zobrist_table[3][3][9] = 0x2D75C25D01EA0639ULL;
    zobrist_table[3][3][10] = 0x5136BF628758FF4DULL;
    zobrist_table[3][3][11] = 0xE49DF6BB803AF506ULL;
    zobrist_table[3][3][12] = 0xEBA1A9D3A61A59E3ULL;
    zobrist_table[3][3][13] = 0xEE1B8CC470358A27ULL;
    zobrist_table[3][4][0] = 0xA39CC4B2AFBF5310ULL;
    zobrist_table[3][4][1] = 0x39C97AB1BB3E780FULL;
    zobrist_table[3][4][2] = 0x501FC6F43D061F79ULL;
    zobrist_table[3][4][3] = 0xAFDBE9D27EBD0E05ULL;
    zobrist_table[3][4][4] = 0xF4DFC9A57A946602ULL;
    zobrist_table[3][4][5] = 0xB67D153D399DAB3CULL;
    zobrist_table[3][4][6] = 0x564274036988F668ULL;
    zobrist_table[3][4][7] = 0x9C7D498A8F76DC87ULL;
    zobrist_table[3][4][8] = 0xBA6CAC4AE82D2FEFULL;
    zobrist_table[3][4][9] = 0xA745BA6DEAEED19BULL;
    zobrist_table[3][4][10] = 0xF8EC2D3446752B5CULL;
    zobrist_table[3][4][11] = 0x382F21E4A57B7700ULL;
    zobrist_table[3][4][12] = 0xEBEE35210C56A92DULL;
    zobrist_table[3][4][13] = 0xC360B3B71251310BULL;
    zobrist_table[3][5][0] = 0xA5319F4782FE3A4AULL;
    zobrist_table[3][5][1] = 0x5E6279DBE09EDD5AULL;
    zobrist_table[3][5][2] = 0x82FA4D7A28D2E08EULL;
    zobrist_table[3][5][3] = 0xCADFF918C41A66D9ULL;
    zobrist_table[3][5][4] = 0x342F22BAE20CEA4AULL;
    zobrist_table[3][5][5] = 0x4C78C7AB4FD24206ULL;
    zobrist_table[3][5][6] = 0x4CB05EC1B14B69DCULL;
    zobrist_table[3][5][7] = 0x8D64B3ADD9577B6BULL;
    zobrist_table[3][5][8] = 0x2A4926F05F221DFCULL;
    zobrist_table[3][5][9] = 0xB386D25CB38742ADULL;
    zobrist_table[3][5][10] = 0x76FBB6EDBC85E5DEULL;
    zobrist_table[3][5][11] = 0x15C0CDD59836404CULL;
    zobrist_table[3][5][12] = 0x1F8CE97ADB34FA8DULL;
    zobrist_table[3][5][13] = 0x9B29B54BE587DD21ULL;
    zobrist_table[3][6][0] = 0x83924F05F5C7B9AAULL;
    zobrist_table[3][6][1] = 0x60900772923C4E5DULL;
    zobrist_table[3][6][2] = 0x27E125A42D206ADAULL;
    zobrist_table[3][6][3] = 0x6D3FAD4C40270546ULL;
    zobrist_table[3][6][4] = 0xF112CFD037B5DBACULL;
    zobrist_table[3][6][5] = 0xB8378D8291CBE386ULL;
    zobrist_table[3][6][6] = 0xC842C19AC1FBE94CULL;
    zobrist_table[3][6][7] = 0x7EBA03520D589A58ULL;
    zobrist_table[3][6][8] = 0x64C371CFAE7FBA11ULL;
    zobrist_table[3][6][9] = 0xA310A849B7975B28ULL;
    zobrist_table[3][6][10] = 0x624C4B62591550FFULL;
    zobrist_table[3][6][11] = 0xD87064FC83DAB265ULL;
    zobrist_table[3][6][12] = 0x8B5230ED2A30363BULL;
    zobrist_table[3][6][13] = 0xFE8B2B79BADA7947ULL;
    zobrist_table[3][7][0] = 0x863043D70A6BE26CULL;
    zobrist_table[3][7][1] = 0x1724925FFB314DA0ULL;
    zobrist_table[3][7][2] = 0x4153BBC7CED5669FULL;
    zobrist_table[3][7][3] = 0x19DE2DEDA0E20045ULL;
    zobrist_table[3][7][4] = 0xBCA5F87B447C999DULL;
    zobrist_table[3][7][5] = 0x156EAB79E9B161F4ULL;
    zobrist_table[3][7][6] = 0xF98DDC84F59DC887ULL;
    zobrist_table[3][7][7] = 0xF81F5C80239DC599ULL;
    zobrist_table[3][7][8] = 0x9DED54FDC69806EAULL;
    zobrist_table[3][7][9] = 0xF78047CFD788C7CCULL;
    zobrist_table[3][7][10] = 0xAFC6EE6FA8E33C94ULL;
    zobrist_table[3][7][11] = 0x14FE7EBCB34DEC74ULL;
    zobrist_table[3][7][12] = 0xD9D9320E71EF5E7AULL;
    zobrist_table[3][7][13] = 0x3DB18A28EC9F6FBFULL;
    zobrist_table[4][0][0] = 0xD9DB30AFF8A10E70ULL;
    zobrist_table[4][0][1] = 0xF0A3A66861E1E80DULL;
    zobrist_table[4][0][2] = 0xE746EBEBCD7E80A2ULL;
    zobrist_table[4][0][3] = 0x65B184F76ED3F30BULL;
    zobrist_table[4][0][4] = 0xE8FB46B52A2D551FULL;
    zobrist_table[4][0][5] = 0x702938155351D2C1ULL;
    zobrist_table[4][0][6] = 0x9F55C5FC20572AEBULL;
    zobrist_table[4][0][7] = 0x7CEB5FB4E8ACABFFULL;
    zobrist_table[4][0][8] = 0x36469FABF59CD100ULL;
    zobrist_table[4][0][9] = 0x6E6716981E830596ULL;
    zobrist_table[4][0][10] = 0x88B7CC6B99C61AA8ULL;
    zobrist_table[4][0][11] = 0xE8C7A01D68815FDAULL;
    zobrist_table[4][0][12] = 0xA9172A051E3B25E5ULL;
    zobrist_table[4][0][13] = 0x47158A7E4BA44898ULL;
    zobrist_table[4][1][0] = 0x60FC47FA3F8B1BAAULL;
    zobrist_table[4][1][1] = 0x8F332483BFE4440EULL;
    zobrist_table[4][1][2] = 0xF5B5B9340106BB05ULL;
    zobrist_table[4][1][3] = 0x8742CED2309944E2ULL;
    zobrist_table[4][1][4] = 0x943EC25A70536E9BULL;
    zobrist_table[4][1][5] = 0x7E30F1105628748ULL;
    zobrist_table[4][1][6] = 0xF91C85FDA0A59518ULL;
    zobrist_table[4][1][7] = 0x3E0363339B0A6817ULL;
    zobrist_table[4][1][8] = 0x42A95D35D5D8575DULL;
    zobrist_table[4][1][9] = 0x2C400B9534E41E75ULL;
    zobrist_table[4][1][10] = 0x25FE3A1848E772BAULL;
    zobrist_table[4][1][11] = 0x335082DC8AD6C1C4ULL;
    zobrist_table[4][1][12] = 0x4FA6961145F21E94ULL;
    zobrist_table[4][1][13] = 0xC1E6415A95F2EE55ULL;
    zobrist_table[4][2][0] = 0xD51536644039D142ULL;
    zobrist_table[4][2][1] = 0x72470ADDAEFBA2AEULL;
    zobrist_table[4][2][2] = 0xDC7A4BEECA84EBCAULL;
    zobrist_table[4][2][3] = 0xDAE720B2CF03FD21ULL;
    zobrist_table[4][2][4] = 0x2B00B570F93EE7CCULL;
    zobrist_table[4][2][5] = 0x5B616E428B9DD3D4ULL;
    zobrist_table[4][2][6] = 0x6B82ED5C7DA5AD52ULL;
    zobrist_table[4][2][7] = 0x1F2E490CDB0F0126ULL;
    zobrist_table[4][2][8] = 0x357D6F2EC4E199A1ULL;
    zobrist_table[4][2][9] = 0xE1018CC5920F3663ULL;
    zobrist_table[4][2][10] = 0x346F3293621D1733ULL;
    zobrist_table[4][2][11] = 0xCF80F75148B75541ULL;
    zobrist_table[4][2][12] = 0xE76DB5EF1BAF02CFULL;
    zobrist_table[4][2][13] = 0x62EBC92CEBB898AULL;
    zobrist_table[4][3][0] = 0x91BE34EB1E39EF8EULL;
    zobrist_table[4][3][1] = 0x3621F97BF4CC645ULL;
    zobrist_table[4][3][2] = 0x4BE1B2488B97EF45ULL;
    zobrist_table[4][3][3] = 0xAC859F8FF706A832ULL;
    zobrist_table[4][3][4] = 0xB96CC27AC2D532FAULL;
    zobrist_table[4][3][5] = 0xA63E0C32F93897B0ULL;
    zobrist_table[4][3][6] = 0x133F3B0A22F7D343ULL;
    zobrist_table[4][3][7] = 0x5FAC971A80185844ULL;
    zobrist_table[4][3][8] = 0xCE33DD7092947D94ULL;
    zobrist_table[4][3][9] = 0x6FEA51CA4FAE2CF5ULL;
    zobrist_table[4][3][10] = 0xAD611A3E80C6BCBDULL;
    zobrist_table[4][3][11] = 0xC234472F5B58796AULL;
    zobrist_table[4][3][12] = 0x52DD34D68744D3C0ULL;
    zobrist_table[4][3][13] = 0x1FB7F62800375C0DULL;
    zobrist_table[4][4][0] = 0xB7CCBA58713B831BULL;
    zobrist_table[4][4][1] = 0x59A78B137315D969ULL;
    zobrist_table[4][4][2] = 0x8A0F42834E0751D7ULL;
    zobrist_table[4][4][3] = 0x56E0A246663F423BULL;
    zobrist_table[4][4][4] = 0xBB2B92C3C87868FAULL;
    zobrist_table[4][4][5] = 0x92484194AEF4259CULL;
    zobrist_table[4][4][6] = 0x1CF3D1797E0750EAULL;
    zobrist_table[4][4][7] = 0xEAF5C033A5CD95E7ULL;
    zobrist_table[4][4][8] = 0x61E406A660A7A7B7ULL;
    zobrist_table[4][4][9] = 0x8E903FD93433B60CULL;
    zobrist_table[4][4][10] = 0xFEAD3BED00FDFEAEULL;
    zobrist_table[4][4][11] = 0xA2B249AB47122FAAULL;
    zobrist_table[4][4][12] = 0xB8E7DF9B992149E8ULL;
    zobrist_table[4][4][13] = 0xBD1296CDE1B4A960ULL;
    zobrist_table[4][5][0] = 0xBA7725A3D454F36DULL;
    zobrist_table[4][5][1] = 0x32E9C06982CE49DEULL;
    zobrist_table[4][5][2] = 0xEC5DF2C7FCAD3888ULL;
    zobrist_table[4][5][3] = 0x99D026A7762A2BA5ULL;
    zobrist_table[4][5][4] = 0x84546026D5A7EB2EULL;
    zobrist_table[4][5][5] = 0xEFFE76E068B1F3C9ULL;
    zobrist_table[4][5][6] = 0xB64E172FBEA01CA0ULL;
    zobrist_table[4][5][7] = 0xFCD26DADFCD2CF1EULL;
    zobrist_table[4][5][8] = 0xB3F0B94C4E2A89F5ULL;
    zobrist_table[4][5][9] = 0x730B19EC2B999F07ULL;
    zobrist_table[4][5][10] = 0xAB3920349EBA8775ULL;
    zobrist_table[4][5][11] = 0x3286423887ECBE86ULL;
    zobrist_table[4][5][12] = 0x86B46F015C03151CULL;
    zobrist_table[4][5][13] = 0xADB5555600E6A305ULL;
    zobrist_table[4][6][0] = 0x9450085B63A029A5ULL;
    zobrist_table[4][6][1] = 0xF86668C16D05C818ULL;
    zobrist_table[4][6][2] = 0x5604C3B667BE9998ULL;
    zobrist_table[4][6][3] = 0x9F22CE0ADC7A9283ULL;
    zobrist_table[4][6][4] = 0xF977EDF4959D133DULL;
    zobrist_table[4][6][5] = 0xB312AD6FBBDC55A2ULL;
    zobrist_table[4][6][6] = 0xF7ADC0AEE5DD6001ULL;
    zobrist_table[4][6][7] = 0x1157C8B3BFAF9E2FULL;
    zobrist_table[4][6][8] = 0xFCD58C0F7E21B8AAULL;
    zobrist_table[4][6][9] = 0x3F64C50CBEEAAC97ULL;
    zobrist_table[4][6][10] = 0xF78D9952A3EE54D4ULL;
    zobrist_table[4][6][11] = 0x4A77814EA6142E5BULL;
    zobrist_table[4][6][12] = 0x55198C0A1326797ULL;
    zobrist_table[4][6][13] = 0xB8A61715683115A8ULL;
    zobrist_table[4][7][0] = 0x27F52FA9A117511FULL;
    zobrist_table[4][7][1] = 0xC76330AFA23C4B27ULL;
    zobrist_table[4][7][2] = 0x65B699ECEFE6F675ULL;
    zobrist_table[4][7][3] = 0x452FAC9AC850320AULL;
    zobrist_table[4][7][4] = 0x2D9B4F22D8A50636ULL;
    zobrist_table[4][7][5] = 0x12CB2F3FC47ADDC9ULL;
    zobrist_table[4][7][6] = 0xC6AD0327D0B93207ULL;
    zobrist_table[4][7][7] = 0x297C0D69AFF956CULL;
    zobrist_table[4][7][8] = 0xE9A413CA59758F83ULL;
    zobrist_table[4][7][9] = 0xCC5D375A43BBBA66ULL;
    zobrist_table[4][7][10] = 0x6940776CB540CCE4ULL;
    zobrist_table[4][7][11] = 0xAF5E490BDFBAAAFAULL;
    zobrist_table[4][7][12] = 0x4DBD3DC98B53C16BULL;
    zobrist_table[4][7][13] = 0x764A44E326EE0EACULL;
    zobrist_table[5][0][0] = 0x4264D159D53DDE5EULL;
    zobrist_table[5][0][1] = 0x2B6C57637C0B03EEULL;
    zobrist_table[5][0][2] = 0x82A4C12E779409B9ULL;
    zobrist_table[5][0][3] = 0x45547D9D0B9E8D4DULL;
    zobrist_table[5][0][4] = 0x193FD24D82A1C54CULL;
    zobrist_table[5][0][5] = 0x9733EF95BEA7C879ULL;
    zobrist_table[5][0][6] = 0x11DB6ACF6C2F5ECCULL;
    zobrist_table[5][0][7] = 0x1126D71A5AECE68FULL;
    zobrist_table[5][0][8] = 0x714699BDA826E5F1ULL;
    zobrist_table[5][0][9] = 0x2A04FF67050DC58CULL;
    zobrist_table[5][0][10] = 0xB5D28DEE81D57930ULL;
    zobrist_table[5][0][11] = 0x29606598F23562B7ULL;
    zobrist_table[5][0][12] = 0x17D259ADB0C12C60ULL;
    zobrist_table[5][0][13] = 0xA2CF179F66E47927ULL;
    zobrist_table[5][1][0] = 0x469A8A20B05C4A59ULL;
    zobrist_table[5][1][1] = 0x4DED5FAA9AE0E1B9ULL;
    zobrist_table[5][1][2] = 0x873116F03579C67EULL;
    zobrist_table[5][1][3] = 0x3CBB5615352C5F80ULL;
    zobrist_table[5][1][4] = 0x557D728CE2D28DA8ULL;
    zobrist_table[5][1][5] = 0x118CC43E44E1B856ULL;
    zobrist_table[5][1][6] = 0xB2FE7205132BA600ULL;
    zobrist_table[5][1][7] = 0xE90C0722D4A74958ULL;
    zobrist_table[5][1][8] = 0xA8A6217585F049FEULL;
    zobrist_table[5][1][9] = 0x77CAB1F95E42E3E0ULL;
    zobrist_table[5][1][10] = 0x8EC2361582F2E770ULL;
    zobrist_table[5][1][11] = 0xCBBEAB0BC9A0E0CULL;
    zobrist_table[5][1][12] = 0x4C0015082B265442ULL;
    zobrist_table[5][1][13] = 0xBC2E9FF5A72F6600ULL;
    zobrist_table[5][2][0] = 0xFF11DC91B6A3CE92ULL;
    zobrist_table[5][2][1] = 0x8E65E4CFD0A410DAULL;
    zobrist_table[5][2][2] = 0x5B1916CD450F0864ULL;
    zobrist_table[5][2][3] = 0xBD6679C09C1317A3ULL;
    zobrist_table[5][2][4] = 0x647EC1543B6BD0A4ULL;
    zobrist_table[5][2][5] = 0x6653C3B78FA09FA2ULL;
    zobrist_table[5][2][6] = 0x7BCEC85D2C1FFACCULL;
    zobrist_table[5][2][7] = 0x427005F6CA2E3611ULL;
    zobrist_table[5][2][8] = 0x9C434723DDE138D8ULL;
    zobrist_table[5][2][9] = 0xB74F34105463852DULL;
    zobrist_table[5][2][10] = 0x423E96D038E9DE81ULL;
    zobrist_table[5][2][11] = 0x9C25B2DBF6BAD673ULL;
    zobrist_table[5][2][12] = 0x3E85B0A9B4E9A806ULL;
    zobrist_table[5][2][13] = 0xA92CD2DED802CB08ULL;
    zobrist_table[5][3][0] = 0xDA0DBC7807D11B6BULL;
    zobrist_table[5][3][1] = 0xDE518343E63EA3D6ULL;
    zobrist_table[5][3][2] = 0x6710B0E79F5904A6ULL;
    zobrist_table[5][3][3] = 0xED9140C051080DEBULL;
    zobrist_table[5][3][4] = 0xEEE133EA6E883110ULL;
    zobrist_table[5][3][5] = 0x3F98E0EEC2F7C23FULL;
    zobrist_table[5][3][6] = 0x44E32DBDC910C201ULL;
    zobrist_table[5][3][7] = 0x1291F006309D57EDULL;
    zobrist_table[5][3][8] = 0xBB798E9BA03A1915ULL;
    zobrist_table[5][3][9] = 0xDEFD56702A66B259ULL;
    zobrist_table[5][3][10] = 0x9442F362F919CB32ULL;
    zobrist_table[5][3][11] = 0x94D8CD47718E3BAFULL;
    zobrist_table[5][3][12] = 0xEED4B1F0E9C3DEEEULL;
    zobrist_table[5][3][13] = 0x25EF2114BA6E736CULL;
    zobrist_table[5][4][0] = 0xF20AB3059B33D947ULL;
    zobrist_table[5][4][1] = 0x759AAEEE431162A4ULL;
    zobrist_table[5][4][2] = 0x299BF22D86CEC133ULL;
    zobrist_table[5][4][3] = 0xC7495DF9237C9540ULL;
    zobrist_table[5][4][4] = 0xE4D4AD86235A63D5ULL;
    zobrist_table[5][4][5] = 0x70D07EBAB73B6062ULL;
    zobrist_table[5][4][6] = 0x4F4C8DB65C706106ULL;
    zobrist_table[5][4][7] = 0x6697F21EC05A32A3ULL;
    zobrist_table[5][4][8] = 0x1DA77D913D90FD27ULL;
    zobrist_table[5][4][9] = 0x34C8D03AB7D9365CULL;
    zobrist_table[5][4][10] = 0xAE7024EDB7EE1A9AULL;
    zobrist_table[5][4][11] = 0x117746184E34FA77ULL;
    zobrist_table[5][4][12] = 0x3A4548F21B3C137BULL;
    zobrist_table[5][4][13] = 0x524550A465A24E8AULL;
    zobrist_table[5][5][0] = 0xEDB924D87E0B6723ULL;
    zobrist_table[5][5][1] = 0xF48FE7D31997E8F3ULL;
    zobrist_table[5][5][2] = 0xB83DA502FCF9616ULL;
    zobrist_table[5][5][3] = 0xCF39EFD70E2AF641ULL;
    zobrist_table[5][5][4] = 0x5F5E71B98F6A644ULL;
    zobrist_table[5][5][5] = 0xC09F025EE38D62A7ULL;
    zobrist_table[5][5][6] = 0xAEECB544377054CFULL;
    zobrist_table[5][5][7] = 0x7E94F5AB08E2FAD3ULL;
    zobrist_table[5][5][8] = 0x874E263FB4345622ULL;
    zobrist_table[5][5][9] = 0xB9559250D09DFA6CULL;
    zobrist_table[5][5][10] = 0xE31E1292F6D0AC1DULL;
    zobrist_table[5][5][11] = 0x7139BED19CF94BC1ULL;
    zobrist_table[5][5][12] = 0xA9B576D757AA5AE1ULL;
    zobrist_table[5][5][13] = 0x464A8296D67E8ECFULL;
    zobrist_table[5][6][0] = 0x9CFD717D1E39A54CULL;
    zobrist_table[5][6][1] = 0x2C354A1BB150A78DULL;
    zobrist_table[5][6][2] = 0x38D9431F18610C9FULL;
    zobrist_table[5][6][3] = 0x3BB42D9D66531DAFULL;
    zobrist_table[5][6][4] = 0x732701337EB9D1C8ULL;
    zobrist_table[5][6][5] = 0xC02823EC60BDADCEULL;
    zobrist_table[5][6][6] = 0xF9333F742B2935F2ULL;
    zobrist_table[5][6][7] = 0x3C593E7F3B51D375ULL;
    zobrist_table[5][6][8] = 0x489CBAFFD1F559AFULL;
    zobrist_table[5][6][9] = 0x8C09786B766B5E3CULL;
    zobrist_table[5][6][10] = 0x63BC6601947678F5ULL;
    zobrist_table[5][6][11] = 0x73A26890363F89C2ULL;
    zobrist_table[5][6][12] = 0x42041769B705FBF3ULL;
    zobrist_table[5][6][13] = 0x7F0FAD3B5482909FULL;
    zobrist_table[5][7][0] = 0x1C66EED297F7634BULL;
    zobrist_table[5][7][1] = 0x36BEB903E8D424EEULL;
    zobrist_table[5][7][2] = 0x142FAB55FE909103ULL;
    zobrist_table[5][7][3] = 0x3F207910BD4F091ULL;
    zobrist_table[5][7][4] = 0x1569570CC2534B4ULL;
    zobrist_table[5][7][5] = 0x7AFB6462DB8AE021ULL;
    zobrist_table[5][7][6] = 0xE38A59AA51CFA14EULL;
    zobrist_table[5][7][7] = 0xD910DDD76215F679ULL;
    zobrist_table[5][7][8] = 0x4986F3A6948B82B1ULL;
    zobrist_table[5][7][9] = 0x322578EBEB391D06ULL;
    zobrist_table[5][7][10] = 0x28FA361A6661B877ULL;
    zobrist_table[5][7][11] = 0xD3005630E149A837ULL;
    zobrist_table[5][7][12] = 0xA5632A15C23105D9ULL;
    zobrist_table[5][7][13] = 0xCB320DB826FB5E56ULL;
    zobrist_table[6][0][0] = 0x7CC0424E9E6ED7CULL;
    zobrist_table[6][0][1] = 0x63243E5303E2E7C4ULL;
    zobrist_table[6][0][2] = 0xE055AF1C252A66D8ULL;
    zobrist_table[6][0][3] = 0x8AE63AB1AA311156ULL;
    zobrist_table[6][0][4] = 0x909311ED0E9F654FULL;
    zobrist_table[6][0][5] = 0x4111329A61263FDDULL;
    zobrist_table[6][0][6] = 0x145B523821464B6DULL;
    zobrist_table[6][0][7] = 0xA6F38E3E767FE953ULL;
    zobrist_table[6][0][8] = 0x4DABB96DD708F3A0ULL;
    zobrist_table[6][0][9] = 0x3B27030E7F524F3ULL;
    zobrist_table[6][0][10] = 0x89778FB7091489CDULL;
    zobrist_table[6][0][11] = 0x8660194D0F93FB05ULL;
    zobrist_table[6][0][12] = 0x21013EEFD733230AULL;
    zobrist_table[6][0][13] = 0xEEF208450AF5E8D2ULL;
    zobrist_table[6][1][0] = 0xC7E21846460A02ECULL;
    zobrist_table[6][1][1] = 0x6EB8F85F1E10553BULL;
    zobrist_table[6][1][2] = 0x30AB1C2E174E3F4BULL;
    zobrist_table[6][1][3] = 0x7FE9DA2007124B2FULL;
    zobrist_table[6][1][4] = 0x215C1C0BA3340D96ULL;
    zobrist_table[6][1][5] = 0x477E4A80BE9F0A63ULL;
    zobrist_table[6][1][6] = 0xD12FF4BFAFD03FB9ULL;
    zobrist_table[6][1][7] = 0x312218D0D87ABBFFULL;
    zobrist_table[6][1][8] = 0x72904D18A9BB6DCBULL;
    zobrist_table[6][1][9] = 0x546E197B63C3817CULL;
    zobrist_table[6][1][10] = 0x4499E3AFA18D58B8ULL;
    zobrist_table[6][1][11] = 0x42850DA8F8375D93ULL;
    zobrist_table[6][1][12] = 0xA2B73A66A4401DABULL;
    zobrist_table[6][1][13] = 0x3ED43AB33E3B4290ULL;
    zobrist_table[6][2][0] = 0x968240EF0F683985ULL;
    zobrist_table[6][2][1] = 0xC9B8056FEF6709E9ULL;
    zobrist_table[6][2][2] = 0x2CDEEC51972AB68BULL;
    zobrist_table[6][2][3] = 0x6DB076BD59805A17ULL;
    zobrist_table[6][2][4] = 0xB2B3D2229AF865DFULL;
    zobrist_table[6][2][5] = 0xA36CF2B98F6D0AAAULL;
    zobrist_table[6][2][6] = 0xF819B75085AD0C99ULL;
    zobrist_table[6][2][7] = 0xE7B128FD0F90E49CULL;
    zobrist_table[6][2][8] = 0x8C0354BE5A6D1EFCULL;
    zobrist_table[6][2][9] = 0x89C08E1C69A36E9AULL;
    zobrist_table[6][2][10] = 0xB62E96933309CDB1ULL;
    zobrist_table[6][2][11] = 0x8951D454E14E939AULL;
    zobrist_table[6][2][12] = 0xEB7FEC926C931D1AULL;
    zobrist_table[6][2][13] = 0x11F10C60A9921B68ULL;
    zobrist_table[6][3][0] = 0x446056BFB6AAFAE5ULL;
    zobrist_table[6][3][1] = 0x9C546496BE47CC7AULL;
    zobrist_table[6][3][2] = 0xF8ECAE24B89B02F9ULL;
    zobrist_table[6][3][3] = 0x128137EAC090BC84ULL;
    zobrist_table[6][3][4] = 0x2D75C843406797B6ULL;
    zobrist_table[6][3][5] = 0x18B8A008F9F59771ULL;
    zobrist_table[6][3][6] = 0xF078F6C26A89353ULL;
    zobrist_table[6][3][7] = 0x340E8462EB2C79D4ULL;
    zobrist_table[6][3][8] = 0x6D9814D5DAC504E5ULL;
    zobrist_table[6][3][9] = 0xB7EF083DA277078ULL;
    zobrist_table[6][3][10] = 0xA31A7B190D8509DBULL;
    zobrist_table[6][3][11] = 0xE9901243175A1163ULL;
    zobrist_table[6][3][12] = 0x83497471D0246CCAULL;
    zobrist_table[6][3][13] = 0x8049E97A781B5120ULL;
    zobrist_table[6][4][0] = 0x196A8D845EC8E9D7ULL;
    zobrist_table[6][4][1] = 0x500C48E1FC147A78ULL;
    zobrist_table[6][4][2] = 0x206A985A0A452B53ULL;
    zobrist_table[6][4][3] = 0x87EE17B880E180BULL;
    zobrist_table[6][4][4] = 0xAA0CB6F5717F5EEDULL;
    zobrist_table[6][4][5] = 0xE539D34D20D1EB7DULL;
    zobrist_table[6][4][6] = 0xC36E5359652B0ED7ULL;
    zobrist_table[6][4][7] = 0xE61541B6B528614CULL;
    zobrist_table[6][4][8] = 0x723280C3E1DF6F91ULL;
    zobrist_table[6][4][9] = 0xBC937D7E064D7A2FULL;
    zobrist_table[6][4][10] = 0x451E07EA8646422CULL;
    zobrist_table[6][4][11] = 0x40008E261722EBBEULL;
    zobrist_table[6][4][12] = 0x534E570FCCE695F7ULL;
    zobrist_table[6][4][13] = 0x4D455C7115F6063EULL;
    zobrist_table[6][5][0] = 0xDC14F82708C0E4A2ULL;
    zobrist_table[6][5][1] = 0xEE3BDCB625D4DD2ULL;
    zobrist_table[6][5][2] = 0x42D15CD3BB8C1409ULL;
    zobrist_table[6][5][3] = 0xBC377F13502E5056ULL;
    zobrist_table[6][5][4] = 0x42A305D521480046ULL;
    zobrist_table[6][5][5] = 0x6153AF71CB6915C1ULL;
    zobrist_table[6][5][6] = 0x1DFCA10CCE9244CBULL;
    zobrist_table[6][5][7] = 0xAD83C3FBDB19A0BBULL;
    zobrist_table[6][5][8] = 0x181437224DC232A6ULL;
    zobrist_table[6][5][9] = 0xD765194F6CC1AEAFULL;
    zobrist_table[6][5][10] = 0x80B380113ED1E0EBULL;
    zobrist_table[6][5][11] = 0x3495D62A8EA32F2EULL;
    zobrist_table[6][5][12] = 0xEC4C277B5481E736ULL;
    zobrist_table[6][5][13] = 0x8262CDC556B2A3E4ULL;
    zobrist_table[6][6][0] = 0x641E9E8DC89B69D3ULL;
    zobrist_table[6][6][1] = 0xE54E1AD1F4CFD336ULL;
    zobrist_table[6][6][2] = 0x7B2CCE17958A3855ULL;
    zobrist_table[6][6][3] = 0x21358EE61ACCD407ULL;
    zobrist_table[6][6][4] = 0xD08EF562A70F268FULL;
    zobrist_table[6][6][5] = 0x86143E1472D837AFULL;
    zobrist_table[6][6][6] = 0x8F036FBEFCEF9215ULL;
    zobrist_table[6][6][7] = 0xD810C3F6B82962A8ULL;
    zobrist_table[6][6][8] = 0x94D43EDED5B48AD0ULL;
    zobrist_table[6][6][9] = 0x8523E065B3877F0EULL;
    zobrist_table[6][6][10] = 0x7BFAAEA891E53CBULL;
    zobrist_table[6][6][11] = 0xFAD32CAFE595E3CBULL;
    zobrist_table[6][6][12] = 0xFDBB37B8D4E4DB03ULL;
    zobrist_table[6][6][13] = 0xBE40F38E4A945554ULL;
    zobrist_table[6][7][0] = 0x3331824728333E0EULL;
    zobrist_table[6][7][1] = 0x63A522E35ECF615DULL;
    zobrist_table[6][7][2] = 0x53001B63856558B2ULL;
    zobrist_table[6][7][3] = 0x68D52EB618EDE6C3ULL;
    zobrist_table[6][7][4] = 0x20599249586AC6E6ULL;
    zobrist_table[6][7][5] = 0x109ADA70932D0488ULL;
    zobrist_table[6][7][6] = 0x4CED509A0B27B4C9ULL;
    zobrist_table[6][7][7] = 0xCC88EBD1D0A079F5ULL;
    zobrist_table[6][7][8] = 0x889F5E9AA6AF9B40ULL;
    zobrist_table[6][7][9] = 0x6AE70FF2504B60B5ULL;
    zobrist_table[6][7][10] = 0x519CD4CC4C5EC38DULL;
    zobrist_table[6][7][11] = 0x45CDA9495A450D23ULL;
    zobrist_table[6][7][12] = 0xBFAD326153461EB3ULL;
    zobrist_table[6][7][13] = 0x852571D4BF9E995CULL;
    zobrist_table[7][0][0] = 0x2345A9D8045432FULL;
    zobrist_table[7][0][1] = 0x1F327A7486B059DCULL;
    zobrist_table[7][0][2] = 0x512E2BEA2614E7E7ULL;
    zobrist_table[7][0][3] = 0xBA0FF0B7EA174C4EULL;
    zobrist_table[7][0][4] = 0xC8E2896A5358BF46ULL;
    zobrist_table[7][0][5] = 0x92B7563053DB4391ULL;
    zobrist_table[7][0][6] = 0x73AA1107119FE69FULL;
    zobrist_table[7][0][7] = 0x4794AB91FABAB7B5ULL;
    zobrist_table[7][0][8] = 0x7442A8CC7ACD7A45ULL;
    zobrist_table[7][0][9] = 0x5D39F1B8E9B2D06AULL;
    zobrist_table[7][0][10] = 0xBDDBF0CAED7852CEULL;
    zobrist_table[7][0][11] = 0x616A43DEF841AD26ULL;
    zobrist_table[7][0][12] = 0xE3BBA436D0CD14A1ULL;
    zobrist_table[7][0][13] = 0x1402F91CECE9D8EDULL;
    zobrist_table[7][1][0] = 0x943735D4EC1B2724ULL;
    zobrist_table[7][1][1] = 0xE5C9BEBCD266EA8ULL;
    zobrist_table[7][1][2] = 0xC7950FA2273EA38ULL;
    zobrist_table[7][1][3] = 0x7DFF04AE8611F8B9ULL;
    zobrist_table[7][1][4] = 0xDA64B870935AC8D9ULL;
    zobrist_table[7][1][5] = 0x407DBB94FE145171ULL;
    zobrist_table[7][1][6] = 0x3ED03C49C8B0DA28ULL;
    zobrist_table[7][1][7] = 0x92E38012B3F2513DULL;
    zobrist_table[7][1][8] = 0x56B1B132BF246424ULL;
    zobrist_table[7][1][9] = 0xFD983DF55C905C22ULL;
    zobrist_table[7][1][10] = 0xCC025364F13B7619ULL;
    zobrist_table[7][1][11] = 0x5EC127B3A4BC7977ULL;
    zobrist_table[7][1][12] = 0x4EB0FF74670F2134ULL;
    zobrist_table[7][1][13] = 0x9927A8FD76EE29AAULL;
    zobrist_table[7][2][0] = 0x5727D740FAD13805ULL;
    zobrist_table[7][2][1] = 0x81EE476C88399110ULL;
    zobrist_table[7][2][2] = 0x77148A52AF4C782ULL;
    zobrist_table[7][2][3] = 0x400839A925FA97DDULL;
    zobrist_table[7][2][4] = 0x389C1CCFAFEF1AC1ULL;
    zobrist_table[7][2][5] = 0x2226FF4390120EA1ULL;
    zobrist_table[7][2][6] = 0x1CDDEE9CE8247487ULL;
    zobrist_table[7][2][7] = 0xC42DDDC22F41F7CDULL;
    zobrist_table[7][2][8] = 0xF06F217A693E6D5DULL;
    zobrist_table[7][2][9] = 0x9EA4F0BBBA5B99CDULL;
    zobrist_table[7][2][10] = 0xCFCD69020CD3AEE8ULL;
    zobrist_table[7][2][11] = 0xFA85459D1966A3BBULL;
    zobrist_table[7][2][12] = 0xAE6AC89A8BB3835BULL;
    zobrist_table[7][2][13] = 0xB6F3D08A4406D47FULL;
    zobrist_table[7][3][0] = 0x344FEFE11B604336ULL;
    zobrist_table[7][3][1] = 0x11180CD942FE9CA9ULL;
    zobrist_table[7][3][2] = 0x923B3BEAA1D3FF82ULL;
    zobrist_table[7][3][3] = 0xA41AAFAC86C0ABFEULL;
    zobrist_table[7][3][4] = 0xDAEB22A514185D06ULL;
    zobrist_table[7][3][5] = 0xCB517E6A12A3C54BULL;
    zobrist_table[7][3][6] = 0x37A6437BD9C2B0CFULL;
    zobrist_table[7][3][7] = 0xD69871BCA4AB4EECULL;
    zobrist_table[7][3][8] = 0x82F01B582C61CBECULL;
    zobrist_table[7][3][9] = 0x6E9D7077DCA1284FULL;
    zobrist_table[7][3][10] = 0x9721C6E50597EBC1ULL;
    zobrist_table[7][3][11] = 0xE66743DC5E3C1D96ULL;
    zobrist_table[7][3][12] = 0x7C969920D8FE4338ULL;
    zobrist_table[7][3][13] = 0xCEB52FC3B5D4CE45ULL;
    zobrist_table[7][4][0] = 0x384DA68248A3FF76ULL;
    zobrist_table[7][4][1] = 0x334C76B8E42B0627ULL;
    zobrist_table[7][4][2] = 0x7E5D933D991BA3CEULL;
    zobrist_table[7][4][3] = 0xE61BACEBDD90F85BULL;
    zobrist_table[7][4][4] = 0x3C377DA0E48E1B4DULL;
    zobrist_table[7][4][5] = 0x73C2F6F06CE9E732ULL;
    zobrist_table[7][4][6] = 0x5DFE36F1ACF424D9ULL;
    zobrist_table[7][4][7] = 0xE9A1A2588B62CCBAULL;
    zobrist_table[7][4][8] = 0x3056DDB0F1DA2B29ULL;
    zobrist_table[7][4][9] = 0x7B6EB806CC544333ULL;
    zobrist_table[7][4][10] = 0x129C03B0B9CF3DDEULL;
    zobrist_table[7][4][11] = 0xD73ECD63D0646CF9ULL;
    zobrist_table[7][4][12] = 0xF9EEF8DBFF876918ULL;
    zobrist_table[7][4][13] = 0x68457E4141ADFE67ULL;
    zobrist_table[7][5][0] = 0x21EA0E2338C9127ULL;
    zobrist_table[7][5][1] = 0x883062FABF2D288BULL;
    zobrist_table[7][5][2] = 0x6176A3CAC53482ECULL;
    zobrist_table[7][5][3] = 0xE0463F9F83A81A4EULL;
    zobrist_table[7][5][4] = 0x138FCC237CB10028ULL;
    zobrist_table[7][5][5] = 0x9DA7FDF2675BB4B3ULL;
    zobrist_table[7][5][6] = 0x8293D779E1F86D03ULL;
    zobrist_table[7][5][7] = 0x940A3AEBCBD5DA31ULL;
    zobrist_table[7][5][8] = 0x6CF3EEEA95A8303BULL;
    zobrist_table[7][5][9] = 0x5A11494F0A453E8CULL;
    zobrist_table[7][5][10] = 0xFCE5D2C6D9E46A51ULL;
    zobrist_table[7][5][11] = 0x1A38311755D3871ULL;
    zobrist_table[7][5][12] = 0xF5E4C4BB30942540ULL;
    zobrist_table[7][5][13] = 0xB22CC3474CA27B41ULL;
    zobrist_table[7][6][0] = 0xA45F419CB0FB4BC8ULL;
    zobrist_table[7][6][1] = 0x8A70103F0168E969ULL;
    zobrist_table[7][6][2] = 0xD265BCD71EBB3EF7ULL;
    zobrist_table[7][6][3] = 0x8332AC334D7AB56DULL;
    zobrist_table[7][6][4] = 0xFE725A5EE31EF8FBULL;
    zobrist_table[7][6][5] = 0x50C80450BF323EF2ULL;
    zobrist_table[7][6][6] = 0xC6CD35FFF885CE63ULL;
    zobrist_table[7][6][7] = 0xA521DADD8B03EE7CULL;
    zobrist_table[7][6][8] = 0xFE692199926C8264ULL;
    zobrist_table[7][6][9] = 0x48525E8A8D2707D7ULL;
    zobrist_table[7][6][10] = 0x6953E9E8868F8154ULL;
    zobrist_table[7][6][11] = 0xF08B56528AC32BBDULL;
    zobrist_table[7][6][12] = 0xED421259D18DA490ULL;
    zobrist_table[7][6][13] = 0x8492C7B5F40FF922ULL;
    zobrist_table[7][7][0] = 0x9A4F17B66886663AULL;
    zobrist_table[7][7][1] = 0x94C05053A14566E6ULL;
    zobrist_table[7][7][2] = 0x73D87FD74EC9521CULL;
    zobrist_table[7][7][3] = 0x218586644D49FFCEULL;
    zobrist_table[7][7][4] = 0x71B5FF55819E0387ULL;
    zobrist_table[7][7][5] = 0x23EC75979615A32EULL;
    zobrist_table[7][7][6] = 0xC5C328968CCC6FF2ULL;
    zobrist_table[7][7][7] = 0xF97C4298FA01208BULL;
    zobrist_table[7][7][8] = 0x40B3D0C629B87BAFULL;
    zobrist_table[7][7][9] = 0x27586DAA2FC706BULL;
    zobrist_table[7][7][10] = 0x6C96EDFAFE99958FULL;
    zobrist_table[7][7][11] = 0xA95B3B44BC735CA7ULL;
    zobrist_table[7][7][12] = 0x947AA9290DF617BULL;
    zobrist_table[7][7][13] = 0x6BBE026B5E4D0C25ULL;
    zobrist_white_castle_king = 0x4813FCAA66F292EDULL;
    zobrist_white_castle_queen = 0xA8B3B3DEEFBFFA3DULL;
    zobrist_black_castle_king = 0xC0426A0CE5346059ULL;
    zobrist_black_castle_queen = 0x4B15253AB6FE7D5ULL;
    zobrist_blacks_turn = 0x17297DB8E6145787ULL;
}

const transposition_entry empty_transposition_entry = {};

const Zobrist zobrist = Zobrist();

TranspositionTable::TranspositionTable(unsigned long int size){
	this->size = size;
	this->data = new transposition_entry[size][2];
	for(unsigned long int i=0;i<size;i++){
		for(int j=0;j<2;j++){
			this->data[i][j] = empty_transposition_entry;
		}
	}
}

TranspositionTable::~TranspositionTable(void){
	delete[] this->data;
}

/*
bool TranspositionTable::exists(GameState *brd){
	unsigned long int index = this->getindex(brd);
	transposition_entry entry = this->data[index];
	if(entry == empty_transposition_entry){
		return false;
	} else {
		return true;
	}
}
*/

unsigned long int TranspositionTable::getindex(GameState *brd){
	return (unsigned long int) ((brd->hash) % size);
}

void TranspositionTable::setitem(GameState *brd, transposition_entry &entry){
	unsigned long int index = this->getindex(brd);
	transposition_entry best_so_far = this->data[index][1];
	if(entry.value.value > best_so_far.value.value && !entry.value.upper_bound){
		this->data[index][1] = entry;
	} else {
		this->data[index][0] = entry;
	}
	/*
	if(!(getitem(brd) == empty_transposition_entry || getitem(brd).brd == entry.brd)){
		EASY_EVENT("Replace");
	} else {
		EASY_EVENT("Fill");
	}
	*/
}

transposition_entry TranspositionTable::getitem(GameState *brd){
	unsigned long int index = this->getindex(brd);
	BoardState smallbrd; 
	
	transposition_entry result = this->data[index][1];
	if (result.key == brd->hash){
		smallbrd = brd->board_state;
		if (result.brd == smallbrd){
			return result;
		}
	}
	result = this->data[index][0];
	if (result.key == brd->hash){
		smallbrd = brd->board_state;
		if (result.brd == smallbrd){
			return result;
		}
	}
	return empty_transposition_entry;
}

MoveHistoryTable::MoveHistoryTable(){
	for(int i=0;i<64;i++){
		for(int j=0;j<64;j++){
			this->data[i][j] = std::make_tuple(0.0, -1.0);
		}
	}
}

bool MoveHistoryTable::compare_moves(move &lhs, move &rhs){
	// We want sorting to put the best moves first, so this 
	// is kinda reversed.
	std::tuple<double, double> left_item = this->getitem(lhs);
	std::tuple<double, double> right_item = this->getitem(rhs);
	double left_value = std::get<0>(left_item);
	double right_value = std::get<0>(right_item);
	double left_strength = std::get<1>(left_item);
	double right_strength = std::get<1>(right_item);
	if(left_strength > 0 && right_strength <= 0){
		return true;
	}
	if(left_value > right_value){
		return true;
	}
	return false;
}

std::tuple<double, double> MoveHistoryTable::getitem(move mv){
	return this->data[mv.from_square][mv.to_square];
}

void MoveHistoryTable::setitem(move mv, double value, double strength){
	std::tuple<double, double> item = this->getitem(mv);
	//double value = std::get<0>(item);
	double old_strength = std::get<1>(item);
	if(strength >= old_strength){
		this->data[mv.from_square][mv.to_square] = std::make_tuple(value, strength);
	}
}


MoveSearchMemory::MoveSearchMemory(unsigned long int tt_size){
	if(tt_size > 0){
		this->tt = new TranspositionTable(tt_size);
	}else{
		this->tt = NULL;
	}
	//this->hh = new MoveHistoryTable();
}

MoveSearchMemory::~MoveSearchMemory(){
	delete this->tt;
//	delete this->hh;
}
									