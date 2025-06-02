/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_and_free_for_execution.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:18:00 by ale               #+#    #+#             */
/*   Updated: 2025/05/29 21:31:31 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
