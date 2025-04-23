/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/23 21:40:15 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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
//	pid = fork();
//	if (pid == -1)
//		perror("fork failed");//non so se va bene come errore
//	if (pid == 0)
//	{
	arr = create_arr(s, env);
	*tokens = separete_in_tokens(s, arr);
	ft_lstiter_tok(*tokens , prnt);
	free(arr);
	check_ambig_redirect(tokens, env);
	expand_dollar(tokens, env);
	ft_lstiter_tok(*tokens , prnt);
	//ft_lstclear_tok(tokens);
	
	arr_of_matrx = create_array_of_matrix(s, env, *tokens);
	//printf("\n");
	for (int z = 0; z < 1; z++)
	{
		for (int y = 0; y < 2; y++)
		{
			printf("s[%d][%d]: %s \n", z, y, arr_of_matrx[z][y]);
		}
	}
	ft_lstclear_tok_mod(tokens);
	return (arr_of_matrx);
//	}
//	else
//	{
//		free(s);
//		waitpid(pid, &error_code, 0);
//		exit(0);
//	}
	return (NULL);
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
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
		first_fork_parsing(s, *env, tokens);
	else
	{
		waitpid(pid, exit_code_pars, 0);
	printf("error_codefirstfork: %d\n", *exit_code_pars);
		if (*exit_code_pars != 0)
			return (NULL);
		else
			return (first_fork_worked(s, *env, tokens));
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

/*
//funz inutile che era in execute, da levare secondo me
void	ft_error(char *msg)
{
	perror(msg);
	return ;
} */

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
	int pid;
	pid = fork();
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
	{
		execve(path, cmds, *env);
		perror("Execve failed in execute");
		free(path);
		//free_paths(cmds);
	}
	else
		waitpid(pid, exit_code, 0);
	free(path);
//	printf("exit, code; %d\n", *exit_code);
}

char	***built_in_or_execute(char *s, char ***env, t_token **tokens, int *exit_code)
{
	char	***cmnds;

	cmnds = parsing(s, env, tokens, exit_code);
	if (cmnds)
	{
		if (cmnds[1] == NULL)
		{
			if ((ft_strncmp(cmnds[0][0], "export", 6) == 0) && cmnds[0][0][6] == '\0')
				ft_export(cmnds[0], env);
			else if ((ft_strncmp(cmnds[0][0], "cd", 2) == 0) && cmnds[0][0][2] == '\0')
				ft_cd_pars(cmnds[0], env);
			else if ((ft_strncmp(cmnds[0][0], "pwd", 3) == 0) && cmnds[0][0][3] == '\0')
				ft_pwd();
			else if ((ft_strncmp(cmnds[0][0], "env", 3) == 0) && cmnds[0][0][3] == '\0')
				ft_env(*env);
			else if ((ft_strncmp(cmnds[0][0], "unset", 5) == 0) && cmnds[0][0][5] == '\0')
				ft_unset(cmnds[0], env);
			else if ((ft_strncmp(cmnds[0][0], "echo", 4) == 0) && cmnds[0][0][4] == '\0')
				ft_echo(&(cmnds[0][1]));
			else
				execute_mod(cmnds[0], env, exit_code);
		}
	}
	return (cmnds);
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
	//error_code = 0; // da cambiare nome della glob var e capire a cosa serve
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
		cmnds = built_in_or_execute(s, &env, &tokens, &exit_code);
		if (s)
			free(s);
		if (cmnds)
			free_cmnds(cmnds);
		modify_exitcode(&env, exit_code);
	}
//	clear_history();
	free_env(env);
	exit(exit_code);
	return (0); // da levare(?)
}

