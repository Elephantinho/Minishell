/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:58:11 by ade-ross          #+#    #+#             */
/*   Updated: 2025/03/21 23:55:55 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	if (envp[i][5] == '\0' || envp[i][5] == NULL)
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

void	ft_cd_null_path(char **envp)
{
	char	*home;
	char	*new_path;
	char	*old_path;

	home = find_home_path(envp);
	if (!home)
		printf("cd: HOME not set\n");//non so se vada bene sto errore
	old_path = getcwd(NULL, 0);
	if (chdir(home) == -1)
	{
		ft_printf("cd: %s: %s\n", home, strerror(errno));
		free(home);
		free (old_path);
		return ;
	}
	if (!old_path)
		;//aggiorna oldpath su env
	new_path = getcwd(NULL, 0);
	//aggiorna path su envp mettendoci home e freea path se serve
	free(home);
	free(new_path);
	free(old_path);
}

void	ft_cd(char *path, char **envp)
{
	char	*old_path;
	char	*new_path;

	if (path == NULL)
		ft_cd_null_path(envp);
	else
	{
		old_path = getcwd(NULL, 0);
		if (chdir(path) == -1)
		{
			ft_printf("cd: %s: %s\n", path, strerror(errno));
			free (old_path);
			return ;
		}
		else
		{
			if (!old_path)
				;//aggiorna oldpath su env
			new_path = getcwd(NULL, 0);
			//aggiorna path su envp mettendoci home e freea path se serve
			free(new_path);
			free(old_path);
		}
	}
}
