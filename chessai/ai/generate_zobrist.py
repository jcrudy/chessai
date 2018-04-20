import random
import clipboard
random.seed(1)


# def rand():
#     suff = 'ULL'
#     n1 = random.getrandbits(64)
#     n2 = random.getrandbits(64)
#     return '(((zobrist_int) %s) + (((zobrist_int) %s) << 64))' % \
#         (hex(n1).upper().replace('X', 'x').replace('L', suff), 
#          hex(n2).upper().replace('X', 'x').replace('L', suff))

def rand():
    suff = 'ULL'
    n = random.getrandbits(64)
    return hex(n).upper().replace('X', 'x').replace('L', suff)

result = ''

result += 'Zobrist::Zobrist(void){\n'

used = set()
for i in range(8):
    for j in range(8):
        for k in range(14):
            n = rand()
            while n in used:
                n = rand()
            used.add(n)
            result += '    zobrist_table[%d][%d][%d] = %s;\n' % (i, j, k, n)

n = rand()
while n in used:
    n = rand()
used.add(n)
result += '    zobrist_white_castle_king = %s;\n' % n
n = rand()
while n in used:
    n = rand()
used.add(n)
result += '    zobrist_white_castle_queen = %s;\n' % n
n = rand()
while n in used:
    n = rand()
used.add(n)
result += '    zobrist_black_castle_king = %s;\n' % n
n = rand()
while n in used:
    n = rand()
used.add(n)
result += '    zobrist_black_castle_queen = %s;\n' % n
n = rand()
while n in used:
    n = rand()
used.add(n)
result += '    zobrist_blacks_turn = %s;\n' % n
result += '}'

clipboard.copy(result)



