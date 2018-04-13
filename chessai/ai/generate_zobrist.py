import random
random.seed(1)
print 'Zobrist::Zobrist(void){'

used = set()
for i in range(8):
    for j in range(8):
        for k in range(14):
            n = random.getrandbits(64)
            while n in used:
                n = random.getrandbits(64)
            used.add(n)
            print '    zobrist_table[%d][%d][%d] = %s;' % (i, j, k, hex(n).upper().replace('X', 'x').replace('L', 'ULL'))


n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print '    zobrist_white_castle_king = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')
n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print '    zobrist_white_castle_queen = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')
n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print '    zobrist_black_castle_king = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')
n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print '    zobrist_black_castle_queen = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')
n = random.getrandbits(64)
while n in used:
    n = random.getrandbits(64)
used.add(n)
print '    zobrist_blacks_turn = %s;' % hex(n).upper().replace('X', 'x').replace('L', 'ULL')
print '}'



