/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:45:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/22 00:20:31 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_matrix(char **matrix)
{
	int	i = 0;

	if (!matrix)
	{
		printf("Matrix is NULL\n");
		return;
	}

	while (matrix[i])
	{
		printf("matrix[%d] = \"%s\"\n", i, matrix[i]);
		i++;
	}
}

void	execute_mod(char **cmds, char ***env, int *exit_code, int save_fd_in)
{
	char	*path;

	if (!cmds)
		return ;
	path = find_path(cmds[0], env, exit_code);
	if (!path)
	{
		close(save_fd_in); //vediamo se serve qui
		return ;
	}
	close(save_fd_in);
	execve(path, cmds, *env);
	perror("Minishell: Execve failed in execute");
	free(path);
	free_cmnds(&cmds);
}

char	**built_in_or_execute(char ***env, t_token **tokens, int *exit_code, int original_fd_in, int original_fd_out, int heredoc_alredy_done)
{
	char	**cmnds;
	int		save_fd_in;
//	int		save_fd_out;
//	int		heredoc_alredy_done;

	cmnds = NULL;
	save_fd_in = dup(STDIN_FILENO);
//	save_fd_out = dup(STDOUT_FILENO);
//	printf("curr: %s\n", (*tokens)->token);
	//heredoc_alredy_done = handle_heredocs(tokens, save_fd_in, original_fd_in, original_fd_out);
	close(original_fd_in);//credo sti 2 close vadano qua ma non sono sicuro
	close(original_fd_out);
	if (handle_redirections(tokens, &heredoc_alredy_done) == 1)
		cmnds = create_matrix_and_free_list(tokens, tokens, &cmnds);
	else
		ft_lstclear_tok(tokens);
	//printf("hooo\n");
//	print_matrix(cmnds);
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
				ft_exit(&cmnds, NULL, *env, exit_code);//non so se c'e ancora s da liberare
			else
				execute_mod(cmnds, env, exit_code, save_fd_in);
	//		printf("hi\n");
			//print_matrix(cmnds);
	}
	free_cmnds(&cmnds);//credo ma non sono sicuro ci vada
	//dup2(save_fd_in, STDIN_FILENO);
	//close(save_fd_in);//giusto qua? va anche dentro execute mod forse
//	dup2(save_fd_out, STDOUT_FILENO);
	//printf("quii\n");
	return (cmnds);
}

void	close_heredoc_pipes(int **heredoc_pipes, int prevpipe, int flag)//non va perche non si puo passare la matrice
{
	int z = 0;
	while(z < 256)//forse non sta funzionando perfettamente perche c'era ancora un/qualche fd aperti
	{
		if (heredoc_pipes[1][z] == 1)
		{
			if(heredoc_pipes[0][z] != prevpipe || flag == 1)
				close(heredoc_pipes[0][z]);
		}
		z++;
	}
}

void	free_arr_of_lists(t_token **arr_of_lists, int count, int flag)
{
	t_token *temp;
	t_token *temp2;
	int		i;

	i = 0;
	while((arr_of_lists)[i])
	{
		temp = (arr_of_lists)[i];
		if (i != count || flag == 1)
		{
			while(temp)
			{
				temp2 = temp->next;
				if((temp)->token)
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

void	ft_execution(t_token **arr_of_lists, char ***env, int *status)
{
	int		i = 0;
	int		count = 0;
	int		cpipe[2];
	int		prevpipe = -1;
//	int		fd_in = -1;
	//int		fd_out = -1;
	pid_t	pids[256];
 	int		save_fd_in;
	save_fd_in = dup(STDIN_FILENO);
	int	save_fd_out;
	save_fd_out = dup(STDOUT_FILENO);/* */
	//int		heredoc_alredy_done;
	t_token **first = arr_of_lists;
	t_token ***first2 = &arr_of_lists;
	int	heredoc_alredy_done;
	int	heredoc_pipes[2][256];

	int fd;
	while(count < 256)//non so nemmeno se serve o forse meglio mettere  -1
	{
		heredoc_pipes[0][count] = 0;
		heredoc_pipes[1][count] = 0;
		count++;
	}
	count = 0;
	while(arr_of_lists[count])
	{
		heredoc_pipes[1][count] = handle_heredocs(&(arr_of_lists[count]), &fd, *env);
		heredoc_pipes[0][count] = fd;
		write(2, "exitst: \n", 8);// da levare sti write
		char *srr = ft_itoa(g_exit_status);
		write(2, srr, ft_strlen(srr));
		free(srr);
		write(2, "\n", 1);
		if (g_exit_status == 130)
		{
			int z = 0;
			while(z < 256)//forse non sta funzionando perfettamente perche c'era ancora un/qualche fd aperti
			{
				if (heredoc_pipes[1][z] == 1)
				{
					close(heredoc_pipes[0][z]);
				}
				z++;
			}
			free_arr_of_lists(arr_of_lists, count, 1);
			close(save_fd_in);
			close(save_fd_out);
			return ;
		}
		count++;
	}
	count = 0;
	while (arr_of_lists[count] && g_exit_status == 0) // Ciclo per eseguire ogni comando // non so se ci va il g exit status == 0
	{
			heredoc_alredy_done = 0;
		//	int save_fd = dup(STDIN_FILENO);
			if (heredoc_pipes[1][count] == 1)
			{
				if (prevpipe != -1)
					close(prevpipe);
				prevpipe = heredoc_pipes[0][count];
				heredoc_alredy_done = 1;
			}
			// Crea una pipe se non è l'ultimo comando
			if (arr_of_lists[count + 1])
			{
				if (pipe(cpipe) == -1)
				{
					perror("Minishell: pipe");
					exit(1);// non v bene exit qua
				}
			}

			pids[i] = fork(); // Crea il processo figlio
			if (pids[i] == -1)
			{
				perror("Minishell: fork");
				exit(1);// non va bene exit qua
			}
			if (pids[i] == 0)
			{
				signal(SIGINT, SIG_DFL);
				//signal(SIGQUIT, SIG_DFL);
				int z = 0;
				while(z < 256)//forse non sta funzionando perfettamente perche c'era ancora un/qualche fd aperti
				{
					if (heredoc_pipes[1][z] == 1)
					{
						if(heredoc_pipes[0][z] != prevpipe)
							close(heredoc_pipes[0][z]);
					}
					z++;
				}
				if (prevpipe != -1 || heredoc_alredy_done == 1)//mom l'ha levato tutto questo if e il uo contenuto mi sa
				{
					dup2(prevpipe, STDIN_FILENO);
					close(prevpipe);
				}
				// Se non è l'ultimo comando, collega stdout alla pipe attuale
				if (arr_of_lists[count + 1])
				{
					close(cpipe[0]);
					dup2(cpipe[1], STDOUT_FILENO);
					close(cpipe[1]);
				}
				// Esegui il comando
			/* int	heredoc_alredy_done =  handle_heredocs(arr_of_lists, save_fd_in);*/
			//	handle_redirections(arr_of_lists, heredoc_alredy_done);
			//	printf("arr_of_lists[%d]->token: %s\n", count, (arr_of_lists[count])->token);

				free_arr_of_lists(arr_of_lists, count, 0);
				built_in_or_execute(env, &arr_of_lists[count], status, save_fd_in, save_fd_out, heredoc_alredy_done);
			//	dup2(save_fd, STDIN_FILENO);
				//close(save_fd);
				//save_fd = -1;
				if (*env)//non so se serve sto if
					free_env(*env);
				//da sistemare qua dovrebbe liberare l array di liste ma non lo fa perché le liste sono arrivate alla fine (credo)
				/* int j;
				j = 0;
				t_token *temp;
				t_token *temp2;
				//printf("(*first2)[j]: %s\n", (*first2)[j]->token);
				while((*first2)[j])
				{
					printf("primo while\n");
					temp = (*first2)[j];
					while(temp)
					{
						printf("secondo while\n");
						temp2 = temp->next;
						if((temp)->token)
							free((temp)->token);
						free(temp);
						temp = temp2;
					}
					j++;
				} */
				free(*first2);
				close_basic_fds_and_exit(*status);
			}
			else  // Codice eseguito dal processo padre
			{
				// Chiudi la pipe precedente se non è più necessaria
				if (prevpipe != -1)
					close(prevpipe);

				// Se ci sono più comandi, salva la pipe per il prossimo comando
				if (arr_of_lists[count + 1])
				{
					prevpipe = cpipe[0];
					close(cpipe[1]);
				}
				if (heredoc_alredy_done == 1)
					dup2(save_fd_in, STDIN_FILENO);
			}
			i++;
		//}
		count++;
	}
	for(int k = 0; k < 256; k++)
	{
		if (heredoc_pipes[1][k] == 1)
		{
			close(heredoc_pipes[0][k]);
			//printf("process : %d, waaaaaaaaaaaaaaaaaa\n", count);
		}
	}
	free_arr_of_lists(first, 0, 1);
	close (save_fd_in);//questi 2 close penso vadano qui ma non sono sicuro al 100% vanno anche chiusi nei figli mi sa
	close (save_fd_out);
	// Aspetta la fine di tutti i figli
	int j = 0;
	for (j = 0; j < i; j++)
		waitpid(pids[j], status, 0);
}
