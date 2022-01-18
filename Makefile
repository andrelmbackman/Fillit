NAME = fillit
SRC = fillit.c solve_map.c
OBJS = $(SRC:.c=.o)
WRNG = -Wall -Werror -Wextra

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	make -C libft/
	gcc $(WRNG) -o $(NAME) $(SRC) libft/libft.a

clean:
	/bin/rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean
re: fclean all