import uuid


class Game_data:
    """!
    Class to store all of the game data
    """
    def __init__(self):
        self.broadcast = True
        self.fork_done = 0
        self.mode = None
        self.last_answer = None
        self.last_command = None
        self.last_broadcast = []
        self.auto_command = []
        self.ip_server = None
        self.team_name = None
        self.uuid_str = str(uuid.uuid4())
        self.port = None
        self.map_size_x = 0
        self.map_size_y = 0
        self.available_connection = 0
        self.lvl = 1
        self.has_arrived = False
        self.nb_arrived = 0
        self.available = {
            "lvl1": 0,
            "lvl2": 0,
            "lvl3": 0,
            "lvl4": 0,
            "lvl5": 0,
            "lvl6": 0,
            "lvl7": 0
        }
        self.uuid_present = []
        self.stones_in_game = ["linemate", "deraumere", "sibur", "mendiane",
                               "phiras", "thystame"]
        self.evolution_infos = {
            "lvl2": [1, 1, 0, 0, 0, 0, 0],
            "lvl3": [2, 1, 1, 1, 0, 0, 0],
            "lvl4": [2, 2, 0, 1, 0, 2, 0],
            "lvl5": [4, 1, 1, 2, 0, 1, 0],
            "lvl6": [4, 1, 2, 1, 3, 0, 0],
            "lvl7": [6, 1, 2, 3, 0, 1, 0],
            "lvl8": [6, 2, 2, 2, 2, 2, 1]
        }
        self.inventory = {
            "food": None,
            "linemate": None,
            "deraumere": None,
            "sibur": None,
            "mendiane": None,
            "phiras": None,
            "thystame": None
        }
        self.vision = {
            "0": [0],
            "1": [1, 2, 3],
            "2": [4, 5, 6, 7, 8],
            "3": [9, 10, 11, 12, 13, 14, 15],
            "4": [16, 17, 18, 19, 20, 21, 22, 23, 24],
            "5": [25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35],
            "6": [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48],
            "7": [49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63],
            "8": [64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80],
        }


myGameData = Game_data()
