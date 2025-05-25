/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:45:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/24 22:28:30 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
	{
		printf("Matrix is NULL\n");
		return ;
	}
	while (matrix[i])
	{
		printf("matrix[%d] = \"%s\"\n", i, matrix[i]);
		i++;
	}
}

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
	perror("Minishell: Execve failed in execute");
	free(path);
	free_cmnds(&cmds);
}

char	**built_in_or_execute(char ***env, t_token **tokens, int *exit_code)
{
	char	**cmnds;
	int		heredoc_alredy_done;

	cmnds = NULL;
	if (handle_redirections(tokens, &heredoc_alredy_done, exit_code) == 1)
		cmnds = create_matrix_and_free_list(tokens, tokens, &cmnds);
	else
		ft_lstclear_tok(tokens);
	if (cmnds && cmnds[0])
	{
		if ((ft_strncmp(cmnds[0], "export", 6) == 0) && cmnds[0][6] == '\0')
			ft_export(cmnds, env);
		else if ((ft_strncmp(cmnds[0], "cd", 2) == 0) && cmnds[0][2] == '\0')
			ft_cd_pars(cmnds, env);
		else if ((ft_strncmp(cmnds[0], "pwd", 3) == 0) && cmnds[0][3] == '\0')
			ft_pwd();
		else if ((ft_strncmp(cmnds[0], "env", 3) == 0) && cmnds[0][3] == '\0')
			ft_env(*env);
		else if ((ft_strncmp(cmnds[0], "unset", 5) == 0) && cmnds[0][5] == '\0')
			ft_unset(cmnds, env);
		else if ((ft_strncmp(cmnds[0], "echo", 4) == 0) && cmnds[0][4] == '\0')
			ft_echo(&(cmnds[1]));
		else if ((ft_strncmp(cmnds[0], "exit", 4) == 0) && cmnds[0][4] == '\0')
			ft_exit(&cmnds, NULL, *env, exit_code);// da testare meglio di sicuro
		else
			execute_mod(cmnds, env, exit_code);
	}
	free_cmnds(&cmnds);
	return (cmnds);
}

void	free_arr_of_lists(t_token **arr_of_lists, int count, int flag)
{
	t_token	*temp;
	t_token	*temp2;
	int		i;

	i = 0;
	while (arr_of_lists && (arr_of_lists)[i])
	{
		temp = (arr_of_lists)[i];
		if (i != count || flag == 1)
		{
			while (temp)
			{
				temp2 = temp->next;
				if ((temp)->token)
					free((temp)->token);
				free(temp);
				temp = temp2;
			}
		}
		i++;
	}
	if (flag == 1)
		free(arr_of_lists);
}

void	init_hereoc_pipes(t_exec *st)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		st->heredoc_pipes[0][i] = 0;
		st->heredoc_pipes[1][i] = 0;
		i++;
	}
}

void	close_heredoc_pipes_first(t_exec *st)
{
	int	k;

	k = 0;
	while (k < 256)
	{
		if (st->heredoc_pipes[1][k] == 1)
			close(st->heredoc_pipes[0][k]);
		k++;
	}
}

int	do_heredoc(t_token **arr_of_lists, t_exec *st, char ***env)
{
	st->count = 0;
	while (arr_of_lists[st->count])
	{
		st->heredoc_pipes[1][st->count] = \
			handle_heredocs(&(arr_of_lists[st->count]), &(st->fd), *env);
		st->heredoc_pipes[0][st->count] = st->fd;
		if (g_exit_status == 130)
		{
			close_heredoc_pipes_first(st);
			free_arr_of_lists(arr_of_lists, st->count, 1);
			return (1);
		}
		st->count++;
	}
	return (0);
}

int	exec_part_before_fork(t_token **arr_of_lists, t_exec *st, int *status)
{
	st->heredoc_alredy_done = 0;
	if (st->heredoc_pipes[1][st->count] == 1)
	{
		if (st->prevpipe != -1)
			close(st->prevpipe);
		st->prevpipe = st->heredoc_pipes[0][st->count];
		st->heredoc_alredy_done = 1;
	}
	if (arr_of_lists[st->count + 1])
	{
		if (pipe(st->cpipe) == -1)
		{
			perror("Minishell: pipe");
			*status = 1;
			return (1);
		}
	}
	return (0);
}

void	close_heredoc_pipes(t_exec *st, int flag)
{
	int	z;

	z = 0;
	while (z < 256)
	{
		if (st->heredoc_pipes[1][z] == 1)
		{
			if (st->heredoc_pipes[0][z] != st->prevpipe || flag == 1)
				close(st->heredoc_pipes[0][z]);
		}
		z++;
	}
}

void	child_in_execution(t_token **arr_of_lists, t_exec *st, \
							char ***env, int *status)
{
	signal(SIGINT, SIG_DFL);
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
	built_in_or_execute(env, &arr_of_lists[st->count], status);
	if (*env)
		free_env(*env);
	free(*(st->first2));
	close_basic_fds_and_exit(*status);
}

void	init_t_exec(t_token **arr_of_lists, t_exec *st)
{
	st->i = 0;
	st->j = 0;
	st->count = 0;
	st->flag = 0;
	st->prevpipe = -1;
	st->first = arr_of_lists;
	st->first2 = &arr_of_lists;
}

void	upd_pipe_in_exec(t_token **arr_of_lists, t_exec *st)
{
	if (st->prevpipe != -1)
		close(st->prevpipe);
	if (arr_of_lists[st->count + 1])
	{
		st->prevpipe = st->cpipe[0];
		close(st->cpipe[1]);
	}
}

void	ft_execution_h(t_token **arr_of_lists, t_exec *st, \
						char ***env, int *status)
{
	if (exec_part_before_fork(arr_of_lists, st, status) == 1)
		return ;
	st->pids[st->i] = fork();
	if (st->pids[st->i] == -1)
	{
		perror("Minishell: fork error");
		*status = 1;
		return ;
	}
	if (st->pids[st->i] == 0)
	{
		child_in_execution(arr_of_lists, st, env, status);
	}
	else
	{
		upd_pipe_in_exec(arr_of_lists, st);
	}
	st->i++;
	(st->count)++;
}

void	ft_execution(t_token **arr_of_lists, char ***env, int *status)
{
	t_exec	st;

	init_t_exec(arr_of_lists, &st);
	init_hereoc_pipes(&st);
	if (do_heredoc(arr_of_lists, &st, env) == 1)
		return ;
	signal(SIGINT, sigint_handler);
	st.count = 0;
	while (arr_of_lists[st.count])
	{
		ft_execution_h(arr_of_lists, &st, env, status);
	}
	close_heredoc_pipes_first(&st);
	free_arr_of_lists(st.first, 0, 1);
	while (st.j < st.i)
	{
		waitpid(st.pids[st.j], status, 0);
		if (transl_exit_code(*status) == 131)
			st.flag = 1;
		st.j++;
	}
	if (st.flag == 1)
		write(2, "^\\Quit (core dumped)\n", 21);
	if (transl_exit_code(*status) != g_exit_status)
		g_exit_status = 0;
}
