/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:22:59 by ale               #+#    #+#             */
/*   Updated: 2025/05/25 17:13:16 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	second_fork_failed(char *s, int *arr, char **env, int exit_code)
{
	free(arr);
	free (s);
	free_env(env);
	close_basic_fds_and_exit(exit_code);
}

void	second_fork_worked(char *s, int *arr, char **env, t_token **tokens)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
		i++;
	*tokens = separete_in_tokens(s, arr, i);
	free(arr);
	free (s);
	check_ambig_redirect(tokens, env);
	expand_dollar(tokens, env);
	ft_lstclear_tok(tokens);
	free_env(env);
	close_basic_fds_and_exit(0);
}

/* void	print_arr_of_lists(t_token	**arr_of_lists)
{
	int i = 0;
	while(arr_of_lists[i] != NULL)
	{
		printf("lista %d\n", i);
		ft_lstiter_tok(arr_of_lists[i], prnt);
		i++;
	}
} */
t_token	**first_fork_worked(char *s, char **env, int i)
{
	int		*arr;
	t_token	*tokens;
	t_token	**arr_of_lists;

	arr = create_arr(s, env);
	tokens = separete_in_tokens(s, arr, i);
	free(arr);
	check_ambig_redirect(&tokens, env);
	expand_dollar(&tokens, env);
	arr_of_lists = create_arr_of_lists(s, &tokens);
	return (arr_of_lists);
}

void	second_fork_parsing(char *s, int *arr, char **env, t_token **tokens)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
		i++;
	free_env(env);
	*tokens = separete_in_tokens(s, arr, i);
	free(arr);
	free (s);
	ft_lstclear_tok(tokens);
	close_basic_fds_and_exit(0);
}

void	first_fork_parsing(char *s, char **env)
{
	int		*arr;
	int		pid2;
	int		exit_code_pars;
	t_token	*tokens;

	arr = create_arr(s, env);
	pid2 = fork();
	if (pid2 == -1)
		perror("fork failed");
	if (pid2 == 0)
		second_fork_parsing(s, arr, env, &tokens);
	else
	{
		waitpid(pid2, &exit_code_pars, 0);
		exit_code_pars = transl_exit_code(exit_code_pars);
		if (exit_code_pars != 0)
			second_fork_failed(s, arr, env, exit_code_pars);
		else
			second_fork_worked(s, arr, env, &tokens);
	}
}
