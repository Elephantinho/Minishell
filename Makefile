CC = cc
CFLAGS = -Wall -Wextra -Werror
LDREADFLAG = -lreadline
NAME = minishell
SRC = main.c \

OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDREADFLAG)

clean:
	rm -f $(OBJ)
	@make -C libft clean --quiet

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean --quiet

re : fclean all

libft/libft.a:
	@echo "Compiling libft..."
	@make -C libft --quiet

.PHONY: all clean fclean re
