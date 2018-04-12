import random
random.seed(0)
print '''
zobrist_int ***create_zobrist_table(){
    zobrist_int *** zobrist_table = (zobrist_int ***) malloc(8*sizeof(zobrist_int**));
    for(int i=0;i<8;i++){
        zobrist_table[i] = (zobrist_int **) malloc(8*sizeof(zobrist_int*));
        for(int j=0;j<14;j++){
            zobrist_table[i][j] = (zobrist_int *) malloc(14*sizeof(zobrist_int));
        }
    }
'''
used = set()
for i in range(8):
    for j in range(8):
        for k in range(14):
            n = random.getrandbits(64)
            while n in used:
                n = random.getrandbits(64)
            used.add(n)
            print '    zobrist_table[%d][%d][%d] = %s;' % (i, j, k, hex(n).upper().replace('X', 'x').replace('L', 'ULL'))


print '''
    return zobrist_table;
}
zobrist_int ***zobrist_table = create_zobrist_table();
'''
n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print 'const zobrist_int zobrist_white_castle_king = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')
n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print 'const zobrist_int zobrist_white_castle_queen = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')
n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print 'const zobrist_int zobrist_black_castle_king = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')
n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print 'const zobrist_int zobrist_black_castle_queen = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')
n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print 'const zobrist_int zobrist_blacks_turn = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')




