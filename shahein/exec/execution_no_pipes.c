/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:56 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/13 18:34:41 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_mod_no_pipes_case(char ***cmds, char ***env, int *exit_code, t_token **tokens)
{
	char	*path;
	int pid;
(void ) tokens;
	pid = fork();
	if (pid == -1)
		perror("fork failed");//non so se va bene come errore
	if (pid == 0)
	{

		if (!(*cmds))
			exit(1) ;
		path = find_path((*cmds)[0], env, exit_code);
		if (!path)
		{
			//ft_lstclear_mod_arr_lst(tokens);
			free_cmnds(cmds);
			free_env(*env);
		//	ft_error("Command execution failed");//magari mettere no path foundcome mess err invece o non serve perche gia lo scrive prima senon trova path(?)
			exit (*exit_code);
		}
		execve(path, *cmds, *env);
		perror("Minishell: Execve failed in execute");
		free(path);
		free_cmnds(cmds);
	}
	else
		 waitpid(pid, exit_code, 0);
//	printf("exit, code; %d\n", *exit_code);
}

char	**built_in_or_execute_no_pipes(char ***env, t_token **tokens, int *exit_code, char *s)
{
	char	**cmnds;

	//DA METTERE REDIREZIONI ANCHE QUI
	cmnds = create_matrix_and_free_arr_of_lists(tokens, tokens, &cmnds);
	free(tokens);
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
			else if ((ft_strncmp(cmnds[0], "exit", 4) == 0) && cmnds[0][4] == '\0')
				ft_exit(&cmnds, s, *env, exit_code);//non so se c'e ancora s da liberare
			else
				execute_mod_no_pipes_case(&cmnds, env, exit_code, tokens);
	}
	free_cmnds(&cmnds);//credo ma non sono sicuro ci vada
	cmnds = NULL;//forse non serve
//	printf("quii\n");
	return (cmnds);
}
