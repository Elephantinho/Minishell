/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:45:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/10 17:49:17 by mshahein         ###   ########.fr       */
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
		//free_paths(cmds);
	//	ft_error("Command execution failed");//magari mettere no path foundcome mess err invece o non serve perche gia lo scrive prima senon trova path(?)
		return ;
	}
	/*int pid;
	 pid = fork();
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
	{ */
		execve(path, cmds, *env);
		perror("Execve failed in execute");
		free(path);
		//free_paths(cmds);
	/* }
	else */
		/* waitpid(pid, exit_code, 0);
	free(path); */
//	printf("exit, code; %d\n", *exit_code);
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
	int		i;
	int		count;
	int		cpipe[2];
	int		prevpipe;
	pid_t	pid;
	int		status;
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	// Conta quanti comandi ci sono nella lista dei token
	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (tokens[i] && ft_isalpha(tokens[i]->token[0]))
			count++;
		i++;
	}

	// Esecuzione dei comandi in pipeline
	i = 0;
	prevpipe = -1;
	while (i < count)
	{
		// Crea una pipe solo se NON siamo sull'ultimo comando
		if (i != count - 1)
		{
			if (pipe(cpipe) == -1)
			{
				perror("Minishell: error: pipe");
				exit(1);
			}
		}

		pid = fork();
		if (pid == -1)
		{
			perror("Minishell: error: fork");
			exit(1);
		}

		if (pid == 0)  // CODICE FIGLIO
		{
			//gestione delle redirezioni
			handle_redirections(&tokens[i], &fd_in, &fd_out);
			// Se NON è il primo comando, collega stdin al pipe precedente
			if (i != 0)
			{
				if (dup2(prevpipe, 0) == -1)
				{
					perror("Minishell: error: dup2");
					exit(1);
				}
				close(prevpipe);
			}
			// Se NON è l'ultimo comando, collega stdout al pipe attuale
			if (i != count - 1)
			{
				close(cpipe[0]);  // Chiudi lettura
				if (dup2(cpipe[1], 1) == -1)
				{
					perror("Minishell: error: dup2");
					exit(1);
				}
				close(cpipe[1]);
			}

			// Esegui il comando
			if (tokens[i])
				built_in_or_execute(env, &tokens[i], &status);
			exit(0); // da mettere exit code
		}
		else  // CODICE PADRE
		{
			// Se NON è il primo comando, chiudi il pipe precedente
			if (i != 0)
				close(prevpipe);
			// Se NON è l'ultimo comando, salva la lettura della pipe per il prossimo giro
			if (i != count - 1)
			{
				close(cpipe[1]);  // Chiudi scrittura
				prevpipe = cpipe[0];  // Salva lettura per il prossimo comando
			}
			// Aspetta il figlio
			waitpid(pid, &status, 0);
		}
		i++;
	}
}

