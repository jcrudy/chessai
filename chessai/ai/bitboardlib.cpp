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
const boardstate emptyboardstate = {empty,empty,empty,empty,
									empty,empty,empty,empty,
									no_enpassant, 0, 0, 0, 0, 0, 0, 0};

const move nomove = {0};

unsigned long long perft(boardstate *brd, int depth){
    std::vector<move> moves = std::vector<move>();
    all_moves(brd, moves);
    int n_moves = moves.size();
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
    	mv = moves.front();
    	moves.pop_back();
    	rec = make_move(brd, &mv);
    	result += perft(brd, depth - 1);
    	unmake_move(brd, &rec);
    }
    return(result);
}

double simple_evaluation(boardstate *brd){
	double white_score, black_score;
	white_score = 0;
	black_score = 0;
	white_score += 100 * population_count(brd->white & brd->p);
	white_score += 320 * population_count(brd->white & brd->n);
	white_score += 330 * population_count(brd->white & brd->b);
	white_score += 500 * population_count(brd->white & brd->r);
	white_score += 900 * population_count(brd->white & brd->q);
	white_score += 200000 * population_count(brd->white & brd->k);
	/*
	if(population_count(brd->white & brd->q) == 0){
		printf("Q is dead\n");
	}
	*/
	
	white_score += 1 * population_count(brd->white & center4);
	white_score += 1 * population_count(brd->white & center16);
	white_score += 5 * population_count(brd->white & brd->p & rank_7);
	white_score += 4 * population_count(brd->white & brd->p & rank_6);
	white_score += 3 * population_count(brd->white & brd->p & rank_5);
	
	black_score += 100 * population_count(brd->black & brd->p);
	black_score += 320 * population_count(brd->black & brd->n);
	black_score += 330 * population_count(brd->black & brd->b);
	black_score += 500 * population_count(brd->black & brd->r);
	black_score += 900 * population_count(brd->black & brd->q);
	black_score += 200000 * population_count(brd->black & brd->k);
	
	black_score += 1 * 100 * population_count(brd->black & center4);
	black_score += 1 * 100 * population_count(brd->black & center16);
	black_score += 5 * population_count(brd->black & brd->p & rank_1);
	black_score += 4 * population_count(brd->black & brd->p & rank_2);
	black_score += 3 * population_count(brd->black & brd->p & rank_3);
	
	
	if(get_whites_turn(brd)){
		return(white_score - black_score);
	}else{
		return(black_score - white_score);
	}
}

negamax_result negamax(boardstate *brd, double prob, double threshold, double alpha, 
					double beta, move *best_move, bool *stop, TranspositionTable *tt,
					MoveHistoryTable *hh,
					int depth, unsigned long long int *node_count, bool quiesce){
	//printf("depth = %d\n", depth);
	// This will store the moves
	std::vector<move> moves = std::vector<move>();
	
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
	negamax_result result;
	bool skip_recursion = false;
	
	// Generate all legal moves
	all_moves(brd, moves);
	num_moves = moves.size();
	std::sort(moves.begin(), moves.end(), [hh](move lhs, move rhs){return hh->compare_moves(lhs, rhs);});

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
	/*
	if(prob >= threshold){
		// Generate all legal moves
		all_moves(brd, moves);
		num_moves = moves.size();
		// If there are no legal moves, this is either checkmate or stalemate
		if (num_moves == 0) {
			if (own_check(brd)){
				result.value = -200000.0; // checkmate!
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
	}else{
		// Quiescence mode
		//all_captures(brd, moves);
		num_moves = moves.size();
		if(num_moves == 0){
			if (own_check(brd)){
				all_moves(brd, moves);
				if (moves.size() == 0) {
					result.value = -200000.0 + depth; // checkmate!
					result.lower_bound = false;
					result.upper_bound = false;
					skip_recursion = true;
				} else {
					result.value = simple_evaluation(brd);
					result.lower_bound = false;
					result.upper_bound = false;
					skip_recursion = true;
				}
			} else {
				result.value = simple_evaluation(brd);
				result.lower_bound = false;
				result.upper_bound = false;
				skip_recursion = true;
			}
		}
		// For quiescence search, stand pat if we can't find a move that's actually
		// better
		alpha = simple_evaluation(brd);
	}
	*/
	
	// Now we're ready to recurse
	negamax_result subresult;
	moverecord rec;
	double quotient = prob / num_moves;
	move best_counter = nomove;
	double value;
	bool init = true;
	
	double this_eval = simple_evaluation(brd);
	for(move mv : moves){
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
			subresult = negamax(brd, quotient, threshold, -beta, -alpha, &best_counter, stop, tt, hh, depth+1, node_count, quiesce);
			value = -subresult.value;
		}else{
			// This is a quiescence / stability search
			value = -simple_evaluation(brd);
			//printf("this_eval = %f, value = %f\n", this_eval, value);
			if(abs(this_eval - value) > 10. && quiesce){
				//printf("Quiesce: depth = %d, this_eval = %f, value = %f\n", depth, this_eval, value);
				subresult = negamax(brd, quotient, threshold, -beta, -value, &best_counter, stop, tt, hh, depth+1, node_count, quiesce);
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
		entry.brd = smallify(brd);
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
	MoveHistoryTable *hh = new MoveHistoryTable();
	while(!(*(arg->stop))){
		result = negamax(arg->brd, 1.0, thresh, -1000000.0, 1000000.0,
						&best_move, arg->stop, arg->tt, hh, 0, &node_count,
						arg->quiesce);
		value = result.value;
		if(!(*(arg->stop))){
			best_value = value;
			*(arg->best_move) = best_move;
		}
		arg->thresh = thresh;
		thresh /= 2;
	}
}

move movesearch_threshold(boardstate *brd, double threshold, TranspositionTable *tt, bool quiesce){
	EASY_PROFILER_ENABLE;
	EASY_BLOCK("movesearch_threshold");
	move best_move = nomove;
	bool blank = true;
	bool stop = false;
	unsigned long long int node_count = 0;
	int depth = 0;
	MoveHistoryTable *hh = new MoveHistoryTable();
	negamax(brd, 1.0, threshold, -1000000.0, 
				1000000.0, &best_move, &stop, tt, hh, depth, &node_count, quiesce);
	EASY_END_BLOCK;
	printf("Visited %llu nodes.\n", node_count);
	profiler::dumpBlocksToFile("test_profile.prof");
	return(best_move);
}

move movesearch_time(boardstate *brd, double time_limit, double *thresh,
					TranspositionTable *tt, bool quiesce){
	move best_move = nomove;
	bool blank = true;
	bool stop = false;
	searcharg arg = {brd, &best_move, &stop, 1., tt, quiesce};
	thread * searcher = new thread(&iterative_negamax, (void *) &arg);
	usleep(time_limit * 1000000.0);
	stop = true;
	searcher->join();
	*thresh = arg.thresh;
	printf("Reached thresh=%e", *thresh);
	return(best_move);
}
/*
move movesearch(boardstate *brd, double time_limit, int *depth){
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
zobrist_int Zobrist::update(zobrist_int previous, boardstate *brd, moverecord *mv) const{
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

zobrist_int Zobrist::hash(boardstate *brd) const{
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
    zobrist_table[0][0][0] = (((zobrist_int) 0x91B7584A2265B1F5ULL) + (((zobrist_int) 0xCD613E30D8F16ADFULL) << 64));
    zobrist_table[0][0][1] = (((zobrist_int) 0x1027C4D1C386BBC4ULL) + (((zobrist_int) 0x1E2FEB89414C343CULL) << 64));
    zobrist_table[0][0][2] = (((zobrist_int) 0xC2CE6F447ED4D57BULL) + (((zobrist_int) 0x78E510617311D8A3ULL) << 64));
    zobrist_table[0][0][3] = (((zobrist_int) 0x612E7696A6CECC1BULL) + (((zobrist_int) 0x35BF992DC9E9C616ULL) << 64));
    zobrist_table[0][0][4] = (((zobrist_int) 0x7CE42C8218072E8CULL) + (((zobrist_int) 0xE4B06CE60741C7A8ULL) << 64));
    zobrist_table[0][0][5] = (((zobrist_int) 0x63CA828DD5F4B3B2ULL) + (((zobrist_int) 0x9B810E766EC9D286ULL) << 64));
    zobrist_table[0][0][6] = (((zobrist_int) 0xC4647159C324C985ULL) + (((zobrist_int) 0xB2221A58008A05A6ULL) << 64));
    zobrist_table[0][0][7] = (((zobrist_int) 0x442E3D437204E52DULL) + (((zobrist_int) 0xCD447E35B8B6D8FEULL) << 64));
    zobrist_table[0][0][8] = (((zobrist_int) 0x9755D4C13A902931ULL) + (((zobrist_int) 0x1A2B8F1FF1FD42A2ULL) << 64));
    zobrist_table[0][0][9] = (((zobrist_int) 0x51431193E6C3F339ULL) + (((zobrist_int) 0x5B6E6E307D4BEDCULL) << 64));
    zobrist_table[0][0][10] = (((zobrist_int) 0xA648A7DD06839EB9ULL) + (((zobrist_int) 0x25B413F8A9A021EULL) << 64));
    zobrist_table[0][0][11] = (((zobrist_int) 0xE1988AD9F06C144AULL) + (((zobrist_int) 0xAFBD67F9619699CFULL) << 64));
    zobrist_table[0][0][12] = (((zobrist_int) 0xF8130C4237730EDFULL) + (((zobrist_int) 0xB9D179E06C0FD4F5ULL) << 64));
    zobrist_table[0][0][13] = (((zobrist_int) 0x8712B8BC076F3787ULL) + (((zobrist_int) 0xC381E88F38C0C8FDULL) << 64));
    zobrist_table[0][1][0] = (((zobrist_int) 0xF06D3FEF701966A0ULL) + (((zobrist_int) 0x8D88348A7EED8D14ULL) << 64));
    zobrist_table[0][1][1] = (((zobrist_int) 0x587FD2803BAB6C39ULL) + (((zobrist_int) 0xAD45F23D3B1A11DFULL) << 64));
    zobrist_table[0][1][2] = (((zobrist_int) 0xC2CD789A380208A9ULL) + (((zobrist_int) 0xF3C64AF775A89294ULL) << 64));
    zobrist_table[0][1][3] = (((zobrist_int) 0xED2F89D94A2F20AAULL) + (((zobrist_int) 0x6A8AC4BA05805975ULL) << 64));
    zobrist_table[0][1][4] = (((zobrist_int) 0xEA90A8F0D66B829EULL) + (((zobrist_int) 0xEC148CB48E73CA47ULL) << 64));
    zobrist_table[0][1][5] = (((zobrist_int) 0x19999E3FA46D6753ULL) + (((zobrist_int) 0xA11D459A2F978D87ULL) << 64));
    zobrist_table[0][1][6] = (((zobrist_int) 0xB94067EDFE175330ULL) + (((zobrist_int) 0x4BE03DB0DC2574BDULL) << 64));
    zobrist_table[0][1][7] = (((zobrist_int) 0xBE3EDC0A1EF2A4F0ULL) + (((zobrist_int) 0xE5446DD4552B82F6ULL) << 64));
    zobrist_table[0][1][8] = (((zobrist_int) 0xF9270F4EB8B333A8ULL) + (((zobrist_int) 0x803468B6B610A9F7ULL) << 64));
    zobrist_table[0][1][9] = (((zobrist_int) 0xF79B17AEEFBA91FCULL) + (((zobrist_int) 0x81F9C1F66C0F3459ULL) << 64));
    zobrist_table[0][1][10] = (((zobrist_int) 0xE901E35CD47D380DULL) + (((zobrist_int) 0x3099FDF5AB99254AULL) << 64));
    zobrist_table[0][1][11] = (((zobrist_int) 0x48BEAB134DA98F1DULL) + (((zobrist_int) 0xF9341C68966BAEA1ULL) << 64));
    zobrist_table[0][1][12] = (((zobrist_int) 0x7FD63116E1EA24C4ULL) + (((zobrist_int) 0xF0DFB4A5D8A064DFULL) << 64));
    zobrist_table[0][1][13] = (((zobrist_int) 0x64B2D2BC815A47C5ULL) + (((zobrist_int) 0xDA71144896C8DA19ULL) << 64));
    zobrist_table[0][2][0] = (((zobrist_int) 0x7AF027BC08D6AF57ULL) + (((zobrist_int) 0xBE6521CC3E2434E3ULL) << 64));
    zobrist_table[0][2][1] = (((zobrist_int) 0x677F6CBDCC22AF58ULL) + (((zobrist_int) 0xAA2CA1AF6A107B75ULL) << 64));
    zobrist_table[0][2][2] = (((zobrist_int) 0x5DFBD3D12C4A3698ULL) + (((zobrist_int) 0xE1FAB9D78C7E134FULL) << 64));
    zobrist_table[0][2][3] = (((zobrist_int) 0xC69D4BD8B3FA7AA7ULL) + (((zobrist_int) 0xBCFBB050ACAB1A6BULL) << 64));
    zobrist_table[0][2][4] = (((zobrist_int) 0x1622BD795FEC898FULL) + (((zobrist_int) 0xA9EC0806705FCA16ULL) << 64));
    zobrist_table[0][2][5] = (((zobrist_int) 0x1BA1621582283D15ULL) + (((zobrist_int) 0x29E821A4C74803E3ULL) << 64));
    zobrist_table[0][2][6] = (((zobrist_int) 0xD707107E855C3844ULL) + (((zobrist_int) 0x5EDA92D864AC5DB9ULL) << 64));
    zobrist_table[0][2][7] = (((zobrist_int) 0xBB968A437D5C8DFCULL) + (((zobrist_int) 0x78255D6807923986ULL) << 64));
    zobrist_table[0][2][8] = (((zobrist_int) 0x4EFBC8D60B21FBACULL) + (((zobrist_int) 0xD92A4AA2B410D93CULL) << 64));
    zobrist_table[0][2][9] = (((zobrist_int) 0x9D643C25FBB230BBULL) + (((zobrist_int) 0x9403560D97DAE38DULL) << 64));
    zobrist_table[0][2][10] = (((zobrist_int) 0xA5AC06D864C2F2E3ULL) + (((zobrist_int) 0x2B28FEF02B9C014EULL) << 64));
    zobrist_table[0][2][11] = (((zobrist_int) 0x3A1890C78092B4D4ULL) + (((zobrist_int) 0x326324DFB695FFBULL) << 64));
    zobrist_table[0][2][12] = (((zobrist_int) 0x33138131C541013DULL) + (((zobrist_int) 0xEB8AC8CE8A245E6BULL) << 64));
    zobrist_table[0][2][13] = (((zobrist_int) 0x8C5FE8F8DC3BF364ULL) + (((zobrist_int) 0x678A5AA33B6FE507ULL) << 64));
    zobrist_table[0][3][0] = (((zobrist_int) 0x5804F92283868A29ULL) + (((zobrist_int) 0xD8F33418F3D4E711ULL) << 64));
    zobrist_table[0][3][1] = (((zobrist_int) 0x5A702CFA93EA5C4EULL) + (((zobrist_int) 0xE8E5B4617589A82BULL) << 64));
    zobrist_table[0][3][2] = (((zobrist_int) 0xA8C24D4244EF7FEBULL) + (((zobrist_int) 0x9BE3CECB8C497C68ULL) << 64));
    zobrist_table[0][3][3] = (((zobrist_int) 0xBAB9F87FF5059285ULL) + (((zobrist_int) 0x62397BC701762741ULL) << 64));
    zobrist_table[0][3][4] = (((zobrist_int) 0xDB610487C89DA11BULL) + (((zobrist_int) 0xF463B337D20B5D59ULL) << 64));
    zobrist_table[0][3][5] = (((zobrist_int) 0xF03EDCA7E2DCAA37ULL) + (((zobrist_int) 0x83333218BD91A1B7ULL) << 64));
    zobrist_table[0][3][6] = (((zobrist_int) 0x21167D8FCF23CAE8ULL) + (((zobrist_int) 0xC703806984C81999ULL) << 64));
    zobrist_table[0][3][7] = (((zobrist_int) 0x349AAE908FB5262CULL) + (((zobrist_int) 0xF320CD576D14475BULL) << 64));
    zobrist_table[0][3][8] = (((zobrist_int) 0x7B297D0B0E5E18BAULL) + (((zobrist_int) 0x5D5F576CDEB8FC4CULL) << 64));
    zobrist_table[0][3][9] = (((zobrist_int) 0x8DED3C9691EB79FAULL) + (((zobrist_int) 0xF0E642F43328AD08ULL) << 64));
    zobrist_table[0][3][10] = (((zobrist_int) 0x69D495DD81355C53ULL) + (((zobrist_int) 0xD037CDFF7C240D49ULL) << 64));
    zobrist_table[0][3][11] = (((zobrist_int) 0x6A17B9AF5B569643ULL) + (((zobrist_int) 0x67DBA858989008ULL) << 64));
    zobrist_table[0][3][12] = (((zobrist_int) 0x8A449EBE89D9BF02ULL) + (((zobrist_int) 0xC9546B439F9D0129ULL) << 64));
    zobrist_table[0][3][13] = (((zobrist_int) 0x54C56C9A9CC9AF4EULL) + (((zobrist_int) 0x99901C0475491BC3ULL) << 64));
    zobrist_table[0][4][0] = (((zobrist_int) 0xCDF8440407295E42ULL) + (((zobrist_int) 0xA2A7AE1F3AC7652CULL) << 64));
    zobrist_table[0][4][1] = (((zobrist_int) 0x8CFE5CD12D5DB79BULL) + (((zobrist_int) 0x2E47DC0E959F3A51ULL) << 64));
    zobrist_table[0][4][2] = (((zobrist_int) 0x1773308CDC6B13ABULL) + (((zobrist_int) 0x8D103ED3CC667E97ULL) << 64));
    zobrist_table[0][4][3] = (((zobrist_int) 0xD9ED17E3CC0E95EEULL) + (((zobrist_int) 0xEE52BDB6D1020A15ULL) << 64));
    zobrist_table[0][4][4] = (((zobrist_int) 0x84F3DD6415AF341ULL) + (((zobrist_int) 0xF18DD1EED77C96C0ULL) << 64));
    zobrist_table[0][4][5] = (((zobrist_int) 0x12093D26AC512B01ULL) + (((zobrist_int) 0xDE3A5DB5154ED512ULL) << 64));
    zobrist_table[0][4][6] = (((zobrist_int) 0x73F7BA8E0445D656ULL) + (((zobrist_int) 0xC10FAA4003BA33DBULL) << 64));
    zobrist_table[0][4][7] = (((zobrist_int) 0x47FC816AC16E2284ULL) + (((zobrist_int) 0x44C5B4763FE31D03ULL) << 64));
    zobrist_table[0][4][8] = (((zobrist_int) 0xCC1B0C3E1C07724EULL) + (((zobrist_int) 0x2F429CE59FF3078FULL) << 64));
    zobrist_table[0][4][9] = (((zobrist_int) 0x4A5012DC582C18C9ULL) + (((zobrist_int) 0x2ADF559A11CBC288ULL) << 64));
    zobrist_table[0][4][10] = (((zobrist_int) 0x4155D7EF28DD37EBULL) + (((zobrist_int) 0xF3B37F32870266C4ULL) << 64));
    zobrist_table[0][4][11] = (((zobrist_int) 0xA81AA40A2B0B8C12ULL) + (((zobrist_int) 0xA5F09E6345DDB87DULL) << 64));
    zobrist_table[0][4][12] = (((zobrist_int) 0x4B63E0EFB62AC1FEULL) + (((zobrist_int) 0xB3DF44A47467537AULL) << 64));
    zobrist_table[0][4][13] = (((zobrist_int) 0x7F1A355E526EB523ULL) + (((zobrist_int) 0x1D3B993F79490EABULL) << 64));
    zobrist_table[0][5][0] = (((zobrist_int) 0x4FDF8E1A060CEA63ULL) + (((zobrist_int) 0x57E54ACC62F5680CULL) << 64));
    zobrist_table[0][5][1] = (((zobrist_int) 0xCBD3F5E06BC15385ULL) + (((zobrist_int) 0x4227DE213023580CULL) << 64));
    zobrist_table[0][5][2] = (((zobrist_int) 0x40E2A20A1BD7CE73ULL) + (((zobrist_int) 0xBAEB41A5E65A8149ULL) << 64));
    zobrist_table[0][5][3] = (((zobrist_int) 0xFA0B85188296F5EAULL) + (((zobrist_int) 0xF72F2BB83586FCA7ULL) << 64));
    zobrist_table[0][5][4] = (((zobrist_int) 0x6E80FA489B0BCA16ULL) + (((zobrist_int) 0xF9BDDEA5D12982E4ULL) << 64));
    zobrist_table[0][5][5] = (((zobrist_int) 0x39B21C95055455E8ULL) + (((zobrist_int) 0x65B675CD0492C4F5ULL) << 64));
    zobrist_table[0][5][6] = (((zobrist_int) 0x90B20BB257E8454ULL) + (((zobrist_int) 0xF5BB9188B80599E9ULL) << 64));
    zobrist_table[0][5][7] = (((zobrist_int) 0x721754EF2904ACECULL) + (((zobrist_int) 0x819D7CA7B46108CCULL) << 64));
    zobrist_table[0][5][8] = (((zobrist_int) 0x6D39EB43AD9CEDDEULL) + (((zobrist_int) 0xD50E00978B7199CDULL) << 64));
    zobrist_table[0][5][9] = (((zobrist_int) 0xFA1B1BF13879399BULL) + (((zobrist_int) 0xA17A4340F9C08FEFULL) << 64));
    zobrist_table[0][5][10] = (((zobrist_int) 0xB1EEDAFFCC3D5506ULL) + (((zobrist_int) 0x736A947A843FDDA7ULL) << 64));
    zobrist_table[0][5][11] = (((zobrist_int) 0x861E02EC39235BC0ULL) + (((zobrist_int) 0x7DBF924A6048457ULL) << 64));
    zobrist_table[0][5][12] = (((zobrist_int) 0xACC66A576518093DULL) + (((zobrist_int) 0xCDAAAC43936AA40CULL) << 64));
    zobrist_table[0][5][13] = (((zobrist_int) 0xA8EA37F7523D2A54ULL) + (((zobrist_int) 0x6D21F4CDA185CC8EULL) << 64));
    zobrist_table[0][6][0] = (((zobrist_int) 0xBCC99AE80F0C8A89ULL) + (((zobrist_int) 0x202CC8284C717095ULL) << 64));
    zobrist_table[0][6][1] = (((zobrist_int) 0x364E433FF7C882F4ULL) + (((zobrist_int) 0xC250A03E023033DULL) << 64));
    zobrist_table[0][6][2] = (((zobrist_int) 0x121B28004E6F5A94ULL) + (((zobrist_int) 0x1391F9B9DBC799B0ULL) << 64));
    zobrist_table[0][6][3] = (((zobrist_int) 0xEACC110E4F73FD94ULL) + (((zobrist_int) 0x4C41D9C0F07534FEULL) << 64));
    zobrist_table[0][6][4] = (((zobrist_int) 0x28804790BE6C6FE9ULL) + (((zobrist_int) 0x909FF4976A8A43EFULL) << 64));
    zobrist_table[0][6][5] = (((zobrist_int) 0x21615022409A8A78ULL) + (((zobrist_int) 0x8F8B2B83022BC320ULL) << 64));
    zobrist_table[0][6][6] = (((zobrist_int) 0xD9BC1D97E0F3A7EFULL) + (((zobrist_int) 0x973082D609B4E5D2ULL) << 64));
    zobrist_table[0][6][7] = (((zobrist_int) 0x37B4000BD1C51F86ULL) + (((zobrist_int) 0xE69BAE29F652D008ULL) << 64));
    zobrist_table[0][6][8] = (((zobrist_int) 0x75FA6DD891FDE85CULL) + (((zobrist_int) 0xD3F21DCC2BE88B46ULL) << 64));
    zobrist_table[0][6][9] = (((zobrist_int) 0xDEB0E066DE26E655ULL) + (((zobrist_int) 0xC7AF3626F9495568ULL) << 64));
    zobrist_table[0][6][10] = (((zobrist_int) 0x9F7A7DAFB43ADC4FULL) + (((zobrist_int) 0x994940E82458CC8ULL) << 64));
    zobrist_table[0][6][11] = (((zobrist_int) 0x334DE73D60C290D0ULL) + (((zobrist_int) 0x1959B9EF58D07674ULL) << 64));
    zobrist_table[0][6][12] = (((zobrist_int) 0x92C9357D34ACCD78ULL) + (((zobrist_int) 0xE585552FAC954AB5ULL) << 64));
    zobrist_table[0][6][13] = (((zobrist_int) 0x976699CC6ED5D1BFULL) + (((zobrist_int) 0x7E0AB2ED31B1C27EULL) << 64));
    zobrist_table[0][7][0] = (((zobrist_int) 0xF01DBF291ABB8BA3ULL) + (((zobrist_int) 0x63DB01FCAA7C314BULL) << 64));
    zobrist_table[0][7][1] = (((zobrist_int) 0x810D2E304BCB6B22ULL) + (((zobrist_int) 0x4673B757FF2E341ULL) << 64));
    zobrist_table[0][7][2] = (((zobrist_int) 0x9CB471A55349DA48ULL) + (((zobrist_int) 0x66FEC086DF229650ULL) << 64));
    zobrist_table[0][7][3] = (((zobrist_int) 0x4806AA81E65150B5ULL) + (((zobrist_int) 0x282EE0BC04A1BDE4ULL) << 64));
    zobrist_table[0][7][4] = (((zobrist_int) 0xDB87872D336B1A45ULL) + (((zobrist_int) 0xCFA6CF3E53E6D093ULL) << 64));
    zobrist_table[0][7][5] = (((zobrist_int) 0x903715C8FCAF4A5AULL) + (((zobrist_int) 0x2298BDB1C85F0D46ULL) << 64));
    zobrist_table[0][7][6] = (((zobrist_int) 0x6DE2B33B56CEF8ECULL) + (((zobrist_int) 0x443BAAC536891EEBULL) << 64));
    zobrist_table[0][7][7] = (((zobrist_int) 0x18AE013EACA91679ULL) + (((zobrist_int) 0x611575C2D67393D6ULL) << 64));
    zobrist_table[0][7][8] = (((zobrist_int) 0x8C31406DEEA3D685ULL) + (((zobrist_int) 0xEA190B2A58068A9DULL) << 64));
    zobrist_table[0][7][9] = (((zobrist_int) 0xD6730839E1E48557ULL) + (((zobrist_int) 0x88C9DA8AAFE673F6ULL) << 64));
    zobrist_table[0][7][10] = (((zobrist_int) 0xC49872C67C081BB7ULL) + (((zobrist_int) 0x88534206FC4A447EULL) << 64));
    zobrist_table[0][7][11] = (((zobrist_int) 0x10B8FE223C116549ULL) + (((zobrist_int) 0xA57AF35B9B81635ULL) << 64));
    zobrist_table[0][7][12] = (((zobrist_int) 0x220D672B15AD9A9DULL) + (((zobrist_int) 0x2AA3300B2B711343ULL) << 64));
    zobrist_table[0][7][13] = (((zobrist_int) 0x89C80C4DE9367ED9ULL) + (((zobrist_int) 0x449C4CA23685156BULL) << 64));
    zobrist_table[1][0][0] = (((zobrist_int) 0x550D40DDC2557035ULL) + (((zobrist_int) 0x8181E84D99A74924ULL) << 64));
    zobrist_table[1][0][1] = (((zobrist_int) 0x415AC400D7547080ULL) + (((zobrist_int) 0x56BEFA395E3C536CULL) << 64));
    zobrist_table[1][0][2] = (((zobrist_int) 0x1D296588571CEEEEULL) + (((zobrist_int) 0x3C35612E4A8D15D8ULL) << 64));
    zobrist_table[1][0][3] = (((zobrist_int) 0xF1A9A658DE0F39A7ULL) + (((zobrist_int) 0xC78FEC459A9E994CULL) << 64));
    zobrist_table[1][0][4] = (((zobrist_int) 0xB7115C02F44D7E40ULL) + (((zobrist_int) 0x7D2186D3E323CE54ULL) << 64));
    zobrist_table[1][0][5] = (((zobrist_int) 0x947810D822A608BFULL) + (((zobrist_int) 0xC52F4FBE8D19821FULL) << 64));
    zobrist_table[1][0][6] = (((zobrist_int) 0x521B18A91AB1C42FULL) + (((zobrist_int) 0x6816DE060A04EF48ULL) << 64));
    zobrist_table[1][0][7] = (((zobrist_int) 0x6156C4DF12BCCDCBULL) + (((zobrist_int) 0xFDC1786BDDBD358FULL) << 64));
    zobrist_table[1][0][8] = (((zobrist_int) 0x25B7501AC9C1FFEFULL) + (((zobrist_int) 0x20012170D418F7AFULL) << 64));
    zobrist_table[1][0][9] = (((zobrist_int) 0x1D5C482557450E65ULL) + (((zobrist_int) 0x96605D959D7CD4F6ULL) << 64));
    zobrist_table[1][0][10] = (((zobrist_int) 0xED192DA3C82AD589ULL) + (((zobrist_int) 0x139F711060C73494ULL) << 64));
    zobrist_table[1][0][11] = (((zobrist_int) 0x8CDECE75921EBCE6ULL) + (((zobrist_int) 0x90E32E8239455353ULL) << 64));
    zobrist_table[1][0][12] = (((zobrist_int) 0xF3C668B114ED2049ULL) + (((zobrist_int) 0x5D698C8B44480030ULL) << 64));
    zobrist_table[1][0][13] = (((zobrist_int) 0x4BA955F3E4096150ULL) + (((zobrist_int) 0x88C780F6907F9669ULL) << 64));
    zobrist_table[1][1][0] = (((zobrist_int) 0x1D43D1FFECD1345EULL) + (((zobrist_int) 0xE592067375305DB7ULL) << 64));
    zobrist_table[1][1][1] = (((zobrist_int) 0x1B943CFC46F57327ULL) + (((zobrist_int) 0xBB662A8C979CB06ULL) << 64));
    zobrist_table[1][1][2] = (((zobrist_int) 0x4BB57B5CD3E89D32ULL) + (((zobrist_int) 0x9D19EE45032B7328ULL) << 64));
    zobrist_table[1][1][3] = (((zobrist_int) 0x3B96D91ABA018EAULL) + (((zobrist_int) 0x69DD649317788B95ULL) << 64));
    zobrist_table[1][1][4] = (((zobrist_int) 0xD37C99611D775B7CULL) + (((zobrist_int) 0xCA357568E2934BF1ULL) << 64));
    zobrist_table[1][1][5] = (((zobrist_int) 0x301BA9880A3EFB80ULL) + (((zobrist_int) 0xC91752A33D589CABULL) << 64));
    zobrist_table[1][1][6] = (((zobrist_int) 0x96380ED6FCF7F49DULL) + (((zobrist_int) 0x297A21D76BC78BF5ULL) << 64));
    zobrist_table[1][1][7] = (((zobrist_int) 0x736EBF511D95389BULL) + (((zobrist_int) 0xAE4ECF4B2AD9A40AULL) << 64));
    zobrist_table[1][1][8] = (((zobrist_int) 0x28B09A933DCDB856ULL) + (((zobrist_int) 0xD85328B6BE773448ULL) << 64));
    zobrist_table[1][1][9] = (((zobrist_int) 0x6F62E63A1A5356B5ULL) + (((zobrist_int) 0xF6F62C28E927DB48ULL) << 64));
    zobrist_table[1][1][10] = (((zobrist_int) 0xCE75F4BA60D6C766ULL) + (((zobrist_int) 0x8AFD2973F8633958ULL) << 64));
    zobrist_table[1][1][11] = (((zobrist_int) 0xD17F6494E8C2D219ULL) + (((zobrist_int) 0x8CDA80A34B452123ULL) << 64));
    zobrist_table[1][1][12] = (((zobrist_int) 0xB62C228E40DF7C9AULL) + (((zobrist_int) 0x50806F017A1D556CULL) << 64));
    zobrist_table[1][1][13] = (((zobrist_int) 0x35263B4519A2105CULL) + (((zobrist_int) 0x51423286A6ECC31FULL) << 64));
    zobrist_table[1][2][0] = (((zobrist_int) 0x6FAADB10A248CFFULL) + (((zobrist_int) 0xC96FA75802B087F8ULL) << 64));
    zobrist_table[1][2][1] = (((zobrist_int) 0xECF45CCBFB8A99A2ULL) + (((zobrist_int) 0xB9FAD67E4BA927C3ULL) << 64));
    zobrist_table[1][2][2] = (((zobrist_int) 0x51FBFCC798B8DA9FULL) + (((zobrist_int) 0x642A357C732902F4ULL) << 64));
    zobrist_table[1][2][3] = (((zobrist_int) 0x6607B61550332CB8ULL) + (((zobrist_int) 0x106EE2AB101E75EBULL) << 64));
    zobrist_table[1][2][4] = (((zobrist_int) 0x513DD1A6E9D40F2BULL) + (((zobrist_int) 0x99F86C8DF845AED9ULL) << 64));
    zobrist_table[1][2][5] = (((zobrist_int) 0x74B31BFBF8449560ULL) + (((zobrist_int) 0x40041E001C823D9EULL) << 64));
    zobrist_table[1][2][6] = (((zobrist_int) 0xC8FEA5D73716E7EAULL) + (((zobrist_int) 0xC725BD979E289761ULL) << 64));
    zobrist_table[1][2][7] = (((zobrist_int) 0xE4264C9FFADE312DULL) + (((zobrist_int) 0xDE1BF0CD8AFC5BEEULL) << 64));
    zobrist_table[1][2][8] = (((zobrist_int) 0x780B25D9B02D3504ULL) + (((zobrist_int) 0x5B177A38A96DFB2CULL) << 64));
    zobrist_table[1][2][9] = (((zobrist_int) 0x2EE7AF97425375BEULL) + (((zobrist_int) 0x3534CCAE8AA67235ULL) << 64));
    zobrist_table[1][2][10] = (((zobrist_int) 0x32FFD03D4EAC98D6ULL) + (((zobrist_int) 0x5C47577B3F12D68EULL) << 64));
    zobrist_table[1][2][11] = (((zobrist_int) 0xD1EA041814D4954EULL) + (((zobrist_int) 0x16E3E38047E1A38BULL) << 64));
    zobrist_table[1][2][12] = (((zobrist_int) 0xC0D76560FBBE9381ULL) + (((zobrist_int) 0x172A401272A9B8A4ULL) << 64));
    zobrist_table[1][2][13] = (((zobrist_int) 0x93090287A6EA2981ULL) + (((zobrist_int) 0x56C11669A4BA3161ULL) << 64));
    zobrist_table[1][3][0] = (((zobrist_int) 0x3A389B09F0D3FA5CULL) + (((zobrist_int) 0xF772F8EA63F666E0ULL) << 64));
    zobrist_table[1][3][1] = (((zobrist_int) 0xA8266954E896A65ULL) + (((zobrist_int) 0x2FD2F79253C617EBULL) << 64));
    zobrist_table[1][3][2] = (((zobrist_int) 0xCAF078B051158DE5ULL) + (((zobrist_int) 0x9439C746D8DDD2EFULL) << 64));
    zobrist_table[1][3][3] = (((zobrist_int) 0xEBDDB098E4BC6E82ULL) + (((zobrist_int) 0x3EEFE7344D84E990ULL) << 64));
    zobrist_table[1][3][4] = (((zobrist_int) 0x19D7B4035596DFDEULL) + (((zobrist_int) 0x9C842B6A8B525B4FULL) << 64));
    zobrist_table[1][3][5] = (((zobrist_int) 0xCEBCC1BA943863A5ULL) + (((zobrist_int) 0x179030DA98910052ULL) << 64));
    zobrist_table[1][3][6] = (((zobrist_int) 0x385C1B333EBEBE3EULL) + (((zobrist_int) 0xCEEA590B05373B76ULL) << 64));
    zobrist_table[1][3][7] = (((zobrist_int) 0x66DAA3653E67026CULL) + (((zobrist_int) 0x449FD49B12840EA1ULL) << 64));
    zobrist_table[1][3][8] = (((zobrist_int) 0xDE1827478D1BC13AULL) + (((zobrist_int) 0xBAAAD6511227932FULL) << 64));
    zobrist_table[1][3][9] = (((zobrist_int) 0x581F255133BB4C2ULL) + (((zobrist_int) 0x289EB06A2A866B4ULL) << 64));
    zobrist_table[1][3][10] = (((zobrist_int) 0xC02FC22A4A7347FAULL) + (((zobrist_int) 0x5BF3F74DCACC9EC8ULL) << 64));
    zobrist_table[1][3][11] = (((zobrist_int) 0x780587F07E465B19ULL) + (((zobrist_int) 0xDBEEF77ADCD69029ULL) << 64));
    zobrist_table[1][3][12] = (((zobrist_int) 0x19D6D73B2778507CULL) + (((zobrist_int) 0xC71A5B11805DB06AULL) << 64));
    zobrist_table[1][3][13] = (((zobrist_int) 0x53FDF07CCB8409D6ULL) + (((zobrist_int) 0x825F854213BD488EULL) << 64));
    zobrist_table[1][4][0] = (((zobrist_int) 0xAA4DA822F3009A5CULL) + (((zobrist_int) 0x2DF810B92C599859ULL) << 64));
    zobrist_table[1][4][1] = (((zobrist_int) 0x2649C1B0C6B5A1C6ULL) + (((zobrist_int) 0x243BD888FC2222D2ULL) << 64));
    zobrist_table[1][4][2] = (((zobrist_int) 0xDD946658D2511C38ULL) + (((zobrist_int) 0x4E3D4D0F51DD5D5CULL) << 64));
    zobrist_table[1][4][3] = (((zobrist_int) 0xB59641D21B5C56D3ULL) + (((zobrist_int) 0xD5AE305B83ACFB7EULL) << 64));
    zobrist_table[1][4][4] = (((zobrist_int) 0x9A15A311EB5AF9F9ULL) + (((zobrist_int) 0x20552F5F4B2220A4ULL) << 64));
    zobrist_table[1][4][5] = (((zobrist_int) 0x34ECF2EDE4CD6075ULL) + (((zobrist_int) 0x8BA56D3424452ECFULL) << 64));
    zobrist_table[1][4][6] = (((zobrist_int) 0xB8FE2F4BE91553A9ULL) + (((zobrist_int) 0xC79D444008216B65ULL) << 64));
    zobrist_table[1][4][7] = (((zobrist_int) 0xD22F02F350E9E079ULL) + (((zobrist_int) 0x9F9F80D0E730CB28ULL) << 64));
    zobrist_table[1][4][8] = (((zobrist_int) 0xAC153076CDC98666ULL) + (((zobrist_int) 0x8D8E3B13E83B3AB1ULL) << 64));
    zobrist_table[1][4][9] = (((zobrist_int) 0xF1878D5FD739543BULL) + (((zobrist_int) 0xFCA7CB5FBF05F8FAULL) << 64));
    zobrist_table[1][4][10] = (((zobrist_int) 0x3497553CB0894F5AULL) + (((zobrist_int) 0x4C8670622D9B8EBFULL) << 64));
    zobrist_table[1][4][11] = (((zobrist_int) 0x899918A76EC15D38ULL) + (((zobrist_int) 0xC6E5973286BEF29ULL) << 64));
    zobrist_table[1][4][12] = (((zobrist_int) 0xDCB284F8B6FEBC3AULL) + (((zobrist_int) 0x3F4ED95AAAF38C2FULL) << 64));
    zobrist_table[1][4][13] = (((zobrist_int) 0xC71C5CF140A980BDULL) + (((zobrist_int) 0xAE9C8563107D72D5ULL) << 64));
    zobrist_table[1][5][0] = (((zobrist_int) 0x725A9A5BF6A07500ULL) + (((zobrist_int) 0x6E1FB6ADCEE9A4FDULL) << 64));
    zobrist_table[1][5][1] = (((zobrist_int) 0x400E67ED8C9CF440ULL) + (((zobrist_int) 0x707C70B48A97B9D8ULL) << 64));
    zobrist_table[1][5][2] = (((zobrist_int) 0x89BE4B4BD9EE50E2ULL) + (((zobrist_int) 0x2C8261B740C1A65ULL) << 64));
    zobrist_table[1][5][3] = (((zobrist_int) 0xD6172ADF654D479AULL) + (((zobrist_int) 0x2BE893F456B30574ULL) << 64));
    zobrist_table[1][5][4] = (((zobrist_int) 0x7C5C483D420A4323ULL) + (((zobrist_int) 0xCB06718C063FA2B6ULL) << 64));
    zobrist_table[1][5][5] = (((zobrist_int) 0xEEC1754CA57D041EULL) + (((zobrist_int) 0xF9EF954E6AABCB78ULL) << 64));
    zobrist_table[1][5][6] = (((zobrist_int) 0x4D759889213147BULL) + (((zobrist_int) 0xB11379A20FF44F65ULL) << 64));
    zobrist_table[1][5][7] = (((zobrist_int) 0x947F81435ADD92D1ULL) + (((zobrist_int) 0x97F2A70223669676ULL) << 64));
    zobrist_table[1][5][8] = (((zobrist_int) 0x237475E120087497ULL) + (((zobrist_int) 0xFBB41D1442553A33ULL) << 64));
    zobrist_table[1][5][9] = (((zobrist_int) 0x46E3DB95D4350B28ULL) + (((zobrist_int) 0x906704C365D60B6EULL) << 64));
    zobrist_table[1][5][10] = (((zobrist_int) 0x2C139C1966AD51FDULL) + (((zobrist_int) 0x16D8E80E9CC930D3ULL) << 64));
    zobrist_table[1][5][11] = (((zobrist_int) 0x7C6A47A73BC8996BULL) + (((zobrist_int) 0x2D75C25D01EA0639ULL) << 64));
    zobrist_table[1][5][12] = (((zobrist_int) 0x5136BF628758FF4DULL) + (((zobrist_int) 0xE49DF6BB803AF506ULL) << 64));
    zobrist_table[1][5][13] = (((zobrist_int) 0xEBA1A9D3A61A59E3ULL) + (((zobrist_int) 0xEE1B8CC470358A27ULL) << 64));
    zobrist_table[1][6][0] = (((zobrist_int) 0xA39CC4B2AFBF5310ULL) + (((zobrist_int) 0x39C97AB1BB3E780FULL) << 64));
    zobrist_table[1][6][1] = (((zobrist_int) 0x501FC6F43D061F79ULL) + (((zobrist_int) 0xAFDBE9D27EBD0E05ULL) << 64));
    zobrist_table[1][6][2] = (((zobrist_int) 0xF4DFC9A57A946602ULL) + (((zobrist_int) 0xB67D153D399DAB3CULL) << 64));
    zobrist_table[1][6][3] = (((zobrist_int) 0x564274036988F668ULL) + (((zobrist_int) 0x9C7D498A8F76DC87ULL) << 64));
    zobrist_table[1][6][4] = (((zobrist_int) 0xBA6CAC4AE82D2FEFULL) + (((zobrist_int) 0xA745BA6DEAEED19BULL) << 64));
    zobrist_table[1][6][5] = (((zobrist_int) 0xF8EC2D3446752B5CULL) + (((zobrist_int) 0x382F21E4A57B7700ULL) << 64));
    zobrist_table[1][6][6] = (((zobrist_int) 0xEBEE35210C56A92DULL) + (((zobrist_int) 0xC360B3B71251310BULL) << 64));
    zobrist_table[1][6][7] = (((zobrist_int) 0xA5319F4782FE3A4AULL) + (((zobrist_int) 0x5E6279DBE09EDD5AULL) << 64));
    zobrist_table[1][6][8] = (((zobrist_int) 0x82FA4D7A28D2E08EULL) + (((zobrist_int) 0xCADFF918C41A66D9ULL) << 64));
    zobrist_table[1][6][9] = (((zobrist_int) 0x342F22BAE20CEA4AULL) + (((zobrist_int) 0x4C78C7AB4FD24206ULL) << 64));
    zobrist_table[1][6][10] = (((zobrist_int) 0x4CB05EC1B14B69DCULL) + (((zobrist_int) 0x8D64B3ADD9577B6BULL) << 64));
    zobrist_table[1][6][11] = (((zobrist_int) 0x2A4926F05F221DFCULL) + (((zobrist_int) 0xB386D25CB38742ADULL) << 64));
    zobrist_table[1][6][12] = (((zobrist_int) 0x76FBB6EDBC85E5DEULL) + (((zobrist_int) 0x15C0CDD59836404CULL) << 64));
    zobrist_table[1][6][13] = (((zobrist_int) 0x1F8CE97ADB34FA8DULL) + (((zobrist_int) 0x9B29B54BE587DD21ULL) << 64));
    zobrist_table[1][7][0] = (((zobrist_int) 0x83924F05F5C7B9AAULL) + (((zobrist_int) 0x60900772923C4E5DULL) << 64));
    zobrist_table[1][7][1] = (((zobrist_int) 0x27E125A42D206ADAULL) + (((zobrist_int) 0x6D3FAD4C40270546ULL) << 64));
    zobrist_table[1][7][2] = (((zobrist_int) 0xF112CFD037B5DBACULL) + (((zobrist_int) 0xB8378D8291CBE386ULL) << 64));
    zobrist_table[1][7][3] = (((zobrist_int) 0xC842C19AC1FBE94CULL) + (((zobrist_int) 0x7EBA03520D589A58ULL) << 64));
    zobrist_table[1][7][4] = (((zobrist_int) 0x64C371CFAE7FBA11ULL) + (((zobrist_int) 0xA310A849B7975B28ULL) << 64));
    zobrist_table[1][7][5] = (((zobrist_int) 0x624C4B62591550FFULL) + (((zobrist_int) 0xD87064FC83DAB265ULL) << 64));
    zobrist_table[1][7][6] = (((zobrist_int) 0x8B5230ED2A30363BULL) + (((zobrist_int) 0xFE8B2B79BADA7947ULL) << 64));
    zobrist_table[1][7][7] = (((zobrist_int) 0x863043D70A6BE26CULL) + (((zobrist_int) 0x1724925FFB314DA0ULL) << 64));
    zobrist_table[1][7][8] = (((zobrist_int) 0x4153BBC7CED5669FULL) + (((zobrist_int) 0x19DE2DEDA0E20045ULL) << 64));
    zobrist_table[1][7][9] = (((zobrist_int) 0xBCA5F87B447C999DULL) + (((zobrist_int) 0x156EAB79E9B161F4ULL) << 64));
    zobrist_table[1][7][10] = (((zobrist_int) 0xF98DDC84F59DC887ULL) + (((zobrist_int) 0xF81F5C80239DC599ULL) << 64));
    zobrist_table[1][7][11] = (((zobrist_int) 0x9DED54FDC69806EAULL) + (((zobrist_int) 0xF78047CFD788C7CCULL) << 64));
    zobrist_table[1][7][12] = (((zobrist_int) 0xAFC6EE6FA8E33C94ULL) + (((zobrist_int) 0x14FE7EBCB34DEC74ULL) << 64));
    zobrist_table[1][7][13] = (((zobrist_int) 0xD9D9320E71EF5E7AULL) + (((zobrist_int) 0x3DB18A28EC9F6FBFULL) << 64));
    zobrist_table[2][0][0] = (((zobrist_int) 0xD9DB30AFF8A10E70ULL) + (((zobrist_int) 0xF0A3A66861E1E80DULL) << 64));
    zobrist_table[2][0][1] = (((zobrist_int) 0xE746EBEBCD7E80A2ULL) + (((zobrist_int) 0x65B184F76ED3F30BULL) << 64));
    zobrist_table[2][0][2] = (((zobrist_int) 0xE8FB46B52A2D551FULL) + (((zobrist_int) 0x702938155351D2C1ULL) << 64));
    zobrist_table[2][0][3] = (((zobrist_int) 0x9F55C5FC20572AEBULL) + (((zobrist_int) 0x7CEB5FB4E8ACABFFULL) << 64));
    zobrist_table[2][0][4] = (((zobrist_int) 0x36469FABF59CD100ULL) + (((zobrist_int) 0x6E6716981E830596ULL) << 64));
    zobrist_table[2][0][5] = (((zobrist_int) 0x88B7CC6B99C61AA8ULL) + (((zobrist_int) 0xE8C7A01D68815FDAULL) << 64));
    zobrist_table[2][0][6] = (((zobrist_int) 0xA9172A051E3B25E5ULL) + (((zobrist_int) 0x47158A7E4BA44898ULL) << 64));
    zobrist_table[2][0][7] = (((zobrist_int) 0x60FC47FA3F8B1BAAULL) + (((zobrist_int) 0x8F332483BFE4440EULL) << 64));
    zobrist_table[2][0][8] = (((zobrist_int) 0xF5B5B9340106BB05ULL) + (((zobrist_int) 0x8742CED2309944E2ULL) << 64));
    zobrist_table[2][0][9] = (((zobrist_int) 0x943EC25A70536E9BULL) + (((zobrist_int) 0x7E30F1105628748ULL) << 64));
    zobrist_table[2][0][10] = (((zobrist_int) 0xF91C85FDA0A59518ULL) + (((zobrist_int) 0x3E0363339B0A6817ULL) << 64));
    zobrist_table[2][0][11] = (((zobrist_int) 0x42A95D35D5D8575DULL) + (((zobrist_int) 0x2C400B9534E41E75ULL) << 64));
    zobrist_table[2][0][12] = (((zobrist_int) 0x25FE3A1848E772BAULL) + (((zobrist_int) 0x335082DC8AD6C1C4ULL) << 64));
    zobrist_table[2][0][13] = (((zobrist_int) 0x4FA6961145F21E94ULL) + (((zobrist_int) 0xC1E6415A95F2EE55ULL) << 64));
    zobrist_table[2][1][0] = (((zobrist_int) 0xD51536644039D142ULL) + (((zobrist_int) 0x72470ADDAEFBA2AEULL) << 64));
    zobrist_table[2][1][1] = (((zobrist_int) 0xDC7A4BEECA84EBCAULL) + (((zobrist_int) 0xDAE720B2CF03FD21ULL) << 64));
    zobrist_table[2][1][2] = (((zobrist_int) 0x2B00B570F93EE7CCULL) + (((zobrist_int) 0x5B616E428B9DD3D4ULL) << 64));
    zobrist_table[2][1][3] = (((zobrist_int) 0x6B82ED5C7DA5AD52ULL) + (((zobrist_int) 0x1F2E490CDB0F0126ULL) << 64));
    zobrist_table[2][1][4] = (((zobrist_int) 0x357D6F2EC4E199A1ULL) + (((zobrist_int) 0xE1018CC5920F3663ULL) << 64));
    zobrist_table[2][1][5] = (((zobrist_int) 0x346F3293621D1733ULL) + (((zobrist_int) 0xCF80F75148B75541ULL) << 64));
    zobrist_table[2][1][6] = (((zobrist_int) 0xE76DB5EF1BAF02CFULL) + (((zobrist_int) 0x62EBC92CEBB898AULL) << 64));
    zobrist_table[2][1][7] = (((zobrist_int) 0x91BE34EB1E39EF8EULL) + (((zobrist_int) 0x3621F97BF4CC645ULL) << 64));
    zobrist_table[2][1][8] = (((zobrist_int) 0x4BE1B2488B97EF45ULL) + (((zobrist_int) 0xAC859F8FF706A832ULL) << 64));
    zobrist_table[2][1][9] = (((zobrist_int) 0xB96CC27AC2D532FAULL) + (((zobrist_int) 0xA63E0C32F93897B0ULL) << 64));
    zobrist_table[2][1][10] = (((zobrist_int) 0x133F3B0A22F7D343ULL) + (((zobrist_int) 0x5FAC971A80185844ULL) << 64));
    zobrist_table[2][1][11] = (((zobrist_int) 0xCE33DD7092947D94ULL) + (((zobrist_int) 0x6FEA51CA4FAE2CF5ULL) << 64));
    zobrist_table[2][1][12] = (((zobrist_int) 0xAD611A3E80C6BCBDULL) + (((zobrist_int) 0xC234472F5B58796AULL) << 64));
    zobrist_table[2][1][13] = (((zobrist_int) 0x52DD34D68744D3C0ULL) + (((zobrist_int) 0x1FB7F62800375C0DULL) << 64));
    zobrist_table[2][2][0] = (((zobrist_int) 0xB7CCBA58713B831BULL) + (((zobrist_int) 0x59A78B137315D969ULL) << 64));
    zobrist_table[2][2][1] = (((zobrist_int) 0x8A0F42834E0751D7ULL) + (((zobrist_int) 0x56E0A246663F423BULL) << 64));
    zobrist_table[2][2][2] = (((zobrist_int) 0xBB2B92C3C87868FAULL) + (((zobrist_int) 0x92484194AEF4259CULL) << 64));
    zobrist_table[2][2][3] = (((zobrist_int) 0x1CF3D1797E0750EAULL) + (((zobrist_int) 0xEAF5C033A5CD95E7ULL) << 64));
    zobrist_table[2][2][4] = (((zobrist_int) 0x61E406A660A7A7B7ULL) + (((zobrist_int) 0x8E903FD93433B60CULL) << 64));
    zobrist_table[2][2][5] = (((zobrist_int) 0xFEAD3BED00FDFEAEULL) + (((zobrist_int) 0xA2B249AB47122FAAULL) << 64));
    zobrist_table[2][2][6] = (((zobrist_int) 0xB8E7DF9B992149E8ULL) + (((zobrist_int) 0xBD1296CDE1B4A960ULL) << 64));
    zobrist_table[2][2][7] = (((zobrist_int) 0xBA7725A3D454F36DULL) + (((zobrist_int) 0x32E9C06982CE49DEULL) << 64));
    zobrist_table[2][2][8] = (((zobrist_int) 0xEC5DF2C7FCAD3888ULL) + (((zobrist_int) 0x99D026A7762A2BA5ULL) << 64));
    zobrist_table[2][2][9] = (((zobrist_int) 0x84546026D5A7EB2EULL) + (((zobrist_int) 0xEFFE76E068B1F3C9ULL) << 64));
    zobrist_table[2][2][10] = (((zobrist_int) 0xB64E172FBEA01CA0ULL) + (((zobrist_int) 0xFCD26DADFCD2CF1EULL) << 64));
    zobrist_table[2][2][11] = (((zobrist_int) 0xB3F0B94C4E2A89F5ULL) + (((zobrist_int) 0x730B19EC2B999F07ULL) << 64));
    zobrist_table[2][2][12] = (((zobrist_int) 0xAB3920349EBA8775ULL) + (((zobrist_int) 0x3286423887ECBE86ULL) << 64));
    zobrist_table[2][2][13] = (((zobrist_int) 0x86B46F015C03151CULL) + (((zobrist_int) 0xADB5555600E6A305ULL) << 64));
    zobrist_table[2][3][0] = (((zobrist_int) 0x9450085B63A029A5ULL) + (((zobrist_int) 0xF86668C16D05C818ULL) << 64));
    zobrist_table[2][3][1] = (((zobrist_int) 0x5604C3B667BE9998ULL) + (((zobrist_int) 0x9F22CE0ADC7A9283ULL) << 64));
    zobrist_table[2][3][2] = (((zobrist_int) 0xF977EDF4959D133DULL) + (((zobrist_int) 0xB312AD6FBBDC55A2ULL) << 64));
    zobrist_table[2][3][3] = (((zobrist_int) 0xF7ADC0AEE5DD6001ULL) + (((zobrist_int) 0x1157C8B3BFAF9E2FULL) << 64));
    zobrist_table[2][3][4] = (((zobrist_int) 0xFCD58C0F7E21B8AAULL) + (((zobrist_int) 0x3F64C50CBEEAAC97ULL) << 64));
    zobrist_table[2][3][5] = (((zobrist_int) 0xF78D9952A3EE54D4ULL) + (((zobrist_int) 0x4A77814EA6142E5BULL) << 64));
    zobrist_table[2][3][6] = (((zobrist_int) 0x55198C0A1326797ULL) + (((zobrist_int) 0xB8A61715683115A8ULL) << 64));
    zobrist_table[2][3][7] = (((zobrist_int) 0x27F52FA9A117511FULL) + (((zobrist_int) 0xC76330AFA23C4B27ULL) << 64));
    zobrist_table[2][3][8] = (((zobrist_int) 0x65B699ECEFE6F675ULL) + (((zobrist_int) 0x452FAC9AC850320AULL) << 64));
    zobrist_table[2][3][9] = (((zobrist_int) 0x2D9B4F22D8A50636ULL) + (((zobrist_int) 0x12CB2F3FC47ADDC9ULL) << 64));
    zobrist_table[2][3][10] = (((zobrist_int) 0xC6AD0327D0B93207ULL) + (((zobrist_int) 0x297C0D69AFF956CULL) << 64));
    zobrist_table[2][3][11] = (((zobrist_int) 0xE9A413CA59758F83ULL) + (((zobrist_int) 0xCC5D375A43BBBA66ULL) << 64));
    zobrist_table[2][3][12] = (((zobrist_int) 0x6940776CB540CCE4ULL) + (((zobrist_int) 0xAF5E490BDFBAAAFAULL) << 64));
    zobrist_table[2][3][13] = (((zobrist_int) 0x4DBD3DC98B53C16BULL) + (((zobrist_int) 0x764A44E326EE0EACULL) << 64));
    zobrist_table[2][4][0] = (((zobrist_int) 0x4264D159D53DDE5EULL) + (((zobrist_int) 0x2B6C57637C0B03EEULL) << 64));
    zobrist_table[2][4][1] = (((zobrist_int) 0x82A4C12E779409B9ULL) + (((zobrist_int) 0x45547D9D0B9E8D4DULL) << 64));
    zobrist_table[2][4][2] = (((zobrist_int) 0x193FD24D82A1C54CULL) + (((zobrist_int) 0x9733EF95BEA7C879ULL) << 64));
    zobrist_table[2][4][3] = (((zobrist_int) 0x11DB6ACF6C2F5ECCULL) + (((zobrist_int) 0x1126D71A5AECE68FULL) << 64));
    zobrist_table[2][4][4] = (((zobrist_int) 0x714699BDA826E5F1ULL) + (((zobrist_int) 0x2A04FF67050DC58CULL) << 64));
    zobrist_table[2][4][5] = (((zobrist_int) 0xB5D28DEE81D57930ULL) + (((zobrist_int) 0x29606598F23562B7ULL) << 64));
    zobrist_table[2][4][6] = (((zobrist_int) 0x17D259ADB0C12C60ULL) + (((zobrist_int) 0xA2CF179F66E47927ULL) << 64));
    zobrist_table[2][4][7] = (((zobrist_int) 0x469A8A20B05C4A59ULL) + (((zobrist_int) 0x4DED5FAA9AE0E1B9ULL) << 64));
    zobrist_table[2][4][8] = (((zobrist_int) 0x873116F03579C67EULL) + (((zobrist_int) 0x3CBB5615352C5F80ULL) << 64));
    zobrist_table[2][4][9] = (((zobrist_int) 0x557D728CE2D28DA8ULL) + (((zobrist_int) 0x118CC43E44E1B856ULL) << 64));
    zobrist_table[2][4][10] = (((zobrist_int) 0xB2FE7205132BA600ULL) + (((zobrist_int) 0xE90C0722D4A74958ULL) << 64));
    zobrist_table[2][4][11] = (((zobrist_int) 0xA8A6217585F049FEULL) + (((zobrist_int) 0x77CAB1F95E42E3E0ULL) << 64));
    zobrist_table[2][4][12] = (((zobrist_int) 0x8EC2361582F2E770ULL) + (((zobrist_int) 0xCBBEAB0BC9A0E0CULL) << 64));
    zobrist_table[2][4][13] = (((zobrist_int) 0x4C0015082B265442ULL) + (((zobrist_int) 0xBC2E9FF5A72F6600ULL) << 64));
    zobrist_table[2][5][0] = (((zobrist_int) 0xFF11DC91B6A3CE92ULL) + (((zobrist_int) 0x8E65E4CFD0A410DAULL) << 64));
    zobrist_table[2][5][1] = (((zobrist_int) 0x5B1916CD450F0864ULL) + (((zobrist_int) 0xBD6679C09C1317A3ULL) << 64));
    zobrist_table[2][5][2] = (((zobrist_int) 0x647EC1543B6BD0A4ULL) + (((zobrist_int) 0x6653C3B78FA09FA2ULL) << 64));
    zobrist_table[2][5][3] = (((zobrist_int) 0x7BCEC85D2C1FFACCULL) + (((zobrist_int) 0x427005F6CA2E3611ULL) << 64));
    zobrist_table[2][5][4] = (((zobrist_int) 0x9C434723DDE138D8ULL) + (((zobrist_int) 0xB74F34105463852DULL) << 64));
    zobrist_table[2][5][5] = (((zobrist_int) 0x423E96D038E9DE81ULL) + (((zobrist_int) 0x9C25B2DBF6BAD673ULL) << 64));
    zobrist_table[2][5][6] = (((zobrist_int) 0x3E85B0A9B4E9A806ULL) + (((zobrist_int) 0xA92CD2DED802CB08ULL) << 64));
    zobrist_table[2][5][7] = (((zobrist_int) 0xDA0DBC7807D11B6BULL) + (((zobrist_int) 0xDE518343E63EA3D6ULL) << 64));
    zobrist_table[2][5][8] = (((zobrist_int) 0x6710B0E79F5904A6ULL) + (((zobrist_int) 0xED9140C051080DEBULL) << 64));
    zobrist_table[2][5][9] = (((zobrist_int) 0xEEE133EA6E883110ULL) + (((zobrist_int) 0x3F98E0EEC2F7C23FULL) << 64));
    zobrist_table[2][5][10] = (((zobrist_int) 0x44E32DBDC910C201ULL) + (((zobrist_int) 0x1291F006309D57EDULL) << 64));
    zobrist_table[2][5][11] = (((zobrist_int) 0xBB798E9BA03A1915ULL) + (((zobrist_int) 0xDEFD56702A66B259ULL) << 64));
    zobrist_table[2][5][12] = (((zobrist_int) 0x9442F362F919CB32ULL) + (((zobrist_int) 0x94D8CD47718E3BAFULL) << 64));
    zobrist_table[2][5][13] = (((zobrist_int) 0xEED4B1F0E9C3DEEEULL) + (((zobrist_int) 0x25EF2114BA6E736CULL) << 64));
    zobrist_table[2][6][0] = (((zobrist_int) 0xF20AB3059B33D947ULL) + (((zobrist_int) 0x759AAEEE431162A4ULL) << 64));
    zobrist_table[2][6][1] = (((zobrist_int) 0x299BF22D86CEC133ULL) + (((zobrist_int) 0xC7495DF9237C9540ULL) << 64));
    zobrist_table[2][6][2] = (((zobrist_int) 0xE4D4AD86235A63D5ULL) + (((zobrist_int) 0x70D07EBAB73B6062ULL) << 64));
    zobrist_table[2][6][3] = (((zobrist_int) 0x4F4C8DB65C706106ULL) + (((zobrist_int) 0x6697F21EC05A32A3ULL) << 64));
    zobrist_table[2][6][4] = (((zobrist_int) 0x1DA77D913D90FD27ULL) + (((zobrist_int) 0x34C8D03AB7D9365CULL) << 64));
    zobrist_table[2][6][5] = (((zobrist_int) 0xAE7024EDB7EE1A9AULL) + (((zobrist_int) 0x117746184E34FA77ULL) << 64));
    zobrist_table[2][6][6] = (((zobrist_int) 0x3A4548F21B3C137BULL) + (((zobrist_int) 0x524550A465A24E8AULL) << 64));
    zobrist_table[2][6][7] = (((zobrist_int) 0xEDB924D87E0B6723ULL) + (((zobrist_int) 0xF48FE7D31997E8F3ULL) << 64));
    zobrist_table[2][6][8] = (((zobrist_int) 0xB83DA502FCF9616ULL) + (((zobrist_int) 0xCF39EFD70E2AF641ULL) << 64));
    zobrist_table[2][6][9] = (((zobrist_int) 0x5F5E71B98F6A644ULL) + (((zobrist_int) 0xC09F025EE38D62A7ULL) << 64));
    zobrist_table[2][6][10] = (((zobrist_int) 0xAEECB544377054CFULL) + (((zobrist_int) 0x7E94F5AB08E2FAD3ULL) << 64));
    zobrist_table[2][6][11] = (((zobrist_int) 0x874E263FB4345622ULL) + (((zobrist_int) 0xB9559250D09DFA6CULL) << 64));
    zobrist_table[2][6][12] = (((zobrist_int) 0xE31E1292F6D0AC1DULL) + (((zobrist_int) 0x7139BED19CF94BC1ULL) << 64));
    zobrist_table[2][6][13] = (((zobrist_int) 0xA9B576D757AA5AE1ULL) + (((zobrist_int) 0x464A8296D67E8ECFULL) << 64));
    zobrist_table[2][7][0] = (((zobrist_int) 0x9CFD717D1E39A54CULL) + (((zobrist_int) 0x2C354A1BB150A78DULL) << 64));
    zobrist_table[2][7][1] = (((zobrist_int) 0x38D9431F18610C9FULL) + (((zobrist_int) 0x3BB42D9D66531DAFULL) << 64));
    zobrist_table[2][7][2] = (((zobrist_int) 0x732701337EB9D1C8ULL) + (((zobrist_int) 0xC02823EC60BDADCEULL) << 64));
    zobrist_table[2][7][3] = (((zobrist_int) 0xF9333F742B2935F2ULL) + (((zobrist_int) 0x3C593E7F3B51D375ULL) << 64));
    zobrist_table[2][7][4] = (((zobrist_int) 0x489CBAFFD1F559AFULL) + (((zobrist_int) 0x8C09786B766B5E3CULL) << 64));
    zobrist_table[2][7][5] = (((zobrist_int) 0x63BC6601947678F5ULL) + (((zobrist_int) 0x73A26890363F89C2ULL) << 64));
    zobrist_table[2][7][6] = (((zobrist_int) 0x42041769B705FBF3ULL) + (((zobrist_int) 0x7F0FAD3B5482909FULL) << 64));
    zobrist_table[2][7][7] = (((zobrist_int) 0x1C66EED297F7634BULL) + (((zobrist_int) 0x36BEB903E8D424EEULL) << 64));
    zobrist_table[2][7][8] = (((zobrist_int) 0x142FAB55FE909103ULL) + (((zobrist_int) 0x3F207910BD4F091ULL) << 64));
    zobrist_table[2][7][9] = (((zobrist_int) 0x1569570CC2534B4ULL) + (((zobrist_int) 0x7AFB6462DB8AE021ULL) << 64));
    zobrist_table[2][7][10] = (((zobrist_int) 0xE38A59AA51CFA14EULL) + (((zobrist_int) 0xD910DDD76215F679ULL) << 64));
    zobrist_table[2][7][11] = (((zobrist_int) 0x4986F3A6948B82B1ULL) + (((zobrist_int) 0x322578EBEB391D06ULL) << 64));
    zobrist_table[2][7][12] = (((zobrist_int) 0x28FA361A6661B877ULL) + (((zobrist_int) 0xD3005630E149A837ULL) << 64));
    zobrist_table[2][7][13] = (((zobrist_int) 0xA5632A15C23105D9ULL) + (((zobrist_int) 0xCB320DB826FB5E56ULL) << 64));
    zobrist_table[3][0][0] = (((zobrist_int) 0x7CC0424E9E6ED7CULL) + (((zobrist_int) 0x63243E5303E2E7C4ULL) << 64));
    zobrist_table[3][0][1] = (((zobrist_int) 0xE055AF1C252A66D8ULL) + (((zobrist_int) 0x8AE63AB1AA311156ULL) << 64));
    zobrist_table[3][0][2] = (((zobrist_int) 0x909311ED0E9F654FULL) + (((zobrist_int) 0x4111329A61263FDDULL) << 64));
    zobrist_table[3][0][3] = (((zobrist_int) 0x145B523821464B6DULL) + (((zobrist_int) 0xA6F38E3E767FE953ULL) << 64));
    zobrist_table[3][0][4] = (((zobrist_int) 0x4DABB96DD708F3A0ULL) + (((zobrist_int) 0x3B27030E7F524F3ULL) << 64));
    zobrist_table[3][0][5] = (((zobrist_int) 0x89778FB7091489CDULL) + (((zobrist_int) 0x8660194D0F93FB05ULL) << 64));
    zobrist_table[3][0][6] = (((zobrist_int) 0x21013EEFD733230AULL) + (((zobrist_int) 0xEEF208450AF5E8D2ULL) << 64));
    zobrist_table[3][0][7] = (((zobrist_int) 0xC7E21846460A02ECULL) + (((zobrist_int) 0x6EB8F85F1E10553BULL) << 64));
    zobrist_table[3][0][8] = (((zobrist_int) 0x30AB1C2E174E3F4BULL) + (((zobrist_int) 0x7FE9DA2007124B2FULL) << 64));
    zobrist_table[3][0][9] = (((zobrist_int) 0x215C1C0BA3340D96ULL) + (((zobrist_int) 0x477E4A80BE9F0A63ULL) << 64));
    zobrist_table[3][0][10] = (((zobrist_int) 0xD12FF4BFAFD03FB9ULL) + (((zobrist_int) 0x312218D0D87ABBFFULL) << 64));
    zobrist_table[3][0][11] = (((zobrist_int) 0x72904D18A9BB6DCBULL) + (((zobrist_int) 0x546E197B63C3817CULL) << 64));
    zobrist_table[3][0][12] = (((zobrist_int) 0x4499E3AFA18D58B8ULL) + (((zobrist_int) 0x42850DA8F8375D93ULL) << 64));
    zobrist_table[3][0][13] = (((zobrist_int) 0xA2B73A66A4401DABULL) + (((zobrist_int) 0x3ED43AB33E3B4290ULL) << 64));
    zobrist_table[3][1][0] = (((zobrist_int) 0x968240EF0F683985ULL) + (((zobrist_int) 0xC9B8056FEF6709E9ULL) << 64));
    zobrist_table[3][1][1] = (((zobrist_int) 0x2CDEEC51972AB68BULL) + (((zobrist_int) 0x6DB076BD59805A17ULL) << 64));
    zobrist_table[3][1][2] = (((zobrist_int) 0xB2B3D2229AF865DFULL) + (((zobrist_int) 0xA36CF2B98F6D0AAAULL) << 64));
    zobrist_table[3][1][3] = (((zobrist_int) 0xF819B75085AD0C99ULL) + (((zobrist_int) 0xE7B128FD0F90E49CULL) << 64));
    zobrist_table[3][1][4] = (((zobrist_int) 0x8C0354BE5A6D1EFCULL) + (((zobrist_int) 0x89C08E1C69A36E9AULL) << 64));
    zobrist_table[3][1][5] = (((zobrist_int) 0xB62E96933309CDB1ULL) + (((zobrist_int) 0x8951D454E14E939AULL) << 64));
    zobrist_table[3][1][6] = (((zobrist_int) 0xEB7FEC926C931D1AULL) + (((zobrist_int) 0x11F10C60A9921B68ULL) << 64));
    zobrist_table[3][1][7] = (((zobrist_int) 0x446056BFB6AAFAE5ULL) + (((zobrist_int) 0x9C546496BE47CC7AULL) << 64));
    zobrist_table[3][1][8] = (((zobrist_int) 0xF8ECAE24B89B02F9ULL) + (((zobrist_int) 0x128137EAC090BC84ULL) << 64));
    zobrist_table[3][1][9] = (((zobrist_int) 0x2D75C843406797B6ULL) + (((zobrist_int) 0x18B8A008F9F59771ULL) << 64));
    zobrist_table[3][1][10] = (((zobrist_int) 0xF078F6C26A89353ULL) + (((zobrist_int) 0x340E8462EB2C79D4ULL) << 64));
    zobrist_table[3][1][11] = (((zobrist_int) 0x6D9814D5DAC504E5ULL) + (((zobrist_int) 0xB7EF083DA277078ULL) << 64));
    zobrist_table[3][1][12] = (((zobrist_int) 0xA31A7B190D8509DBULL) + (((zobrist_int) 0xE9901243175A1163ULL) << 64));
    zobrist_table[3][1][13] = (((zobrist_int) 0x83497471D0246CCAULL) + (((zobrist_int) 0x8049E97A781B5120ULL) << 64));
    zobrist_table[3][2][0] = (((zobrist_int) 0x196A8D845EC8E9D7ULL) + (((zobrist_int) 0x500C48E1FC147A78ULL) << 64));
    zobrist_table[3][2][1] = (((zobrist_int) 0x206A985A0A452B53ULL) + (((zobrist_int) 0x87EE17B880E180BULL) << 64));
    zobrist_table[3][2][2] = (((zobrist_int) 0xAA0CB6F5717F5EEDULL) + (((zobrist_int) 0xE539D34D20D1EB7DULL) << 64));
    zobrist_table[3][2][3] = (((zobrist_int) 0xC36E5359652B0ED7ULL) + (((zobrist_int) 0xE61541B6B528614CULL) << 64));
    zobrist_table[3][2][4] = (((zobrist_int) 0x723280C3E1DF6F91ULL) + (((zobrist_int) 0xBC937D7E064D7A2FULL) << 64));
    zobrist_table[3][2][5] = (((zobrist_int) 0x451E07EA8646422CULL) + (((zobrist_int) 0x40008E261722EBBEULL) << 64));
    zobrist_table[3][2][6] = (((zobrist_int) 0x534E570FCCE695F7ULL) + (((zobrist_int) 0x4D455C7115F6063EULL) << 64));
    zobrist_table[3][2][7] = (((zobrist_int) 0xDC14F82708C0E4A2ULL) + (((zobrist_int) 0xEE3BDCB625D4DD2ULL) << 64));
    zobrist_table[3][2][8] = (((zobrist_int) 0x42D15CD3BB8C1409ULL) + (((zobrist_int) 0xBC377F13502E5056ULL) << 64));
    zobrist_table[3][2][9] = (((zobrist_int) 0x42A305D521480046ULL) + (((zobrist_int) 0x6153AF71CB6915C1ULL) << 64));
    zobrist_table[3][2][10] = (((zobrist_int) 0x1DFCA10CCE9244CBULL) + (((zobrist_int) 0xAD83C3FBDB19A0BBULL) << 64));
    zobrist_table[3][2][11] = (((zobrist_int) 0x181437224DC232A6ULL) + (((zobrist_int) 0xD765194F6CC1AEAFULL) << 64));
    zobrist_table[3][2][12] = (((zobrist_int) 0x80B380113ED1E0EBULL) + (((zobrist_int) 0x3495D62A8EA32F2EULL) << 64));
    zobrist_table[3][2][13] = (((zobrist_int) 0xEC4C277B5481E736ULL) + (((zobrist_int) 0x8262CDC556B2A3E4ULL) << 64));
    zobrist_table[3][3][0] = (((zobrist_int) 0x641E9E8DC89B69D3ULL) + (((zobrist_int) 0xE54E1AD1F4CFD336ULL) << 64));
    zobrist_table[3][3][1] = (((zobrist_int) 0x7B2CCE17958A3855ULL) + (((zobrist_int) 0x21358EE61ACCD407ULL) << 64));
    zobrist_table[3][3][2] = (((zobrist_int) 0xD08EF562A70F268FULL) + (((zobrist_int) 0x86143E1472D837AFULL) << 64));
    zobrist_table[3][3][3] = (((zobrist_int) 0x8F036FBEFCEF9215ULL) + (((zobrist_int) 0xD810C3F6B82962A8ULL) << 64));
    zobrist_table[3][3][4] = (((zobrist_int) 0x94D43EDED5B48AD0ULL) + (((zobrist_int) 0x8523E065B3877F0EULL) << 64));
    zobrist_table[3][3][5] = (((zobrist_int) 0x7BFAAEA891E53CBULL) + (((zobrist_int) 0xFAD32CAFE595E3CBULL) << 64));
    zobrist_table[3][3][6] = (((zobrist_int) 0xFDBB37B8D4E4DB03ULL) + (((zobrist_int) 0xBE40F38E4A945554ULL) << 64));
    zobrist_table[3][3][7] = (((zobrist_int) 0x3331824728333E0EULL) + (((zobrist_int) 0x63A522E35ECF615DULL) << 64));
    zobrist_table[3][3][8] = (((zobrist_int) 0x53001B63856558B2ULL) + (((zobrist_int) 0x68D52EB618EDE6C3ULL) << 64));
    zobrist_table[3][3][9] = (((zobrist_int) 0x20599249586AC6E6ULL) + (((zobrist_int) 0x109ADA70932D0488ULL) << 64));
    zobrist_table[3][3][10] = (((zobrist_int) 0x4CED509A0B27B4C9ULL) + (((zobrist_int) 0xCC88EBD1D0A079F5ULL) << 64));
    zobrist_table[3][3][11] = (((zobrist_int) 0x889F5E9AA6AF9B40ULL) + (((zobrist_int) 0x6AE70FF2504B60B5ULL) << 64));
    zobrist_table[3][3][12] = (((zobrist_int) 0x519CD4CC4C5EC38DULL) + (((zobrist_int) 0x45CDA9495A450D23ULL) << 64));
    zobrist_table[3][3][13] = (((zobrist_int) 0xBFAD326153461EB3ULL) + (((zobrist_int) 0x852571D4BF9E995CULL) << 64));
    zobrist_table[3][4][0] = (((zobrist_int) 0x2345A9D8045432FULL) + (((zobrist_int) 0x1F327A7486B059DCULL) << 64));
    zobrist_table[3][4][1] = (((zobrist_int) 0x512E2BEA2614E7E7ULL) + (((zobrist_int) 0xBA0FF0B7EA174C4EULL) << 64));
    zobrist_table[3][4][2] = (((zobrist_int) 0xC8E2896A5358BF46ULL) + (((zobrist_int) 0x92B7563053DB4391ULL) << 64));
    zobrist_table[3][4][3] = (((zobrist_int) 0x73AA1107119FE69FULL) + (((zobrist_int) 0x4794AB91FABAB7B5ULL) << 64));
    zobrist_table[3][4][4] = (((zobrist_int) 0x7442A8CC7ACD7A45ULL) + (((zobrist_int) 0x5D39F1B8E9B2D06AULL) << 64));
    zobrist_table[3][4][5] = (((zobrist_int) 0xBDDBF0CAED7852CEULL) + (((zobrist_int) 0x616A43DEF841AD26ULL) << 64));
    zobrist_table[3][4][6] = (((zobrist_int) 0xE3BBA436D0CD14A1ULL) + (((zobrist_int) 0x1402F91CECE9D8EDULL) << 64));
    zobrist_table[3][4][7] = (((zobrist_int) 0x943735D4EC1B2724ULL) + (((zobrist_int) 0xE5C9BEBCD266EA8ULL) << 64));
    zobrist_table[3][4][8] = (((zobrist_int) 0xC7950FA2273EA38ULL) + (((zobrist_int) 0x7DFF04AE8611F8B9ULL) << 64));
    zobrist_table[3][4][9] = (((zobrist_int) 0xDA64B870935AC8D9ULL) + (((zobrist_int) 0x407DBB94FE145171ULL) << 64));
    zobrist_table[3][4][10] = (((zobrist_int) 0x3ED03C49C8B0DA28ULL) + (((zobrist_int) 0x92E38012B3F2513DULL) << 64));
    zobrist_table[3][4][11] = (((zobrist_int) 0x56B1B132BF246424ULL) + (((zobrist_int) 0xFD983DF55C905C22ULL) << 64));
    zobrist_table[3][4][12] = (((zobrist_int) 0xCC025364F13B7619ULL) + (((zobrist_int) 0x5EC127B3A4BC7977ULL) << 64));
    zobrist_table[3][4][13] = (((zobrist_int) 0x4EB0FF74670F2134ULL) + (((zobrist_int) 0x9927A8FD76EE29AAULL) << 64));
    zobrist_table[3][5][0] = (((zobrist_int) 0x5727D740FAD13805ULL) + (((zobrist_int) 0x81EE476C88399110ULL) << 64));
    zobrist_table[3][5][1] = (((zobrist_int) 0x77148A52AF4C782ULL) + (((zobrist_int) 0x400839A925FA97DDULL) << 64));
    zobrist_table[3][5][2] = (((zobrist_int) 0x389C1CCFAFEF1AC1ULL) + (((zobrist_int) 0x2226FF4390120EA1ULL) << 64));
    zobrist_table[3][5][3] = (((zobrist_int) 0x1CDDEE9CE8247487ULL) + (((zobrist_int) 0xC42DDDC22F41F7CDULL) << 64));
    zobrist_table[3][5][4] = (((zobrist_int) 0xF06F217A693E6D5DULL) + (((zobrist_int) 0x9EA4F0BBBA5B99CDULL) << 64));
    zobrist_table[3][5][5] = (((zobrist_int) 0xCFCD69020CD3AEE8ULL) + (((zobrist_int) 0xFA85459D1966A3BBULL) << 64));
    zobrist_table[3][5][6] = (((zobrist_int) 0xAE6AC89A8BB3835BULL) + (((zobrist_int) 0xB6F3D08A4406D47FULL) << 64));
    zobrist_table[3][5][7] = (((zobrist_int) 0x344FEFE11B604336ULL) + (((zobrist_int) 0x11180CD942FE9CA9ULL) << 64));
    zobrist_table[3][5][8] = (((zobrist_int) 0x923B3BEAA1D3FF82ULL) + (((zobrist_int) 0xA41AAFAC86C0ABFEULL) << 64));
    zobrist_table[3][5][9] = (((zobrist_int) 0xDAEB22A514185D06ULL) + (((zobrist_int) 0xCB517E6A12A3C54BULL) << 64));
    zobrist_table[3][5][10] = (((zobrist_int) 0x37A6437BD9C2B0CFULL) + (((zobrist_int) 0xD69871BCA4AB4EECULL) << 64));
    zobrist_table[3][5][11] = (((zobrist_int) 0x82F01B582C61CBECULL) + (((zobrist_int) 0x6E9D7077DCA1284FULL) << 64));
    zobrist_table[3][5][12] = (((zobrist_int) 0x9721C6E50597EBC1ULL) + (((zobrist_int) 0xE66743DC5E3C1D96ULL) << 64));
    zobrist_table[3][5][13] = (((zobrist_int) 0x7C969920D8FE4338ULL) + (((zobrist_int) 0xCEB52FC3B5D4CE45ULL) << 64));
    zobrist_table[3][6][0] = (((zobrist_int) 0x384DA68248A3FF76ULL) + (((zobrist_int) 0x334C76B8E42B0627ULL) << 64));
    zobrist_table[3][6][1] = (((zobrist_int) 0x7E5D933D991BA3CEULL) + (((zobrist_int) 0xE61BACEBDD90F85BULL) << 64));
    zobrist_table[3][6][2] = (((zobrist_int) 0x3C377DA0E48E1B4DULL) + (((zobrist_int) 0x73C2F6F06CE9E732ULL) << 64));
    zobrist_table[3][6][3] = (((zobrist_int) 0x5DFE36F1ACF424D9ULL) + (((zobrist_int) 0xE9A1A2588B62CCBAULL) << 64));
    zobrist_table[3][6][4] = (((zobrist_int) 0x3056DDB0F1DA2B29ULL) + (((zobrist_int) 0x7B6EB806CC544333ULL) << 64));
    zobrist_table[3][6][5] = (((zobrist_int) 0x129C03B0B9CF3DDEULL) + (((zobrist_int) 0xD73ECD63D0646CF9ULL) << 64));
    zobrist_table[3][6][6] = (((zobrist_int) 0xF9EEF8DBFF876918ULL) + (((zobrist_int) 0x68457E4141ADFE67ULL) << 64));
    zobrist_table[3][6][7] = (((zobrist_int) 0x21EA0E2338C9127ULL) + (((zobrist_int) 0x883062FABF2D288BULL) << 64));
    zobrist_table[3][6][8] = (((zobrist_int) 0x6176A3CAC53482ECULL) + (((zobrist_int) 0xE0463F9F83A81A4EULL) << 64));
    zobrist_table[3][6][9] = (((zobrist_int) 0x138FCC237CB10028ULL) + (((zobrist_int) 0x9DA7FDF2675BB4B3ULL) << 64));
    zobrist_table[3][6][10] = (((zobrist_int) 0x8293D779E1F86D03ULL) + (((zobrist_int) 0x940A3AEBCBD5DA31ULL) << 64));
    zobrist_table[3][6][11] = (((zobrist_int) 0x6CF3EEEA95A8303BULL) + (((zobrist_int) 0x5A11494F0A453E8CULL) << 64));
    zobrist_table[3][6][12] = (((zobrist_int) 0xFCE5D2C6D9E46A51ULL) + (((zobrist_int) 0x1A38311755D3871ULL) << 64));
    zobrist_table[3][6][13] = (((zobrist_int) 0xF5E4C4BB30942540ULL) + (((zobrist_int) 0xB22CC3474CA27B41ULL) << 64));
    zobrist_table[3][7][0] = (((zobrist_int) 0xA45F419CB0FB4BC8ULL) + (((zobrist_int) 0x8A70103F0168E969ULL) << 64));
    zobrist_table[3][7][1] = (((zobrist_int) 0xD265BCD71EBB3EF7ULL) + (((zobrist_int) 0x8332AC334D7AB56DULL) << 64));
    zobrist_table[3][7][2] = (((zobrist_int) 0xFE725A5EE31EF8FBULL) + (((zobrist_int) 0x50C80450BF323EF2ULL) << 64));
    zobrist_table[3][7][3] = (((zobrist_int) 0xC6CD35FFF885CE63ULL) + (((zobrist_int) 0xA521DADD8B03EE7CULL) << 64));
    zobrist_table[3][7][4] = (((zobrist_int) 0xFE692199926C8264ULL) + (((zobrist_int) 0x48525E8A8D2707D7ULL) << 64));
    zobrist_table[3][7][5] = (((zobrist_int) 0x6953E9E8868F8154ULL) + (((zobrist_int) 0xF08B56528AC32BBDULL) << 64));
    zobrist_table[3][7][6] = (((zobrist_int) 0xED421259D18DA490ULL) + (((zobrist_int) 0x8492C7B5F40FF922ULL) << 64));
    zobrist_table[3][7][7] = (((zobrist_int) 0x9A4F17B66886663AULL) + (((zobrist_int) 0x94C05053A14566E6ULL) << 64));
    zobrist_table[3][7][8] = (((zobrist_int) 0x73D87FD74EC9521CULL) + (((zobrist_int) 0x218586644D49FFCEULL) << 64));
    zobrist_table[3][7][9] = (((zobrist_int) 0x71B5FF55819E0387ULL) + (((zobrist_int) 0x23EC75979615A32EULL) << 64));
    zobrist_table[3][7][10] = (((zobrist_int) 0xC5C328968CCC6FF2ULL) + (((zobrist_int) 0xF97C4298FA01208BULL) << 64));
    zobrist_table[3][7][11] = (((zobrist_int) 0x40B3D0C629B87BAFULL) + (((zobrist_int) 0x27586DAA2FC706BULL) << 64));
    zobrist_table[3][7][12] = (((zobrist_int) 0x6C96EDFAFE99958FULL) + (((zobrist_int) 0xA95B3B44BC735CA7ULL) << 64));
    zobrist_table[3][7][13] = (((zobrist_int) 0x947AA9290DF617BULL) + (((zobrist_int) 0x6BBE026B5E4D0C25ULL) << 64));
    zobrist_table[4][0][0] = (((zobrist_int) 0x4813FCAA66F292EDULL) + (((zobrist_int) 0xA8B3B3DEEFBFFA3DULL) << 64));
    zobrist_table[4][0][1] = (((zobrist_int) 0xC0426A0CE5346059ULL) + (((zobrist_int) 0x4B15253AB6FE7D5ULL) << 64));
    zobrist_table[4][0][2] = (((zobrist_int) 0x17297DB8E6145787ULL) + (((zobrist_int) 0x170C4B00ECD78663ULL) << 64));
    zobrist_table[4][0][3] = (((zobrist_int) 0x13BC6BAD8A9F8F4ULL) + (((zobrist_int) 0x44D5017262279051ULL) << 64));
    zobrist_table[4][0][4] = (((zobrist_int) 0x459F039076E099F9ULL) + (((zobrist_int) 0xC812FED7CBC0981CULL) << 64));
    zobrist_table[4][0][5] = (((zobrist_int) 0xA2C631335F64E0D2ULL) + (((zobrist_int) 0xDA2D6582BFD64E7FULL) << 64));
    zobrist_table[4][0][6] = (((zobrist_int) 0xC4C5475D7B3E5DAAULL) + (((zobrist_int) 0x6372099A5627922CULL) << 64));
    zobrist_table[4][0][7] = (((zobrist_int) 0xCDB4255D74C6224FULL) + (((zobrist_int) 0x7BD558001DD39048ULL) << 64));
    zobrist_table[4][0][8] = (((zobrist_int) 0x250ABF6E5AC04CA4ULL) + (((zobrist_int) 0x25F463566A4A2EADULL) << 64));
    zobrist_table[4][0][9] = (((zobrist_int) 0xFEB89FFF04A65E39ULL) + (((zobrist_int) 0xD065C0E72C0D0A30ULL) << 64));
    zobrist_table[4][0][10] = (((zobrist_int) 0x5E25E8A0429EA21FULL) + (((zobrist_int) 0x208AD9FFDB9E49BEULL) << 64));
    zobrist_table[4][0][11] = (((zobrist_int) 0xC941965096EE86EFULL) + (((zobrist_int) 0xF31AEB0049825407ULL) << 64));
    zobrist_table[4][0][12] = (((zobrist_int) 0x69B48C0EFF6B0446ULL) + (((zobrist_int) 0xF065DF4A4207158AULL) << 64));
    zobrist_table[4][0][13] = (((zobrist_int) 0x498AFB138387A1E7ULL) + (((zobrist_int) 0x6BB685A0BD512B39ULL) << 64));
    zobrist_table[4][1][0] = (((zobrist_int) 0x460F923DB0FA6216ULL) + (((zobrist_int) 0x55FDC4016EFA083BULL) << 64));
    zobrist_table[4][1][1] = (((zobrist_int) 0xE9F9FA5BC6E95218ULL) + (((zobrist_int) 0x3728AAB97C5D00BEULL) << 64));
    zobrist_table[4][1][2] = (((zobrist_int) 0xD4620A8BB728B7F9ULL) + (((zobrist_int) 0xF3085DB87DCADA54ULL) << 64));
    zobrist_table[4][1][3] = (((zobrist_int) 0x66E33812F8B3E021ULL) + (((zobrist_int) 0x6CD4D5B3B7579183ULL) << 64));
    zobrist_table[4][1][4] = (((zobrist_int) 0x107F37D417647FA2ULL) + (((zobrist_int) 0x34C590E72124F447ULL) << 64));
    zobrist_table[4][1][5] = (((zobrist_int) 0x264C679BF76D8381ULL) + (((zobrist_int) 0xBAEC1FCF3AAEB5EDULL) << 64));
    zobrist_table[4][1][6] = (((zobrist_int) 0x1A6F936506B0DA21ULL) + (((zobrist_int) 0x27DCCBB040D3458CULL) << 64));
    zobrist_table[4][1][7] = (((zobrist_int) 0xC652FC977AD35305ULL) + (((zobrist_int) 0x1954F128F3C151A4ULL) << 64));
    zobrist_table[4][1][8] = (((zobrist_int) 0xA65023BA662D6088ULL) + (((zobrist_int) 0x2FFBBD51B937A988ULL) << 64));
    zobrist_table[4][1][9] = (((zobrist_int) 0xC458B4D598C859ULL) + (((zobrist_int) 0x6D7CD4ED16D35266ULL) << 64));
    zobrist_table[4][1][10] = (((zobrist_int) 0xF46ED6DD9CA4F36EULL) + (((zobrist_int) 0xD05F982FEEBB948ULL) << 64));
    zobrist_table[4][1][11] = (((zobrist_int) 0x37E103558CB25244ULL) + (((zobrist_int) 0x6C0046F488D4161AULL) << 64));
    zobrist_table[4][1][12] = (((zobrist_int) 0xC0A78D058C17F6BULL) + (((zobrist_int) 0xA6CE9740F233F692ULL) << 64));
    zobrist_table[4][1][13] = (((zobrist_int) 0xED10E6B8F837A7D6ULL) + (((zobrist_int) 0xBC098FD81A6956D4ULL) << 64));
    zobrist_table[4][2][0] = (((zobrist_int) 0xADD763FA8D86850EULL) + (((zobrist_int) 0xD5BC9F746B6CD23AULL) << 64));
    zobrist_table[4][2][1] = (((zobrist_int) 0xBDBA19EBABF100B0ULL) + (((zobrist_int) 0xFEC08E901E5FA037ULL) << 64));
    zobrist_table[4][2][2] = (((zobrist_int) 0xAF3EF55C43ECF2B9ULL) + (((zobrist_int) 0x2DD5AD98475C61B1ULL) << 64));
    zobrist_table[4][2][3] = (((zobrist_int) 0xCE1C61527ACE7783ULL) + (((zobrist_int) 0xB444090FCB14957DULL) << 64));
    zobrist_table[4][2][4] = (((zobrist_int) 0xC346FDFDB9BE515ULL) + (((zobrist_int) 0x36D71C3FC9530F5EULL) << 64));
    zobrist_table[4][2][5] = (((zobrist_int) 0xA4EEFF8DAD433669ULL) + (((zobrist_int) 0xDDCC33FE165243BDULL) << 64));
    zobrist_table[4][2][6] = (((zobrist_int) 0x1FB0975F63C47F8AULL) + (((zobrist_int) 0x7281C9E4AB300794ULL) << 64));
    zobrist_table[4][2][7] = (((zobrist_int) 0xAE94E3864B53D283ULL) + (((zobrist_int) 0x7F7A6583820062ECULL) << 64));
    zobrist_table[4][2][8] = (((zobrist_int) 0x64A11177E7B33734ULL) + (((zobrist_int) 0x9B2A1BB01DBC77ACULL) << 64));
    zobrist_table[4][2][9] = (((zobrist_int) 0x7AAC3FA2DA97A917ULL) + (((zobrist_int) 0x262D9D551B17A754ULL) << 64));
    zobrist_table[4][2][10] = (((zobrist_int) 0x9D173F5B62E8C79CULL) + (((zobrist_int) 0xB3CFB710E7C7999CULL) << 64));
    zobrist_table[4][2][11] = (((zobrist_int) 0x2AC899D73381D8EFULL) + (((zobrist_int) 0x41F2B2F3854F639DULL) << 64));
    zobrist_table[4][2][12] = (((zobrist_int) 0xBE40D9F36AA68FDBULL) + (((zobrist_int) 0xEF65F0F8E350835FULL) << 64));
    zobrist_table[4][2][13] = (((zobrist_int) 0x896631D2FDF7F3A1ULL) + (((zobrist_int) 0xDE72428749E133B0ULL) << 64));
    zobrist_table[4][3][0] = (((zobrist_int) 0xA237B1967E12F154ULL) + (((zobrist_int) 0xCF696E8FE51F0EBAULL) << 64));
    zobrist_table[4][3][1] = (((zobrist_int) 0xE9BD00A88B77BAB0ULL) + (((zobrist_int) 0xC9E901E136F1A8ECULL) << 64));
    zobrist_table[4][3][2] = (((zobrist_int) 0x9FA16A0CC2793AB2ULL) + (((zobrist_int) 0xDC6DA46E564B7BE9ULL) << 64));
    zobrist_table[4][3][3] = (((zobrist_int) 0x1A54FEC67C68D11CULL) + (((zobrist_int) 0xC1FD9E0002311CEAULL) << 64));
    zobrist_table[4][3][4] = (((zobrist_int) 0xBAB24193FD2CF1A3ULL) + (((zobrist_int) 0x58CD091BA843A823ULL) << 64));
    zobrist_table[4][3][5] = (((zobrist_int) 0xE299D75EED02121DULL) + (((zobrist_int) 0xB573F61AF7FBC221ULL) << 64));
    zobrist_table[4][3][6] = (((zobrist_int) 0xE72C596447D1660ULL) + (((zobrist_int) 0xA01D9D308A6090CFULL) << 64));
    zobrist_table[4][3][7] = (((zobrist_int) 0x4CC3E66870B44E18ULL) + (((zobrist_int) 0xE7792A6FC285DF1AULL) << 64));
    zobrist_table[4][3][8] = (((zobrist_int) 0x19CB517BD7A6965BULL) + (((zobrist_int) 0x820D311A3A82EB36ULL) << 64));
    zobrist_table[4][3][9] = (((zobrist_int) 0x4534D94E4649DEA5ULL) + (((zobrist_int) 0x3F10C021B4CD8E8EULL) << 64));
    zobrist_table[4][3][10] = (((zobrist_int) 0x25F9672969617062ULL) + (((zobrist_int) 0x419DEF822154E354ULL) << 64));
    zobrist_table[4][3][11] = (((zobrist_int) 0x686032B831FFDFFEULL) + (((zobrist_int) 0xA14962F58F93D205ULL) << 64));
    zobrist_table[4][3][12] = (((zobrist_int) 0xE74B7FB69936EE94ULL) + (((zobrist_int) 0xEF54306F5C74033ULL) << 64));
    zobrist_table[4][3][13] = (((zobrist_int) 0xD59E3E5388644451ULL) + (((zobrist_int) 0x8265C9789BE629DBULL) << 64));
    zobrist_table[4][4][0] = (((zobrist_int) 0xF2242639261B5841ULL) + (((zobrist_int) 0x452959CF69EEEC3BULL) << 64));
    zobrist_table[4][4][1] = (((zobrist_int) 0x7AEAE92E47A066E3ULL) + (((zobrist_int) 0x4E48B720B2073B39ULL) << 64));
    zobrist_table[4][4][2] = (((zobrist_int) 0x7DC7922E445DDD25ULL) + (((zobrist_int) 0x7FAE9D4036E2F04EULL) << 64));
    zobrist_table[4][4][3] = (((zobrist_int) 0x995880FB5E209080ULL) + (((zobrist_int) 0x3DDD98597875E73FULL) << 64));
    zobrist_table[4][4][4] = (((zobrist_int) 0x2D18BE2F56A10D9BULL) + (((zobrist_int) 0xC2485EAA9B114332ULL) << 64));
    zobrist_table[4][4][5] = (((zobrist_int) 0xBD3CAA1F2E635D0DULL) + (((zobrist_int) 0x949EBA96E141CD02ULL) << 64));
    zobrist_table[4][4][6] = (((zobrist_int) 0x737C2EE5B1B536F9ULL) + (((zobrist_int) 0x264103C588E63E06ULL) << 64));
    zobrist_table[4][4][7] = (((zobrist_int) 0x8102A2410EE3B911ULL) + (((zobrist_int) 0x874A903353752BD2ULL) << 64));
    zobrist_table[4][4][8] = (((zobrist_int) 0x2293C61EB0AAE07CULL) + (((zobrist_int) 0xC2EBA580A522EEB3ULL) << 64));
    zobrist_table[4][4][9] = (((zobrist_int) 0xFD26770ACFDC3A81ULL) + (((zobrist_int) 0x36930452E439E76DULL) << 64));
    zobrist_table[4][4][10] = (((zobrist_int) 0x9F5F48B450BBD9B0ULL) + (((zobrist_int) 0x7AFBF3587E652242ULL) << 64));
    zobrist_table[4][4][11] = (((zobrist_int) 0x1E4FED4C547D9B70ULL) + (((zobrist_int) 0xE3231FE920BF8361ULL) << 64));
    zobrist_table[4][4][12] = (((zobrist_int) 0xB2C6FBD023DEB6A8ULL) + (((zobrist_int) 0x399B6C9941A7FB5FULL) << 64));
    zobrist_table[4][4][13] = (((zobrist_int) 0xA2A0929B16890D91ULL) + (((zobrist_int) 0xD43B1DD589F07848ULL) << 64));
    zobrist_table[4][5][0] = (((zobrist_int) 0xCCED50DB3F2B9A2ULL) + (((zobrist_int) 0x2C0DACC390258697ULL) << 64));
    zobrist_table[4][5][1] = (((zobrist_int) 0x1DBB2FB1AF4CDFB5ULL) + (((zobrist_int) 0x9031D49539EB63B0ULL) << 64));
    zobrist_table[4][5][2] = (((zobrist_int) 0x80C5B52F330C29C0ULL) + (((zobrist_int) 0xA8EF8120914C95D1ULL) << 64));
    zobrist_table[4][5][3] = (((zobrist_int) 0x4ED01EDFE2608A62ULL) + (((zobrist_int) 0x53E0472C6C198787ULL) << 64));
    zobrist_table[4][5][4] = (((zobrist_int) 0xC6170C370115A71DULL) + (((zobrist_int) 0xD25C806205221A0FULL) << 64));
    zobrist_table[4][5][5] = (((zobrist_int) 0xD27C3A5B4E287100ULL) + (((zobrist_int) 0x386362319D892A6DULL) << 64));
    zobrist_table[4][5][6] = (((zobrist_int) 0xBE38915F15A61486ULL) + (((zobrist_int) 0x47B963B439798287ULL) << 64));
    zobrist_table[4][5][7] = (((zobrist_int) 0xA02AC240AE41BC78ULL) + (((zobrist_int) 0xDC791848FC286E97ULL) << 64));
    zobrist_table[4][5][8] = (((zobrist_int) 0x44E20D0D57508C39ULL) + (((zobrist_int) 0xB80100CA99E43E94ULL) << 64));
    zobrist_table[4][5][9] = (((zobrist_int) 0x6118446184B7D15BULL) + (((zobrist_int) 0x1F24DF0305EB8165ULL) << 64));
    zobrist_table[4][5][10] = (((zobrist_int) 0x58D683C054700723ULL) + (((zobrist_int) 0x1D07D20C23B26AD1ULL) << 64));
    zobrist_table[4][5][11] = (((zobrist_int) 0xE60B483D4035D97CULL) + (((zobrist_int) 0x24ADEF7DC51D7956ULL) << 64));
    zobrist_table[4][5][12] = (((zobrist_int) 0x92F233A4AE634ACCULL) + (((zobrist_int) 0x58D51A050A807A90ULL) << 64));
    zobrist_table[4][5][13] = (((zobrist_int) 0x178185B813CEDB3BULL) + (((zobrist_int) 0xFFAFF116B994F614ULL) << 64));
    zobrist_table[4][6][0] = (((zobrist_int) 0x4CCBE4BF1A6BF371ULL) + (((zobrist_int) 0x3FBB550A512838D7ULL) << 64));
    zobrist_table[4][6][1] = (((zobrist_int) 0x8795A22044F34F87ULL) + (((zobrist_int) 0x5C9C18980CBD7F93ULL) << 64));
    zobrist_table[4][6][2] = (((zobrist_int) 0x140CA1A807FAC177ULL) + (((zobrist_int) 0xECFEBA262397C884ULL) << 64));
    zobrist_table[4][6][3] = (((zobrist_int) 0x5F3F23F3663A4F3AULL) + (((zobrist_int) 0xB85544CAEF0756B9ULL) << 64));
    zobrist_table[4][6][4] = (((zobrist_int) 0xB0F92F03A36CBFA7ULL) + (((zobrist_int) 0x18074AE53DF7B5A2ULL) << 64));
    zobrist_table[4][6][5] = (((zobrist_int) 0x542DA6D0ADFD295BULL) + (((zobrist_int) 0x209DA6C460CD339ULL) << 64));
    zobrist_table[4][6][6] = (((zobrist_int) 0xE3608EC683E6A37AULL) + (((zobrist_int) 0xF57DD6AB52634C8AULL) << 64));
    zobrist_table[4][6][7] = (((zobrist_int) 0x1CB9EEA1F2DC18C6ULL) + (((zobrist_int) 0xEC5F80DD5A346E04ULL) << 64));
    zobrist_table[4][6][8] = (((zobrist_int) 0xCA7E0F4BCDB64AA5ULL) + (((zobrist_int) 0xB962BA01A42538DBULL) << 64));
    zobrist_table[4][6][9] = (((zobrist_int) 0x203AFA3AD7E42F6AULL) + (((zobrist_int) 0xED5F40D09B2D537DULL) << 64));
    zobrist_table[4][6][10] = (((zobrist_int) 0x45657CB4DED18CE5ULL) + (((zobrist_int) 0x17508F8C67B8C2F8ULL) << 64));
    zobrist_table[4][6][11] = (((zobrist_int) 0x939EF122ADD31ECCULL) + (((zobrist_int) 0xB9B221639EE213B9ULL) << 64));
    zobrist_table[4][6][12] = (((zobrist_int) 0x79BFFA4687198E7AULL) + (((zobrist_int) 0x6B314E0B907F2360ULL) << 64));
    zobrist_table[4][6][13] = (((zobrist_int) 0xEF13E6958927B27DULL) + (((zobrist_int) 0x4D14935464CE2877ULL) << 64));
    zobrist_table[4][7][0] = (((zobrist_int) 0x382A1BD2E5F84260ULL) + (((zobrist_int) 0x4D7BE03FA1FA8DF8ULL) << 64));
    zobrist_table[4][7][1] = (((zobrist_int) 0x221468E58C93547AULL) + (((zobrist_int) 0x999F975C0DCEF328ULL) << 64));
    zobrist_table[4][7][2] = (((zobrist_int) 0x1C205729822EE60DULL) + (((zobrist_int) 0x3D96BFB12CD66A72ULL) << 64));
    zobrist_table[4][7][3] = (((zobrist_int) 0xE5B0FCB2370BC2FFULL) + (((zobrist_int) 0x46453B166F42BFF6ULL) << 64));
    zobrist_table[4][7][4] = (((zobrist_int) 0x51DCF528BC3D38AULL) + (((zobrist_int) 0x89F0F4A1401B0277ULL) << 64));
    zobrist_table[4][7][5] = (((zobrist_int) 0xF1E09E06455BF496ULL) + (((zobrist_int) 0x4301B66687B7ABB6ULL) << 64));
    zobrist_table[4][7][6] = (((zobrist_int) 0x204656047925DE5FULL) + (((zobrist_int) 0xB578AFA0673DD93BULL) << 64));
    zobrist_table[4][7][7] = (((zobrist_int) 0xBEB2CCA91A8F973EULL) + (((zobrist_int) 0x11AEE2975F9C3B5BULL) << 64));
    zobrist_table[4][7][8] = (((zobrist_int) 0xFA3BA057A78826D6ULL) + (((zobrist_int) 0x5CF6E7578B509F22ULL) << 64));
    zobrist_table[4][7][9] = (((zobrist_int) 0x8E3465E28B74E9F8ULL) + (((zobrist_int) 0xCDF12419D80476A6ULL) << 64));
    zobrist_table[4][7][10] = (((zobrist_int) 0x81E2021BB92136B9ULL) + (((zobrist_int) 0x94B0CD98AF413D9DULL) << 64));
    zobrist_table[4][7][11] = (((zobrist_int) 0x9E79C6E507C93091ULL) + (((zobrist_int) 0x720B6F484EE17958ULL) << 64));
    zobrist_table[4][7][12] = (((zobrist_int) 0x21D89737AEB292FBULL) + (((zobrist_int) 0x130865E427E0B98AULL) << 64));
    zobrist_table[4][7][13] = (((zobrist_int) 0x944BE91AE9D95E94ULL) + (((zobrist_int) 0xAD36DDEE24554C27ULL) << 64));
    zobrist_table[5][0][0] = (((zobrist_int) 0xD3AC07E5E10E1A45ULL) + (((zobrist_int) 0x7BEC1BCE375D5CF7ULL) << 64));
    zobrist_table[5][0][1] = (((zobrist_int) 0xCD0DFB4BD7726D00ULL) + (((zobrist_int) 0xC4731C46D9259496ULL) << 64));
    zobrist_table[5][0][2] = (((zobrist_int) 0x5D769CEA55E103E8ULL) + (((zobrist_int) 0x4AD70091E37ACA27ULL) << 64));
    zobrist_table[5][0][3] = (((zobrist_int) 0x27D5B39228E68AD3ULL) + (((zobrist_int) 0xCB8CB4BFD95F3DA0ULL) << 64));
    zobrist_table[5][0][4] = (((zobrist_int) 0xD548052B61B95AFEULL) + (((zobrist_int) 0x67D8070270915526ULL) << 64));
    zobrist_table[5][0][5] = (((zobrist_int) 0xFA0955731E2C0EF7ULL) + (((zobrist_int) 0x252820D699DB7B23ULL) << 64));
    zobrist_table[5][0][6] = (((zobrist_int) 0x4B9848D9450EB7AAULL) + (((zobrist_int) 0xAFDC47C4AAB89A16ULL) << 64));
    zobrist_table[5][0][7] = (((zobrist_int) 0xA38D1EADCCA4B02BULL) + (((zobrist_int) 0xF3FF1B4D9A8B0920ULL) << 64));
    zobrist_table[5][0][8] = (((zobrist_int) 0x898B22520218664EULL) + (((zobrist_int) 0x27B97BFF3CC3E09ULL) << 64));
    zobrist_table[5][0][9] = (((zobrist_int) 0xD0B2B05CEB70399FULL) + (((zobrist_int) 0x21F09771A49768D9ULL) << 64));
    zobrist_table[5][0][10] = (((zobrist_int) 0xBF3AA50A612753F1ULL) + (((zobrist_int) 0xF13A08998FD9949CULL) << 64));
    zobrist_table[5][0][11] = (((zobrist_int) 0x19E48393E1FFF8D3ULL) + (((zobrist_int) 0x7C6144875A3AE18ULL) << 64));
    zobrist_table[5][0][12] = (((zobrist_int) 0x6E9487C1C77AD8C8ULL) + (((zobrist_int) 0xADE3485D993B27E2ULL) << 64));
    zobrist_table[5][0][13] = (((zobrist_int) 0x46AC0CEE6C1A7DDCULL) + (((zobrist_int) 0x5EC1C3D1EEFB98A9ULL) << 64));
    zobrist_table[5][1][0] = (((zobrist_int) 0x67F86286688EED8FULL) + (((zobrist_int) 0x7644D38C9B145735ULL) << 64));
    zobrist_table[5][1][1] = (((zobrist_int) 0x19644C160DA3625DULL) + (((zobrist_int) 0xC775B3DD7883FB1EULL) << 64));
    zobrist_table[5][1][2] = (((zobrist_int) 0xA565B2450993FAB3ULL) + (((zobrist_int) 0xB2867E2FB4420D35ULL) << 64));
    zobrist_table[5][1][3] = (((zobrist_int) 0xCFEB88270026AE8BULL) + (((zobrist_int) 0xD4EE8F760AC4CF15ULL) << 64));
    zobrist_table[5][1][4] = (((zobrist_int) 0x965F47121C72BA61ULL) + (((zobrist_int) 0x87CB2D1123BB2E3AULL) << 64));
    zobrist_table[5][1][5] = (((zobrist_int) 0xC361442E82116C71ULL) + (((zobrist_int) 0x8D103FA15B35B769ULL) << 64));
    zobrist_table[5][1][6] = (((zobrist_int) 0xC86DDBCE4559EB49ULL) + (((zobrist_int) 0x9177206DFBCEC1BDULL) << 64));
    zobrist_table[5][1][7] = (((zobrist_int) 0xF7F6701DE8B437FEULL) + (((zobrist_int) 0x5B3E361BA7A50EE5ULL) << 64));
    zobrist_table[5][1][8] = (((zobrist_int) 0x79526C86CD55924FULL) + (((zobrist_int) 0xB28D8AACD1D86841ULL) << 64));
    zobrist_table[5][1][9] = (((zobrist_int) 0xED72F0113EC3AFBEULL) + (((zobrist_int) 0x9F2DC62DCEEBD5C2ULL) << 64));
    zobrist_table[5][1][10] = (((zobrist_int) 0x1B04B28C3D644B75ULL) + (((zobrist_int) 0xF3B435198FF69970ULL) << 64));
    zobrist_table[5][1][11] = (((zobrist_int) 0xDF3B2F485B935771ULL) + (((zobrist_int) 0x1DCC99FC289DE3AEULL) << 64));
    zobrist_table[5][1][12] = (((zobrist_int) 0xA635AA2C6DFEEA6ULL) + (((zobrist_int) 0xB43CE7FAEA955E0EULL) << 64));
    zobrist_table[5][1][13] = (((zobrist_int) 0x6C220D3F504E8C60ULL) + (((zobrist_int) 0xBA2ED757E1381E12ULL) << 64));
    zobrist_table[5][2][0] = (((zobrist_int) 0x40E4C61258A43D4EULL) + (((zobrist_int) 0xA032B015A8558C5DULL) << 64));
    zobrist_table[5][2][1] = (((zobrist_int) 0xE5FB1997FEEC111EULL) + (((zobrist_int) 0xEA63AA58C5A66D6BULL) << 64));
    zobrist_table[5][2][2] = (((zobrist_int) 0x9DF096D00E4034D0ULL) + (((zobrist_int) 0x6A3932EB6F53D0B3ULL) << 64));
    zobrist_table[5][2][3] = (((zobrist_int) 0x5BD6A94D60556919ULL) + (((zobrist_int) 0xC1000BEA4B3F1D20ULL) << 64));
    zobrist_table[5][2][4] = (((zobrist_int) 0x575B3DB1D0EE4266ULL) + (((zobrist_int) 0xCC564CC870E6B31EULL) << 64));
    zobrist_table[5][2][5] = (((zobrist_int) 0x3CF17EBDB3016992ULL) + (((zobrist_int) 0x9C11BED6A28AD8CCULL) << 64));
    zobrist_table[5][2][6] = (((zobrist_int) 0x24F5A90184DCE864ULL) + (((zobrist_int) 0x576C5BE30E580FFEULL) << 64));
    zobrist_table[5][2][7] = (((zobrist_int) 0x1D0E6FDEAC4C09D3ULL) + (((zobrist_int) 0x8356D01DE431AE89ULL) << 64));
    zobrist_table[5][2][8] = (((zobrist_int) 0x8B0445512C154307ULL) + (((zobrist_int) 0xA03B4B0BA48AE5E0ULL) << 64));
    zobrist_table[5][2][9] = (((zobrist_int) 0xE4F882777CC8D334ULL) + (((zobrist_int) 0xC1E9E3BE574AC3FAULL) << 64));
    zobrist_table[5][2][10] = (((zobrist_int) 0x1F197477B5DE8693ULL) + (((zobrist_int) 0x953122A4F9A6A3ACULL) << 64));
    zobrist_table[5][2][11] = (((zobrist_int) 0x7AF20E3F058BD113ULL) + (((zobrist_int) 0x358F0EFBE5B5D483ULL) << 64));
    zobrist_table[5][2][12] = (((zobrist_int) 0xA1B0B3A8621BED79ULL) + (((zobrist_int) 0xF3FDFBE3D57715F1ULL) << 64));
    zobrist_table[5][2][13] = (((zobrist_int) 0x65B1D2302CB9E2BBULL) + (((zobrist_int) 0x3A5163F4B7728BF8ULL) << 64));
    zobrist_table[5][3][0] = (((zobrist_int) 0x3F941EF51985B59FULL) + (((zobrist_int) 0xF991639555EA8C2BULL) << 64));
    zobrist_table[5][3][1] = (((zobrist_int) 0x543C859BF84BEF6BULL) + (((zobrist_int) 0x3EC39C4FA817F426ULL) << 64));
    zobrist_table[5][3][2] = (((zobrist_int) 0xAD429A2BC8D68C82ULL) + (((zobrist_int) 0xBE3455C876181CC4ULL) << 64));
    zobrist_table[5][3][3] = (((zobrist_int) 0x5E9AD1E6789E6608ULL) + (((zobrist_int) 0xA6C404447E1CAE65ULL) << 64));
    zobrist_table[5][3][4] = (((zobrist_int) 0xA9C6057CC5ED8155ULL) + (((zobrist_int) 0xEFD01861B926E626ULL) << 64));
    zobrist_table[5][3][5] = (((zobrist_int) 0x6E96F9B8319AC940ULL) + (((zobrist_int) 0x661B8E2670CB730CULL) << 64));
    zobrist_table[5][3][6] = (((zobrist_int) 0x1ED334D08AC21475ULL) + (((zobrist_int) 0x7CFFC46C924925D4ULL) << 64));
    zobrist_table[5][3][7] = (((zobrist_int) 0x443681BCED40DC4DULL) + (((zobrist_int) 0x200E1425D6F9ABCDULL) << 64));
    zobrist_table[5][3][8] = (((zobrist_int) 0x30EA6ED265E9DEDULL) + (((zobrist_int) 0x6A24578260497284ULL) << 64));
    zobrist_table[5][3][9] = (((zobrist_int) 0xCC8BDD031BE59F38ULL) + (((zobrist_int) 0xA703CAEF06B69AB4ULL) << 64));
    zobrist_table[5][3][10] = (((zobrist_int) 0xF0FC4B47131810BFULL) + (((zobrist_int) 0x7573BB6C2ED6D44CULL) << 64));
    zobrist_table[5][3][11] = (((zobrist_int) 0x6084377CC41DA245ULL) + (((zobrist_int) 0x8085B157AACF05F8ULL) << 64));
    zobrist_table[5][3][12] = (((zobrist_int) 0xD0A01524CC4145BFULL) + (((zobrist_int) 0xEAFF520B49DB5C12ULL) << 64));
    zobrist_table[5][3][13] = (((zobrist_int) 0x277F761727CF91FBULL) + (((zobrist_int) 0x864C68F6F8DB903AULL) << 64));
    zobrist_table[5][4][0] = (((zobrist_int) 0x1B1174FAD3765E6DULL) + (((zobrist_int) 0x412CB34EF2604F52ULL) << 64));
    zobrist_table[5][4][1] = (((zobrist_int) 0x76E4F7EF04CF3AC5ULL) + (((zobrist_int) 0xCF95442D658422B2ULL) << 64));
    zobrist_table[5][4][2] = (((zobrist_int) 0xB466120DA240998EULL) + (((zobrist_int) 0xCAFDFD7EBC6F6237ULL) << 64));
    zobrist_table[5][4][3] = (((zobrist_int) 0x3A763BF0E9A3788DULL) + (((zobrist_int) 0xB20CCDB089A8CA7EULL) << 64));
    zobrist_table[5][4][4] = (((zobrist_int) 0xFDDCCADA640AF86CULL) + (((zobrist_int) 0x8B4BAE04015CEA36ULL) << 64));
    zobrist_table[5][4][5] = (((zobrist_int) 0x3FDD8D5ECDC9FB5EULL) + (((zobrist_int) 0x6C47C6D9FB6EB3A5ULL) << 64));
    zobrist_table[5][4][6] = (((zobrist_int) 0x28ADFDB0E8414D8DULL) + (((zobrist_int) 0x2DD66631A98A6DDCULL) << 64));
    zobrist_table[5][4][7] = (((zobrist_int) 0xA99343B657AC78D0ULL) + (((zobrist_int) 0x13787E133D38F38EULL) << 64));
    zobrist_table[5][4][8] = (((zobrist_int) 0x894ECB0DC667B0A8ULL) + (((zobrist_int) 0x8ECFAFE3EF784C8FULL) << 64));
    zobrist_table[5][4][9] = (((zobrist_int) 0x2933EB1CF5D7EE4DULL) + (((zobrist_int) 0x602CC7092CF49AE2ULL) << 64));
    zobrist_table[5][4][10] = (((zobrist_int) 0x585D23F95D9AD91ULL) + (((zobrist_int) 0x37845506835BB805ULL) << 64));
    zobrist_table[5][4][11] = (((zobrist_int) 0x3C5467166D6BBC9CULL) + (((zobrist_int) 0xA5B4C90CB5DD810ULL) << 64));
    zobrist_table[5][4][12] = (((zobrist_int) 0x84026D89EF8F6F23ULL) + (((zobrist_int) 0x30B3858EB9810331ULL) << 64));
    zobrist_table[5][4][13] = (((zobrist_int) 0x81081239B3473EA3ULL) + (((zobrist_int) 0x9CA354D6B0CC1CECULL) << 64));
    zobrist_table[5][5][0] = (((zobrist_int) 0xFF8AA933A74F7DFFULL) + (((zobrist_int) 0x13C4BE398968B582ULL) << 64));
    zobrist_table[5][5][1] = (((zobrist_int) 0x65EE04653F77675BULL) + (((zobrist_int) 0x7706C34AC78BCE5BULL) << 64));
    zobrist_table[5][5][2] = (((zobrist_int) 0x9127BD471E7CE857ULL) + (((zobrist_int) 0xC607FE9A4D5DAF8ULL) << 64));
    zobrist_table[5][5][3] = (((zobrist_int) 0x16F59E48631199DAULL) + (((zobrist_int) 0x18371C678F59B481ULL) << 64));
    zobrist_table[5][5][4] = (((zobrist_int) 0xD0A40D77A4352C10ULL) + (((zobrist_int) 0xB83C7057A9ABB94ULL) << 64));
    zobrist_table[5][5][5] = (((zobrist_int) 0x84BAED6FFA646036ULL) + (((zobrist_int) 0xC700C80C3D3BC16BULL) << 64));
    zobrist_table[5][5][6] = (((zobrist_int) 0x5567EF4031D76D8ULL) + (((zobrist_int) 0xDBF9FB74F48BC982ULL) << 64));
    zobrist_table[5][5][7] = (((zobrist_int) 0x7767E9C34FDFBCF9ULL) + (((zobrist_int) 0xB9126CEA472FC3B4ULL) << 64));
    zobrist_table[5][5][8] = (((zobrist_int) 0x2AACBA426A6213E1ULL) + (((zobrist_int) 0x22197C77984FBD65ULL) << 64));
    zobrist_table[5][5][9] = (((zobrist_int) 0x8FC947F3FC72011FULL) + (((zobrist_int) 0xD3A4278BB5205660ULL) << 64));
    zobrist_table[5][5][10] = (((zobrist_int) 0xC545FF88517D6EFDULL) + (((zobrist_int) 0xA2F1CFC988E154AAULL) << 64));
    zobrist_table[5][5][11] = (((zobrist_int) 0xFDF9117B72DD0D77ULL) + (((zobrist_int) 0xCD9454E380680348ULL) << 64));
    zobrist_table[5][5][12] = (((zobrist_int) 0x8DC7238E6AE85EFAULL) + (((zobrist_int) 0xB2E9ED252AE90104ULL) << 64));
    zobrist_table[5][5][13] = (((zobrist_int) 0xB2D3D8F8653E7187ULL) + (((zobrist_int) 0xCEF1BDF6639B57DDULL) << 64));
    zobrist_table[5][6][0] = (((zobrist_int) 0x7ED224ED3362591EULL) + (((zobrist_int) 0x47473C91D121950DULL) << 64));
    zobrist_table[5][6][1] = (((zobrist_int) 0xED9D7DCB5C285D6DULL) + (((zobrist_int) 0x426B7D5726C7CFE5ULL) << 64));
    zobrist_table[5][6][2] = (((zobrist_int) 0x478C8B5F911EACE3ULL) + (((zobrist_int) 0x2CD71C4AD847A872ULL) << 64));
    zobrist_table[5][6][3] = (((zobrist_int) 0xB890B6A2C7D2D9B2ULL) + (((zobrist_int) 0x156AF8409F3E07EEULL) << 64));
    zobrist_table[5][6][4] = (((zobrist_int) 0x5C4B4649BB254E83ULL) + (((zobrist_int) 0xEDA92BB4560B9AD2ULL) << 64));
    zobrist_table[5][6][5] = (((zobrist_int) 0x422AFD572488BCE5ULL) + (((zobrist_int) 0x40950A0341485039ULL) << 64));
    zobrist_table[5][6][6] = (((zobrist_int) 0x625F0520596F3D85ULL) + (((zobrist_int) 0x90C28C8D47754F9BULL) << 64));
    zobrist_table[5][6][7] = (((zobrist_int) 0x372A69B77BF362FULL) + (((zobrist_int) 0xF42FE1B42626FB92ULL) << 64));
    zobrist_table[5][6][8] = (((zobrist_int) 0xF574C6332158D607ULL) + (((zobrist_int) 0x39D5976440B282F6ULL) << 64));
    zobrist_table[5][6][9] = (((zobrist_int) 0x1209A614324E10E6ULL) + (((zobrist_int) 0x94500102CD3C409BULL) << 64));
    zobrist_table[5][6][10] = (((zobrist_int) 0x9E5133BE899D52EAULL) + (((zobrist_int) 0x8B02D63632CB13FAULL) << 64));
    zobrist_table[5][6][11] = (((zobrist_int) 0xB752F9C66DE12C08ULL) + (((zobrist_int) 0x3D6566B5DF35DBDEULL) << 64));
    zobrist_table[5][6][12] = (((zobrist_int) 0x23A2258F93DE63D6ULL) + (((zobrist_int) 0x75E3944E8DCD5310ULL) << 64));
    zobrist_table[5][6][13] = (((zobrist_int) 0xB626AD95642D6BD6ULL) + (((zobrist_int) 0x152349B832226707ULL) << 64));
    zobrist_table[5][7][0] = (((zobrist_int) 0xEF4B73D7A01A8C21ULL) + (((zobrist_int) 0x27304C5F13C01044ULL) << 64));
    zobrist_table[5][7][1] = (((zobrist_int) 0xAAD3FCF4C943BE93ULL) + (((zobrist_int) 0x7BF29B50EB9F2EFULL) << 64));
    zobrist_table[5][7][2] = (((zobrist_int) 0x67C779BBBF109E08ULL) + (((zobrist_int) 0x6AD12A0F61F3FBC8ULL) << 64));
    zobrist_table[5][7][3] = (((zobrist_int) 0x23303B1BAEB2841DULL) + (((zobrist_int) 0x98CEB485974C214FULL) << 64));
    zobrist_table[5][7][4] = (((zobrist_int) 0xAC354CDD2111A822ULL) + (((zobrist_int) 0x8BDD915D89DB4616ULL) << 64));
    zobrist_table[5][7][5] = (((zobrist_int) 0xED6E472512FCA4EDULL) + (((zobrist_int) 0xD994539A3DC07BBBULL) << 64));
    zobrist_table[5][7][6] = (((zobrist_int) 0x23B17DE061B50DCDULL) + (((zobrist_int) 0x33D141724921BEF4ULL) << 64));
    zobrist_table[5][7][7] = (((zobrist_int) 0xB80A5424A9690F96ULL) + (((zobrist_int) 0x65AD563CFCA132AAULL) << 64));
    zobrist_table[5][7][8] = (((zobrist_int) 0xBFC247155B5B46B3ULL) + (((zobrist_int) 0x2DA54A07D6AE4CAEULL) << 64));
    zobrist_table[5][7][9] = (((zobrist_int) 0x4C3F529739A01C4FULL) + (((zobrist_int) 0x24D03617B596B597ULL) << 64));
    zobrist_table[5][7][10] = (((zobrist_int) 0x7DFBBB5A590433BDULL) + (((zobrist_int) 0x4AB15FEE890D9238ULL) << 64));
    zobrist_table[5][7][11] = (((zobrist_int) 0x83A828E216AD6632ULL) + (((zobrist_int) 0x4C87032CD3CD6BB8ULL) << 64));
    zobrist_table[5][7][12] = (((zobrist_int) 0xB493C84235763838ULL) + (((zobrist_int) 0x59B5C7776A4D6E5ULL) << 64));
    zobrist_table[5][7][13] = (((zobrist_int) 0xCCF03C364A50D337ULL) + (((zobrist_int) 0x9F40007ECF6975F7ULL) << 64));
    zobrist_table[6][0][0] = (((zobrist_int) 0x1A60C5C697B449D5ULL) + (((zobrist_int) 0x5F64D5B09D7CC285ULL) << 64));
    zobrist_table[6][0][1] = (((zobrist_int) 0x718F4FB3C13733AAULL) + (((zobrist_int) 0x9E4CD6034140E6B1ULL) << 64));
    zobrist_table[6][0][2] = (((zobrist_int) 0xD5419000EE95A3AULL) + (((zobrist_int) 0xC80035E4D41C3466ULL) << 64));
    zobrist_table[6][0][3] = (((zobrist_int) 0x28EF543B50CB7FC0ULL) + (((zobrist_int) 0x21E2ED95CFF10031ULL) << 64));
    zobrist_table[6][0][4] = (((zobrist_int) 0xEC5EEB42F4E65212ULL) + (((zobrist_int) 0xD266B00AA112AD73ULL) << 64));
    zobrist_table[6][0][5] = (((zobrist_int) 0x1CCDF61B1A71580DULL) + (((zobrist_int) 0x6F6F545BDA9EE69BULL) << 64));
    zobrist_table[6][0][6] = (((zobrist_int) 0x9624D494A228587AULL) + (((zobrist_int) 0xBEA29CB93EF34007ULL) << 64));
    zobrist_table[6][0][7] = (((zobrist_int) 0x811580BC353719FDULL) + (((zobrist_int) 0x6596256981FA0627ULL) << 64));
    zobrist_table[6][0][8] = (((zobrist_int) 0xE982148C1F1EF074ULL) + (((zobrist_int) 0xFC570DD0E7F0EE9CULL) << 64));
    zobrist_table[6][0][9] = (((zobrist_int) 0x3651174BB53674FFULL) + (((zobrist_int) 0xF27CFA11D1BC7A14ULL) << 64));
    zobrist_table[6][0][10] = (((zobrist_int) 0xA92DAEA262420FD3ULL) + (((zobrist_int) 0x84774C41EC5643F2ULL) << 64));
    zobrist_table[6][0][11] = (((zobrist_int) 0xD05B490A224ADC1FULL) + (((zobrist_int) 0x940EA61AB75C29D5ULL) << 64));
    zobrist_table[6][0][12] = (((zobrist_int) 0xB99E0DB7412DBABBULL) + (((zobrist_int) 0xB7BBE1D600EE0092ULL) << 64));
    zobrist_table[6][0][13] = (((zobrist_int) 0xCF019ED91EF2BE2AULL) + (((zobrist_int) 0xFC741D8C339863EFULL) << 64));
    zobrist_table[6][1][0] = (((zobrist_int) 0x900DF18DC36A9864ULL) + (((zobrist_int) 0xA9BDB4EE60C7E1D7ULL) << 64));
    zobrist_table[6][1][1] = (((zobrist_int) 0x8B84E5417B665C24ULL) + (((zobrist_int) 0x3B0D11399D13B2FBULL) << 64));
    zobrist_table[6][1][2] = (((zobrist_int) 0x9A73B97448563F0ULL) + (((zobrist_int) 0x2AF346E9A3706225ULL) << 64));
    zobrist_table[6][1][3] = (((zobrist_int) 0xABAC4A78ABEC2357ULL) + (((zobrist_int) 0x8DEB1729EBDED950ULL) << 64));
    zobrist_table[6][1][4] = (((zobrist_int) 0x3BAD948580BBE14EULL) + (((zobrist_int) 0x6912CC4ADAF4081BULL) << 64));
    zobrist_table[6][1][5] = (((zobrist_int) 0x46108B43F7BE93AFULL) + (((zobrist_int) 0xA960B700C4D6547FULL) << 64));
    zobrist_table[6][1][6] = (((zobrist_int) 0x66071F0B6BD33A6BULL) + (((zobrist_int) 0x7E7534D945A077D6ULL) << 64));
    zobrist_table[6][1][7] = (((zobrist_int) 0xAB5646E11904F4CDULL) + (((zobrist_int) 0xD5734E1AD4BE2C52ULL) << 64));
    zobrist_table[6][1][8] = (((zobrist_int) 0x2FC87104212D7797ULL) + (((zobrist_int) 0x41026058F3C3CD2ULL) << 64));
    zobrist_table[6][1][9] = (((zobrist_int) 0xC0F842057434CDAAULL) + (((zobrist_int) 0x7D0B6DA50B7B0E03ULL) << 64));
    zobrist_table[6][1][10] = (((zobrist_int) 0x64D94B3E36DED715ULL) + (((zobrist_int) 0xBAE95D91D2A959A4ULL) << 64));
    zobrist_table[6][1][11] = (((zobrist_int) 0xD285402189E598BAULL) + (((zobrist_int) 0x561478E4ECA5205FULL) << 64));
    zobrist_table[6][1][12] = (((zobrist_int) 0x3E54D185E870FBAFULL) + (((zobrist_int) 0x13BDB673181230AEULL) << 64));
    zobrist_table[6][1][13] = (((zobrist_int) 0xBF001E3EAD99103BULL) + (((zobrist_int) 0xD8ADE43D0AEBA562ULL) << 64));
    zobrist_table[6][2][0] = (((zobrist_int) 0xD57184186C33E05DULL) + (((zobrist_int) 0x30549CC9711829AFULL) << 64));
    zobrist_table[6][2][1] = (((zobrist_int) 0x2C5836B8F4F59C8CULL) + (((zobrist_int) 0x808312489866BA58ULL) << 64));
    zobrist_table[6][2][2] = (((zobrist_int) 0xD8EBC32D30A3E121ULL) + (((zobrist_int) 0x62827E2B827ECCA2ULL) << 64));
    zobrist_table[6][2][3] = (((zobrist_int) 0x5C4CC59D859693E9ULL) + (((zobrist_int) 0x3B93712832737AF7ULL) << 64));
    zobrist_table[6][2][4] = (((zobrist_int) 0xA89C4B655C175A9AULL) + (((zobrist_int) 0x9607CF15E0A37D11ULL) << 64));
    zobrist_table[6][2][5] = (((zobrist_int) 0xC1D431FFFB41ADADULL) + (((zobrist_int) 0xFC0AFBB1C6E0B5E5ULL) << 64));
    zobrist_table[6][2][6] = (((zobrist_int) 0x574E358910832BB7ULL) + (((zobrist_int) 0xD42AA6EE7E788B8ULL) << 64));
    zobrist_table[6][2][7] = (((zobrist_int) 0xB50AD7F755D9916ULL) + (((zobrist_int) 0x9C50E95FD584B246ULL) << 64));
    zobrist_table[6][2][8] = (((zobrist_int) 0xE42AC3222D417214ULL) + (((zobrist_int) 0xDA92657B25CEA933ULL) << 64));
    zobrist_table[6][2][9] = (((zobrist_int) 0xF0439594E81B04E3ULL) + (((zobrist_int) 0x781A9DA049181060ULL) << 64));
    zobrist_table[6][2][10] = (((zobrist_int) 0x9554A0B30B05AE32ULL) + (((zobrist_int) 0x109BAD308044B1FBULL) << 64));
    zobrist_table[6][2][11] = (((zobrist_int) 0xDDB001B7FD95E4F1ULL) + (((zobrist_int) 0x90C05631D5E3337CULL) << 64));
    zobrist_table[6][2][12] = (((zobrist_int) 0x178C53966573E4BFULL) + (((zobrist_int) 0x6662BEC8FE3A0F38ULL) << 64));
    zobrist_table[6][2][13] = (((zobrist_int) 0x8300089ACBF293E6ULL) + (((zobrist_int) 0x928B7F14D791A0FEULL) << 64));
    zobrist_table[6][3][0] = (((zobrist_int) 0x4D21E937A56743ECULL) + (((zobrist_int) 0x44963FF364F62CDEULL) << 64));
    zobrist_table[6][3][1] = (((zobrist_int) 0x5A29396EE7DC97F6ULL) + (((zobrist_int) 0xF605A1C1787B281CULL) << 64));
    zobrist_table[6][3][2] = (((zobrist_int) 0xC90C7BCEF44B596ULL) + (((zobrist_int) 0xF299414D8D5C64D7ULL) << 64));
    zobrist_table[6][3][3] = (((zobrist_int) 0xDF2C10D0E8EC6B3CULL) + (((zobrist_int) 0x47601E47A26EC1FULL) << 64));
    zobrist_table[6][3][4] = (((zobrist_int) 0x4DFAA7976D44209DULL) + (((zobrist_int) 0xBFBAF77D96B3E241ULL) << 64));
    zobrist_table[6][3][5] = (((zobrist_int) 0xCB938EBF513B4224ULL) + (((zobrist_int) 0x989BD675263EEC0BULL) << 64));
    zobrist_table[6][3][6] = (((zobrist_int) 0x8E45661296DE7DB5ULL) + (((zobrist_int) 0xFF33A69BD9D8B4BAULL) << 64));
    zobrist_table[6][3][7] = (((zobrist_int) 0x10DCA628471C583AULL) + (((zobrist_int) 0x9B6E4823DD720B14ULL) << 64));
    zobrist_table[6][3][8] = (((zobrist_int) 0xCA769E0AC9814899ULL) + (((zobrist_int) 0x5C69467EC692B163ULL) << 64));
    zobrist_table[6][3][9] = (((zobrist_int) 0x641997426A45F8D3ULL) + (((zobrist_int) 0x8513E54EFFAE81DCULL) << 64));
    zobrist_table[6][3][10] = (((zobrist_int) 0x60CA48CCA76FF1DULL) + (((zobrist_int) 0x94EC71A6935DB824ULL) << 64));
    zobrist_table[6][3][11] = (((zobrist_int) 0x974BA911D0EFD5FULL) + (((zobrist_int) 0x87908BA192E59274ULL) << 64));
    zobrist_table[6][3][12] = (((zobrist_int) 0x19D60F4203AE7C81ULL) + (((zobrist_int) 0x5500E973E6F7261BULL) << 64));
    zobrist_table[6][3][13] = (((zobrist_int) 0xEED175405631CA9FULL) + (((zobrist_int) 0xC012C0AC5E4BD956ULL) << 64));
    zobrist_table[6][4][0] = (((zobrist_int) 0x8D278868D06AE30ULL) + (((zobrist_int) 0x5EC2A92CA330D7B0ULL) << 64));
    zobrist_table[6][4][1] = (((zobrist_int) 0x12FC552E952D99F7ULL) + (((zobrist_int) 0xE56EFD237C240F10ULL) << 64));
    zobrist_table[6][4][2] = (((zobrist_int) 0x1571620CA2651AF5ULL) + (((zobrist_int) 0x8A22739BD8DE50A0ULL) << 64));
    zobrist_table[6][4][3] = (((zobrist_int) 0x55A0AB16723AC775ULL) + (((zobrist_int) 0xEB4A6DC2800533ACULL) << 64));
    zobrist_table[6][4][4] = (((zobrist_int) 0x8B49284DCF72E552ULL) + (((zobrist_int) 0xEC2F23E100DF3854ULL) << 64));
    zobrist_table[6][4][5] = (((zobrist_int) 0xE8EC6597292452B2ULL) + (((zobrist_int) 0x5C60BF3E53352971ULL) << 64));
    zobrist_table[6][4][6] = (((zobrist_int) 0x2569AA4536C499D2ULL) + (((zobrist_int) 0x94883BA1E560E869ULL) << 64));
    zobrist_table[6][4][7] = (((zobrist_int) 0x96EF069B25F17F9AULL) + (((zobrist_int) 0x676B00EC1B9E778DULL) << 64));
    zobrist_table[6][4][8] = (((zobrist_int) 0xDDE63F075134151EULL) + (((zobrist_int) 0x6BBD6A3C823647D0ULL) << 64));
    zobrist_table[6][4][9] = (((zobrist_int) 0x5C2B12ECD24C91C6ULL) + (((zobrist_int) 0x57670D2FFEE2FD5EULL) << 64));
    zobrist_table[6][4][10] = (((zobrist_int) 0x42808849DA1421B3ULL) + (((zobrist_int) 0x5E5504189BDCC7F7ULL) << 64));
    zobrist_table[6][4][11] = (((zobrist_int) 0xB6006F1209A0472EULL) + (((zobrist_int) 0xC47E1BCD103F3569ULL) << 64));
    zobrist_table[6][4][12] = (((zobrist_int) 0x3F2457CDA177EB6EULL) + (((zobrist_int) 0xCA597DECD1E3CE9BULL) << 64));
    zobrist_table[6][4][13] = (((zobrist_int) 0xC12D512F43F89EEDULL) + (((zobrist_int) 0x65A4FE7EF81EBCB8ULL) << 64));
    zobrist_table[6][5][0] = (((zobrist_int) 0x48AAC7B68CE62EBDULL) + (((zobrist_int) 0xC92C3F4592E2AB5AULL) << 64));
    zobrist_table[6][5][1] = (((zobrist_int) 0x155EFA9F9E5E018BULL) + (((zobrist_int) 0xB56703D7132D93A4ULL) << 64));
    zobrist_table[6][5][2] = (((zobrist_int) 0xE786BA332B9E8E92ULL) + (((zobrist_int) 0xF3D05037EFAA4C5CULL) << 64));
    zobrist_table[6][5][3] = (((zobrist_int) 0x69EEAB4A446D7598ULL) + (((zobrist_int) 0x20539F511552B161ULL) << 64));
    zobrist_table[6][5][4] = (((zobrist_int) 0x8D0389DD484D4356ULL) + (((zobrist_int) 0xA41FC4A8B9E4B758ULL) << 64));
    zobrist_table[6][5][5] = (((zobrist_int) 0x3C1F3ADF43476C2AULL) + (((zobrist_int) 0x194CA67D35E8AE21ULL) << 64));
    zobrist_table[6][5][6] = (((zobrist_int) 0xB8C1A06046F1F3C1ULL) + (((zobrist_int) 0xC0FD5B57AFCE949ULL) << 64));
    zobrist_table[6][5][7] = (((zobrist_int) 0x831C27CEBCD00477ULL) + (((zobrist_int) 0xC99305C84D238065ULL) << 64));
    zobrist_table[6][5][8] = (((zobrist_int) 0xCF9034ADDF9E5384ULL) + (((zobrist_int) 0x343353B0F9D36E2EULL) << 64));
    zobrist_table[6][5][9] = (((zobrist_int) 0x8B2DB754D26FAA2AULL) + (((zobrist_int) 0x8CFB8251133B6BABULL) << 64));
    zobrist_table[6][5][10] = (((zobrist_int) 0x56F44F8150C1E48AULL) + (((zobrist_int) 0x4BC9AFD3ED004C2CULL) << 64));
    zobrist_table[6][5][11] = (((zobrist_int) 0x8423FA5BDC009DA5ULL) + (((zobrist_int) 0x9064139221CE34EULL) << 64));
    zobrist_table[6][5][12] = (((zobrist_int) 0xD06AE58771359D55ULL) + (((zobrist_int) 0xCC8EF3A15D2B5496ULL) << 64));
    zobrist_table[6][5][13] = (((zobrist_int) 0x98BBBBFBF5A2C0EULL) + (((zobrist_int) 0xFD41A332075983CFULL) << 64));
    zobrist_table[6][6][0] = (((zobrist_int) 0x6AE1043650C3192CULL) + (((zobrist_int) 0x29EF95E9BFF18E2DULL) << 64));
    zobrist_table[6][6][1] = (((zobrist_int) 0x8E979917E309EC61ULL) + (((zobrist_int) 0xB4F5FDBA0A667CF5ULL) << 64));
    zobrist_table[6][6][2] = (((zobrist_int) 0xB3BA5D0E969E5481ULL) + (((zobrist_int) 0xA12251BDA9E23FE1ULL) << 64));
    zobrist_table[6][6][3] = (((zobrist_int) 0x869F0A4BDF777AC9ULL) + (((zobrist_int) 0x2F32EBDB6CB13CD1ULL) << 64));
    zobrist_table[6][6][4] = (((zobrist_int) 0xE7371F87F919C8B5ULL) + (((zobrist_int) 0x3B9B56AE328A7F0CULL) << 64));
    zobrist_table[6][6][5] = (((zobrist_int) 0x966295991D61153AULL) + (((zobrist_int) 0xF949A9F1214AA97CULL) << 64));
    zobrist_table[6][6][6] = (((zobrist_int) 0x8198F9CC96338789ULL) + (((zobrist_int) 0xB8B72AA91F5842A6ULL) << 64));
    zobrist_table[6][6][7] = (((zobrist_int) 0x7555560B443FB052ULL) + (((zobrist_int) 0xC80A69283240D337ULL) << 64));
    zobrist_table[6][6][8] = (((zobrist_int) 0x5C7E94520E27B9D9ULL) + (((zobrist_int) 0x74C472BBF65EBFFCULL) << 64));
    zobrist_table[6][6][9] = (((zobrist_int) 0xED53BDA455BDAB5FULL) + (((zobrist_int) 0x9D4F9A42F6C9BCB7ULL) << 64));
    zobrist_table[6][6][10] = (((zobrist_int) 0x5ACC5117B925DD5AULL) + (((zobrist_int) 0xECF50B6E3842CBF3ULL) << 64));
    zobrist_table[6][6][11] = (((zobrist_int) 0xA2A9908CEEBB6118ULL) + (((zobrist_int) 0x39238450264E491ULL) << 64));
    zobrist_table[6][6][12] = (((zobrist_int) 0x7D1E2AFFFB4DBAFDULL) + (((zobrist_int) 0x2A156E4708427A40ULL) << 64));
    zobrist_table[6][6][13] = (((zobrist_int) 0xE6103B1E40D924ADULL) + (((zobrist_int) 0xA34C4498D4D1138ULL) << 64));
    zobrist_table[6][7][0] = (((zobrist_int) 0x3AE725910259794AULL) + (((zobrist_int) 0xE32A9E7BC3C42754ULL) << 64));
    zobrist_table[6][7][1] = (((zobrist_int) 0x8638C26B15ABE5B8ULL) + (((zobrist_int) 0x2C5E6907D12C9226ULL) << 64));
    zobrist_table[6][7][2] = (((zobrist_int) 0xF22343EF08FC9944ULL) + (((zobrist_int) 0x3343B7A587355806ULL) << 64));
    zobrist_table[6][7][3] = (((zobrist_int) 0x7167C7B9359DA954ULL) + (((zobrist_int) 0x3E3696CC49EC713DULL) << 64));
    zobrist_table[6][7][4] = (((zobrist_int) 0x81823D607D9062F5ULL) + (((zobrist_int) 0x532C97355F12A09DULL) << 64));
    zobrist_table[6][7][5] = (((zobrist_int) 0xF1C75FDF6458CE09ULL) + (((zobrist_int) 0x12CF7BEEA7473852ULL) << 64));
    zobrist_table[6][7][6] = (((zobrist_int) 0x98255BB431FB56FAULL) + (((zobrist_int) 0x3001B9142E76DD6CULL) << 64));
    zobrist_table[6][7][7] = (((zobrist_int) 0x9F80BE13AF347213ULL) + (((zobrist_int) 0xF4965F1F4C05C1FBULL) << 64));
    zobrist_table[6][7][8] = (((zobrist_int) 0x94CD826DEED626A7ULL) + (((zobrist_int) 0x9D1907E26D1E121DULL) << 64));
    zobrist_table[6][7][9] = (((zobrist_int) 0x5D0CD9E4795972A8ULL) + (((zobrist_int) 0x7CC251AA05EE7C39ULL) << 64));
    zobrist_table[6][7][10] = (((zobrist_int) 0xEE16CA5A0549AE39ULL) + (((zobrist_int) 0xA8BE977A1AD21096ULL) << 64));
    zobrist_table[6][7][11] = (((zobrist_int) 0x93F57068A02929ADULL) + (((zobrist_int) 0x9EA90005AA1F8452ULL) << 64));
    zobrist_table[6][7][12] = (((zobrist_int) 0xD88E5847F3C33813ULL) + (((zobrist_int) 0xD3CAEAFB6EB65112ULL) << 64));
    zobrist_table[6][7][13] = (((zobrist_int) 0x950ADE47B529E5F5ULL) + (((zobrist_int) 0x56C1858A57F64F4DULL) << 64));
    zobrist_table[7][0][0] = (((zobrist_int) 0xA59D054B12F5B904ULL) + (((zobrist_int) 0x31FEC1FE6B91461DULL) << 64));
    zobrist_table[7][0][1] = (((zobrist_int) 0x83A40773B39DA6E1ULL) + (((zobrist_int) 0x7E8CD540CDE19CD2ULL) << 64));
    zobrist_table[7][0][2] = (((zobrist_int) 0xD78C1A16F3B53254ULL) + (((zobrist_int) 0x9BA2540ED5094917ULL) << 64));
    zobrist_table[7][0][3] = (((zobrist_int) 0xA9122A069049084DULL) + (((zobrist_int) 0xF09935708CE4C8E6ULL) << 64));
    zobrist_table[7][0][4] = (((zobrist_int) 0xDAE958F88047C621ULL) + (((zobrist_int) 0x999775E47A446BB9ULL) << 64));
    zobrist_table[7][0][5] = (((zobrist_int) 0xBD06A949AE34B1A8ULL) + (((zobrist_int) 0xE7BC539393617CCEULL) << 64));
    zobrist_table[7][0][6] = (((zobrist_int) 0xC49C1282DB6EF511ULL) + (((zobrist_int) 0x9A8D945773380F5AULL) << 64));
    zobrist_table[7][0][7] = (((zobrist_int) 0x2A5615F6789EEB58ULL) + (((zobrist_int) 0x44AD2C4BD5032625ULL) << 64));
    zobrist_table[7][0][8] = (((zobrist_int) 0xD1C44202ACF67F8DULL) + (((zobrist_int) 0x4D30841886426BAAULL) << 64));
    zobrist_table[7][0][9] = (((zobrist_int) 0xC3D3561F903E07B5ULL) + (((zobrist_int) 0x657C11BFCE429EDDULL) << 64));
    zobrist_table[7][0][10] = (((zobrist_int) 0x8A2A70579B7D630DULL) + (((zobrist_int) 0x4160EDE64257AE5BULL) << 64));
    zobrist_table[7][0][11] = (((zobrist_int) 0x3C1412D4F6C1972ULL) + (((zobrist_int) 0xC1E335A69AC7640DULL) << 64));
    zobrist_table[7][0][12] = (((zobrist_int) 0xC82B9CA50BBCB351ULL) + (((zobrist_int) 0x7521269B7523B960ULL) << 64));
    zobrist_table[7][0][13] = (((zobrist_int) 0x5B047C42E454021AULL) + (((zobrist_int) 0x820B49F83B6DC6ABULL) << 64));
    zobrist_table[7][1][0] = (((zobrist_int) 0x358AB2CB71B435FFULL) + (((zobrist_int) 0x79DB1796B312BB95ULL) << 64));
    zobrist_table[7][1][1] = (((zobrist_int) 0x55E951C5ECEDD0C8ULL) + (((zobrist_int) 0xFD0E423CB23EF624ULL) << 64));
    zobrist_table[7][1][2] = (((zobrist_int) 0x2513EA80A0366B60ULL) + (((zobrist_int) 0xDCC1AFB66246F0BFULL) << 64));
    zobrist_table[7][1][3] = (((zobrist_int) 0xDE357AD6FF6C730ULL) + (((zobrist_int) 0x1C790ECFA456A270ULL) << 64));
    zobrist_table[7][1][4] = (((zobrist_int) 0xDF1CA14A5B37C7A2ULL) + (((zobrist_int) 0xEA5F0E71C8ED5301ULL) << 64));
    zobrist_table[7][1][5] = (((zobrist_int) 0x417C64670218C7D8ULL) + (((zobrist_int) 0x8A85FEFFC05CE7B5ULL) << 64));
    zobrist_table[7][1][6] = (((zobrist_int) 0xDD4E6CFBDF6C6C8ULL) + (((zobrist_int) 0x60F4F1634E72DB14ULL) << 64));
    zobrist_table[7][1][7] = (((zobrist_int) 0x5310FBC703D47842ULL) + (((zobrist_int) 0x4F0F0DA6569192C8ULL) << 64));
    zobrist_table[7][1][8] = (((zobrist_int) 0xE0C215BE96D4E1A7ULL) + (((zobrist_int) 0xD2F3B53FC9755CEFULL) << 64));
    zobrist_table[7][1][9] = (((zobrist_int) 0xCBBDBF0DED0521EULL) + (((zobrist_int) 0xB7723D4C35646533ULL) << 64));
    zobrist_table[7][1][10] = (((zobrist_int) 0x5421D2C914ECB493ULL) + (((zobrist_int) 0xABE63C701EB0DB42ULL) << 64));
    zobrist_table[7][1][11] = (((zobrist_int) 0xD22CDA44FD3244F2ULL) + (((zobrist_int) 0x10F7179EA53B56ADULL) << 64));
    zobrist_table[7][1][12] = (((zobrist_int) 0xC7F3059120DC84B8ULL) + (((zobrist_int) 0x4B56813CB0D5FDFFULL) << 64));
    zobrist_table[7][1][13] = (((zobrist_int) 0x68DF8B22F5A05735ULL) + (((zobrist_int) 0x573D5DC79B80FEDDULL) << 64));
    zobrist_table[7][2][0] = (((zobrist_int) 0x6F703553B89D84CULL) + (((zobrist_int) 0xA4E0880AF65F28EEULL) << 64));
    zobrist_table[7][2][1] = (((zobrist_int) 0xB08C2CBCB3577755ULL) + (((zobrist_int) 0xC16A4A632ED80E5CULL) << 64));
    zobrist_table[7][2][2] = (((zobrist_int) 0xC1BB6958C426DBB0ULL) + (((zobrist_int) 0xBFF5887A811196CAULL) << 64));
    zobrist_table[7][2][3] = (((zobrist_int) 0xA409613292F47B34ULL) + (((zobrist_int) 0x4D71A2E75DA43B78ULL) << 64));
    zobrist_table[7][2][4] = (((zobrist_int) 0x60C5A3164B334CCCULL) + (((zobrist_int) 0xED5903746BA1BB2BULL) << 64));
    zobrist_table[7][2][5] = (((zobrist_int) 0xF9196AA686C24BD1ULL) + (((zobrist_int) 0xCF88E8337621211BULL) << 64));
    zobrist_table[7][2][6] = (((zobrist_int) 0xDBA0E8BFDDC395D0ULL) + (((zobrist_int) 0xF0B60FC812FF2249ULL) << 64));
    zobrist_table[7][2][7] = (((zobrist_int) 0x685FA08B32F0F6A9ULL) + (((zobrist_int) 0x3B4A9816F00057BBULL) << 64));
    zobrist_table[7][2][8] = (((zobrist_int) 0xACF264A9B9C963FULL) + (((zobrist_int) 0x3DA256DE9E166EA5ULL) << 64));
    zobrist_table[7][2][9] = (((zobrist_int) 0x397C6A75A1374ADAULL) + (((zobrist_int) 0xB69102E63E55B274ULL) << 64));
    zobrist_table[7][2][10] = (((zobrist_int) 0x611DC4806509B280ULL) + (((zobrist_int) 0x9F33214535CC4955ULL) << 64));
    zobrist_table[7][2][11] = (((zobrist_int) 0xB8579B0F26E85F9BULL) + (((zobrist_int) 0x4C9BF327FD50AD1FULL) << 64));
    zobrist_table[7][2][12] = (((zobrist_int) 0xB801FBBCBE6A99E7ULL) + (((zobrist_int) 0x5C2F66A9E10F238AULL) << 64));
    zobrist_table[7][2][13] = (((zobrist_int) 0xB6715FE0005FE4E2ULL) + (((zobrist_int) 0xAFFB7C97B45835DBULL) << 64));
    zobrist_table[7][3][0] = (((zobrist_int) 0x71BBCFEA4EA8BA03ULL) + (((zobrist_int) 0x2BBE8E6B7F7713D1ULL) << 64));
    zobrist_table[7][3][1] = (((zobrist_int) 0x257994ADACDD471AULL) + (((zobrist_int) 0xFDF830F907FBDD18ULL) << 64));
    zobrist_table[7][3][2] = (((zobrist_int) 0x6FDEBBF75EEA1539ULL) + (((zobrist_int) 0x578656A98DCC1817ULL) << 64));
    zobrist_table[7][3][3] = (((zobrist_int) 0xCD1AFCF4DFD74033ULL) + (((zobrist_int) 0x7D5CA2ED83618765ULL) << 64));
    zobrist_table[7][3][4] = (((zobrist_int) 0xF065F2E6514D2290ULL) + (((zobrist_int) 0x1C8C66829A90105EULL) << 64));
    zobrist_table[7][3][5] = (((zobrist_int) 0xA55483E395679759ULL) + (((zobrist_int) 0xCF766EDE4AD36FB5ULL) << 64));
    zobrist_table[7][3][6] = (((zobrist_int) 0xA9A4C1F88C4D1DD7ULL) + (((zobrist_int) 0x6DF5EAF146AFFD36ULL) << 64));
    zobrist_table[7][3][7] = (((zobrist_int) 0xD78C860C02E418D9ULL) + (((zobrist_int) 0xC093B8CB4F8BB47FULL) << 64));
    zobrist_table[7][3][8] = (((zobrist_int) 0xA3821107162054FCULL) + (((zobrist_int) 0x1D6E69587DEC95C0ULL) << 64));
    zobrist_table[7][3][9] = (((zobrist_int) 0x3877202B804B4B70ULL) + (((zobrist_int) 0x9B0A7D25DEC6DD5AULL) << 64));
    zobrist_table[7][3][10] = (((zobrist_int) 0xA4B1B297BF76CF0CULL) + (((zobrist_int) 0xF934D17FBFD73C04ULL) << 64));
    zobrist_table[7][3][11] = (((zobrist_int) 0xED4A368DFD595626ULL) + (((zobrist_int) 0x6FD0613243C1EF62ULL) << 64));
    zobrist_table[7][3][12] = (((zobrist_int) 0xC8CFB9555F6B997BULL) + (((zobrist_int) 0xDE0B9D43B05CAC0ULL) << 64));
    zobrist_table[7][3][13] = (((zobrist_int) 0x98CFBB441A3C9365ULL) + (((zobrist_int) 0x83A1012F83E60E75ULL) << 64));
    zobrist_table[7][4][0] = (((zobrist_int) 0x29BE8D8282E66B1DULL) + (((zobrist_int) 0x4AC4430A2135A722ULL) << 64));
    zobrist_table[7][4][1] = (((zobrist_int) 0xC5F082AEC2BA5EAULL) + (((zobrist_int) 0xE2601E08FA7F335FULL) << 64));
    zobrist_table[7][4][2] = (((zobrist_int) 0x37DEF267117C7DCBULL) + (((zobrist_int) 0xAC24CCC700CFD099ULL) << 64));
    zobrist_table[7][4][3] = (((zobrist_int) 0x6C45E05B0FD1F298ULL) + (((zobrist_int) 0xB73FACB8BB52AF4FULL) << 64));
    zobrist_table[7][4][4] = (((zobrist_int) 0x562D3BBDA3ED7B2ULL) + (((zobrist_int) 0xE155D2A10F04B49ULL) << 64));
    zobrist_table[7][4][5] = (((zobrist_int) 0x8ED9A49024B5A59ULL) + (((zobrist_int) 0x56D1372189B6DF05ULL) << 64));
    zobrist_table[7][4][6] = (((zobrist_int) 0xC8FF89B3552C92BDULL) + (((zobrist_int) 0x9C8C768004CC01C8ULL) << 64));
    zobrist_table[7][4][7] = (((zobrist_int) 0x8F1C873F0240AADFULL) + (((zobrist_int) 0x780DABBA361BA5DEULL) << 64));
    zobrist_table[7][4][8] = (((zobrist_int) 0x4429C9F9333A6521ULL) + (((zobrist_int) 0x94EAFC854B9CEB25ULL) << 64));
    zobrist_table[7][4][9] = (((zobrist_int) 0x85821AA48CF86E57ULL) + (((zobrist_int) 0xE387D1B5405A6B61ULL) << 64));
    zobrist_table[7][4][10] = (((zobrist_int) 0x2EC3CC333BC7BDA8ULL) + (((zobrist_int) 0x64363D4C35F3A315ULL) << 64));
    zobrist_table[7][4][11] = (((zobrist_int) 0xF4D2E33E3127FC4ULL) + (((zobrist_int) 0xF85EA4263D145248ULL) << 64));
    zobrist_table[7][4][12] = (((zobrist_int) 0xB3574C278E2A1E1AULL) + (((zobrist_int) 0x90C7E5C73DFC87CULL) << 64));
    zobrist_table[7][4][13] = (((zobrist_int) 0x53A1B5B254D6F493ULL) + (((zobrist_int) 0x1EA7C5F668216F2BULL) << 64));
    zobrist_table[7][5][0] = (((zobrist_int) 0x90030AEC0418008DULL) + (((zobrist_int) 0x816FE1272F5F4BAAULL) << 64));
    zobrist_table[7][5][1] = (((zobrist_int) 0x17FB3543A3E02767ULL) + (((zobrist_int) 0x2F5269CFC2F0D5D7ULL) << 64));
    zobrist_table[7][5][2] = (((zobrist_int) 0x3992967B37E715ADULL) + (((zobrist_int) 0x4DDF19CB2D310B5DULL) << 64));
    zobrist_table[7][5][3] = (((zobrist_int) 0xCE587091E7DB782CULL) + (((zobrist_int) 0xF0D49CA19081FF0ULL) << 64));
    zobrist_table[7][5][4] = (((zobrist_int) 0x50591164CB7BF940ULL) + (((zobrist_int) 0xB9FA521EE0C80266ULL) << 64));
    zobrist_table[7][5][5] = (((zobrist_int) 0x1014E6CA2573D716ULL) + (((zobrist_int) 0x7173ED44D53DCF4FULL) << 64));
    zobrist_table[7][5][6] = (((zobrist_int) 0x3B1EC2F0266A1D83ULL) + (((zobrist_int) 0xBF6372930B090ED6ULL) << 64));
    zobrist_table[7][5][7] = (((zobrist_int) 0xF637826B494697AEULL) + (((zobrist_int) 0xEED7C4E582591CEULL) << 64));
    zobrist_table[7][5][8] = (((zobrist_int) 0x16DA2A3A96EC1B5CULL) + (((zobrist_int) 0x33423AA271491B28ULL) << 64));
    zobrist_table[7][5][9] = (((zobrist_int) 0x3A519F3CCB200053ULL) + (((zobrist_int) 0x2F6383D0AA2E29A4ULL) << 64));
    zobrist_table[7][5][10] = (((zobrist_int) 0xEB4FEAE1E837F23ULL) + (((zobrist_int) 0xDD5E1A633CE604CULL) << 64));
    zobrist_table[7][5][11] = (((zobrist_int) 0xBA75FAE0BF04888BULL) + (((zobrist_int) 0x166161D61DADECF8ULL) << 64));
    zobrist_table[7][5][12] = (((zobrist_int) 0xC9497DC4F3DFE94BULL) + (((zobrist_int) 0xBE112BC1CFC26411ULL) << 64));
    zobrist_table[7][5][13] = (((zobrist_int) 0xF03ABA8F384735D1ULL) + (((zobrist_int) 0xB6CBE1DE493E98E6ULL) << 64));
    zobrist_table[7][6][0] = (((zobrist_int) 0x86F71912408B4204ULL) + (((zobrist_int) 0xDF03202A6C3F81E6ULL) << 64));
    zobrist_table[7][6][1] = (((zobrist_int) 0xB8FBB54A3FA6D8E5ULL) + (((zobrist_int) 0xB953CDCE08426379ULL) << 64));
    zobrist_table[7][6][2] = (((zobrist_int) 0xC3D4A2674073D07CULL) + (((zobrist_int) 0x53655C6931DE54A5ULL) << 64));
    zobrist_table[7][6][3] = (((zobrist_int) 0x5B73EE9A5994A1A1ULL) + (((zobrist_int) 0xC3B2CCCF744AB1FCULL) << 64));
    zobrist_table[7][6][4] = (((zobrist_int) 0xEC2254D9DFD2ECC1ULL) + (((zobrist_int) 0xDE0420C2A8D8A8F1ULL) << 64));
    zobrist_table[7][6][5] = (((zobrist_int) 0x61E8303B9D903E47ULL) + (((zobrist_int) 0xADCCF8BDDD51C603ULL) << 64));
    zobrist_table[7][6][6] = (((zobrist_int) 0x16E1839D62F3DB21ULL) + (((zobrist_int) 0xEE862AB46D147D54ULL) << 64));
    zobrist_table[7][6][7] = (((zobrist_int) 0xD4FED5423E973B1FULL) + (((zobrist_int) 0x7D45C9C5D4881F67ULL) << 64));
    zobrist_table[7][6][8] = (((zobrist_int) 0x57FD0E22E09AB5F2ULL) + (((zobrist_int) 0x2DBA1741E92C15E4ULL) << 64));
    zobrist_table[7][6][9] = (((zobrist_int) 0xA62D6E8F9ADC7681ULL) + (((zobrist_int) 0x3D5E19B51D2480CAULL) << 64));
    zobrist_table[7][6][10] = (((zobrist_int) 0xC5DDDD3512803301ULL) + (((zobrist_int) 0x6FC484DBCC2B38B3ULL) << 64));
    zobrist_table[7][6][11] = (((zobrist_int) 0x46E42744E2ADE707ULL) + (((zobrist_int) 0x4DC696D98842C61CULL) << 64));
    zobrist_table[7][6][12] = (((zobrist_int) 0xF8B87EDCEBB769F9ULL) + (((zobrist_int) 0x55C50E4BEE4721D7ULL) << 64));
    zobrist_table[7][6][13] = (((zobrist_int) 0xD4E3319EC1375DDEULL) + (((zobrist_int) 0x68C50D385EDC0277ULL) << 64));
    zobrist_table[7][7][0] = (((zobrist_int) 0x5D473C8674D2D35AULL) + (((zobrist_int) 0x50DE36D75A151335ULL) << 64));
    zobrist_table[7][7][1] = (((zobrist_int) 0xF5463276656385EFULL) + (((zobrist_int) 0x82E0766D78A81FB3ULL) << 64));
    zobrist_table[7][7][2] = (((zobrist_int) 0x5ECB3CA30461587BULL) + (((zobrist_int) 0x4D6BE2872099A8A6ULL) << 64));
    zobrist_table[7][7][3] = (((zobrist_int) 0x4D5DD1362B031301ULL) + (((zobrist_int) 0x20732AA5911ACC7BULL) << 64));
    zobrist_table[7][7][4] = (((zobrist_int) 0x8C6C6764DF21CA9BULL) + (((zobrist_int) 0xBA11FC33B61E093DULL) << 64));
    zobrist_table[7][7][5] = (((zobrist_int) 0x2ABBFCC226455098ULL) + (((zobrist_int) 0xA517D182752AC62AULL) << 64));
    zobrist_table[7][7][6] = (((zobrist_int) 0x26F90507A097021CULL) + (((zobrist_int) 0x293ED17F229BE150ULL) << 64));
    zobrist_table[7][7][7] = (((zobrist_int) 0xD00A2B4114667D17ULL) + (((zobrist_int) 0x40FE7AAE9CAE8B34ULL) << 64));
    zobrist_table[7][7][8] = (((zobrist_int) 0x5B1FB5823C4508B1ULL) + (((zobrist_int) 0x50B1C7ABA5227B6FULL) << 64));
    zobrist_table[7][7][9] = (((zobrist_int) 0x46FBFB302BEA3FC4ULL) + (((zobrist_int) 0x791AD404DB1C99DFULL) << 64));
    zobrist_table[7][7][10] = (((zobrist_int) 0x13C77DBD4F4B245BULL) + (((zobrist_int) 0x276DCEE06DA8EC24ULL) << 64));
    zobrist_table[7][7][11] = (((zobrist_int) 0x5A6F5D998CCA96B3ULL) + (((zobrist_int) 0x731E33ACE2E7B339ULL) << 64));
    zobrist_table[7][7][12] = (((zobrist_int) 0x1B801CBBEA97B607ULL) + (((zobrist_int) 0x27E2F47AD8445118ULL) << 64));
    zobrist_table[7][7][13] = (((zobrist_int) 0x50DB1104AF3C7029ULL) + (((zobrist_int) 0xAF63336B11B64A61ULL) << 64));
    zobrist_white_castle_king = (((zobrist_int) 0x7AC5D58C2FD16EC8ULL) + (((zobrist_int) 0x8F3FF1888DBF8CCULL) << 64));
    zobrist_white_castle_queen = (((zobrist_int) 0xBFFE10FFC315153ULL) + (((zobrist_int) 0xF47C1174B9E4BCC0ULL) << 64));
    zobrist_black_castle_king = (((zobrist_int) 0xA643CE683110DDFEULL) + (((zobrist_int) 0xBC4195C35B22A216ULL) << 64));
    zobrist_black_castle_queen = (((zobrist_int) 0x5DB7A0F9F66418A4ULL) + (((zobrist_int) 0xEF34609281FBA43EULL) << 64));
    zobrist_blacks_turn = (((zobrist_int) 0x5AF51434DECD2CD9ULL) + (((zobrist_int) 0xD9EFB08EDBA5913FULL) << 64));
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
bool TranspositionTable::exists(boardstate *brd){
	unsigned long int index = this->getindex(brd);
	transposition_entry entry = this->data[index];
	if(entry == empty_transposition_entry){
		return false;
	} else {
		return true;
	}
}
*/

unsigned long int TranspositionTable::getindex(boardstate *brd){
	return (unsigned long int) ((brd->hash) % size);
}

void TranspositionTable::setitem(boardstate *brd, transposition_entry &entry){
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

transposition_entry TranspositionTable::getitem(boardstate *brd){
	unsigned long int index = this->getindex(brd);
	smallboardstate smallbrd; 
	
	transposition_entry result = this->data[index][1];
	if (result.key == brd->hash){
		smallbrd = smallify(brd);
		if (result.brd == smallbrd){
			return result;
		}
	}
	result = this->data[index][0];
	if (result.key == brd->hash){
		smallbrd = smallify(brd);
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

									