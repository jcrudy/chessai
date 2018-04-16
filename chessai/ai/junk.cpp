
negamax_result negamax(boardstate *brd, double prob, double threshold, double alpha, 
						double beta, move *best_move, bool *stop, TranspositionTable *tt,
						int depth, unsigned long long int *node_count){
	std::queue<move> moves = std::queue<move>();
	int num_moves;
	negamax_result result;
	negamax_result subresult;
	if(current >= threshold){
		// Generate all legal moves
		all_moves(brd, moves);
		num_moves = moves.size();
		
		// If there are no legal moves, this is either checkmate or stalemate
		if (num_moves == 0) {
			if (own_check(brd)){
				result.value = -200000.0; // checkmate!
				result.lower_bound = false;
				result.upper_bound = false;
				return result;
			} else {
				result.value = 0.0; // stalemate
				result.lower_bound = false;
				result.upper_bound = false;
				return result;
			}
		} 
	} else {
		// Quiescence mode
		all_captures(brd, moves);
		num_moves = moves.size();
		if(num_moves == 0){
			if (own_check(brd)){
				all_moves(brd, moves);
				if (moves.size() == 0) {
					result.value = -200000.0; // checkmate!
					result.lower_bound = false;
					result.upper_bound = false;
					return result
				} else {
					result.value = simple_evaluation(brd);
					result.lower_bound = false;
					result.upper_bound = false;
					return result;
				}
			} else {
				result.value = simple_evaluation(brd);
				result.lower_bound = false;
				result.upper_bound = false;
				return result;
			}
		}
	}
	
	// If we got here, then current >= threshold because otherwise we 
	// would return early in the above else block.
	double value;
	move best_counter;
	move mv;
	bool init = true;
	moverecord rec;
	double quotient = current / num_moves;
	transposition_entry entry;
	smallboardstate smallbrd;
	
	bool eliminated;
	if(tt != NULL){
		// Go through all moves once and check for transposition table entries.
		for(int i=0;i<num_moves;i++){
			eliminated = false;
			mv = moves.front();
			moves.pop();
			rec = make_move(brd, &mv);
			(*node_count)++;
			
			entry = tt->getitem(brd);
			if(entry != empty_transposition_entry){
				if(entry.prob >= prob){
					if(entry.value.lower_bound){
						// This is an upper bound on our result
						if(-entry.value.value < alpha){
							eliminated = true;
						}
					} else {
						eliminated = true;
						if(-entry.value.value >= alpha){
							result.value = -entry.value.value;
							result.lower_bound = false;
							alpha = result.value;
						}
					}
				} else {
					// In this case, a deeper search may yield a 
					// higher value for entry.value.value
					if(-entry.value.value < alpha){
						eliminated = true;
					}
				}
			}
			// TODO: Fill in here
			
			
			
			// Done with this move...
			unmake_move(brd, &rec);
			if(!eliminated){
				// for now!
				moves.push(mv);
			}
			
		}
	
	}
	
}

negamax_result negafrax(boardstate *brd, double current, double threshold, double alpha, 
				double beta, move *best_move, bool *stop, TranspositionTable *tt, int depth,
				unsigned long long int *node_count){
	std::queue<move> moves = std::queue<move>();
	int num_moves;
	negamax_result result;
	if(current >= threshold){
		// Generate all legal moves
		all_moves(brd, moves);
		num_moves = moves.size();
		
		// If there are no legal moves, this is either checkmate or stalemate
		if (num_moves == 0) {
			if (own_check(brd)){
				return -200000.0; // checkmate!
			} else {
				return 0.0; // stalemate
			}
		}
	} else {
		// Quiescence mode
		EASY_BLOCK("Quiescence");
		all_captures(brd, moves);
		num_moves = moves.size();
		if(num_moves == 0){
			if (own_check(brd)){
				all_moves(brd, moves);
				if (moves.size() == 0) {
					return -200000.0; // checkmate!
				} else {
					return simple_evaluation(brd);
				}
			} else {
				return simple_evaluation(brd);
			}
		}
		EASY_END_BLOCK;
	}
	
	double value;
	move best_counter;
	move mv;
	bool init = true;
	moverecord rec;
	double quotient = current / num_moves;
	transposition_entry entry;
	smallboardstate smallbrd;
	
	// First look at moves that have a transposition table entry
	EASY_BLOCK("Transposition table lookup");
	bool eliminated;
	if(tt != NULL){
		for(int i=0;i<num_moves;i++){
			eliminated = false;
			mv = moves.front();
			moves.pop();
			rec = make_move(brd, &mv);
			(*node_count)++;
			entry = tt->getitem(brd);
			
			if(!(entry == empty_transposition_entry)){
				if(entry.value.value > result.value){
					result = entry.value;
					if(!entry.value.lower_bound || 
					if(entry.value.lower_bound){
						result = entry.value;
						
					} else {
						result.value = value;
						result.lower_bound = false;
						eliminated = true;
					}
				}
				if(result.value > alpha){
					alpha = result.value;
				}
			}
			
			if(entry.key == brd->hash && 
			   entry.prob >= quotient && entry.alpha <= -beta 
			   && entry.beta >= -alpha){
				value = entry.value;
				best_counter = entry.best_move;
				unmake_move(brd, &rec);
				if(value > alpha){
					alpha = value;
				}
				if(init){
					result.value = value;
					result.lower_bound = false;
					*best_move = mv;
					init = false;
				}
				if(value > best_value){
					result.value = value;
					*best_move = mv;
				}
				if(alpha > beta || (*stop)){
					result.lower_bound = true;
					break;
				}
			
			} else {
				moves.push(mv);
				unmake_move(brd, &rec);
				continue;
			}
			
		}
	}
	EASY_END_BLOCK;
	
	// Now look at moves we haven't searched sufficiently yet
	EASY_BLOCK("Recurse");
//	num_moves = moves.size();
//	quotient = current / num_moves;
	negamax_result subresult;
	while(!moves.empty()){
		mv = moves.front();
		moves.pop();
		rec = make_move(brd, &mv);
		(*node_count)++;
		subresult = negafrax(brd, quotient, threshold, -beta, -alpha, &best_counter, stop, tt, depth+1, node_count);
		value = -subresult.value;
		if(tt != NULL){
			entry.key = brd->hash;
			entry.prob = quotient;
			entry.value = subresult;
			entry.best_move = best_counter;
			entry.brd = smallify(brd);
			tt->setitem(brd, entry);
		}
		unmake_move(brd, &rec);
		if(value > alpha){
			alpha = value;
		}
		if(init){
			result.value = value;
			result.lower_bound = false;
			*best_move = mv;
			init = false;
		}
		if(value > best_value){
			result.value = value;
			*best_move = mv;
		}
		if(alpha > beta || (*stop)){
			result.lower_bound = true;
			break;
		}
	}
	EASY_END_BLOCK;
	
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

