import sys
import socket
import re
from game_data import *
from utils import *
from brodcast_man import receive_answer
from main import check_inventory


def find_path(data, item):
    global myGameData
    data = data.replace('[', ' ')
    data = data.replace(']', ' ')
    splitData = data.split(",")
    instructions = []
    count = 0
    for i in range(0, len(splitData)):
        if splitData[i].find(item) != -1:
            break
        count += 1
    if count == len(splitData):
        return ["Forward" for f in range(0, myGameData.lvl)]
    elif (splitData[0].find(item)) != -1:
        return ["Take " + item]
    else:
        fCount = 0
        limit = 1
        tile = 0
        width = 1
        for i in range(0, len(splitData)):
            if i == limit:
                limit += limit + 2
                fCount += 1
                width += 2
            if splitData[i].find(item) != -1:
                for a in range(0, fCount):
                    instructions.append("Forward")
                tile = i
                break
        viewLine = [b for b in range((limit - width), limit)]
        middle = viewLine[int((len(viewLine) / 2))]
        if width > 3:
            middle -= 1
        if tile < middle:
            instructions.append("Left")
            for t in range(0, (middle - tile)):
                instructions.append("Forward")
            instructions.append("Take " + item)
        elif tile > middle:
            instructions.append("Right")
            for t in range(0, (tile - middle)):
                instructions.append("Forward")
            instructions.append("Take " + item)
        else:
            instructions.append("Take " + item)
        return instructions

def search_choice(client_socket, data, item):
    global myGameData
    add_command = []
    add_command = find_path(data, item)
    while (len(add_command) > 0):
        myGameData.auto_command.append(add_command[0])
        add_command.pop(0)
    while (len(myGameData.auto_command) > 0):
        command = myGameData.auto_command[0] + "\n"
        print(myGameData.auto_command[0])
        myGameData.auto_command.pop(0)
        client_socket.send(command.encode())
        data = receive_answer(client_socket)

def search_item(client_socket, item, quantity):
    global myGameData
    while (quantity > int(myGameData.inventory[item])):
        if myGameData.mode == "gather":
            return
        print("Look")
        client_socket.send(("Look"+"\n").encode())
        myGameData.last_command = "Look"
        myGameData.mode = item
        data = receive_answer(client_socket)
        search_choice(client_socket, data, item)
        check_inventory(client_socket)
        if (item != "food"):
            if (int(myGameData.inventory["food"]) < 5):
                search_item(client_socket, "food", 30)
    myGameData.mode = None

def drop_items_on_tile(client_socket):
    global myGameData
    lvl = "lvl"+str(myGameData.lvl+1)
    stones_needed = myGameData.evolution_infos[lvl].copy()
    stones_needed.pop(0)
    index = 0
    for stone in stones_needed:
        stone_name = myGameData.stones_in_game[index]
        for i in range(0, stone):
            print("Set "+stone_name)
            client_socket.send(("Set "+stone_name+"\n").encode())
            receive_answer(client_socket)
        index += 1

def take_all_on_tile(client_socket):
    global myGameData
    print("Look")
    client_socket.send(("Look\n").encode())
    data = receive_answer(client_socket)
    data = data.replace('[', ' ')
    data = data.replace(']', ' ')
    splitData = data.split(",")
    player_tile = splitData[0]
    items_to_take = player_tile.split()
    while (len(items_to_take) > 0):
        if items_to_take[0] == "player":
            items_to_take.pop(0)
        else:
            print("Take "+items_to_take[0])
            client_socket.send(("Take "+items_to_take[0]+"\n").encode())
            data = receive_answer(client_socket)
            items_to_take.pop(0)
