from utils import *
from game_data import *


def join(answer, client_socket):
    """
    Join an evolution place
    :param answer: broadcast message
    :param client_socket: client socke
    :return: None
    """
    global myGameData
    if myGameData.has_arrived == True:
        return
    if answer == "0,":
        printGreen("Player is on the elevation tile")
        client_socket.send(
            ("Broadcast " + myGameData.team_name + " arrived\n").encode())
        print("Broadcast " + myGameData.team_name + " arrived")
        receive_answer(client_socket)
        myGameData.has_arrived = True
    elif answer == "2," or answer == "1," or answer == "8,":
        printGreen("Forward")
        client_socket.send(("Forward\n").encode())
        receive_answer(client_socket)
    elif answer == "3,":
        printGreen("Left\nForward")
        client_socket.send(("Left\n").encode())
        receive_answer(client_socket)
        client_socket.send(("Forward\n").encode())
        receive_answer(client_socket)
    elif answer == "7,":
        printGreen("Right\nForward")
        client_socket.send(("Right\n").encode())
        receive_answer(client_socket)
        client_socket.send(("Forward\n").encode())
        receive_answer(client_socket)
    else:
        printGreen("Left\nLeft\nForward")
        client_socket.send(("Left\n").encode())
        receive_answer(client_socket)
        client_socket.send(("Left\n").encode())
        receive_answer(client_socket)
        client_socket.send(("Forward\n").encode())
        receive_answer(client_socket)
    # exit(0)
    return


def broadcast_man(data, answer, client_socket, type):
    """
    Manage broadcast message
    :param data: message received
    :param answer: message received split
    :param client_socket: client socket
    :param type: Players type of play
    :return: None
    """
    global myGameData
    if answer[2] != myGameData.team_name:
        return ()
    print(data)
    message = data.split(", ")
    if message[1] == myGameData.team_name + " nb_player" and myGameData.presence == False:
        print("Broadcast " + myGameData.team_name + " present " + myGameData.uuid_str + " " + str(myGameData.lvl))
        client_socket.send(("Broadcast " + myGameData.team_name + " present " + myGameData.uuid_str + " " + str(myGameData.lvl) + "\n").encode())
        data = receive_answer(client_socket)
        myGameData.presence = True
        myGameData.broadcast = False
    elif type == "asker" and len(answer) > 4 and answer[3] == "present":
        if answer[4] in myGameData.uuid_present:
            return ()
        myGameData.uuid_present.append(answer[4])
        myGameData.available["lvl" + answer[5]] += 1
    elif message[1] == myGameData.team_name + " end nb_player":
        myGameData.presence = False
    elif message[1] == myGameData.team_name + " gather":
        myGameData.mode = "gather"
        join(answer[1], client_socket)
    elif message[1] == myGameData.team_name + " arrived":
        myGameData.nb_arrived += 1
    else:
        myGameData.last_broadcast.append(answer)


def answer_management(data, client_socket, type):
    """
    Manage answer from server
    :param data: message received
    :param client_socket: client socket
    :param type: Players type of play
    :return: -1 if dead, 0 if ok, 1 if message
    """
    global myGameData
    if data == "dead":
        print("YOU DIED x)")
        client_socket.close()
        print("Connexion fermée.")
        return (-1)
    else:
        answer = data.split()
        if answer[0] == "message":
            broadcast_man(data, answer, client_socket, type)
            return (1)
        elif data == "Elevation underway":
            print(data)
            myGameData.broadcast = False
            data = receive_answer(client_socket)
            if data == "ko":
                printGreen("Evolution failed")
            else:
                printGreen("Evolution is a success")
                myGameData.lvl += 1
                myGameData.broadcast = True
            return (0)
        print(data)
        return (0)


def receive_answer(client_socket, type=""):
    """
    Receive answer from server
    :param client_socket: client socket
    :param type: Type of message
    :return: message received
    """
    answer = 1
    while (answer != 0):
        data = read_server(client_socket)
        answer = answer_management(data, client_socket, type)
    return data


def read_server(client_socket):
    """
    Read message from server
    :param client_socket: client socket
    :return: message received
    """
    msg = ""
    while (1):
        char_read = client_socket.recv(1)
        if not char_read:
            break
        elif (char_read == b'\n'):
            return (msg)
        else:
            msg += char_read.decode()
    return (msg)
