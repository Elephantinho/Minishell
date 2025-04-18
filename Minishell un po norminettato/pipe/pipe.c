/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:47:30 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/09 09:39:48 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

int	pipe_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				return (1);
			else if (str[i + 1] == '\0')
				return (1);
			else if (str[i - 1] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

#include "../includes/minishell.h"

void	execute_pipeline(char *cmd_line, char ***env)
{
	char **commands;
	int i = 0;
	int fd[2];  // pipe
	pid_t pid;

	// Splitta il comando in base al carattere pipe '|'
	commands = ft_split(cmd_line, '|');
	if (!commands)
	{
		perror("ft_split failed in execute_pipeline");
		return;
	}

	// Loop per ogni comando separato da pipe
	while (commands[i])
	{
		if (pipe(fd) == -1)
		{
			perror("Pipe failed");
			return;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			return;
		}

		if (pid == 0)  // Processo figlio
		{
			// Se non è l'ultimo comando, l'output va nella pipe
			if (commands[i + 1])
				dup2(fd[1], STDOUT_FILENO);
			// Se non è il primo comando, l'input viene dalla pipe precedente
			if (i > 0)
				dup2(fd[0], STDIN_FILENO);

			// Chiudi la pipe, non serve più
			close(fd[0]);
			close(fd[1]);

			// Esegui il comando
			execute(commands[i], env);
			exit(0);
		}
		else  // Processo padre
		{
			// Chiude la pipe nel processo padre, per non usarla nel ciclo successivo
			close(fd[1]);
			// Se non è l'ultimo comando, l'input del prossimo comando sarà dalla pipe
			if (i > 0)
				close(fd[0]);

			wait(NULL);  // Attende la terminazione del figlio
		}
		i++;
	}
	// Libera i comandi splittati
	free_paths(commands);
}



