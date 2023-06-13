from utils import *
from game_data import *
from brodcast_man import receive_answer
from search_item import *

def can_evolve(client_socket):
    global myGameData
    can_lvl_up = 0
    lvl = "lvl"+str(myGameData.lvl+1)
    stones_needed = myGameData.evolution_infos[lvl].copy()
    stones_needed.pop(0)
    index = 0
    for stone in stones_needed:
        stone_name = myGameData.stones_in_game[index]
        my_stone = int(myGameData.inventory[stone_name])
        if my_stone < stone:
            search_item(client_socket, stone_name, stone - my_stone)
            can_lvl_up += 1
        index += 1
    if can_lvl_up == 0:
        return (True)
    else:
        return (False)

def go_evolve(client_socket):
    global myGameData
    if myGameData.lvl == 1:
        take_all_on_tile(client_socket)
        print("Set linemate")
        client_socket.send(("Set linemate\n").encode())
        data = receive_answer(client_socket)
        if data == "ok":
            print("Incantation")
            client_socket.send(("Incantation\n").encode())
            data = receive_answer(client_socket)
            if data != "Elevation underway":
                printGreen("Evolution failed")
        else:
            printGreen("Item not found in inventory")
    elif myGameData.presence != True and myGameData.broadcast == True:
        print("Broadcast "+ myGameData.team_name +" nb_player")
        client_socket.send(("Broadcast "+ myGameData.team_name +" nb_player\n").encode())
        data = receive_answer(client_socket, "asker")
        for i in range(0, 4):
            print("Left")
            client_socket.send(("Left"+"\n").encode())
            data = receive_answer(client_socket, "asker")
        print("Broadcast "+ myGameData.team_name +" end nb_player")
        client_socket.send(("Broadcast "+ myGameData.team_name +" end nb_player\n").encode())
        data = receive_answer(client_socket, "asker")
        nb_player = 0
        for value in myGameData.available.values():
            nb_player += value
        print("lvl"+str(myGameData.lvl))
        printGreen(str(myGameData.available["lvl"+str(myGameData.lvl)]))
        if myGameData.available["lvl"+str(myGameData.lvl)] >= 5:
            gathering_mode_and_incantation(client_socket)
        elif (nb_player < 5 and myGameData.fork_done < 5):
            print("Fork")
            client_socket.send(("Fork\n").encode())
            data = receive_answer(client_socket)
            myGameData.fork_done += 1
        elif (nb_player >= 5):
            printGreen("wait others to evolve")
            for i in range(0, 12):
                print("Left")
                client_socket.send(("Left"+"\n").encode())
                data = receive_answer(client_socket, "asker")
        else:
            printGreen("wait clients to connect")
            for i in range(0, 12):
                print("Left")
                client_socket.send(("Left"+"\n").encode())
                data = receive_answer(client_socket, "asker")

def gathering_mode(client_socket):
    global myGameData
    while myGameData.nb_arrived < 5:
        client_socket.send(("Broadcast " + myGameData.team_name + " gather\n").encode())
        print("Broadcast " + myGameData.team_name + " gather")
        data = receive_answer(client_socket, "asker")
        printGreen(str(myGameData.nb_arrived))
        for i in range(0, 4):
                print("Left")
                client_socket.send(("Left"+"\n").encode())
                data = receive_answer(client_socket, "asker")
    return (True)

def gathering_mode_and_incantation(client_socket):
    if gathering_mode(client_socket) == True:
        take_all_on_tile(client_socket)
        drop_items_on_tile(client_socket)
        print("Incantation")
        client_socket.send(("Incantation\n").encode())
        data = receive_answer(client_socket)
        if data == "Elevation underway":
            data = receive_answer(client_socket)
            if data == "ko":
                printGreen("Evolution failed")
            else:
                printGreen("Evolution is a success")
                myGameData.lvl += 1
        else:
            printGreen("Evolution failed")
