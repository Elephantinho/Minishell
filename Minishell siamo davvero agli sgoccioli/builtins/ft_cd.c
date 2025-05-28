/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:58:11 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/28 01:49:49 by ale              ###   ########.fr       */
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
	if (envp[i][5] == '\0' || envp[i] == NULL)
		return (NULL);
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	return (path);
}

void	set_or_add_env(char *name, char *value, char ***envp)
{
	if (ft_getenv(name, *envp))
		ft_setenv(name, value, envp);
	else
		ft_addenv(name, value, envp);
}

void	ft_cd_null_path(char ***envp)
{
	char	*home;
	char	*new_pwd;
	char	*old_pwd;

	home = find_home_path(*envp);
	if (!home)
		write(2, "Minishell: cd: HOME not set\n", 28);
	old_pwd = getcwd(NULL, 0);
	if (chdir(home) == -1)
	{
		ft_printf("cd: %s: %s\n", home, strerror(errno));//da mettere write 2 forse?
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

void	ft_cd_pars(char **args, char ***envp)
{
	if (args == NULL || args[0] == NULL)
	{
		write(2, "no path present\n", 16);
		return ;
	}
	ft_cd(args[1], envp);
}

void	ft_cd(char *path, char ***envp)
{
	char	*old_pwd;
	char	*new_pwd;

	if (path == NULL)
		ft_cd_null_path(envp);
	else
	{
		old_pwd = getcwd(NULL, 0);
		if (chdir(path) == -1)
		{
			ft_printf("cd: %s: %s\n", path, strerror(errno));//da mettere write 2 forse?
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
