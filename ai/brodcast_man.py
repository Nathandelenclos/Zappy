from utils import *
from game_data import *

def join(answer, client_socket):
    global myGameData
    # printRed(myGameData.mode)
    if myGameData.has_arrived == True:
        return
    if answer == "0,":
        printGreen("Player is on the elevation tile")
        client_socket.send(("Broadcast " + myGameData.team_name + " arrived\n").encode())
        printGreen("Broadcast " + myGameData.team_name + " arrived")
        receive_answer(client_socket)
        # printGreen(myGameData.mode)
        myGameData.has_arrived = True
    elif answer == "2," or answer == "1," or answer == "8,":
        printGreen("Forward")
        client_socket.send(("Forward\n").encode())
        receive_answer(client_socket)
    elif answer == "3,":
        printGreen("Left")
        client_socket.send(("Left\n").encode())
        receive_answer(client_socket)
        printGreen("Forward")
        client_socket.send(("Forward\n").encode())
        receive_answer(client_socket)
    elif answer == "7,":
        printGreen("Right")
        client_socket.send(("Right\n").encode())
        receive_answer(client_socket)
        printGreen("Forward")
        client_socket.send(("Forward\n").encode())
        receive_answer(client_socket)
    else:
        printGreen("Left")
        client_socket.send(("Left\n").encode())
        receive_answer(client_socket)
        printGreen("Left")
        client_socket.send(("Left\n").encode())
        receive_answer(client_socket)
        printGreen("Forward")
        client_socket.send(("Forward\n").encode())
        receive_answer(client_socket)
    # exit(0)
    return


def broadcast_man(data, answer, client_socket, type):
    global myGameData
    if answer[2] != myGameData.team_name:
        return ()
    print(data)
    message = data.split(", ")
    # if message[1] == myGameData.team_name+" nb_player" and myGameData.presence == False:
    if message[1] == myGameData.team_name+" nb_player":
        print("Broadcast "+ myGameData.team_name +" present "+ myGameData.uuid_str +" "+str(myGameData.lvl))
        client_socket.send(("Broadcast "+ myGameData.team_name +" present "+ myGameData.uuid_str +" "+str(myGameData.lvl)+"\n").encode())
        data = receive_answer(client_socket)
        # myGameData.presence = True
        myGameData.broadcast = False
    elif type == "asker" and len(answer) > 4 and answer[3] == "present":
        # if answer[4] in myGameData.uuid_present:
        #     return ()
        # myGameData.uuid_present.append(answer[4])
        myGameData.available["lvl"+answer[5]] += 1
    # elif message[1] == myGameData.team_name+" end nb_player":
    #     myGameData.presence = False
    elif message[1] == myGameData.team_name + " gather":
        myGameData.mode = "gather"
        join(answer[1], client_socket)
    elif message[1] == myGameData.team_name + " arrived" and myGameData.mode != "gather":
        myGameData.nb_arrived += 1
    # else:
    #     myGameData.last_broadcast.append(answer)

def answer_management(data, client_socket, type):
    global myGameData
    if data == "dead":
        print("YOU DIED x)")
        client_socket.close()
        print("Connexion fermée.")
        exit()
    else:
        answer = data.split()
        if answer[0] == "message":
            broadcast_man(data, answer, client_socket, type)
            return(1)
        # elif data == "Elevation underway":
        #     # if type != "again":
        #     print(data)
        #     myGameData.broadcast = False
        #     return(1)
        #     # data = receive_answer(client_socket)
        #     # if data == "ko":
        #     #     printGreen("Evolution failed")
        # elif data == "Current level: "+str(myGameData.lvl+1):
        #     print(data)
        #     printGreen("Evolution is a success")
        #     myGameData.lvl += 1
        #     myGameData.broadcast = True
        #     myGameData.mode = None
        #     # else:
        #     #     answer_management("Elevation underway", client_socket, "again")
        #     return (0)
        print(data)
        return (0)
    
def receive_answer(client_socket, type=""):
    global myGameData
    answer = 1
    index = 0
    while (answer != 0):
        data = read_server(client_socket)
        if data == "Elevation underway":
            print(data)
            myGameData.broadcast = False
            index += 1
            continue
        elif data == "Current level: "+str(myGameData.lvl+1):
            print(data)
            printGreen("Evolution is a success")
            myGameData.lvl += 1
            myGameData.broadcast = True
            myGameData.mode = None
            myGameData.has_arrived = False
            return()
        elif data == "ko" and index == 1:
            myGameData.broadcast = True
            myGameData.mode = None
            myGameData.has_arrived = False
        answer = answer_management(data, client_socket, type)
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
