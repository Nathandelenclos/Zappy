import uuid


class Game_data:
    def __init__(self):
        self.broadcast = True
        self.fork_done = 0
        self.presence = False
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
        self.stones_in_game = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
        self.evolution_infos  = {
            "lvl2": [1, 1, 0, 0, 0, 0, 0],
            "lvl3": [2, 1, 1, 1, 0, 0, 0],
            "lvl4": [2, 2, 0, 1, 0, 2, 0],
            "lvl5": [4, 1, 1, 2, 0, 1, 0],
            "lvl6": [4, 1, 2, 1, 3, 0, 0],
            "lvl7": [6, 1, 2, 3, 0, 1, 0],
            "lvl8": [6, 2, 2, 2, 2, 2, 1]
        }
        self.inventory  = { #inventaire commun a faire apres pour opti, ia qui rammasse le dernier item necessaire lance l'appel (broadcast)
            "food": None,
            "linemate": None ,
            "deraumere": None ,
            "sibur": None ,
            "mendiane": None ,
            "phiras": None ,
            "thystame": None 
        }

myGameData = Game_data()