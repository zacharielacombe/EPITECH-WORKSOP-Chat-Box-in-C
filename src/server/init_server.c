/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_server
*/

#include "server.h"
#include "errno.h"

server_t *init_server(char *ip_addr, int port)
{
    server_t *server = malloc(sizeof(server_t));
    int fd;
    socklen_t *addrlen;
    void *buf = malloc(256);

    if (server == NULL)
        return NULL;
    server->ip_addr = ip_addr;
    server->port = port;
    // init socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    server->socket = fd;
    if (fd == -1)
        return NULL;
    // init server addr*
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(port);
    server->addr.sin_addr.s_addr = inet_addr(ip_addr);
    // bind
    if (bind(fd, (struct sockaddr *)&server->addr, sizeof(struct sockaddr_in)) == -1) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    // listen
    if (listen(fd, 16) == -1)
        return NULL;
    addrlen = malloc(sizeof(server->addr));
    int fda = accept(fd, (struct sockaddr *)&server->addr, addrlen);
    if (fda == -1)
        return NULL;
    int size = recv(fda, buf, 256, 0);
    if (size == -1)
        return NULL;
//    FD_SET(fda, &server->fds);
    FD_SET(fd, &server->fds);
    server->fd_array = malloc(sizeof(int) * 17);
    for (int i = 0; i < 17; i++)
        server->fd_array[i] = -1;
    server->fd_array[0] = fda;
    printf("finished initialization\n");
    return server;
}