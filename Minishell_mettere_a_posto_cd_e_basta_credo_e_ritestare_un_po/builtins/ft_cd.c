/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:58:11 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/29 23:05:56 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>

char	*find_home_path(char **envp)
{
	char	*path;
	int		i;

	if (envp == NULL)
		return (NULL);
	i = 0;
	while (ft_strncmp(envp[i], "HOME=", 5))
		i++;
	if (ft_strncmp(envp[i], "HOME=", 5) != 0)
		return (NULL);
	if (envp[i] == NULL || envp[i][5] == '\0')
		return (NULL);
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	return (path);
}

void	check_home_exist()

void	ft_cd_null_path(char ***envp, int *exit_code, int is_inside_pipe)
{
	char	*home;
	char	*new_pwd;
	char	*old_pwd;

	
	old_pwd = getcwd(NULL, 0);
	if (chdir(home) == -1)
	{
		print_cd_error(home);
		free(home);
		free (old_pwd);
		return ;
	}
	if (old_pwd)
		set_or_add_env("OLDPWD", old_pwd, envp);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		set_or_add_env("PWD", new_pwd, envp);
	free(home);
	free(new_pwd);
	free(old_pwd);
}

void	ft_cd(char *path, char ***envp, \
		int *exit_code, int is_inside_pipe)
{
	char	*old_pwd;
	char	*new_pwd;

	if (path == NULL)
		return ;
		ft_cd_null_path(envp);
	else
	{
		old_pwd = getcwd(NULL, 0);
		if (chdir(path) == -1)
		{
			print_cd_error(path);
			free (old_pwd);
			return ;
		}
		else
		{
			if (old_pwd)
				set_or_add_env("OLDPWD", old_pwd, envp);
			new_pwd = getcwd(NULL, 0);
			if (new_pwd)
				set_or_add_env("PWD", new_pwd, envp);
			free(new_pwd);
			free(old_pwd);
		}
	}
}
