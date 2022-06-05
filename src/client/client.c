/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** client
*/

#include "client.h"

void client(char *ip_addr, int port)
{
    client_t *client = init_client(ip_addr, port);

    launch_client(client);

    return;
}