/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/22 00:21:32 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int g_exit_status = 0;

t_token **parsing_2(char *s, char **env)
{
	//non la sto usando al momento
	int		*arr;
//	char	***arr_of_matrx;
	t_token	**arr_of_lists;
	t_token *tokens;//listone unico ancora da dividere in lista di token
//	int	pid;
	int		i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
			i++;
	if (s ==  NULL || s[i] == '\0')
		return (NULL);
//	pid = fork();
//	if (pid == -1)
//		perror("fork failed");//non so se va bene come errore
//	if (pid == 0)
//	{
	arr = create_arr(s, env);
	tokens = separete_in_tokens(s, arr);
	free(arr);
	check_ambig_redirect(&tokens, env);
	expand_dollar(&tokens, env);
	printf("\n");//da levare
	ft_lstiter_tok(tokens , prnt);//sarà da levare stampa solo la lista dei token

	//arr_of_matrx = create_array_of_matrix(s, env, *tokens);//da non fare piu e fare dentro a ogni pipe la sua matrice
	arr_of_lists = create_arr_of_lists(s, env, &tokens);

	int j = 0;
	while(arr_of_lists[j] != NULL)
	{
		printf("lista %d\n", j);
		ft_lstiter_tok(arr_of_lists[j], prnt);
		j++;
	}
	//da levare questo doppio ciclo for che stampa la matrice
	/* for (int z = 0; z < 1; z++)
	{
		for (int y = 0; y < 2; y++)
		{
			printf("s[%d][%d]: %s \n", z, y, arr_of_matrx[z][y]);
		}
	} */
	//ft_lstclear_tok_mod(tokens);//non va piu bene perche la lista
	//non va piu liberata ora che si fa l?arr_of lists
	//e andra ritornato larray of list non arr_of matrx che non va piu fatto
	return (arr_of_lists); //da cambiare ritornando arr_of_lists
//	}
//	else
//	{
//		free(s);
//		waitpid(pid, &error_code, 0);
//		exit(0);
//	}
//	return (NULL);
}
/* int	initial_check(char *s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0' && (s[i] == 32 || (s[i] >= 9 && \
			s[i] <= 13)))
		i++;
	if (s ==  NULL || s[i] == '\0')
		return (1);
	return (0);
} */
t_token **parsing(char *s, char ***env, int *exit_code_pars)
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
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
		first_fork_parsing(s, *env);
	else
	{
		waitpid(pid, exit_code_pars, 0);
	//printf("error_codefirstfork: %d\n", *exit_code_pars);
		if (*exit_code_pars != 0)
			return (NULL);
		else
			return (first_fork_worked(s, *env));
	}
	return (NULL); //non ci dovrebbe mai andare qui credo
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
	char	*s;
	int		exit_code;
	t_token		**token_list;

	token_list = NULL;
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
	env = copy_env(envp);
	//error_code = 0; // da cambiare nome della glob var e capire a cosa serve
	exit_code = 0;
	shlvl(&env);
	//int flagg = 1;
	while (1)
	{
		g_exit_status = 0;
		signal(SIGQUIT, sigquit_handler);
		signal(SIGINT, sigint_handler);
		// Leggi la riga di input
		s = readline("minishell ");
		//s = get_next_line(0);
		//printf("s: (%s)", s);
	 	if (!s)
		{
			write(1, "exit\n", 5);
			break;
		}// Uscita se l'utente digita EOF (Ctrl+D)
		add_history(s);
		token_list = parsing(s, &env, &exit_code);
		printf("finito parsing\n");
		if (token_list && (*token_list)->token)
		{
			if (token_list[1] == NULL)
			{
				//printf("caso1!!!!!!!!!!!\n");
				built_in_or_execute_no_pipes(&env, token_list, &exit_code, s);
			}
			else
			{
				//printf("caso2!!!!!!!!!!!\n");
				ft_execution(token_list, &env, &exit_code);
			}
		}
	/* 	cmnds = built_in_or_execute(s, &env, &tokens, &exit_code);
		if (s)
			free(s);
		if (cmnds)// ochhio che qui cmnds era ancora con triplo puntatore
			free_cmnds(cmnds);*/
		modify_exitcode(&env, exit_code);//per segnali se serve 130=33280   131=33536
	}
//	clear_history();
	free_env(env);
	close_basic_fds_and_exit(exit_code);// qua invece della variabile exit code mi sa che va preso exit code da env o forse no
	return (0); // da levare(?)
}

