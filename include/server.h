/*
** EPITECH PROJECT, 2022
** -EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** server
*/

#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

bool error_handling_s(int ac, char *port);
void server(int port);