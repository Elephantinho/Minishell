/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:26:02 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/09 09:46:04 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char *cmd, char ***env)
{
	char	**paths;
	char	*full_path;

	paths = get_paths_from_env(env);
	if (!paths)
		return (NULL);
	full_path = find_command_in_paths(cmd, paths);
	return (full_path);
}

char	*getenv_path(char ***env)
{
	int	i;

	i = 0;
	while (*env[i])
	{
		if (ft_strncmp(*env[i], "PATH=", 5) == 0)
			return (*env[i] + 5);
		i++;
	}
	return (NULL);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*build_path(char *dir, char *cmd)
{
	char	*path;

	path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!path)
		perror("Malloc failed in build_path");
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}

char	**get_paths_from_env(char ***env)
{
	char	*path_env;
	char	**paths;

	path_env = getenv_path(env);
	if (!path_env)
	{
		perror("PATH environment variable not found");
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		perror("Split failed in get_paths_from_env");
	return (paths);
}

char	*find_command_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		full_path = build_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths(paths);
	perror("Command not found in PATH");
	return (NULL);
}
