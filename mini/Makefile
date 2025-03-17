# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 14:23:17 by mchiaram          #+#    #+#              #
#    Updated: 2025/02/24 17:47:08 by mchiaram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
LIBFT		:= libft/libft.a
CC			:= cc
CFLAGS		:= -Werror -Wextra -Wall -I./include
LIB			:= ft
RM			:= rm -rf
SRC_DIR		:= src
BUILD_DIR	:= .build
DIR_DUP		:= mkdir -p $(@D)

SRCS		:= $(SRC_DIR)/exec_init/minishell.c \
				$(SRC_DIR)/exec_init/init_prompt.c \
				$(SRC_DIR)/exec_init/process.c \
				$(SRC_DIR)/exec_init/redir.c \
				$(SRC_DIR)/exec_init/pipes.c \
				$(SRC_DIR)/exec_init/sig_handlers.c \
				$(SRC_DIR)/exec_init/hd_utils.c \
				$(SRC_DIR)/exec_init/utils.c \
				$(SRC_DIR)/parsing/parse.c \
				$(SRC_DIR)/parsing/input_management/t_parse_values_fill.c \
				$(SRC_DIR)/parsing/input_management/t_parse_types_fill.c \
				$(SRC_DIR)/parsing/input_management/t_token_fill.c \
				$(SRC_DIR)/parsing/input_management/t_token_value_copy.c \
				$(SRC_DIR)/parsing/input_management/manage_quotes.c \
				$(SRC_DIR)/parsing/input_management/parse_utils.c \
				$(SRC_DIR)/free_mem/free_mem.c \
				$(SRC_DIR)/free_mem/free_parse_struct.c \
				$(SRC_DIR)/free_mem/free_token_struct.c \
				$(SRC_DIR)/free_mem/free_env_struct.c \
				$(SRC_DIR)/handle_env/handle_env.c \
				$(SRC_DIR)/builtins/builtin.c \
				$(SRC_DIR)/builtins/ft_cd.c \
				$(SRC_DIR)/builtins/ft_echo.c \
				$(SRC_DIR)/builtins/ft_exit.c \
				$(SRC_DIR)/builtins/ft_pwd.c \
				$(SRC_DIR)/builtins/ft_unset.c \
				$(SRC_DIR)/builtins/ft_env.c \
				$(SRC_DIR)/builtins/export/ft_export.c \
				$(SRC_DIR)/builtins/export/export_errors_handle.c \
				$(SRC_DIR)/builtins/export/export_print.c

OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LDFLAGS		:= $(addprefix -L,$(dir $(LIBFT)))
LDLIB		:= $(addprefix -l,$(LIB)) -lreadline

all : $(LIBFT) header $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(LDFLAGS) $^ $(LDLIB) -o $@ && echo "${BOLD}${GREEN}Done!${NO_COLOR}" \
	|| echo "${BOLD}${RED}Error compiling $(C_NAME)${NO_COLOR}";

$(LIBFT):
	$(MAKE) -C $(@D)
	$(MAKE) bonus -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP) $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

clean: 
	$(MAKE) clean -C libft
	$(RM) $(BUILD_DIR)

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)

header: 
	${info }
	${info ${BOLD}Creating -> ${YELLOW}$(NAME)${NO_COLOR}}
	@if $(MAKE) -q $(NAME) ; then \
		echo "${BOLD}${YELLOW}No changes detected, not rebuilding $(NAME)${NO_COLOR}"; \
	fi

supp:
	touch ~/.supp.supp
	echo "{" > ~/.supp.supp
	echo "   IgnoreReadlineLeak" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   match-leak-kinds: reachable" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   fun:add_history" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   IgnoreReadlineLeak" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   match-leak-kinds: reachable" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   fun:readline" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   IgnoreReadlineLeak" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   fun:readline" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   Malloc_Leak_Below_Main" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   fun:malloc" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   obj:/usr/bin/*" >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   Calloc_Leak_Below_Main" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   fun:calloc" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   obj:/usr/bin/*" >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "{" >> ~/.supp.supp
	echo "   Realloc_Leak_Below_Main" >> ~/.supp.supp
	echo "   Memcheck:Leak" >> ~/.supp.supp
	echo "   fun:realloc" >> ~/.supp.supp
	echo "   ..." >> ~/.supp.supp
	echo "   obj:/usr/bin/*" >> ~/.supp.supp
	echo "}" >> ~/.supp.supp
	echo "use file supp to suppress valgrind errors: valgrind --suppressions="'"$$HOME/.supp.supp"'" ./minishell"

.PHONY: all re clean fclean header supp
.SILENT:

YELLOW		:= ${shell tput setaf 3}
GREEN		:= ${shell tput setaf 2}
RED			:= ${shell tput setaf 1}
NO_COLOR	:= ${shell tput sgr0}
BOLD		:= ${shell tput bold}