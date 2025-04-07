/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:33:14 by ale               #+#    #+#             */
/*   Updated: 2025/04/08 00:53:40 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/get_next_line_bonus.h"

struct	s_token_quotes;
struct	s_token;

enum	e_token_type_for_quotes
{
	NO_QUOTES,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
};

enum	e_token_type
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
	int				e_token_type;
	struct s_token	*next;
}					t_token;

typedef struct s_token_quotes
{
	char					*token;
	int						e_token_type_for_quotes;
	struct s_token_quotes	*next;
}				t_token_quotes;

t_token_quotes	*ft_lstlast_quotes(t_token_quotes *lst);
t_token_quotes	*ft_lstnew_quotes(void *content, int token_type);
void			ft_lstadd_back_quotes(t_token_quotes **lst, \
				t_token_quotes *new);
void			ft_lstclear_quotes(t_token_quotes **lst);

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
