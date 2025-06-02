/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:51:46 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/31 18:26:08 by ale              ###   ########.fr       */
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

char	*build_path(char *dir, char *cmd, int *exit_code)
{
	char	*path;

	path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!path)
	{
		perror("Minishel: Malloc failed in build_path");
		*exit_code = 1;
		return (NULL);
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

int	check(char **full_path, char *cmd, char **paths, int *exit_code)
{
	if (access(*full_path, X_OK) == 0)
	{
		if (is_directory(*full_path, cmd, exit_code))
		{
			free(*full_path);
			free_paths(paths);
			*full_path = NULL;
			return (1);
		}
		free_paths(paths);
		return (1);
	}
	return (0);
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
		if (check(&full_path, cmd, paths, exit_code) == 1)
			return (full_path);
		free(full_path);
		i++;
	}
	free_paths(paths);
	write(2, cmd, ft_strlen(cmd));
	write (2, ": ", 2);
	write(2, "Command not found\n", 19);
	*exit_code = 127;
	return (NULL);
}
