/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:26:02 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/25 19:21:28 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_directory(char *path, char *cmd)
{
	struct stat path_stat;

	if (!path)
		return 0;

	if (stat(path, &path_stat) == -1) // stat is good or not?
		return 0;

	if (S_ISDIR(path_stat.st_mode))//si puo usare sta roba?
	{
		write(2, "Minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Is a directory\n", 18);
		return 1;
	}
	return 0;
}

char	*find_path(char *cmd, char ***env, int *exit_code)
{
	char	**paths;
	char	*full_path;

	paths = get_paths_from_env(env, cmd, exit_code);
	if (!paths)
		return (NULL);
	full_path = find_command_in_paths(cmd, paths, exit_code);
	return (full_path);
}

char	*getenv_path(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
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

char	*build_path(char *dir, char *cmd, int *exit_code)
{
	char	*path;

	path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!path)
	{
		perror("Minishel: Malloc failed in build_path");
		*exit_code = 1;
		//mettere return NULL?
	}
	ft_strlcpy(path, dir, ft_strlen(dir) + 1); //messo stlcpy instead strcpy
	ft_strlcat(path, "/", ft_strlen(path) + 2);//messo stlcat instead strcat
	ft_strlcat(path, cmd, ft_strlen(path)+  ft_strlen(cmd) + 1);//messo stlcat instead strcat
	return (path);
}

char	**get_paths_from_env(char ***env, char *cmd, int *exit_code)
{
	char	*path_env;
	char	**paths;

	path_env = getenv_path(*env);
	if (!path_env)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
		*exit_code = 127;
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		perror("Split failed");//va bene come errore??
		*exit_code = 1;
	}
	return (paths);
}

char	*find_command_in_paths(char *cmd, char **paths, int *exit_code)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths && paths[i] && cmd[0] != '\0')
	{
		full_path = build_path(paths[i], cmd, exit_code);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			if (is_directory(full_path, cmd))
			{
				free(full_path);
				free_paths(paths);
				return (NULL);
			}
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths(paths);
	write(2, cmd, ft_strlen(cmd));
	if(cmd[0])
		write(2, ": ", 2);
	write(2, "Command not found\n", 20);
	*exit_code = 127;
	return (NULL);
}
