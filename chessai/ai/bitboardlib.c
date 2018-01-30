#include "bitboardlib.h"

void bitboard_to_arr(boardstate *bb, char* arr){
	int i;
	bitboard mask;
	for (i=0; i<64; i++){
		mask = places[i];
		if (bb->white & mask){
			if (bb->k & mask){
				arr[i] = 'K';
				continue;
			}
			if (bb->q & mask){
				arr[i] = 'Q';
				continue;
			}
			if (bb->b & mask){
				arr[i] = 'B';
				continue;
			}
			if (bb->r & mask){
				arr[i] = 'R';
				continue;
			}
			if (bb->n & mask){
				arr[i] = 'N';
				continue;
			}
			if (bb->p & mask){
				arr[i] = 'P';
				continue;
			}
		}
		if (bb->black & mask){
			if (bb->k & mask){
				arr[i] = 'k';
				continue;
			}
			if (bb->q & mask){
				arr[i] = 'q';
				continue;
			}
			if (bb->b & mask){
				arr[i] = 'b';
				continue;
			}
			if (bb->r & mask){
				arr[i] = 'r';
				continue;
			}
			if (bb->n & mask){
				arr[i] = 'n';
				continue;
			}
			if (bb->p & mask){
				arr[i] = 'p';
				continue;
			}
		}
		arr[i] = '-';
	}
};
