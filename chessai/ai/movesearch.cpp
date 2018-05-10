#include "movesearch.h"

const AlphaBetaValue empty_alpha_beta_value = AlphaBetaValue();
const TranspositionEntry null_te = TranspositionEntry();
const float SimpleEvaluation::mate = 200000;
const float SimpleEvaluation::draw = 0;
const float SimpleEvaluation::delta = 1000;
const int KillerTable::num_ply = 200;

void TranspositionTable::initialize(size_t size){
	this->size = size;
	this->data = new TranspositionEntry[size][2];
	for(unsigned long int i=0;i<size;i++){
		for(int j=0;j<2;j++){
			this->data[i][j] = null_te;
		}
	}
}

TranspositionEntry TranspositionTable::getitem(GameState &game){
	size_t index = getindex(game);
	TranspositionEntry candidate = data[index][0];
	if(candidate.key == game.hash && candidate.brd == game.board_state){
		return candidate;
	}
	candidate = data[index][1];
	if(candidate.key == game.hash && candidate.brd == game.board_state){
		return candidate;
	}
	return null_te;
}

void TranspositionTable::setitem(GameState &game, const TranspositionEntry &entry){
	bool maximize = game.board_state.whites_turn;
	size_t index = getindex(game);
	TranspositionEntry old = data[index][0];
	if(old == null_te){
		// There's nothing here yet
		data[index][0] = entry;
		return;
	}else if(old.key == entry.key && old.brd == entry.brd &&
			 (old.depth < entry.depth || (entry.depth == old.depth && (old.value.fail_low || old.value.fail_high)))){
		// The same position but scored to greater depth
		data[index][0] = entry;
		return;
	}
	if(maximize){
		if(old.value.fail_low && !entry.value.fail_low){
			data[index][0] = entry;
			return;
		}else if(old.value.value < entry.value.value){
			data[index][0] = entry;
			return;
		}
	}else{
		if(old.value.fail_high && !entry.value.fail_high){
			data[index][0] = entry;
			return;
		}else if(old.value.value > entry.value.value){
			data[index][0] = entry;
			return;
		}
	}

	// If we got here, the best entry didn't get replaced.  Then we
	// replace the other entry unless it's the same position at a greater
	// depth or width
	old = data[index][1];
	if(old.key == entry.key && old.brd == entry.brd &&
	   (old.depth > entry.depth || (entry.depth == old.depth && (entry.value.fail_low || entry.value.fail_high)))){
		// Do not replace
	}else{
		data[index][1] = entry;
		return;
	}
}
