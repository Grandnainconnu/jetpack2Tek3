##
## Makefile for Makefile in /home/jean.walrave/projects/epitech/jetpack2Tek3_2016
## 
## Made by Jean Walrave
## Login   <jean.walrave@epitech.net>
## 
## Started on  Thu Jul 13 09:08:21 2017 Jean Walrave
## Last update Thu Jul 20 09:49:24 2017 Jean Walrave
##

SERVER		= serverJ2T3

SERVER_SRCS	= server/srcs/server.c \
		  server/srcs/argparser/argparser.c \
		  server/srcs/argparser/port.c \
		  server/srcs/argparser/gravity.c \
		  server/srcs/argparser/map.c \
		  server/srcs/network/nserver.c \
		  server/srcs/network/nclient.c \
		  server/srcs/network/socket.c \
		  server/srcs/network/message.c \
		  server/srcs/network/hookers/hooker.c \
		  server/srcs/network/hookers/chooker_id.c \
		  server/srcs/network/hookers/chooker_map.c \
		  server/srcs/network/hookers/chooker_ready.c \
		  server/srcs/network/hookers/chooker_fire.c \
		  server/srcs/game/map.c \
		  server/srcs/game/player.c \
		  server/srcs/game/game.c \
		  server/srcs/game/displacement.c \

SERVER_OBJS	= $(SERVER_SRCS:.c=.o)

CC		= gcc

CFLAGS		+= -W -Wall -Wextra -Werror

CPPFLAGS	+= -Iserver/includes/

RM		= rm -rf

all:	server
	@echo        "|-----------------------|"
	@echo        "|     IT\'S WORKING!    |"
	@echo        "|     ____v__   _  _    |"
	@echo        "|    | 0     |  \||/    |"
	@echo        "|    |       |__/ |     |"
	@echo        "|    ~~~~~~~~~~~~~~~    |"
	@echo        "|-----------------------|"

server: $(SERVER)

$(SERVER):	$(SERVER_OBJS)
		$(CC) -o $(SERVER) $(SERVER_OBJS) -lm

clean:
	$(RM) $(SERVER_OBJS)

fclean: clean
	$(RM) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
