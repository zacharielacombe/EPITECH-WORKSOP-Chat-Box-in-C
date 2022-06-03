/*
** EPITECH PROJECT, 2022
** -EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** client
*/

#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


bool error_handling_c(int ac, char *port);
void client(char *address, int port);