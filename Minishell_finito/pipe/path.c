/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:26:02 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/26 17:36:53 by mshahein         ###   ########.fr       */
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

void	write_no_such_file_or_dir(char *cmd, int *exit_code)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory\n", 28);
	*exit_code = 127;
}

int	absolute_path(char *cmd, int *exit_code)
{
	//char	*full_path;
	int		i;

	i = 0;
	int last;
	while(cmd[i] != '\0')
		i++;
	last = i - 1;
	i = 0;
/* 	while (cmd && cmd[0] != '\0')
	{ */
		//full_path = build_path(paths[i], cmd, exit_code);
		if (!cmd || cmd[0] == '\0')
			return 0;//non so se e giusto return 0 qua
		if (access(cmd, X_OK) == 0)
		{
			printf("zaa\n");
			if (is_directory(cmd, cmd))
			{
				//free(cmd);
				//free_paths(paths);
				return (2);
			}
			if (cmd[last] == '/')
			{
				write_no_such_file_or_dir(cmd, exit_code);
				return (3);
			}
			//free_paths(paths);
			return (1);
		}
		/* if (cmd[0] == '/' && cmd[last] == '/')
		{
			write(2, "not a directory\n", 16);
			return (3);
		} */
	//	free(cmd);
		i++;
	//}
//	free_paths(paths);
	//write(2, cmd, ft_strlen(cmd));
	//if(cmd[0])
	//	write(2, ": ", 2);
	//write(2, "Command not found\n", 19);
	*exit_code = 127;// non so se e giusto
	return (0);
}

char	*find_path(char *cmd, char ***env, int *exit_code)
{
	char	**paths;
	char	*full_path;
	int		res_abs_path;
	int		last;

	last = 0;
	while(cmd[last] != '\0')
		last++;
	last = last - 1;
	res_abs_path = absolute_path(cmd, exit_code);
	if (res_abs_path == 1)
		return (cmd);
	else if (res_abs_path == 2 || res_abs_path == 3)
		return(NULL);
	/* else if( cmd[0] == '/' || cmd[last] == '/')
		return (write_no_such_file_or_dir(cmd, exit_code), NULL); //non va bene*/
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
		write_no_such_file_or_dir(cmd, exit_code);
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
			return (free_paths(paths), NULL);
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
	write(2, "Command not found\n", 19);
	*exit_code = 127;
	return (NULL);
}
