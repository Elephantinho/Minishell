/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:56 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/27 20:26:04 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_mod_no_pipes_case_child(char ***cmds, char ***env, \
							int *exit_code, t_exec_no_pipes *s)
{
	char	*path;

	path = find_path((*cmds)[0], env, exit_code);
	if (!path)
	{
		if (s->save_fd_in != STDIN_FILENO)
			close(s->save_fd_in);
		if (s->save_fd_out != STDOUT_FILENO)
			close(s->save_fd_out);
		free_cmnds(cmds);
		free_env(*env);
		close_basic_fds_and_exit(*exit_code);
	}
	close(s->save_fd_in);
	close(s->save_fd_out);
	execve(path, *cmds, *env);
	write(2, "Minishell: ", 11);
	perror(path);
	free(path);
	free_cmnds(cmds);
	free_env(*env);
	close_basic_fds_and_exit(*exit_code);
}

void	execute_mod_no_pipes_case(char ***cmds, char ***env, \
							int *exit_code, t_exec_no_pipes *s)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		perror("fork failed");
	if (pid == 0)
	{
		execute_mod_no_pipes_case_child(cmds, env, exit_code, s);
	}
	else
		waitpid(pid, exit_code, 0);
	if (!WIFEXITED(*exit_code) && transl_exit_code(*exit_code) == 131)
		write(2, "^\\Quit (core dumped)\n", 21);
}

void	built_in_or_execute_no_pipes_h(char ***env, \
										int *exit_code, t_exec_no_pipes *s)
{
	if ((ft_strncmp(s->cmnds[0], "export", 6) == 0) && !s->cmnds[0][6])
		ft_export(s->cmnds, env);
	else if ((ft_strncmp(s->cmnds[0], "cd", 2) == 0) && !s->cmnds[0][2])
		ft_cd_pars(s->cmnds, env);
	else if ((ft_strncmp(s->cmnds[0], "pwd", 3) == 0) && !s->cmnds[0][3])
		ft_pwd();
	else if ((ft_strncmp(s->cmnds[0], "env", 3) == 0) && !s->cmnds[0][3])
		ft_env(*env);
	else if ((ft_strncmp(s->cmnds[0], "unset", 5) == 0) && !s->cmnds[0][5])
		ft_unset(s->cmnds, env);
	else if ((ft_strncmp(s->cmnds[0], "echo", 4) == 0) && !s->cmnds[0][4])
		ft_echo(&(s->cmnds[1]));
	else if ((ft_strncmp(s->cmnds[0], "exit", 4) == 0) && !s->cmnds[0][4])
	{
		write(2, "exit\n", 5);
		ft_exit_no_pipes(&(s->cmnds), s, *env, exit_code);//non so se c'e ancora s da liberare
	}
	else
		execute_mod_no_pipes_case(&(s->cmnds), env, exit_code, s);//in questo caso bisogna passare save fd in e chiuderlo dentro mi sa
}

char	**built_in_or_execute_no_pipes(char ***env, t_token **tk_list, \
														int *exit_code)
{
	t_exec_no_pipes	st;

	init_built_in_or_exec_no_pipes(env, tk_list, exit_code, &st);
	if (g_exit_status == 130)
	{
		return (handle_cntrl_c_in_exec_no_pipe(&st), NULL);//non so se è giusto ritornare NULL qui
	}
	if (handle_redirections(tk_list, &st.heredoc_alredy_done, exit_code) == 1)
		st.cmnds = create_matrix_and_free_list(tk_list, tk_list, &st.cmnds);
	else
		ft_lstclear_tok(&(tk_list[0]));
	if (st.heredoc_alredy_done == 1)
		dup2(st.fd, STDIN_FILENO);
	if (st.fd >= 0)
		close(st.fd);
	free(tk_list);
	if (st.cmnds)
	{
		built_in_or_execute_no_pipes_h(env, exit_code, &st);
	}
	free_cmnds(&st.cmnds);
	reset_stdin_stdout_in_exec_no_pipe(&st);
	st.cmnds = NULL;
	return (st.cmnds);
}
