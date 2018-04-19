from chessai.ai.random_ai import RandomChessAI
from chessai.ai.my_ai import MyAI

ai_dict = dict(
               random = (RandomChessAI, dict()),
               californium = (MyAI, dict(tt_size=5000000, time_limit=6., use_quiescence=False)),
               berkelium = (MyAI, dict(tt_size=5000000, time_limit=6., use_quiescence=True)),
               )
