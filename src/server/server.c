/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** server
*/

#include "server.h"

void server(char *ip_addr, int port)
{
    printf("Your ip address is : %s.\n", ip_addr);
    server_t *server = init_server(ip_addr, port);

    run_server(server);
}