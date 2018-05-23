#include "movesearch.h"

const AlphaBetaValue empty_alpha_beta_value = AlphaBetaValue();
const TranspositionEntry null_te = TranspositionEntry();
const EvaluationEntry null_ee = EvaluationEntry();
const int SimpleEvaluation::infinity = 1000000;
const int SimpleEvaluation::mate = 200000;
const int SimpleEvaluation::draw = 0;
const int SimpleEvaluation::delta = 1000;
const int LogisticEvaluation::infinity = 10000000;
const int LogisticEvaluation::mate = 9000000;
const int LogisticEvaluation::draw = 0;
const int LogisticEvaluation::delta = 28000;
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
TranspositionTable::TranspositionTable(size_t size) {
	initialize(size);
}

TranspositionEntry TranspositionTable::getitem(GameState &game){
	if(size == 0){
		return null_te;
	}
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
	if(size == 0){
		return;
	}
	bool maximize = game.board_state.whites_turn;
	size_t index = getindex(game);
	TranspositionEntry old = data[index][0];
	if(old == null_te){
		// There's nothing here yet
		data[index][0] = entry;
		return;
	}else if(old.key == entry.key && old.brd == entry.brd && old.depth < entry.depth){
		// Replace with deeper result
		data[index][0] = entry;
		return;
	}

	// If we got here, the best entry didn't get replaced.  Then we
	// replace the other entry unless it's the same position at a greater
	// depth or width
	old = data[index][1];
	if(old.key == entry.key && old.brd == entry.brd &&
	   (old.depth > entry.depth || (entry.depth == old.depth && (entry.fail_low || entry.fail_high)))){
		// Do not replace
	}else{
		data[index][1] = entry;
		return;
	}
}



void EvaluationTable::initialize(size_t size){
	this->size = size;
	this->data = new EvaluationEntry[size];
	for(size_t i=0;i<size;i++){
		this->data[i] = null_ee;
	}
}
EvaluationTable::EvaluationTable(size_t size) {
	initialize(size);
}

EvaluationEntry EvaluationTable::getitem(GameState &game){
	if(size == 0){
		return null_ee;
	}
	size_t index = getindex(game);
	EvaluationEntry candidate = data[index];
	if(candidate.key == game.hash && candidate.brd == game.board_state){
		return candidate;
	}
	return null_ee;
}

void EvaluationTable::setitem(GameState &game, const EvaluationEntry &entry){
	if(size == 0){
		return;
	}
	size_t index = getindex(game);
	data[index] = entry;
}

