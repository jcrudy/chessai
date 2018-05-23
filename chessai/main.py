from chessai.client import Client
import argparse
from chessai.ai_names import ai_dict
import logging


def main(args):
    print(1)
    client = Client(args.host, args.port, args.tournament, 
                    args.player, ai_dict[args.ai][0](**ai_dict[args.ai][1]))
    print(2)
    client.connect()
    print(3)
    client.wait_for_messages()
    
if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s %(message)s', datefmt='%m/%d %I:%M:%S %p', level=logging.DEBUG)

    parser = argparse.ArgumentParser(description='Chess client.')
    parser.add_argument("host", type=str, help="Host to connect to")
    parser.add_argument("port", type=int, help="Port to connect to")
    parser.add_argument("tournament", type=str, help="Tournament to play in")
    parser.add_argument("player", type=str, help="Player name")
    parser.add_argument("ai", type=str, help="AI name")
    args = parser.parse_args()
    
    main(args)
