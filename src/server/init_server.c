/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_server
*/

#include "server.h"

server_t *init_server(char *ip_addr, int port)
{
    server_t *server = malloc(sizeof(server_t));
    struct sockaddr_in addr_server;
    int fd;
    socklen_t *addrlen;
    void *buf = malloc(256);

    if (server == NULL)
        return NULL;
    server->ip_addr = ip_addr;
    server->port = port;
    // init socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        return NULL;
    // init server addr
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port);
    addr_server.sin_addr.s_addr = inet_addr(ip_addr);
    // bind
    if (bind(fd, (struct sockaddr *)&addr_server, sizeof(addr_server)) == -1)
        return NULL;
    // listen
    if (listen(fd, 10) == -1)
        return NULL;
    addrlen = malloc(sizeof(addr_server));
    int fda = accept(fd, (struct sockaddr *)&addr_server, addrlen);
    if (fda == -1)
        return NULL;
    int size = recv(fda, buf, 256, 0);
    if (size == -1)
        return NULL;
    /*
    FD_SET(fda, &server->fds);
    FD_SET(fd, &server->fds);
    server->fd_array = malloc(sizeof(FD_SETSIZE));
    for (int i = 0; i < FD_SETSIZE; i++)
        server->fd_array[i] = NULL;
    server->fd_array[0] = fd;
    server->fd_array[1] = fda;
    */
    return server;
}