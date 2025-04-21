/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/21 00:42:55 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <sys/wait.h>

//int	error_code;

/*
void	handle_pipes_or_execute(char *cmd_line, char ***env)
{
	if (pipe_check(cmd_line))
	{
		// Se c'è una pipe, esegui la pipeline
		execute_pipeline(cmd_line, env);
	}
	else
	{
		// Se non c'è pipe, esegui il comando normale
		execute(cmd_line, env);
	}
} */

void parsing(char *s, char **env, t_token **tokens)
{
	int	*arr;
	int	pid;
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
			i++;
	if (s ==  NULL || s[i] == '\0')
		return (NULL);
	/* pid = fork();
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
	{ */
		arr = create_arr(s, env);
		*tokens = separete_in_tokens(s, arr);
		ft_lstiter_tok(*tokens , prnt);
		free(arr);
		free (s);
		check_ambig_redirect(tokens, env);
		expand_dollar(tokens, env);
		printf("\n");
		ft_lstiter_tok(*tokens , prnt);
	//	ft_lstclear_tok(tokens);
/* 	}
	else
	{
		free(s);
		waitpid(pid, &error_code, 0);
	} */
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char		**env;
//	char		**args;
	char		*s;
	int		shlvl;
	t_token		*tokens;

	env = copy_env(envp);
	error_code = 0;
	if (ft_getenv("SHLVL", env))
	{
		shlvl = ft_atoi(ft_getenv("SHLVL", env)) + 1;
		s = ft_itoa(shlvl);
		ft_setenv("SHLVL", s, &env);
		free(s);
		/* s = ft_getenv("SHLVL", env);
		printf("shlvl: %s\n", s); */
	}
	//while (1)
	{
		// Leggi la riga di input
		/* s = readline("minishell ");
		if (!s)
			break; // Uscita se l'utente digita EOF (Ctrl+D)
		add_history(s); */
		s = get_next_line(0);
		parsing(s, env, &tokens);


		//handle_pipes_or_execute(s, &env);
		/* args = ft_split(s, ' ');
		if (ft_strncmp(args[0], "export", 6) == 0)
			ft_export(args, &env);
		if (ft_strncmp(args[0], "cd", 2) == 0)
			ft_cd_pars(args, &env);
		if (ft_strncmp(args[0], "pwd", 3) == 0)
			ft_pwd();
		if (ft_strncmp(args[0], "env", 3) == 0)
			ft_env(env);
		if (ft_strncmp(args[0], "unset", 5) == 0)
			ft_unset(args, &env);
		free(s);
		if (args)
		{
			int i = 0;
			while (args[i])
			{
				free(args[i]); // Libera ogni argomento
				i++;
			}
			free(args); // Libera l'array degli argomenti
		} */
	}
	/* if (env)
	{
		int i = 0;
		while (env[i])
		{
			free(env[i]); // Libera ogni stringa nell'ambiente
			i++;
		}
		free(env); // Libera l'array di puntatori
	} */
	free_env(env);
//METTERE EXIT CON L'ULTIMO EXIT CODE tipo exit(error_code);
	return (0);
}

