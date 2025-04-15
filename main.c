/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/09 09:43:05 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char	**env;
	char	**args;
	char	*s;

	env = copy_env(envp);
	while (1)
	{
		// Leggi la riga di input
		s = readline("minishell ");
		if (!s)
			break; // Uscita se l'utente digita EOF (Ctrl+D)
		add_history(s);

	/* //s = "\"\" ahaha \" ohohoh\'ehe\'\"\"  iii\"\"\"ahah\'\"ww\'\'\' |   ";
		s = get_next_line(0);
		arr = create_arr(s);
		//da qui vanno nel fork i sa e s va liberata fuori dal fork
		tokens = separete_in_tokens(s, arr);
		free(arr);
		free (s);
		check_ambig_redirect(&tokens, env);
		expand_dollar(&tokens, env);
		//printf("(%s)\n", s);
		// for(int i = 0; i < ft_strlen(s) - 1; i++)
		//	printf("%d", arr[i]);
		printf("\n");
		ft_lstiter_tok(tokens , prnt);
		ft_lstclear_tok(&tokens);
	//	free(arr);
	//	free(s); */

		
		handle_pipes_or_execute(s, &env);
		args = ft_split(s, ' ');
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
		}
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

