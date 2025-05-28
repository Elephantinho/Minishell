/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:51:46 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/28 00:59:48 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	ft_strlcpy(path, dir, ft_strlen(dir) + 1);
	ft_strlcat(path, "/", ft_strlen(path) + 2);
	ft_strlcat(path, cmd, ft_strlen(path)+ ft_strlen(cmd) + 1);
	return (path);
}

char	**get_paths_from_env(char ***env, char *cmd, int *exit_code)
{
	char	*path_env;
	char	**paths;

	path_env = getenv_path(*env);
	if (!path_env)
	{
		write_no_such_file_or_dir(cmd, exit_code);
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		perror("Split failed");
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
			return (free_paths(paths), NULL);
		if (access(full_path, X_OK) == 0)
		{
			if (is_directory(full_path, cmd, exit_code))
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
	if (cmd[0])
		write (2, ": ", 2);
	write(2, "Command not found\n", 19);
	*exit_code = 127;
	return (NULL);
}
