/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:56 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/23 23:25:29 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_mod_no_pipes_case(char ***cmds, char ***env, int *exit_code, int fd_in, int fd_out)
{
	char	*path;
	int		pid;

	pid = fork();
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
	{
		if (!(*cmds))
			close_basic_fds_and_exit(1);//serve a qualcosa questo caso? e perche usciamo con 1 non con 0 in caso?
		path = find_path((*cmds)[0], env, exit_code);
		if (!path)
		{
			if(fd_in != STDIN_FILENO)
				close(fd_in);
			if(fd_out != STDOUT_FILENO)
				close(fd_out);
			free_cmnds(cmds);
			free_env(*env);
			close_basic_fds_and_exit(*exit_code);
		}
		close(fd_in);
		close(fd_out);
		execve(path, *cmds, *env);
		perror("Minishell: Execve failed in execute");
		free(path);
		free_cmnds(cmds);
	}
	else
		waitpid(pid, exit_code, 0);
	if (transl_exit_code(*exit_code) == 131)
		write(2, "^\\Quit (core dumped)\n", 21);
//	printf("exit, code; %d\n", *exit_code);
}

char	**built_in_or_execute_no_pipes(char ***env, t_token **token_list, int *exit_code, char *s)
{
	char	**cmnds;
	int		save_fd_in;
	int		save_fd_out;
	int		heredoc_alredy_done;
	int		fd;

	save_fd_in = dup(STDIN_FILENO);
	save_fd_out = dup(STDOUT_FILENO);


	cmnds = NULL;
	heredoc_alredy_done = handle_heredocs(token_list, &fd, *env);
	if (g_exit_status == 130)
	{
		int l = 0;
		while(l < 256)//forse non sta funzionando perfettamente perche c'era ancora un/qualche fd aperti
		{
			if (heredoc_alredy_done == 1)//ha senso questo? meglio metere de fd != -1 forse?
			{
				close(fd);
			}
			l++;
		}
		//free_arr_of_lists(arr_of_lists, count, 1);
		t_token *temp2;
		l = 0;
			while(*token_list)
			{
				temp2 = (*token_list)->next;
				if((*token_list)->token)
					free((*token_list)->token);
				free(*token_list);
				*token_list = temp2;
			}
			free(token_list);
			l++;
		close(save_fd_in);
		close(save_fd_out);
		return NULL;// non so se va bene ritornare null
	}
	if (handle_redirections(token_list, &heredoc_alredy_done, exit_code) == 1)
		cmnds = create_matrix_and_free_list(token_list, token_list, &cmnds);
	else
		ft_lstclear_tok(&(token_list[0]));
	if (heredoc_alredy_done == 1)
		dup2(fd, STDIN_FILENO);
	if(fd >= 0)
		close(fd);
	free(token_list);
	if (cmnds)
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
				ft_exit(&cmnds, s, *env, exit_code);//non so se c'e ancora s da liberare
			else
				execute_mod_no_pipes_case(&cmnds, env, exit_code, save_fd_in, save_fd_out);//in questo caso bisogna passare save fd in e chiuderlo dentro mi sa
	}
	free_cmnds(&cmnds);
	dup2(save_fd_in, STDIN_FILENO);
	close(save_fd_in);
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
	cmnds = NULL;//forse non serve
	return (cmnds);
}
