/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_client
*/

#include "client.h"

client_t *init_client(char *ip_addr, int port)
{
    client_t *client = malloc(sizeof(client_t));

    client->ip_addr = ip_addr;
    client->port = port;
    socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr_server;
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port);
    addr_server.sin_addr.s_addr = inet_addr(ip_addr);

    return client;
}
