from chessai.ai.random_ai import RandomChessAI
from chessai.ai.tournament_ai import TournamentAI

ai_dict = dict(
               random = (RandomChessAI, dict()),
               californium = (TournamentAI, dict(do_ponder=False, do_refresh=False)),
               berkelium = (TournamentAI, dict(do_ponder=False, do_refresh=True)),
               )
