/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** run_server
*/

#include "server.h"

void server_loop(server_t *server)
{
    printf("new_loop\n");
    void *buf = malloc(256);
    ssize_t size;
    int new_fd = -1;
    int r;

    server->readfds = server->fds;
    server->writefds = server->fds;
    select(1024, &server->readfds, &server->writefds, NULL, NULL);
    if (FD_ISSET(server->socket, &server->readfds)) {
        socklen_t addrlen = sizeof(server->addr);
        new_fd = accept(server->socket, (struct sockaddr *)&server->addr, &addrlen);
        FD_SET(new_fd, &server->fds);
    }
    if (new_fd != -1) {
        for (r = 0; server->fd_array[r] != -1; r++);
        server->fd_array[r] = new_fd;
    }
    for (int i = 0; server->fd_array[i] != -1; i++) {
        if (FD_ISSET(server->fd_array[i], &server->readfds)) {
            printf("before recv\n");
            size += recv(server->fd_array[i], buf, 256, 0);
            printf("buf = %s\n", buf);
        }
    }
    
    for (int i = 0; server->fd_array[i] != -1; i++) {
        printf("server->fd_arrray[%d] = %d\n", i, server->fd_array[i]);
        if (FD_ISSET(server->fd_array[i], &server->writefds)) {
            printf("before send\n");
            send(server->fd_array[i], buf, size, 0);
        }
    }
    free(buf);
    return;
}

void run_server(server_t *server)
{
    while(1) {
        server_loop(server);
        sleep(1);
    }
    return;
}
