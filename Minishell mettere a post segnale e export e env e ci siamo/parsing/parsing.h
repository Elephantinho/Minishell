/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:31:52 by ale               #+#    #+#             */
/*   Updated: 2025/05/28 15:58:27 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../includes/libft/libft.h"
# include "../includes/libft/get_next_line_bonus.h"

enum	e_token_type_for_quotes
{
	NO_QUOTES,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
};

enum	e_tk_type
{
	NORMAL,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
};

typedef struct s_token
{
	char			*token;
	int				e_tk_type;
	struct s_token	*next;
}					t_token;

void			update_token_type(int *token_type, int quotes_type);
int				init_tok_type(char *s);
int				init_start(int tok_type);
void			oth_update_token_type(int *tok_type, char *s, int i, \
				int *start);

t_token			*ft_lstlast_tok(t_token *lst);
t_token			*ft_lstnew_tok(void *content, int token_type);
void			ft_lstadd_back_tok(t_token **lst, \
				t_token *new);
void			ft_lstclear_tok(t_token **lst);
void			ft_lstdelone_tok(t_token *lst);

void			fill_arr_single(char *s, int **arr, int *i);
void			fill_arr_double(char *s, int **arr, int *i);
int				*create_arr(char *s, char **env);

t_token			*separete_in_tokens(char *s, int *arr, int index);
void			ft_lstiter_tok(t_token *lst, void (*f)(void *));
void			prnt(void *s);

#endif