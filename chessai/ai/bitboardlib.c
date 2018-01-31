#include "bitboardlib.h"
#include <stdio.h>

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


const stateflags empty_flags = 0b00000000;
const stateflags white_castle_king_mask = 0b00000001;
const stateflags white_castle_queen_mask = 0b00000010;
const stateflags black_castle_king_mask = 0b00000100;
const stateflags black_castle_queen_mask = 0b00001000;
const stateflags turn_mask = 0b00010000;

const boardstate emptyboardstate = {empty,empty,empty,empty,
									empty,empty,empty,empty,
									0b11111111, empty_flags, 0, 0};


void bitboard_to_arr(boardstate *bb, char* arr){
	int i;
	bitboard mask;
	for (i=0; i<64; i++){
		mask = places[i];
		printf("%s\n", arr);
		printf("%d\n", i);
		if (bb->white & mask){
			printf("white\n");
			if (bb->k & mask){
				printf("k\n");
				arr[i] = 'K';
				continue;
			}
			if (bb->q & mask){
				printf("q\n");
				arr[i] = 'Q';
				continue;
			}
			if (bb->b & mask){
				printf("b\n");
				arr[i] = 'B';
				continue;
			}
			if (bb->r & mask){
				printf("r\n");
				arr[i] = 'R';
				continue;
			}
			if (bb->n & mask){
				printf("n\n");
				arr[i] = 'N';
				continue;
			}
			if (bb->p & mask){
				printf("p\n");
				arr[i] = 'P';
				continue;
			}
		}
		if (bb->black & mask){
			printf("black\n");
			if (bb->k & mask){
				printf("k\n");
				arr[i] = 'k';
				continue;
			}
			if (bb->q & mask){
				printf("q\n");
				arr[i] = 'q';
				continue;
			}
			if (bb->b & mask){
				printf("b\n");
				arr[i] = 'b';
				continue;
			}
			if (bb->r & mask){
				printf("r\n");
				arr[i] = 'r';
				continue;
			}
			if (bb->n & mask){
				printf("n\n");
				arr[i] = 'n';
				continue;
			}
			if (bb->p & mask){
				printf("p\n");
				arr[i] = 'p';
				continue;
			}
		}
		arr[i] = '-';
	}
};
