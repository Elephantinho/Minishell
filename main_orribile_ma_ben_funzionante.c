/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/16 01:42:45 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

void parsing(char *s, char **env, t_token **tokens)
{
	//valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes ./minishell
	int	*arr;
	int	pid;
	int	pid2;

	pid = fork();
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
	{
		arr = create_arr(s, env);
		pid2 = fork();
		if (pid2 == -1)
		perror("fork failed");//non so se va bene come errore
		if (pid2 == 0)
		{
			free_env(env);
			*tokens = separete_in_tokens(s, arr);
			free(arr);
			free (s);
			ft_lstclear_tok(tokens);
			exit(0);
		}
		else
		{
			waitpid(pid2, &error_code, 0);
	//		printf("error_code: %d\n", error_code);
			if (error_code != 0)
			{
				free(arr);
				free (s);
				exit (error_code);
			}
			else
				*tokens = separete_in_tokens(s, arr);
		}
	//	ft_lstiter_tok(*tokens , prnt);
		free(arr);
		free (s);
		check_ambig_redirect(tokens, env);
		expand_dollar(tokens, env);
		printf("\n");
	//	ft_lstiter_tok(*tokens , prnt);
		ft_lstclear_tok(tokens);
	}
	else
	{
		waitpid(pid, &error_code, 0);
		if (error_code != 0)
		{
			free(s);
			return ;
		}
		else
		{
			arr = create_arr(s, env);
			*tokens = separete_in_tokens(s, arr);
			free(arr);
			free (s);
			check_ambig_redirect(tokens, env);
			expand_dollar(tokens, env);
			printf("\n");
			ft_lstiter_tok(*tokens , prnt);
			ft_lstclear_tok(tokens);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char	**env;
	//char	**args;
	char	*s = "aaa > $aaa ";
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

	return (0);
}

