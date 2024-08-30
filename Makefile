# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geymat <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 04:17:20 by geymat            #+#    #+#              #
#    Updated: 2024/02/18 11:47:47 by geymat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = the_project/delete.c \
     the_project/events.c \
     the_project/ft_split.c \
     the_project/main.c \
     the_project/parsing_checks.c \
     the_project/parsing_utils.c \
     the_project/thegame.c \
     the_project/utils.c \
     the_project/window.c

HEADERS = the_project/so_long.h

OBJECTS = $(SRCS:.c=.o)

MINILIBX = minilibx-linux/libmlx.a

NAME = so_long

CFLAGS = -Wall -Wextra -Werror

MINIFLAGS = -lX11 -lXext -Lminilibx-linux/ -lmlx

all: $(NAME)

%.o: %.c $(HEADERS) $(MINIHEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -I.

$(MINILIBX):
	cd ./minilibx-linux && $(MAKE) all


$(NAME): $(OBJECTS) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(MINIFLAGS)
 
clean:
	cd ./minilibx-linux && $(MAKE) clean
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

rickroll:
	curl ascii.live/rick

.PHONY: re all clean fclean rickroll
