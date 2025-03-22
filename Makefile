CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDREADFLAG = -lreadline
NAME = minishell
SRC = main.c \
		env/add_env.c \
		env/free_env.c \
		env/copy_print_env.c \
		env/env_size.c \
		env/get_set_env.c \
		builtins/env.c \
		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_pwd.c \
		builtins/export.c \
		builtins/unset.c \

OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): includes/libft/libft.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDREADFLAG) includes/libft/libft.a

clean:
	rm -f $(OBJ)
	@make -C includes/libft clean --quiet

fclean: clean
	rm -f $(NAME)
	@make -C includes/libft fclean --quiet

re : fclean all

includes/libft/libft.a:
	@echo "Compiling libft..."
	@make -C includes/libft --quiet

.PHONY: all clean fclean re
