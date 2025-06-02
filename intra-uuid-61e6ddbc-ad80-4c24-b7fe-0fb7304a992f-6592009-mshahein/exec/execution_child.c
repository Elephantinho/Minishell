/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:15:25 by ale               #+#    #+#             */
/*   Updated: 2025/05/30 22:32:36 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_mod(char **cmds, char ***env, int *exit_code)
{
	char	*path;

	if (!cmds)
		return ;
	path = find_path(cmds[0], env, exit_code);
	if (!path)
	{
		return ;
	}
	execve(path, cmds, *env);
	write(2, "Minishell: ", 11);
	perror(path);
	free(path);
}

void	built_in_or_execute_h(char ***env, t_token **arr_of_lists, \
							char	**cmnds, int *exit_code)
{
	if ((ft_strncmp(cmnds[0], "export", 6) == 0) && cmnds[0][6] == '\0')
		ft_export(cmnds, env);
	else if ((ft_strncmp(cmnds[0], "cd", 2) == 0) && cmnds[0][2] == '\0')
		ft_cd_pars(&(cmnds[1]), env, exit_code, 1);
	else if ((ft_strncmp(cmnds[0], "pwd", 3) == 0) && cmnds[0][3] == '\0')
		ft_pwd();
	else if ((ft_strncmp(cmnds[0], "env", 3) == 0) && cmnds[0][3] == '\0')
		ft_env(*env);
	else if ((ft_strncmp(cmnds[0], "unset", 5) == 0) && cmnds[0][5] == '\0')
		ft_unset(cmnds, env);
	else if ((ft_strncmp(cmnds[0], "echo", 4) == 0) && cmnds[0][4] == '\0')
		ft_echo(&(cmnds[1]));
	else if ((ft_strncmp(cmnds[0], "exit", 4) == 0) && cmnds[0][4] == '\0')
	{
		ft_exit(&cmnds, arr_of_lists, *env, exit_code);
	}
	else
		execute_mod(cmnds, env, exit_code);
}

char	**built_in_or_execute(char ***env, t_token **arr_of_lists, \
									t_token **tokens, int *exit_code)
{
	char	**cmnds;
	int		heredoc_alredy_done;

	cmnds = NULL;
	if (handle_redirections(tokens, &heredoc_alredy_done, exit_code, 1) == 1)
		cmnds = create_matrix_free_lst(tokens, arr_of_lists, &cmnds, env);
	else
		ft_lstclear_tok(tokens);
	if (cmnds && cmnds[0])
	{
		built_in_or_execute_h(env, arr_of_lists, cmnds, exit_code);
	}
	free_cmnds(&cmnds);
	return (cmnds);
}

void	child_in_execution(t_token **arr_of_lists, t_exec *st, \
							char ***env, int *status)
{
	signal(SIGINT, sigint_handler_third);
	signal(SIGQUIT, SIG_DFL);
	close_heredoc_pipes(st, 0);
	if (st->prevpipe != -1 || st->heredoc_alredy_done == 1)
	{
		dup2(st->prevpipe, STDIN_FILENO);
		close(st->prevpipe);
	}
	if (arr_of_lists[st->count + 1])
	{
		close(st->cpipe[0]);
		dup2(st->cpipe[1], STDOUT_FILENO);
		close(st->cpipe[1]);
	}
	free_arr_of_lists(arr_of_lists, st->count, 0);
	built_in_or_execute(env, arr_of_lists, &arr_of_lists[st->count], status);
	if (*env)
		free_env(*env);
	free(st->first);
	close_basic_fds_and_exit(*status);
}
