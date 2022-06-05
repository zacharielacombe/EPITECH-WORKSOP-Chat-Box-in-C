/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** get_hostname
*/

#include "server.h"

static char *read_command_output(FILE *fp)
{
    char path[1035];
    char *command_output;

    while (fgets(path, sizeof(path), fp) != NULL);
    for (size_t i = 0; path[i] != '\0'; ++i)
    {
        if (path[i] == ' ')
        {
            path[i] = '\0';
            break;
        }
    }

    return (command_output = strdup(path));
}

char *get_hostname(void)
{
    FILE *fp;
    char *command_ouptut;

    fp = popen("hostname -I", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error : Failed to run command.\n" );
        exit(EXIT_FAILURE);
    }

    command_ouptut = read_command_output(fp);

    pclose(fp);

    return command_ouptut;
}