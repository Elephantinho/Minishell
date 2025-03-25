/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/03/25 13:02:15 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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
	free_env(&env);

	return (0);
}

