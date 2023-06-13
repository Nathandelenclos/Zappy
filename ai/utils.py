def printGreen(data):
    print("\033[92m" + data + "\033[0m")

def man_help():
    print("USAGE:  ./zappy_ai -p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")
