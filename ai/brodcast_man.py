from utils import *
from game_data import *

def join(answer):
    if answer == "0":
        printGreen("Player is on the elevation tile")
    elif answer == "2" or answer == "1" or answer == "8":
        printGreen("Forward")
    elif answer == "3":
        printGreen("Left\nForward")
    elif answer == "7":
        printGreen("Right\nForward")
    else:
        printGreen("Left\nLeft\nForward")
    exit(0)
    return


def broadcast_man(data, answer, client_socket):
    global myGameData
    if answer[2] != myGameData.team_name:
        return ()
    print(data)
    message = data.split(", ")
    if message[1] == myGameData.team_name+" nb_player" and myGameData.presence == False:
        print("Broadcast "+ myGameData.team_name +" present "+ myGameData.uuid_str +" "+str(myGameData.lvl))
        client_socket.send(("Broadcast "+ myGameData.team_name +" present "+ myGameData.uuid_str +" "+str(myGameData.lvl)+"\n").encode())
        data = receive_answer(client_socket)
        myGameData.presence = True
        myGameData.broadcast = False
    elif myGameData.mode == "asker" and answer[3] == "present":
        if answer[4] in myGameData.uuid_present:
            return ()
        myGameData.uuid_present.append(answer[4])
        myGameData.available["lvl"+answer[5]] += 1
    elif message[1] == myGameData.team_name+" end nb_player":
        myGameData.presence = False
    elif message[1] == myGameData.team_name + " gather":
        myGameData.mode = "gather"
        join(answer[1])
    else:
        myGameData.last_broadcast.append(answer)

def answer_management(data, client_socket):
    global myGameData
    if data == "dead":
        print("YOU DIED x)")
        client_socket.close()
        print("Connexion fermée.")
        return (-1)
    else:
        answer = data.split()
        if answer[0] == "message":
            broadcast_man(data, answer, client_socket)
            return(1)
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
    
def receive_answer(client_socket, mode=""):
    answer = 1
    while (answer != 0):
        data = read_server(client_socket)
        answer = answer_management(data, client_socket)
    return data

def read_server(client_socket):
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
