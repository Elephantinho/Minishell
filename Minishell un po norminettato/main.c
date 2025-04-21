/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/21 04:23:31 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

void	ft_lstclear_tok_mod(t_token **lst)
{
	t_token	*temp;

	if (lst == 0)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	*lst = 0;
}

char ***parsing_2(char *s, char **env, t_token **tokens)
{
	//non la sto usando al momento
	int	*arr;
	char ***arr_of_matrx;
//	int	pid;
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
			i++;
	if (s ==  NULL || s[i] == '\0')
		return (NULL);
/* 	pid = fork();
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
	{ */
		arr = create_arr(s, env);
		*tokens = separete_in_tokens(s, arr);
		ft_lstiter_tok(*tokens , prnt);
		free(arr);
		check_ambig_redirect(tokens, env);
		expand_dollar(tokens, env);
		printf("\n");
		ft_lstiter_tok(*tokens , prnt);
		//ft_lstclear_tok(tokens);
		arr_of_matrx =  create_array_of_matrix(*tokens);
		for (int z = 0; z < 1; z++)
		{
			for (int y = 0; y < 2; y++)
			{
				printf("s[%d][%d]: %s \n", z, y, arr_of_matrx[z][y]);
			}
		}
		ft_lstclear_tok_mod(tokens);
		return (arr_of_matrx);
	/* }
	else
	{
		free(s);
		waitpid(pid, &error_code, 0);
		exit(0);
	} */
	return (NULL);
}

void	second_fork_failed(char *s, int *arr, char **env)
{
	free(arr);
	free (s);
	free_env(env);
//	printf("error_code1111: %d\n", error_code);
	exit (error_code + 1); //da modificare error code
}

void	second_fork_worked(char *s, int *arr, char **env, t_token **tokens)
{
		*tokens = separete_in_tokens(s, arr);
	//	ft_lstiter_tok(*tokens , prnt);
		free(arr);
		free (s);
		check_ambig_redirect(tokens, env);
		expand_dollar(tokens, env);
		printf("\n");
	//	ft_lstiter_tok(*tokens , prnt);
		ft_lstclear_tok(tokens);
		free_env(env);
		exit (0);
}

char	***first_fork_worked(char *s, char **env, t_token **tokens)
{
	char	***arr_of_matrx;
	int		*arr;

	arr = create_arr(s, env);
	*tokens = separete_in_tokens(s, arr);
	free(arr);
	check_ambig_redirect(tokens, env);
	expand_dollar(tokens, env);
	printf("\n");//da levare
	ft_lstiter_tok(*tokens , prnt);//da levare
	arr_of_matrx =  create_array_of_matrix(*tokens);
	//printf("end first fork worked\n");
	//da levare questo doppio ciclo for che stampa la matrice
	for (int z = 0; z < 1; z++)
	{
		for (int y = 0; y < 2; y++)
			printf("s[%d][%d]: %s \n", z, y, arr_of_matrx[z][y]);
	}
	ft_lstclear_tok_mod(tokens);//da controllare sta funz(?)
	return (arr_of_matrx);
}

void	second_fork_parsing(char *s, int *arr, char **env, t_token **tokens)
{
	free_env(env);
	*tokens = separete_in_tokens(s, arr);
	free(arr);
	free (s);
	ft_lstclear_tok(tokens);
	exit(0);
}

void	first_fork_parsing(char *s, char **env, t_token **tokens)
{
	int	*arr;
	int	pid2;
	int	exit_code_pars;

	arr = create_arr(s, env);
	pid2 = fork();
	if (pid2 == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid2 == 0)
		second_fork_parsing(s, arr, env, tokens);
	else
	{
		waitpid(pid2, &exit_code_pars, 0);
	//	printf("error_codesecfork: %d\n", exit_code_pars);
		if (exit_code_pars != 0)
			second_fork_failed(s, arr, env);
		else
			second_fork_worked(s, arr, env, tokens);
	}
}

void	modify_exitcode(char ***env, int exit_code)
{
	char	*temp;

	if (ft_getenv("last_ex_cd", *env))
	{
		temp = ft_itoa(exit_code);
		ft_setenv("last_ex_cd", temp, env);
	//	printf("lastexcdd: %d\n", ft_atoi(ft_getenv("last_ex_cd", *env)));
		free(temp);
	}
	else//serve se per caso cancellano manualmente la variabile
	{
		temp = ft_itoa(exit_code);
		ft_addenv("last_ex_cd", temp, env);
		free(temp);
	}
}

char	***parsing(char *s, char ***env, t_token **tokens, int *exit_code_pars)
{
	//valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes ./minishell
	int	pid;
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
			i++;
	if (s ==  NULL || s[i] == '\0')
		return (NULL);
	pid = fork();
//	printf("first fork\n");
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
		first_fork_parsing(s, *env, tokens);
	else
	{
		waitpid(pid, exit_code_pars, 0);
	//	printf("error_codefirstfork: %d\n", *exit_code_pars);
		if (*exit_code_pars != 0)
			return (NULL);
		else
			return (first_fork_worked(s, *env, tokens));
	}
	return (NULL); //non ci dovrebbe mai andare qui credo
}

void	free_cmnds(char ***cmnds)
{
	//un po' TESTATA da vedere sia giusta
	if (cmnds)
	{
		int i = 0;
		while (cmnds[i])
		{
			// Libera ogni argomento
			int j = 0;
			while(cmnds[i][j])
			{
				free(cmnds[i][j]);
				j++;
			}
			free(cmnds[i]);
			i++;
		}
		free(cmnds); // Libera l'array degli argomenti
	}
}

void	shlvl(char ***env)
{
	int		shlvl;
	char	*s;

	if (ft_getenv("SHLVL", *env))
	{
		shlvl = ft_atoi(ft_getenv("SHLVL", *env)) + 1;
		s = ft_itoa(shlvl);
		ft_setenv("SHLVL", s, env);
		free(s);
		/* s = ft_getenv("SHLVL", env);
		printf("shlvl: %s\n", s); */
	}
	else
		ft_addenv("SHLVL", "0", env);
	if (ft_getenv("last_ex_cd", *env))
	{
		ft_setenv("last_ex_cd", "0", env);
	}
	else
		ft_addenv("last_ex_cd", "0", env);

}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char	**env;
	char	***cmnds;
	char	*s = "aaa > $aaa ";
	int		exit_code;
	t_token		*tokens;

	env = copy_env(envp);
	error_code = 0; // da levare
	exit_code = 0;
	shlvl(&env);
	//int flagg = 1;
	while (1)
	{
		// Leggi la riga di input
	//	s = readline("minishell ");
		s = get_next_line(0);
		//printf("s: (%s)", s);
	 	if (!s)
			break;// Uscita se l'utente digita EOF (Ctrl+D)
	//	add_history(s);
		cmnds = parsing(s, &env, &tokens, &exit_code);
	 	if (cmnds)
		{
			if (cmnds[1] == NULL)
			{
				if (ft_strncmp(cmnds[0][0], "export", 6) == 0)
					ft_export(cmnds[0], &env);
				if (ft_strncmp(cmnds[0][0], "cd", 2) == 0)
					ft_cd_pars(cmnds[0], &env);
				if (ft_strncmp(cmnds[0][0], "pwd", 3) == 0)
					ft_pwd();
				if (ft_strncmp(cmnds[0][0], "env", 3) == 0)
					ft_env(env);
				if (ft_strncmp(cmnds[0][0], "unset", 5) == 0)
					ft_unset(cmnds[0], &env);
				if (ft_strncmp(cmnds[0][0], "echo", 4) == 0)
					ft_echo(&(cmnds[0][1]));
			}
		}
		if (s)
			free(s);
		if (cmnds)
			free_cmnds(cmnds);
		modify_exitcode(&env, exit_code);
	}
//	clear_history();
	free_env(env);

	return (0);
}

