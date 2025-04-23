/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:22:59 by ale               #+#    #+#             */
/*   Updated: 2025/04/23 22:27:06 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	second_fork_failed(char *s, int *arr, char **env, int exit_code)
{
	free(arr);
	free (s);
	free_env(env);
//	printf("error_code1111: %d\n", error_code);
	exit (exit_code); //da modificare error code
}

void	second_fork_worked(char *s, int *arr, char **env, t_token **tokens)
{
	char	***arr_of_matrx;

	*tokens = separete_in_tokens(s, arr);
//	ft_lstiter_tok(*tokens , prnt);
	free(arr);
	free (s);
	check_ambig_redirect(tokens, env);
	expand_dollar(tokens, env);
//	printf("\n");
	arr_of_matrx =  create_array_of_matrix(NULL, env, *tokens);
//	ft_lstiter_tok(*tokens , prnt);
	ft_lstclear_tok_mod(tokens);
	if (arr_of_matrx)
		free_cmnds(arr_of_matrx);
	free_env(env);
	exit (0);
}

char	***first_fork_worked(char *s, char **env, t_token **tokens)
{
	char	***arr_of_matrx;
	int		*arr;

	t_token	**arr_of_lists;

	arr = create_arr(s, env);
	*tokens = separete_in_tokens(s, arr);
	free(arr);
	check_ambig_redirect(tokens, env);
	expand_dollar(tokens, env);
//	printf("\n");//da levare
	ft_lstiter_tok(*tokens , prnt);//da levare
	arr_of_lists = create_arr_of_lists(s, env, *tokens);
	int i = 0;
	while(arr_of_lists[i] != NULL)
	{
		printf("lista %d\n", i);
		ft_lstiter_tok(arr_of_lists[i] , prnt);
		i++;
	}
	arr_of_matrx = create_array_of_matrix(s, env, *tokens);
	//printf("end first fork worked\n");
	//da levare questo doppio ciclo for che stampa la matrice
	for (int z = 0; z < 2; z++)
	{
		for (int y = 0; y < 3; y++)
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
		exit_code_pars = transl_exit_code(exit_code_pars);
		if (exit_code_pars != 0)
			second_fork_failed(s, arr, env, exit_code_pars);
		else
			second_fork_worked(s, arr, env, tokens);
	}
}
