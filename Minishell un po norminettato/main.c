/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/19 20:41:57 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>


int	count_n_of_matrx(t_token *token)
{
	int	len;
	int	flag;

	len = 0;
	flag = 1;
	while(token)
	{
		if(token->e_tk_type == NORMAL && flag == 1)
		{
			len++;
			flag = 0;
		}
		else if (token->e_tk_type == PIPE)
			flag = 1;
		token = token->next;
	}
	return (len);
}

int	count_n_of_lines(t_token *tokens)
{
	int	n_lines;

	n_lines = 0;
	while (tokens && tokens->e_tk_type == NORMAL)
		{
			n_lines++;
			tokens = tokens->next;
		}
	return (n_lines);
}

char	***create_array_of_matrix(t_token *tokens)
{
	char	***arr_of_matrx;
	int		i;
	int		len;
	int		lines;
	int		j;

	len = count_n_of_matrx(tokens);
	i = 0;
//	printf("len: %d\n", len);
	arr_of_matrx = malloc(sizeof(char **) * (len + 1));
	while(i < len && tokens)
	{
//		printf("oooo\n");
//		printf("token type: %d, token: %s    \n", tokens->e_tk_type, tokens->token);
		lines = count_n_of_lines(tokens);
//		printf("lines: %d\n", lines);
//		printf("i: %d   ", i);
		arr_of_matrx[i] = malloc(sizeof(char *) * (lines + 1));
		j = 0;
		while (tokens && tokens->e_tk_type == NORMAL)
		{
			arr_of_matrx[i][j] = tokens->token;
			j++;
			tokens = tokens->next;
	//		if (tokens)
	//		printf("aatoken type: %d, token: %s    \n", tokens->e_tk_type, tokens->token);
		}
		arr_of_matrx[i][j] = NULL;
		while (tokens && tokens->e_tk_type == PIPE)
			tokens = tokens->next;
		i++;
	}
	arr_of_matrx[i] = NULL;
	return (arr_of_matrx);
}

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
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
	{
		arr = create_arr(s, env);
		*tokens = separete_in_tokens(s, arr);
		ft_lstiter_tok(*tokens , prnt);
		free(arr);
		free (s);
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
		//ft_lstclear_tok_mod(tokens);
		return (arr_of_matrx);
	}
	else
	{
		free(s);
		waitpid(pid, &error_code, 0);
		exit(0);
	}
	return (NULL);
}

void	second_fork_failed(char *s, int *arr)
{
	free(arr);
	free (s);
	//printf("error_code1: %d\n", error_code);
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
		exit (0);
}

char	***first_fork_worked(char *s, char **env, t_token **tokens)
{
	char	***arr_of_matrx;
	int		*arr;

	arr = create_arr(s, env);
	printf("c\n");
	*tokens = separete_in_tokens(s, arr);
	printf("ddlalal\n");
	free(arr);
	free (s);
	check_ambig_redirect(tokens, env);
	expand_dollar(tokens, env);
	printf("\n");//da levare
	ft_lstiter_tok(*tokens , prnt);//da levare
	arr_of_matrx =  create_array_of_matrix(*tokens);
	printf("end first fork worked\n");
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
	printf("ohhohoh\n");
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
//		printf("error_code: %d\n", error_code);
		if (exit_code_pars != 0)
			second_fork_failed(s, arr);
		else
			second_fork_worked(s, arr, env, tokens);
	}
}

char	***parsing(char *s, char **env, t_token **tokens)
{
	//valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes ./minishell
	int	pid;
	int	exit_code_pars;

	pid = fork();
	printf("first fork\n");
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
		first_fork_parsing(s, env, tokens);
	else
	{
		waitpid(pid, &exit_code_pars, 0);
		if (exit_code_pars != 0)
			return (free(s), NULL);
		else
			return (first_fork_worked(s, env, tokens));
	}
	return (NULL); //non ci dovrebbe mai andare qui credo
}

void	free_cmnds(char ***cmnds)
{
	//NON TESTATA da vedere sia giusta
	if (cmnds)
	{
		int i = 0;
		while (cmnds[i])
		{
			// Libera ogni argomento
			int j = 0;
			while(cmnds[i])
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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char	**env;
	char	***cmnds;
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
	//int flagg = 1;
	while (1)
	{
		// Leggi la riga di input
	//	s = readline("minishell ");
		s = get_next_line(0);
		printf("s: (%s)", s);
		printf("AAAuuuu\n");
	 	if (!s)
			break;// Uscita se l'utente digita EOF (Ctrl+D)
	//	add_history(s);
		printf("bbb\n");
		cmnds = parsing(s, env, &tokens);
		printf("cadacc4u832470324\n");
		//printf("siamo qui\n");
		//cmnds = ft_split(s, ' ');
	 	if (cmnds && cmnds[1] == NULL)
		{
			printf("aaddd\n");
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
		//	printf("EEE\n");
			free(s);
		//	printf("FFF\n");
		//free_cmnds(cmnds);
		}
	}
//	clear_history();
	free_env(env);

	return (0);
}

