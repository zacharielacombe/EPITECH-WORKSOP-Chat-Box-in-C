##
## EPITECH PROJECT, 2022
## -EPITECH-WORKSOP-Chat-Box-in-C
## File description:
## Makefile
##


SRC_SERVER	=	server/main.c \
				include/error_handling.c	\
				server/server.c	\

SRC_CLIENT	=	client/main.c \
				include/error_handling.c	\
				client/client.c	\

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

CFLAGS += -I./include

NAME_SERVER	=	run_server

NAME_CLIENT	=	run_client

all:	compile

compile: $(OBJ_SERVER) $(OBJ_CLIENT)
		gcc -o $(NAME_SERVER) $(OBJ_SERVER)
		gcc -o $(NAME_CLIENT) $(OBJ_CLIENT)


clean:
		rm -f $(OBJ_SERVER)
		rm -f $(OBJ_CLIENT)


fclean: clean
		rm -f $(NAME_SERVER)
		rm -f $(NAME_CLIENT)

re:	fclean all
