import sys
import argparse
from utils import *
from game_data import *


def error_man():
    """!
    Manage error
    @return: None
    """
    global myGameData

    if len(sys.argv) == 2:
        if sys.argv[1] == "-help":
            man_help()
            raise SystemExit()
        else:
            raise Exception("Bad arguments\n")
    elif len(sys.argv) == 5 or len(sys.argv) == 7:
        parser = argparse.ArgumentParser(add_help=False)
        parser.add_argument('-p', type=int)
        parser.add_argument('-n', type=str)
        parser.add_argument('-h', type=str)
        args = parser.parse_args()
        myGameData.port = args.p
        myGameData.team_name = args.n
        myGameData.ip_server = args.h
        if myGameData.team_name == None or myGameData.port == None:
            raise Exception("Bad arguments\n")
        if myGameData.ip_server == None:
            myGameData.ip_server = "127.0.0.1"
    else:
        raise Exception("Bad arguments\n")
