import sys
import socket
import re
from utils import *
from game_data import *
from error_man import error_man
from brodcast_man import receive_answer, read_server
from evolution import *


def check_inventory(client_socket):
    """!
    Check the inventory
    @param client_socket: client socket
    @return: None
    """
    global myGameData
    print("Inventory")
    client_socket.send(("Inventory" + "\n").encode())
    data = receive_answer(client_socket)
    clean_string = data.strip("[] ")
    pattern = r"(\w+)\s(\d+)"
    matches = re.findall(pattern, clean_string)
    data = [[name, value] for name, value in matches]
    while (len(data) > 0):
        myGameData.inventory[data[0][0]] = data[0][1]
        data.pop(0)


def action_choice(client_socket):
    """!
    Choose the action to do
    @param client_socket: client socket
    @return: None
    """
    global myGameData
    if myGameData.has_arrived == True:
        receive_answer(client_socket)
        return()
    check_inventory(client_socket)
    sys.stderr.write("level " + str(myGameData.lvl) + "\n")
    if (int(myGameData.inventory["food"]) < 20 and myGameData.mode == None):
        search_item(client_socket, "food", 30)        
    elif myGameData.mode == None:
        if (can_evolve(client_socket) == True and myGameData.mode == None):
            go_evolve(client_socket)


def main():
    """!
    Main function
    @return: None
    """
    global myGameData

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client_socket.connect((myGameData.ip_server, myGameData.port))
        print("Connexion au serveur établie.")
        print(read_server(client_socket))
        client_socket.send((myGameData.team_name + "\n").encode())
        free_places = read_server(client_socket)
        myGameData.available_connection = free_places
        print(free_places)
        map_size = read_server(client_socket).split()
        if len(map_size) >= 2:
            myGameData.map_size_x = map_size[0]
            myGameData.map_size_y = map_size[1]
            print(map_size[0] + " " + map_size[1])
        while (1):
            action_choice(client_socket)
    except ConnectionRefusedError:
        print("La connexion au serveur a été refusée.")


if __name__ == "__main__":
    try:
        error_man()
        main()
    except SystemExit:
        exit(0)
    except Exception as error:
        sys.stdout.write(str(error))
        exit(84)
