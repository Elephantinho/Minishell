/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:58:11 by ade-ross          #+#    #+#             */
/*   Updated: 2025/03/22 21:04:18 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>

char	*find_home_path(char **envp)
{
	char	*path;
	int		i;

	//da provare facendosi passare env da momo
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (ft_strncmp(envp[i], "HOME=", 5))
		i++;
	if (ft_strncmp(envp[i], "HOME=", 5) != 0)
		return (NULL);
	if (envp[i][5] == '\0' || envp[i] == NULL)
		return (NULL);
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));//credo
	return (path);
}
/*
char	*find_pwd_path(char **envp)
{
	char	*path;
	int		i;

	//da provare facendosi passare env da momo
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (ft_strncmp(envp[i], "PWD=", 4))
		i++;
	if (ft_strncmp(envp[i], "PWD=", 4) != 0)
		return (NULL);
	if (envp[i][4] == '\0' || envp[i][4] == NULL)
		return (NULL);
	return (path);
} */
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
		printf("cd: HOME not set\n");//non so se vada bene sto errore
	old_pwd = getcwd(NULL, 0);
	if (chdir(home) == -1)
	{
		ft_printf("cd: %s: %s\n", home, strerror(errno));
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
	//printf("arg 0: %s, arg 1: %s\n", args[0], args[1]);
	if (args == NULL || args[0] == NULL)
	{
		ft_printf("no path present");
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
			ft_printf("cd: %s: %s\n", path, strerror(errno));
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
