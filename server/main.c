/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    if (!(error_handling(ac, av[1])))
    {
        printf("%s\n", "Bad argument");
        return 84;
    }

    server(atoi(av[1]));

    return 0;
}