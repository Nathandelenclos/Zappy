/*
** EPITECH PROJECT, 2023
** YEP-400-LIL-4-1-zappy
** File description:
** message.h
*/

#ifndef MESSAGE_H_
    #define MESSAGE_H_

    // Messages
    #define WELCOME "WELCOME\n"
    #define KO "ko\n"
    #define OK "ok\n"
    #define HELP "USAGE: ./zappy_server -p port -x width -y height -n name1" \
           " name2 ... -c clientsNb -f freq\n" \
           "    port is the port number\n" \
           "    width is the width of the world\n" \
           "    height is the height of the world\n" \
           "    nameX is the name of the team X\n" \
           "    clientsNb is the number of authorized clients per team\n" \
           "    freq is the reciprocal of time unit for execution of actions"
    #define GRAPHIC "GRAPHIC"
    #define DEAD "dead\n"
    #define ELEVATION_UNDERWAY "Elevation underway\n"

    #define FOOD_QUANTITY 10
    // Error messages
    #define ERROR_SOCKET "Erreur lors de la surveillance des sockets\n"
    #define ERROR_CONNEXION "Erreur lors de l'acceptation de la connexion client"

#endif /* !MESSAGE_H_ */
