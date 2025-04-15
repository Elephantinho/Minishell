/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:31:52 by ale               #+#    #+#             */
/*   Updated: 2025/04/13 00:18:26 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/libft/libft.h"
#include "../includes/libft/get_next_line_bonus.h"

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

void			fill_arr_single(char *s, int **arr, int *i);
void			fill_arr_double(char *s, int **arr, int *i);
int				*create_arr(char *s);
void			create_token(char *s, t_token **token_list, int token_type, int *arr);
void			check_synt_err_redirect(char *s, int i, t_token **token_list, int *arr);
void			check_synt_err_pipe(char *s, int i, t_token **token_list, int *arr);
void			check_quotes(char *s, int i, int *quotes_open);
t_token			*separete_in_tokens(char *s, int *arr);
void			ft_lstiter_tok(t_token *lst, void (*f)(void *));
void			prnt(void *s);
