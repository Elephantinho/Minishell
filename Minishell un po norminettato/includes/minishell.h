/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:34 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/19 21:22:51 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "../parsing/parsing.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	error_code;

typedef struct s_tk_division
{
	int	i;
	int	prev_is_whitespace;
	int	start;
	int	quotes_open;
}			t_str_tk_division;

typedef struct s_expand_dollar
{
	char	*s;
	int		i;
	t_token	*first;
	int		quotes_open;
	int		i_before_dollar;
	int		deleted_quotes_until;
	t_token	*prev;
	int		start;
	char	*env_content;
	char	*new_tok;
}			t_str;

// env
char	**copy_env(char **envp);
char	**ft_addenv(char *name, char *value, char ***env);
char	*ft_getenv(char *name, char **env);
void	ft_setenv(char *name, char *value, char ***env);
void	print_env(char **env);
void	free_env(char **env);
int		ft_env_size(char **env);

//cd
void	ft_cd_pars(char **args, char ***envp);
void	ft_cd_null_path(char ***envp);
char	*find_home_path(char **envp);

// builtins
void	ft_export(char **args, char ***env);
void	ft_env(char **env);
void	ft_unset(char **args, char ***env);
void	ft_cd(char *path, char ***envp);
void	ft_echo(char **args);
void	ft_pwd(void);

void	check_ambig_redirect(t_token **tokens, char **env);
void	check_ambig_redirect_h(char *s, int i, t_token **tks, char **env);

void	expand_dollar(t_token **tks, char **env);

//create token
void	create_token(char *s, t_token **token_list, int token_type, int *arr);
void	check_synt_err_redirect(char *s, int i, t_token **token_list, int *arr);
void	check_synt_err_pipe(char *s, int i, t_token **token_list, int *arr);
void	check_quotes(char *s, int i, int *quotes_open);

//tk_division
void	heredoc_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr);
void	redirect_input_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr);

void	create_token_base_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr);
void	base_case(t_str_tk_division *strct);
void	pipe_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr);
void	append_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr);
void	redirect_output_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr);

#endif
