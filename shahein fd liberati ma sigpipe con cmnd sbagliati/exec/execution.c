/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:45:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/15 02:18:15 by ale              ###   ########.fr       */
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
		free_cmnds(&cmds);
		free_env(*env);
		exit (*exit_code);
		return ;
	}
	close(save_fd_in);
	execve(path, cmds, *env);
	perror("Minishell: Execve failed in execute");
	free(path);
	free_cmnds(&cmds);
}

char	**built_in_or_execute(char ***env, t_token **tokens, int *exit_code, int original_fd_in, int original_fd_out)
{
	char	**cmnds;
	int		save_fd_in;
//	int		save_fd_out;
	int		heredoc_alredy_done;

	save_fd_in = dup(STDIN_FILENO);
//	save_fd_out = dup(STDOUT_FILENO);
//	printf("curr: %s\n", (*tokens)->token);
	heredoc_alredy_done = handle_heredocs(tokens, save_fd_in, original_fd_in, original_fd_out);
	close(original_fd_in);//credo sti 2 close vadano qua ma non sono sicuro
	close(original_fd_out);
	handle_redirections(tokens, heredoc_alredy_done);
	cmnds = create_matrix_and_free_arr_of_lists(tokens, tokens, &cmnds);
	printf("hooo\n");
	print_matrix(cmnds);
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
				ft_exit(&cmnds, NULL, *env, exit_code);//non so se c'e ancora s da liberare
			else
				execute_mod(cmnds, env, exit_code, save_fd_in);
			printf("hi\n");
			print_matrix(cmnds);
	}
	free_cmnds(&cmnds);//credo ma non sono sicuro ci vada
	cmnds = NULL;//forse non serve
	dup2(save_fd_in, STDIN_FILENO);
	close(save_fd_in);//giusto qua? va anche dentro execute mod forse
//	dup2(save_fd_out, STDOUT_FILENO);
	printf("quii\n");
	return (cmnds);
}


void	ft_execution(t_token **tokens, char ***env, int *status)
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
	t_token **first = tokens;
	t_token ***first2 = &tokens;

	while (tokens[count]) // Ciclo per eseguire ogni comando
	{
		if (tokens[count]->e_tk_type == 0) // Se è un comando da mettere anche se e' un redirect(?)
		{
			// Crea una pipe se non è l'ultimo comando
			if (tokens[count + 1])
			{
				if (pipe(cpipe) == -1)
				{
					perror("Minishell: pipe");
					exit(1);
				}
			}
			pids[i] = fork(); // Crea il processo figlio
			if (pids[i] == -1)
			{
				perror("Minishell: fork");
				exit(1);
			}
			if (pids[i] == 0)
			{
				if (prevpipe != -1)
				{
					dup2(prevpipe, STDIN_FILENO);
					close(prevpipe);
				}
				// Se non è l'ultimo comando, collega stdout alla pipe attuale
				if (tokens[count + 1])
				{
					close(cpipe[0]);
					dup2(cpipe[1], STDOUT_FILENO);
					close(cpipe[1]);
				}
				// Esegui il comando
			/* int	heredoc_alredy_done =  handle_heredocs(tokens, save_fd_in);*/
			//	handle_redirections(tokens, heredoc_alredy_done);
				printf("tokens[%d]->token: %s\n", count, (tokens[count])->token);
				built_in_or_execute(env, &tokens[count], status, save_fd_in, save_fd_out);
				if (*env)//non so se serve sto if
					free_env(*env);
				/*
				//da sistemare qua dovrebbe liberare l array di liste ma non lo fa perché le liste sono arrivate alla fine (credo)
				int j;
				j = 0;
				t_token *temp;
				t_token *temp2;
				//printf("(*first2)[j]: %s\n", (*first2)[j]->token);
				while((*first2)[j])
				{
					temp = (*first2)[j];
					while(temp)
					{
						temp2 = temp->next;
						free((temp)->token);
						free(temp);
						temp = temp2;
					}
					j++;
				}
				free(*first2); */
				exit(*status);
			}
			else  // Codice eseguito dal processo padre
			{
				// Chiudi la pipe precedente se non è più necessaria
				if (prevpipe != -1)
					close(prevpipe);

				// Se ci sono più comandi, salva la pipe per il prossimo comando
				if (tokens[count + 1])
				{
					prevpipe = cpipe[0];
					close(cpipe[1]);
				}
			}
			i++;
		}
		count++;
	}
	int j;
	j = 0;
	t_token *temp;
	t_token *temp2;
	//printf("first[j]: %s", first[j]->token);
	while(first[j])
	{
		temp = first[j];
		while(temp)
		{
			temp2 = temp->next;
			free((temp)->token);
			free(temp);
			temp = temp2;
		}
		j++;
	}
	free(first);
	close (save_fd_in);//questi 2 close penso vadano qui ma non sono sicuro al 100% vanno anche chiusi nei figli mi sa
	close (save_fd_out);
	// Aspetta la fine di tutti i figli
	for (j = 0; j < i; j++)
		waitpid(pids[j], status, 0);
}


