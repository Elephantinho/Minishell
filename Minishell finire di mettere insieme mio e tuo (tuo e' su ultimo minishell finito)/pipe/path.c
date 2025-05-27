/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:26:02 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/27 17:46:49 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_directory(char *path, char *cmd, int *exit_code)
{
	struct stat path_stat;

	if (!path)
		return (0);
	if (stat(path, &path_stat) == -1)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
	{
		write(2, "Minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Is a directory\n", 18);
		*exit_code = 126;
		return (1);
	}
	return (0);
}

void	write_no_such_file_or_dir(char *cmd, int *exit_code)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory\n", 28);
	*exit_code = 127;
}

int	absolute_path(char *cmd, int *exit_code)
{
	int		i;

	i = 0;
	int last;
	while (cmd[i] != '\0')
		i++;
	last = i - 1;
	i = 0;
	if (!cmd || cmd[0] == '\0')
		return (0);
	if (access(cmd, X_OK) == 0)
	{
		if (is_directory(cmd, cmd, exit_code))
		{
			return (2);
		}
		if (cmd[last] == '/')
		{
			write_no_such_file_or_dir(cmd, exit_code);
			return (3);
		}
		return (1);
	}
	return (0);
}

char	*find_path(char *cmd, char ***env, int *exit_code)
{
	char	**paths;
	char	*full_path;
	int		res_abs_path;
	int		last;

	last = 0;
	while (cmd[last] != '\0')
		last++;
	last = last - 1;
	res_abs_path = absolute_path(cmd, exit_code);
	if (res_abs_path == 1)
		return (cmd);
	else if (res_abs_path == 2 || res_abs_path == 3)
		return (NULL);
	paths = get_paths_from_env(env, cmd, exit_code);
	if (!paths)
		return (NULL);
	full_path = find_command_in_paths(cmd, paths, exit_code);
	return (full_path);
}
