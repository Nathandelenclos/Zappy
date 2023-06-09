import sys
import socket
import random
import re
from game_data import *
from utils import *
from brodcast_man import receive_answer
from main import check_inventory


def find_row_in_vis(tile):
    """!
    Find the row in which the seeked item is
    @param tile: tile on which the item is
    @return: number of row on which the item is and middle of this row
    """
    for row_number, values in myGameData.vision.items():
        if tile in values:
            middle_number = values[len(values) // 2]
            return int(row_number), middle_number


def go_to_item(splitData, item):
    """!
    Instructions to go to the seeked item
    @param splitData Look result
    @param item: seeked item
    @return: list of instructions
    """
    global myGameData
    instructions = []
    tile = 0
    row = None
    middle = None
    for i in range(0, len(splitData)):
        if splitData[i].find(item) != -1:
            tile = i
            row, middle = find_row_in_vis(tile)
            break
    for f in range(0, row):
        instructions.append("Forward")
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


def find_path(data, item):
    """!
    Find the path to the item
    @param data: Values returned by the server when the look command is used
    @param item: Item to find
    @return: List of instructions to get to the item
    """
    global myGameData
    data = data.replace('[', ' ')
    data = data.replace(']', ' ')
    splitData = data.split(",")
    count = 0
    for i in range(0, len(splitData)):
        if splitData[i].find(item) != -1:
            break
        count += 1
    if count == len(splitData):
        randomNbr = random.randint(0, 3)
        if (randomNbr == 0):
            return ["Left", "Forward", "Forward", "Forward"]
        elif (randomNbr == 1):
            return ["Right", "Forward", "Forward", "Forward"]
        return ["Forward" for f in range(0, random.randint(0, 6))]
    elif (splitData[0].find(item)) != -1:
        return ["Take " + item]
    else:
        return go_to_item(splitData, item)


def search_choice(client_socket, data, item):
    """!
    Search the item and add the instructions to the auto_command list
    @param client_socket:
    @param data:
    @param item:
    @return:
    """
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
    """!
    Search the item and add the instructions to the auto_command list
    @param client_socket: client socket
    @param item: item to search
    @param quantity: quantity of item to search
    @return: None
    """
    global myGameData
    while (quantity > int(myGameData.inventory[item])):
        if myGameData.mode == "gather":
            return
        print("Look")
        client_socket.send(("Look" + "\n").encode())
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
    """!
    Drop all items on the tile
    @param client_socket: client socket
    @return: None
    """
    global myGameData
    lvl = "lvl" + str(myGameData.lvl + 1)
    stones_needed = myGameData.evolution_infos[lvl].copy()
    stones_needed.pop(0)
    index = 0
    for stone in stones_needed:
        stone_name = myGameData.stones_in_game[index]
        for i in range(0, stone):
            print("Set " + stone_name)
            client_socket.send(("Set " + stone_name + "\n").encode())
            receive_answer(client_socket)
        index += 1


def take_all_on_tile(client_socket):
    """!
    Take all items on the tile
    @param client_socket: client socket
    @return: None
    """
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
            print("Take " + items_to_take[0])
            client_socket.send(("Take " + items_to_take[0] + "\n").encode())
            data = receive_answer(client_socket)
            items_to_take.pop(0)
