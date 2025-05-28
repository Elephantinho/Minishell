/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_pipes_h.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:55:58 by ale               #+#    #+#             */
/*   Updated: 2025/05/27 15:24:18 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_built_in_or_exec_no_pipes(char ***env, t_token **token_list, \
										int *exit_code, t_exec_no_pipes *st)
{
	st->env = env;
	st->token_list = token_list;
	st->exit_code = exit_code;
	st->save_fd_in = dup(STDIN_FILENO);
	st->save_fd_out = dup(STDOUT_FILENO);
	st->cmnds = NULL;
	st->heredoc_alredy_done = handle_heredocs(token_list, &(st->fd), *env);
}

void	handle_cntrl_c_in_exec_no_pipe(t_exec_no_pipes *st)
{
	if (st->fd >= 0) //testare bene cntrl c
		close(st->fd);
	free_arr_of_lists(st->token_list, 1, 1);
	close(st->save_fd_in);
	close(st->save_fd_out);
}

void	reset_stdin_stdout_in_exec_no_pipe(t_exec_no_pipes *st)
{
	dup2(st->save_fd_in, STDIN_FILENO);
	close(st->save_fd_in);
	dup2(st->save_fd_out, STDOUT_FILENO);
	close(st->save_fd_out);
}
