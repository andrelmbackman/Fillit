# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abackman <abackman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 14:24:03 by acamaras          #+#    #+#              #
#    Updated: 2022/01/20 13:00:30 by abackman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
SRC = fillit.c solve_map.c create_map.c check_tetri.c map_utilities.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	gcc $(CFLAGS) -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $<

$(LIBFT):
		make -C libft

clean:
	/bin/rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean
re: fclean all