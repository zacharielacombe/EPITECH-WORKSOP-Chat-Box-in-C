/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** main
*/

#include "client.h"

int main(int ac, char **av)
{
    if (error_handling(ac, av[2]) == EXIT_FAILURE)
    {
        fprintf(stderr, "Error : Incorrect argument(s).\nUSAGE : ./server [ip address] [port]\n");
        return EXIT_FAILURE;
    }
    else
    {
        client(av[1], atoi(av[2]));
    }

    return 0;
}