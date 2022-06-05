/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** error_handling
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int error_handling(int ac, char *port)
{
    if (ac != 2)
        return EXIT_FAILURE;

    size_t port_len = strlen(port);

    for (size_t i = 0; i != port_len; ++i)
    {
        if ((isdigit(port[i])) == 0)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}