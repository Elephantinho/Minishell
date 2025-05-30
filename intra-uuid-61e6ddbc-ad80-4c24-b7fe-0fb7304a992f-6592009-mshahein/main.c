/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/28 19:49:14 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_exit_status = 0;

t_token	**parsing_2(char *s, char **env)
{
	int		*arr;
	t_token	**arr_of_lists;
	t_token	*tokens;
	int		i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
		i++;
	if (s == NULL || s[i] == '\0')
		return (NULL);
	arr = create_arr(s, env);
	tokens = separete_in_tokens(s, arr, i);
	free(arr);
	check_ambig_redirect(&tokens, env);
	expand_dollar(&tokens, env);
	arr_of_lists = create_arr_of_lists(s, &tokens);
	return (arr_of_lists);
}

/* int	initial_check(char *s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
		i++;
	if (s ==  NULL || s[i] == '\0')
		return (1);
	return (0);
} */
t_token	**parsing(char *s, char ***env, int *exit_code_pars)
{
	int	pid;
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
		i++;
	if (s == NULL || s[i] == '\0')
		return (NULL);
	pid = fork();
	if (pid == -1)
		perror("fork failed");
	if (pid == 0)
		first_fork_parsing(s, *env);
	else
	{
		waitpid(pid, exit_code_pars, 0);
		if (*exit_code_pars != 0)
			return (NULL);
		else
			return (first_fork_worked(s, *env, i));
	}
	return (NULL);
}

void	shlvl(char ***env)
{
	int		shlvl;
	char	*s;

	if (ft_getenv("SHLVL", *env))
	{
		shlvl = ft_atoi(ft_getenv("SHLVL", *env)) + 1;
		s = ft_itoa(shlvl);
		ft_setenv("SHLVL", s, env);
		free(s);
	}
	else
		ft_addenv("SHLVL", "0", env);
	if (ft_getenv("last_ex_cd", *env))
	{
		ft_setenv("last_ex_cd", "0", env);
	}
	else
		ft_addenv("last_ex_cd", "0", env);
}

int	main_h(char ***env,	char *s, int *exit_code, t_token **token_list)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	s = readline("minishell> ");
	if (!s)
		return (write(1, "exit\n", 5), 1);
	if (g_exit_status != 0)
	{
		modify_exitcode(env, *exit_code);
	}
	if (!(s[0] == '\0'))
		add_history(s);
	g_exit_status = 0;
	token_list = parsing(s, env, exit_code);
	if (token_list && token_list[0] && (token_list[0])->token)
	{
		if (token_list[1] == NULL)
			built_in_or_execute_no_pipes(env, token_list, exit_code);
		else
			ft_execution(token_list, env, exit_code);
	}
	else if (token_list)
		free_arr_of_lists(token_list, 1, 1);
	modify_exitcode(env, *exit_code);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		**env;
	int			exit_code;
	t_token		**token_list;
	char		*s;

	(void)argc;
	(void)argv;
	s = NULL;
	token_list = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	env = copy_env(envp);
	exit_code = 0;
	shlvl(&env);
	while (1)
	{
		if (main_h(&env, s, &exit_code, token_list) == 1)
			break ;
	}
	modify_exitcode(&env, exit_code);
	exit_code = get_last_exit_code(env);
	free_env(env);
	close_basic_fds_and_exit(exit_code);
}
