/*
** EPITECH PROJECT, 2022
** -EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** error_handling
*/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

bool error_handling_c(int ac, char *port)
{
    if (ac != 3 || strlen(port) != 4)
        return false;
    for (int i = 0; i != strlen(port); ++i)
        if ((isdigit(port[i])) == 0)
            return false;
    return true;
}

bool error_handling_s(int ac, char *port)
{
    if (ac != 2 || strlen(port) != 4)
        return false;
    for (int i = 0; i != strlen(port); ++i)
        if ((isdigit(port[i])) == 0)
            return false;
    return true;
}