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
	white_score += 200000 * population_count(brd->white & brd->k);
	
	white_score += .4 * 100 * population_count(brd->white & center4);
	white_score += .1 * 100 * population_count(brd->white & center16);
	
	black_score += 100 * population_count(brd->black & brd->p);
	black_score += 320 * population_count(brd->black & brd->n);
	black_score += 330 * population_count(brd->black & brd->b);
	black_score += 500 * population_count(brd->black & brd->r);
	black_score += 900 * population_count(brd->black & brd->q);
	black_score += 200000 * population_count(brd->black & brd->k);
	
	black_score += .4 * 100 * population_count(brd->black & center4);
	black_score += .1 * 100 * population_count(brd->black & center16);
	
	if(get_whites_turn(brd)){
		return(white_score - black_score);
	}else{
		return(black_score - white_score);
	}
}

double negafrax(boardstate *brd, double current, double threshold, double alpha, 
				double beta, move *best_move, bool *stop){
	if (current < threshold){
		return simple_evaluation(brd);
	}
	
	// Generate all legal moves
	std::queue<move> moves = std::queue<move>();
	all_moves(brd, moves);
	int num_moves = moves.size();
	
	double value;
	double best_value;
	move best_counter;
	move mv;
	bool init = true;
	moverecord rec;
	double quotient = current / num_moves;
	while(!moves.empty()){
		mv = moves.front();
		moves.pop();
		rec = make_move(brd, &mv);
		value = -negafrax(brd, quotient, threshold, -beta, -alpha, &best_counter, stop);
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
	return best_value;
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

move movesearch_threshold(boardstate *brd, double threshold){
	move best_move;
	bool blank = true;
	bool stop = false;
	negafrax(brd, 1.0, threshold, -1000000.0, 
				1000000.0, &best_move, &stop);
//	negfrax(brd, depth, -1000000.0, 1000000.0, &best_move, &stop, blank);
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
    zobrist_table[0][0][0] = 0x629F6FBED82C07CDULL;
    zobrist_table[0][0][1] = 0xE3E70682C2094CACULL;
    zobrist_table[0][0][2] = 0xA5D2F346BAA9455ULL;
    zobrist_table[0][0][3] = 0xF728B4FA42485E3AULL;
    zobrist_table[0][0][4] = 0x7C65C1E582E2E662ULL;
    zobrist_table[0][0][5] = 0xEB1167B367A9C378ULL;
    zobrist_table[0][0][6] = 0xD4713D60C8A70639ULL;
    zobrist_table[0][0][7] = 0xF7C1BD874DA5E709ULL;
    zobrist_table[0][0][8] = 0x5BA91FAF7A024204ULL;
    zobrist_table[0][0][9] = 0xE443DF789558867FULL;
    zobrist_table[0][0][10] = 0x37EBDCD9E87A1613ULL;
    zobrist_table[0][0][11] = 0x23A7711A81332876ULL;
    zobrist_table[0][0][12] = 0x23C6612F48268673ULL;
    zobrist_table[0][0][13] = 0x1846D424C17C6279ULL;
    zobrist_table[0][1][0] = 0xCCA5A5A19E4D6E3CULL;
    zobrist_table[0][1][1] = 0xFCBD04C340212EF7ULL;
    zobrist_table[0][1][2] = 0x88561712E8E5216AULL;
    zobrist_table[0][1][3] = 0xB4862B21FB97D435ULL;
    zobrist_table[0][1][4] = 0x9A164106CF6A659EULL;
    zobrist_table[0][1][5] = 0x259F4329E6F4590BULL;
    zobrist_table[0][1][6] = 0x19488DEC4F65D4D9ULL;
    zobrist_table[0][1][7] = 0x12E0C8B2BAD640FBULL;
    zobrist_table[0][1][8] = 0xD9B8A714E61A441CULL;
    zobrist_table[0][1][9] = 0x5487CE1EAF19922AULL;
    zobrist_table[0][1][10] = 0x8F4FF31E78DE5857ULL;
    zobrist_table[0][1][11] = 0x5A92118719C78DF4ULL;
    zobrist_table[0][1][12] = 0x50F244556F25E2A2ULL;
    zobrist_table[0][1][13] = 0xA3F2C9BF9C6316B9ULL;
    zobrist_table[0][2][0] = 0x3458A748E9BB17BCULL;
    zobrist_table[0][2][1] = 0x8D723104F77383C1ULL;
    zobrist_table[0][2][2] = 0x71545A137A1D5006ULL;
    zobrist_table[0][2][3] = 0x85776E9ADD84F39EULL;
    zobrist_table[0][2][4] = 0xFF18E0242AF9FC3ULL;
    zobrist_table[0][2][5] = 0xEB2083E6CE164DBAULL;
    zobrist_table[0][2][6] = 0xEA7E9D498C778EA6ULL;
    zobrist_table[0][2][7] = 0x17E0AA3C03983CA8ULL;
    zobrist_table[0][2][8] = 0xD71037D1B83E90ECULL;
    zobrist_table[0][2][9] = 0xB5D32B1666194CB1ULL;
    zobrist_table[0][2][10] = 0xC8F8E3D0D3290A4CULL;
    zobrist_table[0][2][11] = 0xA0116BE5AB0C1681ULL;
    zobrist_table[0][2][12] = 0x9CA5499D004AE545ULL;
    zobrist_table[0][2][13] = 0xD3FBF47A7E5B1E7FULL;
    zobrist_table[0][3][0] = 0x55485822DE1B372AULL;
    zobrist_table[0][3][1] = 0xBAF3897A3E70F16AULL;
    zobrist_table[0][3][2] = 0xB421EAEB534097CAULL;
    zobrist_table[0][3][3] = 0x101FBCCCDED733E8ULL;
    zobrist_table[0][3][4] = 0xEAC1C14F30E9C5CCULL;
    zobrist_table[0][3][5] = 0x38C1962E9148624FULL;
    zobrist_table[0][3][6] = 0xCDA8056C3D15EEF7ULL;
    zobrist_table[0][3][7] = 0x247A8333F7B0B7D2ULL;
    zobrist_table[0][3][8] = 0x8B0163C1CD9D2B7DULL;
    zobrist_table[0][3][9] = 0x1759EDC372AE2244ULL;
    zobrist_table[0][3][10] = 0xFE43C49E149818D1ULL;
    zobrist_table[0][3][11] = 0xE005B86051EF1922ULL;
    zobrist_table[0][3][12] = 0xFF7B118E820865D6ULL;
    zobrist_table[0][3][13] = 0x7D41E602EECE328BULL;
    zobrist_table[0][4][0] = 0x4D2B9DEB1BEB3711ULL;
    zobrist_table[0][4][1] = 0x4A84EB038D1FD9B7ULL;
    zobrist_table[0][4][2] = 0x1FF39849B4E1357DULL;
    zobrist_table[0][4][3] = 0x552F233A8C25166AULL;
    zobrist_table[0][4][4] = 0xEC188EFBD080E66EULL;
    zobrist_table[0][4][5] = 0x3405095C8A5006C1ULL;
    zobrist_table[0][4][6] = 0xCCA74147F6BE1F72ULL;
    zobrist_table[0][4][7] = 0x8C1745A79A6A5F92ULL;
    zobrist_table[0][4][8] = 0x49A3E80E966E1277ULL;
    zobrist_table[0][4][9] = 0x1775336D71EACD05ULL;
    zobrist_table[0][4][10] = 0xCC45782198A6416DULL;
    zobrist_table[0][4][11] = 0x5129FB7C6288E1A5ULL;
    zobrist_table[0][4][12] = 0x3DFABC08935DDD72ULL;
    zobrist_table[0][4][13] = 0x2F1205544A5308CCULL;
    zobrist_table[0][5][0] = 0xD24BACE4307BF326ULL;
    zobrist_table[0][5][1] = 0x870E15C2FCD81B5ULL;
    zobrist_table[0][5][2] = 0xFB3675B89CDEB3E6ULL;
    zobrist_table[0][5][3] = 0x42930B33A81AD477ULL;
    zobrist_table[0][5][4] = 0x11AF923D79FDEF7CULL;
    zobrist_table[0][5][5] = 0xADC0DA7A16FEBAA0ULL;
    zobrist_table[0][5][6] = 0x215663ABC1F254B8ULL;
    zobrist_table[0][5][7] = 0x2648EE38E07405EBULL;
    zobrist_table[0][5][8] = 0x9E469E6EC62B2C8ULL;
    zobrist_table[0][5][9] = 0x148B2758D7AB7928ULL;
    zobrist_table[0][5][10] = 0xB306D1A8E5EEAC76ULL;
    zobrist_table[0][5][11] = 0xD450FE4AEC4F217BULL;
    zobrist_table[0][5][12] = 0xAEF9C00B8A64C1B9ULL;
    zobrist_table[0][5][13] = 0xD67E55FD642BFA42ULL;
    zobrist_table[0][6][0] = 0x864A7A50B48D73F1ULL;
    zobrist_table[0][6][1] = 0x85940927468FF53DULL;
    zobrist_table[0][6][2] = 0x3C49D76FCFC6E625ULL;
    zobrist_table[0][6][3] = 0x37176E84D977E993ULL;
    zobrist_table[0][6][4] = 0xADF20806E5214606ULL;
    zobrist_table[0][6][5] = 0xD344749096FD35D0ULL;
    zobrist_table[0][6][6] = 0x6B5F5241F323CA74ULL;
    zobrist_table[0][6][7] = 0x467437419466E472ULL;
    zobrist_table[0][6][8] = 0x7E1EA9C573581A81ULL;
    zobrist_table[0][6][9] = 0xA425799AA905D750ULL;
    zobrist_table[0][6][10] = 0xB341FACDFF0AC0F1ULL;
    zobrist_table[0][6][11] = 0xFB82860DEABCA8D0ULL;
    zobrist_table[0][6][12] = 0x5B7C709ACB175A5AULL;
    zobrist_table[0][6][13] = 0x5306F3F515166570ULL;
    zobrist_table[0][7][0] = 0x1D878F9F9CDF5A86ULL;
    zobrist_table[0][7][1] = 0x964A870C7C879B74ULL;
    zobrist_table[0][7][2] = 0x55D44936A1515607ULL;
    zobrist_table[0][7][3] = 0x30BCAB0ED8570102ULL;
    zobrist_table[0][7][4] = 0x426465E3E37952DULL;
    zobrist_table[0][7][5] = 0x4562BE7FBB42E0B2ULL;
    zobrist_table[0][7][6] = 0xB490B6081DFC8352ULL;
    zobrist_table[0][7][7] = 0x5F3F563838701A14ULL;
    zobrist_table[0][7][8] = 0x2BA4B180CB69CA38ULL;
    zobrist_table[0][7][9] = 0x6D16EE18552116DDULL;
    zobrist_table[0][7][10] = 0xFEBD845D0DFAE43ULL;
    zobrist_table[0][7][11] = 0xC87A746319C16A0DULL;
    zobrist_table[0][7][12] = 0xDAF66C5F2577BFFAULL;
    zobrist_table[0][7][13] = 0x38018B47B29A8B06ULL;
    zobrist_table[1][0][0] = 0xD12ECBC40B9475B1ULL;
    zobrist_table[1][0][1] = 0xA25B59FD92E8E269ULL;
    zobrist_table[1][0][2] = 0xEFBFC19EE8F6CF32ULL;
    zobrist_table[1][0][3] = 0x9A27D85888C132ADULL;
    zobrist_table[1][0][4] = 0x12F175FFAE3B16ECULL;
    zobrist_table[1][0][5] = 0x1FDB8B3206D599E8ULL;
    zobrist_table[1][0][6] = 0x3042E325A28F5AB0ULL;
    zobrist_table[1][0][7] = 0xD480865F9B38FE80ULL;
    zobrist_table[1][0][8] = 0x1EA45CD69371A71FULL;
    zobrist_table[1][0][9] = 0x176EA1B164264CD5ULL;
    zobrist_table[1][0][10] = 0xD576D4155EC17DBEULL;
    zobrist_table[1][0][11] = 0x1DB53334FB0323A1ULL;
    zobrist_table[1][0][12] = 0x9B0252440950FD13ULL;
    zobrist_table[1][0][13] = 0x31D0B6640589F877ULL;
    zobrist_table[1][1][0] = 0xF87F43FDF6062541ULL;
    zobrist_table[1][1][1] = 0xB7D6467B2F5A522AULL;
    zobrist_table[1][1][2] = 0x7AAF0E891FB797FAULL;
    zobrist_table[1][1][3] = 0xBA26D85135E8579AULL;
    zobrist_table[1][1][4] = 0xFA34266CCFDBA9BULL;
    zobrist_table[1][1][5] = 0xADE9B2B4EFDD35F8ULL;
    zobrist_table[1][1][6] = 0x8B53031D05D51433ULL;
    zobrist_table[1][1][7] = 0x9EDFA3DA6CF55B15ULL;
    zobrist_table[1][1][8] = 0xD5FDB76A19FBEB1DULL;
    zobrist_table[1][1][9] = 0x11EBCD49428A1C22ULL;
    zobrist_table[1][1][10] = 0x126CBC8F38884479ULL;
    zobrist_table[1][1][11] = 0x4D125E7FA59CEC98ULL;
    zobrist_table[1][1][12] = 0x6FA231E959ACDD98ULL;
    zobrist_table[1][1][13] = 0xFA07A3F2E295065ULL;
    zobrist_table[1][2][0] = 0x7795E98680EE526EULL;
    zobrist_table[1][2][1] = 0x98B33C6E0A14B90AULL;
    zobrist_table[1][2][2] = 0xB306D70019D5F970ULL;
    zobrist_table[1][2][3] = 0x642AAD48FCFCFA81ULL;
    zobrist_table[1][2][4] = 0x429817C53308FB2EULL;
    zobrist_table[1][2][5] = 0xE786AB375BCA47BEULL;
    zobrist_table[1][2][6] = 0x78601602BB4A06CBULL;
    zobrist_table[1][2][7] = 0xE6FD68E8D69C91C2ULL;
    zobrist_table[1][2][8] = 0x91DC59EFEB21A3F6ULL;
    zobrist_table[1][2][9] = 0xB29C467D2B5F6932ULL;
    zobrist_table[1][2][10] = 0x3412FC12AC322C12ULL;
    zobrist_table[1][2][11] = 0xC470F0E7F76FBFB8ULL;
    zobrist_table[1][2][12] = 0xC9E4DAB20EDC6D2BULL;
    zobrist_table[1][2][13] = 0x28805C5DAD1B8F60ULL;
    zobrist_table[1][3][0] = 0x2975D279D86DBF11ULL;
    zobrist_table[1][3][1] = 0x878B9F6B57A1CB71ULL;
    zobrist_table[1][3][2] = 0x1E01A934402D0BAFULL;
    zobrist_table[1][3][3] = 0xEBE2136898C75205ULL;
    zobrist_table[1][3][4] = 0xAA6524AB713B7E05ULL;
    zobrist_table[1][3][5] = 0x361524C2CC0F859ULL;
    zobrist_table[1][3][6] = 0xAE68690A78BC7175ULL;
    zobrist_table[1][3][7] = 0xE66CD36E68EF8F5FULL;
    zobrist_table[1][3][8] = 0xDFF3334B91B15F5DULL;
    zobrist_table[1][3][9] = 0xEAE2025E82339E23ULL;
    zobrist_table[1][3][10] = 0xA62081434FBAECC0ULL;
    zobrist_table[1][3][11] = 0x637E0EDC5B6E4AE7ULL;
    zobrist_table[1][3][12] = 0xA859890CD670F668ULL;
    zobrist_table[1][3][13] = 0x27460F22403D1F83ULL;
    zobrist_table[1][4][0] = 0xB0D9C2AA8F837EF7ULL;
    zobrist_table[1][4][1] = 0x753C7C99032F06CAULL;
    zobrist_table[1][4][2] = 0x143E2E04BDD7D19BULL;
    zobrist_table[1][4][3] = 0xBD30291A55FEA08EULL;
    zobrist_table[1][4][4] = 0x8B5885CA0BB2C3F0ULL;
    zobrist_table[1][4][5] = 0x2284B7A447E7F593ULL;
    zobrist_table[1][4][6] = 0xC31D5A973D792FA1ULL;
    zobrist_table[1][4][7] = 0x7B59051BF40048D7ULL;
    zobrist_table[1][4][8] = 0x9C31D9B25A2B745BULL;
    zobrist_table[1][4][9] = 0xAC642B4C49B25DEDULL;
    zobrist_table[1][4][10] = 0x971C702D5BF49C04ULL;
    zobrist_table[1][4][11] = 0xE456697CF2686BAAULL;
    zobrist_table[1][4][12] = 0xDA90F534A23D4C9DULL;
    zobrist_table[1][4][13] = 0x21E150949EFEE464ULL;
    zobrist_table[1][5][0] = 0x4F6FA985B732D46FULL;
    zobrist_table[1][5][1] = 0xBF9CC545635518F7ULL;
    zobrist_table[1][5][2] = 0xD432F8DB6A174C1CULL;
    zobrist_table[1][5][3] = 0x14AA451CA69CFB85ULL;
    zobrist_table[1][5][4] = 0x983631890063E42FULL;
    zobrist_table[1][5][5] = 0xB2D650AF313B32B7ULL;
    zobrist_table[1][5][6] = 0x28FAFD04559B5975ULL;
    zobrist_table[1][5][7] = 0x391CF0463D4A5D51ULL;
    zobrist_table[1][5][8] = 0x72B8FF39A32C9B6FULL;
    zobrist_table[1][5][9] = 0xB5D97EF760EF1471ULL;
    zobrist_table[1][5][10] = 0xAC7C8803E01BBF50ULL;
    zobrist_table[1][5][11] = 0xDFE1B30791725F0AULL;
    zobrist_table[1][5][12] = 0x8135D586A1689ADULL;
    zobrist_table[1][5][13] = 0xDF26F51766FAF989ULL;
    zobrist_table[1][6][0] = 0x9145DE05B3AB1B2CULL;
    zobrist_table[1][6][1] = 0xC5ADF6816B10E53AULL;
    zobrist_table[1][6][2] = 0xB5816B74A985AB61ULL;
    zobrist_table[1][6][3] = 0x2A69ACC70BF9C0EFULL;
    zobrist_table[1][6][4] = 0x105ADA6B720299E3ULL;
    zobrist_table[1][6][5] = 0xB3969057425CB200ULL;
    zobrist_table[1][6][6] = 0x7244F536285E25B4ULL;
    zobrist_table[1][6][7] = 0xE28BC9FF870F084CULL;
    zobrist_table[1][6][8] = 0xE8754CD37CBD7025ULL;
    zobrist_table[1][6][9] = 0x9A9E43108FB83BABULL;
    zobrist_table[1][6][10] = 0x4884CC167733FULL;
    zobrist_table[1][6][11] = 0x9F6048FE245A460ULL;
    zobrist_table[1][6][12] = 0x53710F577E9CF84FULL;
    zobrist_table[1][6][13] = 0xD675EBF74FE30C9AULL;
    zobrist_table[1][7][0] = 0xCC36D8C77863FE5ULL;
    zobrist_table[1][7][1] = 0xD29DC5DFCF1DA110ULL;
    zobrist_table[1][7][2] = 0xF963A7EFE00111E5ULL;
    zobrist_table[1][7][3] = 0x6A46721ACFFA6CDDULL;
    zobrist_table[1][7][4] = 0x8C6E90373020DA5CULL;
    zobrist_table[1][7][5] = 0xF689A4A5FFDA0336ULL;
    zobrist_table[1][7][6] = 0xFA83ADA4A2121AC5ULL;
    zobrist_table[1][7][7] = 0xD663049D155E18B1ULL;
    zobrist_table[1][7][8] = 0x2169DF82B9BDEE2DULL;
    zobrist_table[1][7][9] = 0x3C54C71FCA05536ULL;
    zobrist_table[1][7][10] = 0xF3158C0C66DD7794ULL;
    zobrist_table[1][7][11] = 0x6AE04D52ADB328CBULL;
    zobrist_table[1][7][12] = 0xDE59F550F0FC2BULL;
    zobrist_table[1][7][13] = 0x3A8987936A98D74ULL;
    zobrist_table[2][0][0] = 0xC1378BE5B7A28E0AULL;
    zobrist_table[2][0][1] = 0xFAF1501B009A815BULL;
    zobrist_table[2][0][2] = 0xACFEBB4BD29E8693ULL;
    zobrist_table[2][0][3] = 0x9CB017C18741AE91ULL;
    zobrist_table[2][0][4] = 0x30C1FB6A19086515ULL;
    zobrist_table[2][0][5] = 0x9BBD750D1E707C52ULL;
    zobrist_table[2][0][6] = 0x32D1F81BA636425CULL;
    zobrist_table[2][0][7] = 0x4D6B234FDFA7C6EDULL;
    zobrist_table[2][0][8] = 0xB044284A47ACF2F6ULL;
    zobrist_table[2][0][9] = 0x2EA60B99FA7FF8BFULL;
    zobrist_table[2][0][10] = 0x79C147C719A5711BULL;
    zobrist_table[2][0][11] = 0xEC3AA314DA9BB017ULL;
    zobrist_table[2][0][12] = 0xA0ACF4C9658DE17EULL;
    zobrist_table[2][0][13] = 0x597AAB614D30DBCULL;
    zobrist_table[2][1][0] = 0xE9F41CC04653A560ULL;
    zobrist_table[2][1][1] = 0xCCC14D5173F660D8ULL;
    zobrist_table[2][1][2] = 0x1DA3B7E2CAD6E514ULL;
    zobrist_table[2][1][3] = 0x41A93F90DC821527ULL;
    zobrist_table[2][1][4] = 0xA7502A812227D96DULL;
    zobrist_table[2][1][5] = 0xD138D1508557716AULL;
    zobrist_table[2][1][6] = 0xA51AD4F3A699BAE0ULL;
    zobrist_table[2][1][7] = 0x1D77CE4058D87776ULL;
    zobrist_table[2][1][8] = 0x27896389DF3277FDULL;
    zobrist_table[2][1][9] = 0xD9EAD9264745DD9EULL;
    zobrist_table[2][1][10] = 0xAD4041504C14982ULL;
    zobrist_table[2][1][11] = 0x34AB18FD0A68E88EULL;
    zobrist_table[2][1][12] = 0x4279B14DAE55CDFFULL;
    zobrist_table[2][1][13] = 0x50910BDC8EF066D4ULL;
    zobrist_table[2][2][0] = 0x5DECC06AF24DFDD8ULL;
    zobrist_table[2][2][1] = 0x914591AEF03D866AULL;
    zobrist_table[2][2][2] = 0xD974C146E8EC01B3ULL;
    zobrist_table[2][2][3] = 0xD8AB0B300AC0CF0DULL;
    zobrist_table[2][2][4] = 0xF61164CEBFC74CA9ULL;
    zobrist_table[2][2][5] = 0x9B8B71A1B38A05FBULL;
    zobrist_table[2][2][6] = 0x7E969CF3A7C5CB87ULL;
    zobrist_table[2][2][7] = 0xA4E695C9B65D1226ULL;
    zobrist_table[2][2][8] = 0x756B0715E7180322ULL;
    zobrist_table[2][2][9] = 0x6F790959A3E04B3BULL;
    zobrist_table[2][2][10] = 0xDF14C6125F58D5B5ULL;
    zobrist_table[2][2][11] = 0x2DA44DA189B5B368ULL;
    zobrist_table[2][2][12] = 0x6025F0AE35354579ULL;
    zobrist_table[2][2][13] = 0x4A814D53964DDB77ULL;
    zobrist_table[2][3][0] = 0x2371EA2C0247145FULL;
    zobrist_table[2][3][1] = 0x4578BAB326A97465ULL;
    zobrist_table[2][3][2] = 0x56672017555A4085ULL;
    zobrist_table[2][3][3] = 0x5E00EA6DCA24BE4DULL;
    zobrist_table[2][3][4] = 0x17FD3736B7EF941CULL;
    zobrist_table[2][3][5] = 0xC787DDFB5697F17CULL;
    zobrist_table[2][3][6] = 0x9215F4F9EDB95F2ULL;
    zobrist_table[2][3][7] = 0x4505F4F60A8C46C7ULL;
    zobrist_table[2][3][8] = 0x2640211E29F2C3C7ULL;
    zobrist_table[2][3][9] = 0x955D0E77FB5EB866ULL;
    zobrist_table[2][3][10] = 0x5C6460364A1EB1B7ULL;
    zobrist_table[2][3][11] = 0xFD42F69765111656ULL;
    zobrist_table[2][3][12] = 0x2130260C8C69778FULL;
    zobrist_table[2][3][13] = 0x1D69D9FC4B1CB8BDULL;
    zobrist_table[2][4][0] = 0xBB0378EB7A62722EULL;
    zobrist_table[2][4][1] = 0xEF0A81ED3D5D60BCULL;
    zobrist_table[2][4][2] = 0x4ED135530C5A876FULL;
    zobrist_table[2][4][3] = 0xDB66BFDA2DF96747ULL;
    zobrist_table[2][4][4] = 0xBA8982DD85E69EA9ULL;
    zobrist_table[2][4][5] = 0x4D7BD307122411E6ULL;
    zobrist_table[2][4][6] = 0xD5E73E3F673617D9ULL;
    zobrist_table[2][4][7] = 0x4C9A0AE15419EEFCULL;
    zobrist_table[2][4][8] = 0x1BD094486A2B3200ULL;
    zobrist_table[2][4][9] = 0x8F928DC519724CE3ULL;
    zobrist_table[2][4][10] = 0x7B2E1B82E89DC815ULL;
    zobrist_table[2][4][11] = 0x564AE90979585E69ULL;
    zobrist_table[2][4][12] = 0xCC417E7CD741D609ULL;
    zobrist_table[2][4][13] = 0xCFF4C56BF9EA2C64ULL;
    zobrist_table[2][5][0] = 0x1FD3C01757F98D1EULL;
    zobrist_table[2][5][1] = 0x1DB2B4527AA56A18ULL;
    zobrist_table[2][5][2] = 0x7F6B8793B318AD4CULL;
    zobrist_table[2][5][3] = 0x9AEDBD06D316B4AULL;
    zobrist_table[2][5][4] = 0x55C7ED9D4D4985DCULL;
    zobrist_table[2][5][5] = 0xAFE6790ABC18A40BULL;
    zobrist_table[2][5][6] = 0x27D99A23E4F7625EULL;
    zobrist_table[2][5][7] = 0x2AA36CF7EB70BA65ULL;
    zobrist_table[2][5][8] = 0x90823EDAA0722AA0ULL;
    zobrist_table[2][5][9] = 0xCE5DC80760257199ULL;
    zobrist_table[2][5][10] = 0xFDD2ED7AF97CCC57ULL;
    zobrist_table[2][5][11] = 0x16408169A38D8AFCULL;
    zobrist_table[2][5][12] = 0xCECA2EE310DA8A95ULL;
    zobrist_table[2][5][13] = 0x32B2C49215ACE7A1ULL;
    zobrist_table[2][6][0] = 0x38974DF5BFF773CEULL;
    zobrist_table[2][6][1] = 0x628308690FA7EE05ULL;
    zobrist_table[2][6][2] = 0x191B8ADF0202861CULL;
    zobrist_table[2][6][3] = 0x8E751EB764D09913ULL;
    zobrist_table[2][6][4] = 0x4A31B24384DD6DA6ULL;
    zobrist_table[2][6][5] = 0xEB8F205672D3CC5DULL;
    zobrist_table[2][6][6] = 0xC9CD4AF97D161F29ULL;
    zobrist_table[2][6][7] = 0xB6E355F695BB440DULL;
    zobrist_table[2][6][8] = 0x379DEDA1ADE6C5E9ULL;
    zobrist_table[2][6][9] = 0x156AF4586C4C3935ULL;
    zobrist_table[2][6][10] = 0x385AF4635E4AF862ULL;
    zobrist_table[2][6][11] = 0xFFC573D5FD0BA70EULL;
    zobrist_table[2][6][12] = 0x95D1805142CB6D1DULL;
    zobrist_table[2][6][13] = 0x2AA50F4EC6F00933ULL;
    zobrist_table[2][7][0] = 0x31234EFE6E648043ULL;
    zobrist_table[2][7][1] = 0x1D7173E55BC7FDEBULL;
    zobrist_table[2][7][2] = 0xD26D53961058FE8CULL;
    zobrist_table[2][7][3] = 0xDA54F267DD138266ULL;
    zobrist_table[2][7][4] = 0x7120911B3B68B57ULL;
    zobrist_table[2][7][5] = 0x869BDBD2E72BB5B7ULL;
    zobrist_table[2][7][6] = 0xC09FCD8F739CD488ULL;
    zobrist_table[2][7][7] = 0x33A1D1C2AD4AB155ULL;
    zobrist_table[2][7][8] = 0x7F411FED1E70E799ULL;
    zobrist_table[2][7][9] = 0x41A8A6E165E04993ULL;
    zobrist_table[2][7][10] = 0xA41865BF350D278DULL;
    zobrist_table[2][7][11] = 0xFF3E0BA10AC728B4ULL;
    zobrist_table[2][7][12] = 0xCC249558F2AD985FULL;
    zobrist_table[2][7][13] = 0x9F9821883744DA64ULL;
    zobrist_table[3][0][0] = 0x1AC902EE25777CF0ULL;
    zobrist_table[3][0][1] = 0x755A3AC132AE2A20ULL;
    zobrist_table[3][0][2] = 0x5C94938160C6B3EDULL;
    zobrist_table[3][0][3] = 0xD3B564B08BE04C3EULL;
    zobrist_table[3][0][4] = 0x1AD0A6F226BDD974ULL;
    zobrist_table[3][0][5] = 0x98A33736FD1AC7CEULL;
    zobrist_table[3][0][6] = 0x7CE71B48FBA52E59ULL;
    zobrist_table[3][0][7] = 0x905C053B25FDACBEULL;
    zobrist_table[3][0][8] = 0xA36BCB0167E98363ULL;
    zobrist_table[3][0][9] = 0x6C596216AE0FDBC8ULL;
    zobrist_table[3][0][10] = 0x856F3D95E0AE1A1BULL;
    zobrist_table[3][0][11] = 0xADE7CEF37ED2EC2FULL;
    zobrist_table[3][0][12] = 0xE345AC72EAC39204ULL;
    zobrist_table[3][0][13] = 0xD5627386528CC241ULL;
    zobrist_table[3][1][0] = 0xFF88EC827F99D273ULL;
    zobrist_table[3][1][1] = 0xA2939B3B7FA74D8AULL;
    zobrist_table[3][1][2] = 0xDFEC4623AB899605ULL;
    zobrist_table[3][1][3] = 0x8AF5890333B5B3CEULL;
    zobrist_table[3][1][4] = 0xEE6A8E2F9C19ED34ULL;
    zobrist_table[3][1][5] = 0x27C013F38018399ULL;
    zobrist_table[3][1][6] = 0xB4A1CA795718ADA2ULL;
    zobrist_table[3][1][7] = 0xBF3DF0BBF66AC168ULL;
    zobrist_table[3][1][8] = 0x51797350E6256403ULL;
    zobrist_table[3][1][9] = 0x52631DB9D17034CEULL;
    zobrist_table[3][1][10] = 0x866D7002091472ADULL;
    zobrist_table[3][1][11] = 0xDFDE228125FB5F3DULL;
    zobrist_table[3][1][12] = 0x9A431F7A41C30359ULL;
    zobrist_table[3][1][13] = 0x27E969E2C8BF23FBULL;
    zobrist_table[3][2][0] = 0x61067A8CD7A3283CULL;
    zobrist_table[3][2][1] = 0x4B5CA436953C178EULL;
    zobrist_table[3][2][2] = 0xB4D4DFCCB7D779CCULL;
    zobrist_table[3][2][3] = 0x786E30EFCE9B2E70ULL;
    zobrist_table[3][2][4] = 0xCCC93FF710FCE97DULL;
    zobrist_table[3][2][5] = 0x843B2A7D15AB2C21ULL;
    zobrist_table[3][2][6] = 0xEA5F24B6DE6FEC4BULL;
    zobrist_table[3][2][7] = 0x10FC9EEE0A1727F7ULL;
    zobrist_table[3][2][8] = 0x21681081399F8A8FULL;
    zobrist_table[3][2][9] = 0x4CEA2DF00A66DC4EULL;
    zobrist_table[3][2][10] = 0xC2472FD603E9BA02ULL;
    zobrist_table[3][2][11] = 0x72D6BC20D80D6A1CULL;
    zobrist_table[3][2][12] = 0xDCA5B35354A1D505ULL;
    zobrist_table[3][2][13] = 0xCCF719AB2922FBD8ULL;
    zobrist_table[3][3][0] = 0xDE62D43F261908B9ULL;
    zobrist_table[3][3][1] = 0x75F2BC20A7F5195CULL;
    zobrist_table[3][3][2] = 0x5F0EF320F7F60E7FULL;
    zobrist_table[3][3][3] = 0x61D9FE398147A8F4ULL;
    zobrist_table[3][3][4] = 0x87A1798FE6ADDD9EULL;
    zobrist_table[3][3][5] = 0x89B30A0809F2923ULL;
    zobrist_table[3][3][6] = 0x1734A26C92E94E89ULL;
    zobrist_table[3][3][7] = 0xCB4D18D6ADB6DA35ULL;
    zobrist_table[3][3][8] = 0x849B8A44CE1BB02AULL;
    zobrist_table[3][3][9] = 0x99A2ECB1C202387BULL;
    zobrist_table[3][3][10] = 0x138C3460FD938ADCULL;
    zobrist_table[3][3][11] = 0x6D265DD8BF391FBBULL;
    zobrist_table[3][3][12] = 0xC12EA9B8E7E13ED8ULL;
    zobrist_table[3][3][13] = 0x4A276DDA34C3494AULL;
    zobrist_table[3][4][0] = 0xE6B106E289110AF0ULL;
    zobrist_table[3][4][1] = 0x6AF79AD2993EC8C6ULL;
    zobrist_table[3][4][2] = 0xF8F8F071D360DA69ULL;
    zobrist_table[3][4][3] = 0xD872298C7B72590BULL;
    zobrist_table[3][4][4] = 0xF8E45086CA819C6FULL;
    zobrist_table[3][4][5] = 0x9B8086DA63794035ULL;
    zobrist_table[3][4][6] = 0x3BCB50B3961D8DCFULL;
    zobrist_table[3][4][7] = 0xDD620222D9EFE28BULL;
    zobrist_table[3][4][8] = 0x53E4B42CC4DA021ULL;
    zobrist_table[3][4][9] = 0xE2A01335A83023ABULL;
    zobrist_table[3][4][10] = 0xBDA17DA2000FC63DULL;
    zobrist_table[3][4][11] = 0x4D6CD7822E9583EAULL;
    zobrist_table[3][4][12] = 0x91FCFE8881C16E98ULL;
    zobrist_table[3][4][13] = 0x552AE5CA4124405BULL;
    zobrist_table[3][5][0] = 0x7E56AC3D10CC8711ULL;
    zobrist_table[3][5][1] = 0x4312ECE2DC2151E1ULL;
    zobrist_table[3][5][2] = 0xD334886FF164F9D8ULL;
    zobrist_table[3][5][3] = 0xC5C142624D849EC5ULL;
    zobrist_table[3][5][4] = 0x62584AB368777BABULL;
    zobrist_table[3][5][5] = 0x6238D0A0CF5E9EA3ULL;
    zobrist_table[3][5][6] = 0x29EE7F3D0FF030B8ULL;
    zobrist_table[3][5][7] = 0xEF7E85ECA417956FULL;
    zobrist_table[3][5][8] = 0x3D2BF042209818D1ULL;
    zobrist_table[3][5][9] = 0xBABD4745497E9F1AULL;
    zobrist_table[3][5][10] = 0x5582A3BDD476FE38ULL;
    zobrist_table[3][5][11] = 0xF11DDFF70E370526ULL;
    zobrist_table[3][5][12] = 0x7B38785B0932F5B6ULL;
    zobrist_table[3][5][13] = 0x2412579D6AF944E0ULL;
    zobrist_table[3][6][0] = 0xE3D484087DE8A234ULL;
    zobrist_table[3][6][1] = 0x9A1A7D6FDD02E100ULL;
    zobrist_table[3][6][2] = 0x14E5064CB799AE8EULL;
    zobrist_table[3][6][3] = 0xB2DDC481AC6D5DF8ULL;
    zobrist_table[3][6][4] = 0xCF6F111C26C06E67ULL;
    zobrist_table[3][6][5] = 0x5A4F4145FC98C279ULL;
    zobrist_table[3][6][6] = 0x9018AEE69407BE7ULL;
    zobrist_table[3][6][7] = 0x775E0EC39C9D03F3ULL;
    zobrist_table[3][6][8] = 0x7579501A62FDA854ULL;
    zobrist_table[3][6][9] = 0x19FAA06E0C0A5967ULL;
    zobrist_table[3][6][10] = 0xC734BB05788C31F6ULL;
    zobrist_table[3][6][11] = 0x52DAAD326C00984ULL;
    zobrist_table[3][6][12] = 0x992A34A1084FA819ULL;
    zobrist_table[3][6][13] = 0x21F8C1569E0DF45BULL;
    zobrist_table[3][7][0] = 0x52EBDAC5A1457899ULL;
    zobrist_table[3][7][1] = 0xB3386C3E1AF4787FULL;
    zobrist_table[3][7][2] = 0xA6245B598C94AF98ULL;
    zobrist_table[3][7][3] = 0x31E9CA8058BF3B9EULL;
    zobrist_table[3][7][4] = 0xC88E03B662276CBCULL;
    zobrist_table[3][7][5] = 0xC707AEF9C6C3744CULL;
    zobrist_table[3][7][6] = 0x1C6A4B5E7D859725ULL;
    zobrist_table[3][7][7] = 0xF66B32DE19B5837ULL;
    zobrist_table[3][7][8] = 0xB368C5539C30CEAAULL;
    zobrist_table[3][7][9] = 0x9D44C93E7799A8E2ULL;
    zobrist_table[3][7][10] = 0xEF151673A1DF3DA7ULL;
    zobrist_table[3][7][11] = 0xA6855857567E5862ULL;
    zobrist_table[3][7][12] = 0xF83032491FD3AF07ULL;
    zobrist_table[3][7][13] = 0xB6AF98B2AEBA42D0ULL;
    zobrist_table[4][0][0] = 0x4BDFFA7D9F3DD894ULL;
    zobrist_table[4][0][1] = 0xD960AF85C9DF7E44ULL;
    zobrist_table[4][0][2] = 0xF55E3AA2208A393EULL;
    zobrist_table[4][0][3] = 0x633CBF79E96AA1AFULL;
    zobrist_table[4][0][4] = 0x4B36B545CCA1A034ULL;
    zobrist_table[4][0][5] = 0xBEEBB4EAEAB9221BULL;
    zobrist_table[4][0][6] = 0xF521CA9FDF5E6F78ULL;
    zobrist_table[4][0][7] = 0xFBBFF9E0AE56702AULL;
    zobrist_table[4][0][8] = 0x1F1E0EE9CF6C9992ULL;
    zobrist_table[4][0][9] = 0xDC45488D84DDA9B9ULL;
    zobrist_table[4][0][10] = 0xFEEF71CBC915D113ULL;
    zobrist_table[4][0][11] = 0x9C67417306AA871ULL;
    zobrist_table[4][0][12] = 0x645BD776C838A145ULL;
    zobrist_table[4][0][13] = 0x5F1FF97C71CFF814ULL;
    zobrist_table[4][1][0] = 0x30C32323C1B199C4ULL;
    zobrist_table[4][1][1] = 0x5B471C437499B28CULL;
    zobrist_table[4][1][2] = 0xA1CBA182CA20854DULL;
    zobrist_table[4][1][3] = 0xF4DD05D51349747AULL;
    zobrist_table[4][1][4] = 0xE6E4B8DF0B6D9611ULL;
    zobrist_table[4][1][5] = 0xA3C2C6FEF2D9A38ULL;
    zobrist_table[4][1][6] = 0x4160FF927C7550F2ULL;
    zobrist_table[4][1][7] = 0x6D2ED7CE6AC9D8AULL;
    zobrist_table[4][1][8] = 0x8522DC4EF1DD50BFULL;
    zobrist_table[4][1][9] = 0x91BACF80AAA07996ULL;
    zobrist_table[4][1][10] = 0xE0397E67926146DEULL;
    zobrist_table[4][1][11] = 0x3ACAAF82374A6CC9ULL;
    zobrist_table[4][1][12] = 0xC6BE643217EE0EB0ULL;
    zobrist_table[4][1][13] = 0xE27AC8E9D1C3D1BCULL;
    zobrist_table[4][2][0] = 0xA09F1AEDE38690E7ULL;
    zobrist_table[4][2][1] = 0x809E2109C7867A38ULL;
    zobrist_table[4][2][2] = 0x8611F583B2D10E3DULL;
    zobrist_table[4][2][3] = 0x81D1BF066B8C66F2ULL;
    zobrist_table[4][2][4] = 0xF20B575D4E28E674ULL;
    zobrist_table[4][2][5] = 0x254BF7AE1D0AB994ULL;
    zobrist_table[4][2][6] = 0xE44FC3A96D0C62C3ULL;
    zobrist_table[4][2][7] = 0x6C0BE55C90E639E1ULL;
    zobrist_table[4][2][8] = 0x15831FEEEC41E6F6ULL;
    zobrist_table[4][2][9] = 0x1AD1DAAAEF8D9FF0ULL;
    zobrist_table[4][2][10] = 0x101BB5FA6A677623ULL;
    zobrist_table[4][2][11] = 0x6A4805421965E435ULL;
    zobrist_table[4][2][12] = 0x27F9E728C618FC1EULL;
    zobrist_table[4][2][13] = 0xF45DA406BBF9BB01ULL;
    zobrist_table[4][3][0] = 0xCA9571E407DC02B1ULL;
    zobrist_table[4][3][1] = 0x6E5BAC20725C2675ULL;
    zobrist_table[4][3][2] = 0x6AC1CA75AFB918C8ULL;
    zobrist_table[4][3][3] = 0x7F22CD1207B6E08EULL;
    zobrist_table[4][3][4] = 0xDD32E231EB561699ULL;
    zobrist_table[4][3][5] = 0x53125FFDF655860BULL;
    zobrist_table[4][3][6] = 0x40A978BFB8F8903BULL;
    zobrist_table[4][3][7] = 0x5A3DA367141B1A1BULL;
    zobrist_table[4][3][8] = 0x1F12A0E912011CAAULL;
    zobrist_table[4][3][9] = 0xB1182D235BF80676ULL;
    zobrist_table[4][3][10] = 0x586F1721078548D7ULL;
    zobrist_table[4][3][11] = 0x2D8B5B41590E83DAULL;
    zobrist_table[4][3][12] = 0xD48C93F3028D042BULL;
    zobrist_table[4][3][13] = 0x3B019FCBF96D4403ULL;
    zobrist_table[4][4][0] = 0x5DA53B38D1AA6C5EULL;
    zobrist_table[4][4][1] = 0x98BA0F0E120D7126ULL;
    zobrist_table[4][4][2] = 0x24AEBA79E4B82987ULL;
    zobrist_table[4][4][3] = 0xD3D1AF353E0C86ULL;
    zobrist_table[4][4][4] = 0xA8B56F85346D2B7EULL;
    zobrist_table[4][4][5] = 0xBB6B0095AC7B7AB2ULL;
    zobrist_table[4][4][6] = 0xE6A1A40BF031F4B9ULL;
    zobrist_table[4][4][7] = 0xBF7B68AE1F8941B6ULL;
    zobrist_table[4][4][8] = 0x4B1347F601D6D903ULL;
    zobrist_table[4][4][9] = 0xB080E0035E7F503CULL;
    zobrist_table[4][4][10] = 0xEECB325B064F768DULL;
    zobrist_table[4][4][11] = 0x3B9CEA959AD7558FULL;
    zobrist_table[4][4][12] = 0x2452BC39DBF2EED1ULL;
    zobrist_table[4][4][13] = 0x743C7E9D2FDEB035ULL;
    zobrist_table[4][5][0] = 0x7A089CA81CC5A8A0ULL;
    zobrist_table[4][5][1] = 0xB51D70D8582DD972ULL;
    zobrist_table[4][5][2] = 0x421AA15EF58C43CEULL;
    zobrist_table[4][5][3] = 0x726D44A215203C7ULL;
    zobrist_table[4][5][4] = 0x35475C5EF76DCE6EULL;
    zobrist_table[4][5][5] = 0x55C36C3D5CBBC080ULL;
    zobrist_table[4][5][6] = 0xF5FE0213792ECD75ULL;
    zobrist_table[4][5][7] = 0x4BDD5F994AE9EE11ULL;
    zobrist_table[4][5][8] = 0xE0DF7F74EFE78B60ULL;
    zobrist_table[4][5][9] = 0x8D9ECFB9F5492E22ULL;
    zobrist_table[4][5][10] = 0x53B53B92A2CB5F38ULL;
    zobrist_table[4][5][11] = 0x97D01E702F1D9BEFULL;
    zobrist_table[4][5][12] = 0x14AFE646FE3216BDULL;
    zobrist_table[4][5][13] = 0x88819F421A42B629ULL;
    zobrist_table[4][6][0] = 0x4EC985FF94B28B9DULL;
    zobrist_table[4][6][1] = 0x606821D6280A07EEULL;
    zobrist_table[4][6][2] = 0x259CFF81E5CE0CA6ULL;
    zobrist_table[4][6][3] = 0x200F7753F217FAACULL;
    zobrist_table[4][6][4] = 0x390A9016CDEC85DAULL;
    zobrist_table[4][6][5] = 0x8222134550DE4292ULL;
    zobrist_table[4][6][6] = 0x3C9590D33E2AAD3EULL;
    zobrist_table[4][6][7] = 0x2F16FB50C13E66AFULL;
    zobrist_table[4][6][8] = 0x5F59AA2C4A82E06AULL;
    zobrist_table[4][6][9] = 0xA9C72E7B6B770DF1ULL;
    zobrist_table[4][6][10] = 0xDC68D4FD0BD7696FULL;
    zobrist_table[4][6][11] = 0x99E8C82821DA132CULL;
    zobrist_table[4][6][12] = 0x64D027590542BD75ULL;
    zobrist_table[4][6][13] = 0xB3C161C313F2A37CULL;
    zobrist_table[4][7][0] = 0x21CC14B312BDF75FULL;
    zobrist_table[4][7][1] = 0x4CA49AAF6B944E09ULL;
    zobrist_table[4][7][2] = 0x6AB015638CFFBBB1ULL;
    zobrist_table[4][7][3] = 0xED28508DBDAA3BFAULL;
    zobrist_table[4][7][4] = 0x9750CA7E246CB09CULL;
    zobrist_table[4][7][5] = 0x4C4B91FE6C148FC6ULL;
    zobrist_table[4][7][6] = 0x5AC4B6C7A31034DDULL;
    zobrist_table[4][7][7] = 0x3F80C31F15A5712CULL;
    zobrist_table[4][7][8] = 0xA1FDCDF171DF24D9ULL;
    zobrist_table[4][7][9] = 0xA31559405E87905AULL;
    zobrist_table[4][7][10] = 0x877A2133F2ED33E1ULL;
    zobrist_table[4][7][11] = 0x605DD4D60ECFB95BULL;
    zobrist_table[4][7][12] = 0x2284FD9689BBA65ULL;
    zobrist_table[4][7][13] = 0xF642C8F36ACF49EBULL;
    zobrist_table[5][0][0] = 0xE6B920DABA6A098FULL;
    zobrist_table[5][0][1] = 0x70F8DD9952177EB7ULL;
    zobrist_table[5][0][2] = 0x5F20F4063438B4E4ULL;
    zobrist_table[5][0][3] = 0xF3CC9D8A4B1678E4ULL;
    zobrist_table[5][0][4] = 0x174F7A54788C161EULL;
    zobrist_table[5][0][5] = 0x2F7A304FF344C911ULL;
    zobrist_table[5][0][6] = 0x1BCE35D8CBE88A3FULL;
    zobrist_table[5][0][7] = 0x1CB66F6746E785ADULL;
    zobrist_table[5][0][8] = 0x9B050DB28EE4FD02ULL;
    zobrist_table[5][0][9] = 0x27649A62B02DE52CULL;
    zobrist_table[5][0][10] = 0xB3DD77E1CBB02FE9ULL;
    zobrist_table[5][0][11] = 0xEDA2FC4C7237D420ULL;
    zobrist_table[5][0][12] = 0x2F751BDE66163E5BULL;
    zobrist_table[5][0][13] = 0x6BF4D047C4841A8DULL;
    zobrist_table[5][1][0] = 0x2CBB93C26E84F8EAULL;
    zobrist_table[5][1][1] = 0xF5A3E8933F7A2748ULL;
    zobrist_table[5][1][2] = 0x5723A95974151ACCULL;
    zobrist_table[5][1][3] = 0x85FA2D5CEFE6171BULL;
    zobrist_table[5][1][4] = 0x5AF95C78247F4D97ULL;
    zobrist_table[5][1][5] = 0xA1AB17C0766229CCULL;
    zobrist_table[5][1][6] = 0x1624D318A32652E8ULL;
    zobrist_table[5][1][7] = 0xC149FA8E7BB8C2F1ULL;
    zobrist_table[5][1][8] = 0x4B7350D13421BEAFULL;
    zobrist_table[5][1][9] = 0xD48644820078CB12ULL;
    zobrist_table[5][1][10] = 0x72F774B1B2F11EF9ULL;
    zobrist_table[5][1][11] = 0x764657CA9E65736CULL;
    zobrist_table[5][1][12] = 0x37FEF6B501FDA698ULL;
    zobrist_table[5][1][13] = 0x1D4D11804C6E6FBBULL;
    zobrist_table[5][2][0] = 0xFA92CD28C4C536FBULL;
    zobrist_table[5][2][1] = 0x4D18C103A100ED14ULL;
    zobrist_table[5][2][2] = 0x9BF1F1D18B92C247ULL;
    zobrist_table[5][2][3] = 0x6C98F73D27FE1B4BULL;
    zobrist_table[5][2][4] = 0xC058A332B4CFAFA8ULL;
    zobrist_table[5][2][5] = 0x17B18E6E78AFF58EULL;
    zobrist_table[5][2][6] = 0x7F67EE1AAD9D1F42ULL;
    zobrist_table[5][2][7] = 0xF5FEBA5EC2953F51ULL;
    zobrist_table[5][2][8] = 0x8B32992A3B7C1F9AULL;
    zobrist_table[5][2][9] = 0x67C21355C3121AF6ULL;
    zobrist_table[5][2][10] = 0xA1CF0D1D47B3DF41ULL;
    zobrist_table[5][2][11] = 0x588D91DFBE86A8EULL;
    zobrist_table[5][2][12] = 0x4523DBBB1EEED219ULL;
    zobrist_table[5][2][13] = 0xAB2212C9E23B580EULL;
    zobrist_table[5][3][0] = 0x1098240A614BE3ULL;
    zobrist_table[5][3][1] = 0x65FF6ADC41AEF3F7ULL;
    zobrist_table[5][3][2] = 0xE3FBDBDA86AE9D5CULL;
    zobrist_table[5][3][3] = 0xB5C03F6F94E4CC44ULL;
    zobrist_table[5][3][4] = 0x71D04B0F656FA7E6ULL;
    zobrist_table[5][3][5] = 0xBF1DF6871A1EC042ULL;
    zobrist_table[5][3][6] = 0x5A9414B840AAEC7AULL;
    zobrist_table[5][3][7] = 0xDF0D6301488CAC4EULL;
    zobrist_table[5][3][8] = 0xAC2C10D0C15648FFULL;
    zobrist_table[5][3][9] = 0x322F1499E8A56F31ULL;
    zobrist_table[5][3][10] = 0x15D38CA9986CC8D5ULL;
    zobrist_table[5][3][11] = 0x120961EA09135087ULL;
    zobrist_table[5][3][12] = 0x4332559DCAD00273ULL;
    zobrist_table[5][3][13] = 0x889C8AE24E3C0F2DULL;
    zobrist_table[5][4][0] = 0x1E415C4E57030EDEULL;
    zobrist_table[5][4][1] = 0xDC0520A487BA3B90ULL;
    zobrist_table[5][4][2] = 0xE404D8083FC18C00ULL;
    zobrist_table[5][4][3] = 0xC31277FDEB83AF16ULL;
    zobrist_table[5][4][4] = 0x116E8A6429DEB984ULL;
    zobrist_table[5][4][5] = 0xDC66A27B6A325333ULL;
    zobrist_table[5][4][6] = 0x48622A674A294067ULL;
    zobrist_table[5][4][7] = 0x226962278513D91EULL;
    zobrist_table[5][4][8] = 0x85E7425092F078B8ULL;
    zobrist_table[5][4][9] = 0x35D4CD35A08C3A00ULL;
    zobrist_table[5][4][10] = 0x1AF55C2688083EBCULL;
    zobrist_table[5][4][11] = 0xF4A5CC36692A7BCEULL;
    zobrist_table[5][4][12] = 0x8B279C29A274C0D7ULL;
    zobrist_table[5][4][13] = 0xBDCE29EF674610EBULL;
    zobrist_table[5][5][0] = 0xE76F8A76C74F11CDULL;
    zobrist_table[5][5][1] = 0x47534952C9C5FEF1ULL;
    zobrist_table[5][5][2] = 0x713ECEB14AD12B4CULL;
    zobrist_table[5][5][3] = 0x9177B6D45F2E9167ULL;
    zobrist_table[5][5][4] = 0x2347B24FA0F9C074ULL;
    zobrist_table[5][5][5] = 0x1F9078D52835BCDBULL;
    zobrist_table[5][5][6] = 0x1EDA4209B270AF55ULL;
    zobrist_table[5][5][7] = 0x66B6208761A53FDDULL;
    zobrist_table[5][5][8] = 0x77CB1A27974FDEDCULL;
    zobrist_table[5][5][9] = 0x8F42CEBE23B870F3ULL;
    zobrist_table[5][5][10] = 0x4C88B9D8AB12FB53ULL;
    zobrist_table[5][5][11] = 0xA1D20EBC5AA3892AULL;
    zobrist_table[5][5][12] = 0xBE0A5A5679009C61ULL;
    zobrist_table[5][5][13] = 0x37CF80256A447A90ULL;
    zobrist_table[5][6][0] = 0x7D25CEFB7A0A02BAULL;
    zobrist_table[5][6][1] = 0x8066B49BB1D792A0ULL;
    zobrist_table[5][6][2] = 0x7E22E1B751783032ULL;
    zobrist_table[5][6][3] = 0xF55B2E5CA6ED0AC0ULL;
    zobrist_table[5][6][4] = 0x71A8C9C60F6AB75BULL;
    zobrist_table[5][6][5] = 0x248F4A254CD8EF24ULL;
    zobrist_table[5][6][6] = 0x7EDA9AB9BEC60FFEULL;
    zobrist_table[5][6][7] = 0xE32866D30D6A78B0ULL;
    zobrist_table[5][6][8] = 0x3739076A9F032CDCULL;
    zobrist_table[5][6][9] = 0x5AFB9565068A3C38ULL;
    zobrist_table[5][6][10] = 0x641659C078B61DAFULL;
    zobrist_table[5][6][11] = 0xFE2D9D1DE377B008ULL;
    zobrist_table[5][6][12] = 0xD8A230DE02969326ULL;
    zobrist_table[5][6][13] = 0xFA999F9B86DE3365ULL;
    zobrist_table[5][7][0] = 0xAFD8643211035083ULL;
    zobrist_table[5][7][1] = 0x14D4DAD6DDFAE808ULL;
    zobrist_table[5][7][2] = 0xF305EE95AFB120F4ULL;
    zobrist_table[5][7][3] = 0xECB3D561BDF0B015ULL;
    zobrist_table[5][7][4] = 0x65264961AB4414AEULL;
    zobrist_table[5][7][5] = 0x5C7CBC6201A4F7A1ULL;
    zobrist_table[5][7][6] = 0x1DBC24FD0A8AA1E4ULL;
    zobrist_table[5][7][7] = 0xF520F49EF1C846ULL;
    zobrist_table[5][7][8] = 0x453432CDFFEB5D5FULL;
    zobrist_table[5][7][9] = 0xA3EF802EDF8693CEULL;
    zobrist_table[5][7][10] = 0x4AE302F3B31E9BE8ULL;
    zobrist_table[5][7][11] = 0xE695F8BABA2338FEULL;
    zobrist_table[5][7][12] = 0x240397213A082921ULL;
    zobrist_table[5][7][13] = 0x92A651D7C069C542ULL;
    zobrist_table[6][0][0] = 0x30F2C48549B564FBULL;
    zobrist_table[6][0][1] = 0x6F1BDD071AFF71AEULL;
    zobrist_table[6][0][2] = 0xB7626F4975FD3537ULL;
    zobrist_table[6][0][3] = 0x62565A955487B5C3ULL;
    zobrist_table[6][0][4] = 0x54A8762B2B12C92CULL;
    zobrist_table[6][0][5] = 0xA5E3A7196BF52DFDULL;
    zobrist_table[6][0][6] = 0xAFFE2554E5AEF699ULL;
    zobrist_table[6][0][7] = 0x25E4979D6F6DDF79ULL;
    zobrist_table[6][0][8] = 0xEEE84BCB7281B8A9ULL;
    zobrist_table[6][0][9] = 0x25C29B6AB575BC6EULL;
    zobrist_table[6][0][10] = 0x50EA1324862F78E1ULL;
    zobrist_table[6][0][11] = 0x35783F662114C2D6ULL;
    zobrist_table[6][0][12] = 0x2FD3B9F2E90F79F8ULL;
    zobrist_table[6][0][13] = 0x596305B371B221E4ULL;
    zobrist_table[6][1][0] = 0xFBC59E92CA1209ADULL;
    zobrist_table[6][1][1] = 0x6D62E40C638D521AULL;
    zobrist_table[6][1][2] = 0x7DF0FE6BCE8D75F2ULL;
    zobrist_table[6][1][3] = 0xBAD3116B63B8A897ULL;
    zobrist_table[6][1][4] = 0xCBAB5B51385C5FDCULL;
    zobrist_table[6][1][5] = 0x707421D43239D04BULL;
    zobrist_table[6][1][6] = 0x344AF454F0A61C5EULL;
    zobrist_table[6][1][7] = 0xB5C25D429626D8C4ULL;
    zobrist_table[6][1][8] = 0xE7E3F52C0CBF404DULL;
    zobrist_table[6][1][9] = 0x884FD16636ABF8CULL;
    zobrist_table[6][1][10] = 0xA217CF253BE95767ULL;
    zobrist_table[6][1][11] = 0xDEFA786415AC15C3ULL;
    zobrist_table[6][1][12] = 0x5D158E442FCF3B87ULL;
    zobrist_table[6][1][13] = 0xBE3FEAFD0E96ED9BULL;
    zobrist_table[6][2][0] = 0xAD7027CFA358CB1DULL;
    zobrist_table[6][2][1] = 0x3BAA17F92C623AC3ULL;
    zobrist_table[6][2][2] = 0x4C2ABDAA9C5C11EBULL;
    zobrist_table[6][2][3] = 0x162D5C729CCD3E1FULL;
    zobrist_table[6][2][4] = 0xDE6C8762B475E15EULL;
    zobrist_table[6][2][5] = 0xC061C99B831A352AULL;
    zobrist_table[6][2][6] = 0xC57C799848D002BEULL;
    zobrist_table[6][2][7] = 0xE2091F49E0A10D2BULL;
    zobrist_table[6][2][8] = 0x6953A1155A62DDC4ULL;
    zobrist_table[6][2][9] = 0xDCF035B7552C6E8ULL;
    zobrist_table[6][2][10] = 0xB261D0D2A1C2D9BFULL;
    zobrist_table[6][2][11] = 0xAA66B4648420B8D9ULL;
    zobrist_table[6][2][12] = 0xA604E5AFF4DB1C1EULL;
    zobrist_table[6][2][13] = 0x8C141838F46860A2ULL;
    zobrist_table[6][3][0] = 0xBC02BA67EE04BDDEULL;
    zobrist_table[6][3][1] = 0x6E3C18C9EF1FA0A3ULL;
    zobrist_table[6][3][2] = 0x7460D20D94B9CDB5ULL;
    zobrist_table[6][3][3] = 0x413770E27D7DE1F5ULL;
    zobrist_table[6][3][4] = 0x79C45C38B440FFE0ULL;
    zobrist_table[6][3][5] = 0x56525CE03725BD0CULL;
    zobrist_table[6][3][6] = 0xACFEBA4441030AEULL;
    zobrist_table[6][3][7] = 0xD7422560B36F3CDULL;
    zobrist_table[6][3][8] = 0x598CA3B429B10823ULL;
    zobrist_table[6][3][9] = 0x4A30F7CD00FDEC23ULL;
    zobrist_table[6][3][10] = 0x1D34690A795AC54ULL;
    zobrist_table[6][3][11] = 0x104DFF6623F1B67EULL;
    zobrist_table[6][3][12] = 0x6D80AB08C963D148ULL;
    zobrist_table[6][3][13] = 0x38DFE76BAE358290ULL;
    zobrist_table[6][4][0] = 0x9BCFB1C4F87E3560ULL;
    zobrist_table[6][4][1] = 0x8EC9EA986581F934ULL;
    zobrist_table[6][4][2] = 0x3891AEF5EBE0572CULL;
    zobrist_table[6][4][3] = 0x315E80807425F4E9ULL;
    zobrist_table[6][4][4] = 0x9BBAC83856E9B78DULL;
    zobrist_table[6][4][5] = 0x9B3A0C891A32E148ULL;
    zobrist_table[6][4][6] = 0x15EB3A3DE2014A45ULL;
    zobrist_table[6][4][7] = 0x51ABF5E5CB775E24ULL;
    zobrist_table[6][4][8] = 0x8930D17952AB793FULL;
    zobrist_table[6][4][9] = 0xE4BACD7874ABA9FCULL;
    zobrist_table[6][4][10] = 0x4168705A533C9A31ULL;
    zobrist_table[6][4][11] = 0x85A1282A0761585BULL;
    zobrist_table[6][4][12] = 0x30AC79DD0B5AAFEFULL;
    zobrist_table[6][4][13] = 0x14827A895E6364C6ULL;
    zobrist_table[6][5][0] = 0xDEB4E6C435A7C6EDULL;
    zobrist_table[6][5][1] = 0x5882E3BB864696C1ULL;
    zobrist_table[6][5][2] = 0xD658B1B33012AE1CULL;
    zobrist_table[6][5][3] = 0x4053B188339D78F5ULL;
    zobrist_table[6][5][4] = 0xBAA172ACAC33F644ULL;
    zobrist_table[6][5][5] = 0x4D236555BC5074ACULL;
    zobrist_table[6][5][6] = 0x845398134FEE7144ULL;
    zobrist_table[6][5][7] = 0x6279D944DC2897C6ULL;
    zobrist_table[6][5][8] = 0x7B69E69041300879ULL;
    zobrist_table[6][5][9] = 0xDF39CCAA580C79FCULL;
    zobrist_table[6][5][10] = 0x3D6E2667B6651D6EULL;
    zobrist_table[6][5][11] = 0x4E49DF560B648ACDULL;
    zobrist_table[6][5][12] = 0x8D4E2753EF26A5B7ULL;
    zobrist_table[6][5][13] = 0x25B7C5F1284B9D7ULL;
    zobrist_table[6][6][0] = 0x7ECC040C75FF93F0ULL;
    zobrist_table[6][6][1] = 0x702DC88AB97FB3BBULL;
    zobrist_table[6][6][2] = 0xEACA38110C26E5D9ULL;
    zobrist_table[6][6][3] = 0x6980B561CF1ACCC1ULL;
    zobrist_table[6][6][4] = 0x7E5B637DFA98C115ULL;
    zobrist_table[6][6][5] = 0x70AAF52575E417DDULL;
    zobrist_table[6][6][6] = 0x15EAE9D21E3D59D0ULL;
    zobrist_table[6][6][7] = 0x3DBBA3AF14DBAD22ULL;
    zobrist_table[6][6][8] = 0xD3861B58194665D3ULL;
    zobrist_table[6][6][9] = 0x275F275CC3F3F74DULL;
    zobrist_table[6][6][10] = 0xE25E651269FCBEF0ULL;
    zobrist_table[6][6][11] = 0x36A5BE06EB52EE01ULL;
    zobrist_table[6][6][12] = 0x9CDD9F6C70CDC4A8ULL;
    zobrist_table[6][6][13] = 0xD16903F213BFA9FEULL;
    zobrist_table[6][7][0] = 0x8F1B5BE16D4BA69CULL;
    zobrist_table[6][7][1] = 0xE2F88051C13C6688ULL;
    zobrist_table[6][7][2] = 0x64FC0DBAD44F85E7ULL;
    zobrist_table[6][7][3] = 0xF57B8A920A12F3B3ULL;
    zobrist_table[6][7][4] = 0x3FEE2FC72E2DFFDFULL;
    zobrist_table[6][7][5] = 0x38553AC87D718591ULL;
    zobrist_table[6][7][6] = 0xD728525620CA35ABULL;
    zobrist_table[6][7][7] = 0x476C4878DEFFED7AULL;
    zobrist_table[6][7][8] = 0x5A23754BEF38D426ULL;
    zobrist_table[6][7][9] = 0xFEA2A33A51D11BCDULL;
    zobrist_table[6][7][10] = 0x1B770DEB6F51EA78ULL;
    zobrist_table[6][7][11] = 0xE64DDD918E9B185EULL;
    zobrist_table[6][7][12] = 0x9C2E55624916E844ULL;
    zobrist_table[6][7][13] = 0xC9FE60368A83EFC8ULL;
    zobrist_table[7][0][0] = 0xB6088C973380DCFCULL;
    zobrist_table[7][0][1] = 0xC707E77B4BF0AE53ULL;
    zobrist_table[7][0][2] = 0x8397D4127118BB71ULL;
    zobrist_table[7][0][3] = 0x764AB5109ACBA588ULL;
    zobrist_table[7][0][4] = 0xA2652C9E89421C6DULL;
    zobrist_table[7][0][5] = 0x45C596D442D01BA3ULL;
    zobrist_table[7][0][6] = 0x43D2C473B56735EULL;
    zobrist_table[7][0][7] = 0x9D683A9E1E651AC1ULL;
    zobrist_table[7][0][8] = 0xB63F83C6C89309E9ULL;
    zobrist_table[7][0][9] = 0x2C2DF3C219518F87ULL;
    zobrist_table[7][0][10] = 0x6A27241FBB9E5A02ULL;
    zobrist_table[7][0][11] = 0x37D316A43FAFA217ULL;
    zobrist_table[7][0][12] = 0xE139D15D48D8B9EFULL;
    zobrist_table[7][0][13] = 0xFF4533FEBC6FF6ACULL;
    zobrist_table[7][1][0] = 0x1A6009EA8DCE886ULL;
    zobrist_table[7][1][1] = 0x89181BA3BDEE9231ULL;
    zobrist_table[7][1][2] = 0x6DA313E783E9973BULL;
    zobrist_table[7][1][3] = 0xCBDC014DBEDB42EULL;
    zobrist_table[7][1][4] = 0x627B585F1F2DE275ULL;
    zobrist_table[7][1][5] = 0x45C190A8A52BA0CEULL;
    zobrist_table[7][1][6] = 0xF89D3FDA1E454241ULL;
    zobrist_table[7][1][7] = 0x908E0372BCBE9A42ULL;
    zobrist_table[7][1][8] = 0x3AC49EFA5BE12D09ULL;
    zobrist_table[7][1][9] = 0xB76FC5B2ACC512DFULL;
    zobrist_table[7][1][10] = 0x8BF06F64B4178592ULL;
    zobrist_table[7][1][11] = 0x483C1A4EA91DA2CDULL;
    zobrist_table[7][1][12] = 0xBD6817B638B80611ULL;
    zobrist_table[7][1][13] = 0xE6CD3595D4F0D65DULL;
    zobrist_table[7][2][0] = 0x1095E4973D798F0BULL;
    zobrist_table[7][2][1] = 0x4EB9876884A5B1C3ULL;
    zobrist_table[7][2][2] = 0x53CA8C05ACB5959FULL;
    zobrist_table[7][2][3] = 0x5F89D54D3BCD6AECULL;
    zobrist_table[7][2][4] = 0x7AF2F402A0E624F1ULL;
    zobrist_table[7][2][5] = 0x9501E917496DC27BULL;
    zobrist_table[7][2][6] = 0x23254D812BDFB727ULL;
    zobrist_table[7][2][7] = 0x3F7BA05CF4BB315ULL;
    zobrist_table[7][2][8] = 0x813DD49A8D99743CULL;
    zobrist_table[7][2][9] = 0x5DF2E07353F04099ULL;
    zobrist_table[7][2][10] = 0xA283453695DECD6EULL;
    zobrist_table[7][2][11] = 0xCFDEF30306792B47ULL;
    zobrist_table[7][2][12] = 0xE0789F97213C121CULL;
    zobrist_table[7][2][13] = 0x27BE03816544C97DULL;
    zobrist_table[7][3][0] = 0x2D4076BCF9CB2EE8ULL;
    zobrist_table[7][3][1] = 0xFDC1293082AE752FULL;
    zobrist_table[7][3][2] = 0x22B56BE11392A255ULL;
    zobrist_table[7][3][3] = 0x34DD7624C3D9B3B0ULL;
    zobrist_table[7][3][4] = 0xEA455FC7C80CB483ULL;
    zobrist_table[7][3][5] = 0x7F2A2E65C6596F7FULL;
    zobrist_table[7][3][6] = 0xC46AC0D691CA9F9EULL;
    zobrist_table[7][3][7] = 0xF8247E70B2194FF3ULL;
    zobrist_table[7][3][8] = 0x3C3DA91136A52DF9ULL;
    zobrist_table[7][3][9] = 0x21D32E24BB891746ULL;
    zobrist_table[7][3][10] = 0x3BD3147DD0F0C75DULL;
    zobrist_table[7][3][11] = 0x62759469C28D2AD5ULL;
    zobrist_table[7][3][12] = 0x9BC698825A7C831AULL;
    zobrist_table[7][3][13] = 0x21EE302E974D9D49ULL;
    zobrist_table[7][4][0] = 0x7F9B76EFA1057256ULL;
    zobrist_table[7][4][1] = 0xEAF94919E69B7971ULL;
    zobrist_table[7][4][2] = 0x9DB3466D1BA6CC61ULL;
    zobrist_table[7][4][3] = 0x6A8E22FD57CAF0DULL;
    zobrist_table[7][4][4] = 0x989BB03086C47B06ULL;
    zobrist_table[7][4][5] = 0x7D3C279B5BCE228BULL;
    zobrist_table[7][4][6] = 0x4F06EA1874A26444ULL;
    zobrist_table[7][4][7] = 0xF568C9C6033C1469ULL;
    zobrist_table[7][4][8] = 0x8E36B82F3856BE31ULL;
    zobrist_table[7][4][9] = 0x29BCCEE9A71B80EFULL;
    zobrist_table[7][4][10] = 0xE10B4AADA92D6B05ULL;
    zobrist_table[7][4][11] = 0xCF2A21987EA496F5ULL;
    zobrist_table[7][4][12] = 0xBCC4616DF40D2A37ULL;
    zobrist_table[7][4][13] = 0x8BC88BCF7B1D4049ULL;
    zobrist_table[7][5][0] = 0xB4480761505E9C9BULL;
    zobrist_table[7][5][1] = 0x142A6C95D9082A42ULL;
    zobrist_table[7][5][2] = 0x232F8C5B425832C0ULL;
    zobrist_table[7][5][3] = 0x66DFEB1E9AB3CC27ULL;
    zobrist_table[7][5][4] = 0x30E9BE17B4134208ULL;
    zobrist_table[7][5][5] = 0x5100F186D25AB049ULL;
    zobrist_table[7][5][6] = 0x4AAEB212C90DED29ULL;
    zobrist_table[7][5][7] = 0xF19B43DA6253DFE3ULL;
    zobrist_table[7][5][8] = 0x356AF7370F2670D2ULL;
    zobrist_table[7][5][9] = 0x50AE265209CD3BDFULL;
    zobrist_table[7][5][10] = 0xBF401E04B9F94EC6ULL;
    zobrist_table[7][5][11] = 0x3FE65F90F631681EULL;
    zobrist_table[7][5][12] = 0xDCEB201357D9AF8DULL;
    zobrist_table[7][5][13] = 0xAB1E679470F2297AULL;
    zobrist_table[7][6][0] = 0xA8E6A772B9CDE60CULL;
    zobrist_table[7][6][1] = 0x39D5B552A867A0F0ULL;
    zobrist_table[7][6][2] = 0x581BA30742965873ULL;
    zobrist_table[7][6][3] = 0x298E9A79ABECFC0BULL;
    zobrist_table[7][6][4] = 0x45892C14E0E15D3ULL;
    zobrist_table[7][6][5] = 0x92D6FF735B3A4595ULL;
    zobrist_table[7][6][6] = 0xEE5144D8A1D8B42ULL;
    zobrist_table[7][6][7] = 0xA1645F58BB78EB2DULL;
    zobrist_table[7][6][8] = 0x5A79B46A26B61B06ULL;
    zobrist_table[7][6][9] = 0x7DB931CE05A0F421ULL;
    zobrist_table[7][6][10] = 0xFB2DE1EA0B976C2ULL;
    zobrist_table[7][6][11] = 0x3DD0C8660649DEF5ULL;
    zobrist_table[7][6][12] = 0x32F594D0B82B61CULL;
    zobrist_table[7][6][13] = 0xF20E8BDA39CC6D88ULL;
    zobrist_table[7][7][0] = 0x53A081A6A7647989ULL;
    zobrist_table[7][7][1] = 0xD22A3A6211091978ULL;
    zobrist_table[7][7][2] = 0x584D3C020FF9D318ULL;
    zobrist_table[7][7][3] = 0xA9FA4EA6F8DB1A4DULL;
    zobrist_table[7][7][4] = 0x22C71D046C32FAFFULL;
    zobrist_table[7][7][5] = 0xEC071CF1E47638ECULL;
    zobrist_table[7][7][6] = 0x72EF7DCE376E22A6ULL;
    zobrist_table[7][7][7] = 0x245DB6CA6F6A2196ULL;
    zobrist_table[7][7][8] = 0x4FDC13515BA830DCULL;
    zobrist_table[7][7][9] = 0xA629D3322D4BA5A4ULL;
    zobrist_table[7][7][10] = 0xBA626AEE542D19C0ULL;
    zobrist_table[7][7][11] = 0xC90853FDFC9EA692ULL;
    zobrist_table[7][7][12] = 0x689C0559BF4FA4A3ULL;
    zobrist_table[7][7][13] = 0x27752FE61F68C6EULL;
    zobrist_white_castle_king = 0xE413961F68C6DD5EULL;
    zobrist_white_castle_queen = 0x88A0EDCE4384860CULL;
    zobrist_black_castle_king = 0xCDFA4CC88805AE31ULL;
    zobrist_black_castle_queen = 0xFB0A6A90BC52B34EULL;
    zobrist_blacks_turn = 0xB476998DAFC8128AULL;
}


const Zobrist zobrist = Zobrist();
									