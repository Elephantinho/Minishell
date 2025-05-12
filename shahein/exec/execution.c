/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:45:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/12 18:40:41 by mshahein         ###   ########.fr       */
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
		perror("Execve failed in execute");
		free(path);
}

char	**built_in_or_execute(char ***env, t_token **tokens, int *exit_code)
{
	char	**cmnds;

	cmnds = create_matrix(tokens, tokens, &cmnds);
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
			else
				execute_mod(cmnds, env, exit_code);
	}
	free_cmnds(cmnds);//credo ma non sono sicuro ci vada
	cmnds = NULL;//forse non serve
	printf("quii\n");
	return (cmnds);
}


void	ft_execution(t_token **tokens, char ***env)
{
	int		i = 0;
	int		count = 0;
	int		cpipe[2];
	int		prevpipe = -1;
	int		fd_in = -1;
	int		fd_out = -1;
	pid_t	pids[256];
	int		status = 0;

	while (tokens[count]) // Ciclo per eseguire ogni comando
	{
		if (tokens[count]->e_tk_type == 0) // Se è un comando
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
				handle_redirections(&tokens[count], &fd_in, &fd_out);
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
				built_in_or_execute(env, &tokens[count], &status);
				exit(status);
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
	// Aspetta la fine di tutti i figli
	for (int j = 0; j < i; j++)
		waitpid(pids[j], &status, 0);
}


