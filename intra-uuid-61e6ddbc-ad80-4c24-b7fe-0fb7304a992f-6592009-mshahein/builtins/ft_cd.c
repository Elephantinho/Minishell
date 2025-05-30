/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:58:11 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/30 22:53:57 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>

char	*find_home_path(char **envp)
{
	char	*path;
	int		i;

	if (envp == NULL )
		return (NULL);
	i = 0;
	while ((envp)[i] && ft_strncmp((envp)[i], "HOME=", 5) != 0)
	{
		i++;
	}
	if ((envp)[i] == NULL || (ft_strncmp((envp)[i], "HOME=", 5) == 0 && \
													(envp)[i][5] == '\0'))
		return (NULL);
	path = ft_substr((envp)[i], 5, ft_strlen((envp)[i]));
	return (path);
}

void	print_home_not_set(int *exit_code, int is_inside_pipe)
{
	if (is_inside_pipe == 1)
		*exit_code = 1;
	else
		*exit_code = 256;
	write(2, "Minishell: cd: HOME not set\n", 28);
}

void	ft_cd_null_path(char ***envp, int *exit_code, int is_inside_pipe)
{
	char	*home;
	char	*new_pwd;
	char	*old_pwd;

	home = find_home_path(*envp);
	if (!home)
	{print_home_not_set(exit_code, is_inside_pipe);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(home) == -1)
	{
		print_cd_error(home, exit_code, is_inside_pipe);
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

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		print_cd_error(path, exit_code, is_inside_pipe);
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
