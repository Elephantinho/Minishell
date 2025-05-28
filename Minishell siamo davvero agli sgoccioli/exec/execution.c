/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:45:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/28 01:19:12 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	print_matrix(char **matrix)
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
} */
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

void	init_t_exec(t_token **arr_of_lists, t_exec *st)
{
	st->i = 0;
	st->j = 0;
	st->count = 0;
	st->flag = 0;
	st->prevpipe = -1;
	st->first = arr_of_lists;
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
		if (!WIFEXITED(*status) && transl_exit_code(*status) == 131)
			st.flag = 1;
		st.j++;
	}
	if (st.flag == 1)
		write(2, "^\\Quit (core dumped)\n", 21);
	if (transl_exit_code(*status) != g_exit_status)
		g_exit_status = 0;
}
