/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** run_server
*/

#include "server.h"

fd_set server_loop(server_t *server)
{
    server->readfds = server->fds;
    server->writefds = server->fds;

    /*while (fds->fd_array[i] != NULL) {
        FD_SET(fds->fd_array[i], rfds);
        FD_SET(, wfds);
        i++;
    }*/
    select(1024, &server->readfds, &server->writefds, NULL, NULL);
    return;
}

void run_server(server_t *server)
{
    return;
}
