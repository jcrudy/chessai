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

unsigned long long perft(boardstate *brd, int depth){
    std::queue<move> moves = std::queue<move>();
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
    	moves.pop();
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
	white_score += 20000 * population_count(brd->white & brd->k);
	black_score += 100 * population_count(brd->black & brd->p);
	black_score += 320 * population_count(brd->black & brd->n);
	black_score += 330 * population_count(brd->black & brd->b);
	black_score += 500 * population_count(brd->black & brd->r);
	black_score += 900 * population_count(brd->black & brd->q);
	black_score += 20000 * population_count(brd->black & brd->k);
	if(get_whites_turn(brd)){
		return(white_score - black_score);
	}else{
		return(black_score - white_score);
	}
}

double quiescence(boardstate *brd, double alpha, double beta, bool *stop){
	double stand_pat = simple_evaluation(brd);
	std::queue<move> moves = std::queue<move>();
	bool is_check = own_check(brd);
	if(is_check){
		all_moves(brd, moves);
	}else{
		all_captures(brd, moves);
	}
	if(stand_pat >= beta){
		return(beta);
	}
	if(stand_pat > alpha){
		alpha = stand_pat;
	}
	move mv;
	moverecord rec;
	double score;
	while((!moves.empty()) & (!(*stop))){
		mv = moves.front();
		moves.pop();
		rec = make_move(brd, &mv);
		score = quiescence(brd, -beta, -alpha, stop);
		unmake_move(brd, &rec);
		if(score >= beta){
			return(beta);
		}
		if(score > alpha){
			alpha = score;
		}
	}
	return(alpha);
}

double negamax(boardstate *brd, int depth, double alpha, double beta, move *best_move, bool *stop, bool blank){
	if(depth == 0){
		return(quiescence(brd, alpha, beta, stop));
	}
	std::queue<move> moves = std::queue<move>();
	if(!blank){
		moves.push(*best_move);
	}
	all_moves(brd, moves);
	double value;
	double best_value;
	move best_counter;
	move mv;
	bool init = true;
	moverecord rec;
	while(!moves.empty()){
		mv = moves.front();
		moves.pop();
		rec = make_move(brd, &mv);
		value = -negamax(brd, depth-1, -beta, -alpha, &best_counter, stop, true);
		unmake_move(brd, &rec);
		if(value > alpha){
			alpha = value;
		}
		if(init){
			best_value = value;
			*best_move = mv;
			init = false;
		}
		if(value > best_value){
			best_value = value;
			*best_move = mv;
		}
		if(alpha > beta || (*stop)){
			break;
		}
		
	}
	return(best_value);
}

void iterative_negamax(void *varg){
	searcharg *arg = (searcharg *) varg;
	int depth = 1;
	double result;
	while(!(*(arg->stop))){
		result = negamax(arg->brd, depth, -1000000.0, 1000000.0, arg->best_move, arg->stop, arg->blank);
		arg->blank = false;
		arg->depth = depth;
		depth++;
	}
}

move movesearch_depth(boardstate *brd, int depth){
	move best_move;
	bool blank = true;
	bool stop = false;
	negamax(brd, depth, -1000000.0, 1000000.0, &best_move, &stop, blank);
	return(best_move);
}

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
									