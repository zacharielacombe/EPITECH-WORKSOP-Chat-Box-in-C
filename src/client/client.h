/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** client
*/

#pragma once

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <netdb.h>
#include <stdio.h>

typedef struct client_s {
    fd_set readfds;
    fd_set writefds;
    fd_set fds;

    char *ip_addr;

    int socket;
    int port;
} client_t;

int error_handling(int ac, char *port);
client_t *init_client(char *ip_addr, int port);
void run_client(client_t *client);
void client(char *ip_addr, int port);
