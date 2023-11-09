# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 18:27:55 by jdufour           #+#    #+#              #
#    Updated: 2023/10/27 19:48:37 by jdufour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client

SERVER = server

SRCS_CLIENT = ft_printf/ft_format.c\
	ft_printf/ft_printf.c\
	'code de dingue attention.c'\
	client.c\

SRCS_SERVER = ft_printf/ft_format.c\
	ft_printf/ft_printf.c\
	server.c\

OBJS = $(SRCS:%.c=%.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -rfv

all: $(CLIENT) $(SERVER)

$(CLIENT): $(OBJS)
	$(CC) $(FLAGS) -o $(CLIENT) $(SRCS_CLIENT) $(OBJS)

$(SERVER): $(OBJS)
	$(CC) $(FLAGS) -o $(SERVER) $(SRCS_SERVER) $(OBJS)

clean:
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(CLIENT)
	$(RM) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
