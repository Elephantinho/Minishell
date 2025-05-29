CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDREADFLAG = -lreadline
NAME = minishell
VALGRIND = valgrind --suppressions=valgrind.supp --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --track-fds=yes --trace-children=yes

SRC = main.c \
		env/add_env.c \
		env/free_env.c \
		env/copy_print_env.c \
		env/env_size.c \
		env/get_set_env.c \
		builtins/env.c \
		builtins/ft_cd.c \
		builtins/ft_cd_h.c \
		builtins/ft_echo.c \
		builtins/ft_pwd.c \
		builtins/export.c \
		builtins/unset.c \
		builtins/unset_utils.c \
		builtins/exit.c \
		parsing/check_ambig_redirect.c \
		parsing/create_tokens.c \
		parsing/dollar_special_cases.c \
		parsing/expand_dollar.c \
		parsing/get_var_from_env.c \
		parsing/init_token.c \
		parsing/parsing_list.c \
		parsing/take_out_quotes.c \
		parsing/tk_division_big_while.c \
		parsing/tk_division_big_while_h.c \
		parsing/tokens_division.c \
		parsing/create_arr_of_lists.c \
		pipe/path.c \
		pipe/path_h.c \
		parsing_forks.c \
		parsing_forks_h.c \
		free_vari.c \
		exec/execution_child.c \
		exec/execution.c \
		exec/execution_no_pipes.c \
		exec/execution_no_pipes_h.c \
		exec/handle_pipes_and_free_for_execution.c \
		redirections/redirections.c \
		redirections/redirections_utils.c \
		redirections/handle_heredoc.c \
		create_matrix.c \
		signals/signals.c \
		#	parsing/create_arr_of_matrix.c \#

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

val: $(NAME)
	@echo "Using Valgrind..."
	@$(VALGRIND) ./$(NAME)

re : fclean all

includes/libft/libft.a:
	@echo "Compiling libft..."
	@make -C includes/libft --quiet

.PHONY: all clean fclean val re
