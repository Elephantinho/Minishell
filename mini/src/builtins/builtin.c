/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:40:14 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:40:16 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_builtins(t_token *data, char *builtin, int fd)
{
	char	**new_env;
	size_t	i;

	data->env->exit_stat = 0;
	if (!ft_strcmp(builtin, "unset") && data->value[1])
	{
		i = 1;
		while (data->value[i])
		{
			new_env = ft_unset(data->env->var, data->value[i++]);
			free_environment(data->env, 0);
			data->env->var = new_env;
		}
	}
	else if (!ft_strcmp(builtin, "export"))
	{
		if (!ft_export(data, fd))
			data->env->exit_stat = 1;
	}
	else
	{
		if (!ft_cd(data))
			data->env->exit_stat = 1;
	}
}

static int	open_null(int fd1)
{
	close (fd1);
	fd1 = open("/dev/null", O_WRONLY);
	if (fd1 == -1)
	{
		perror("open");
		return (0);
	}
	return (fd1);
}

int	execute_builtin(t_token *data, char *builtin, int fd1)
{
	if ((data->next && data->next->value)
		&& check_if_builtin(data->next->value[0]))
	{
		fd1 = open_null(fd1);
		if (!fd1)
			return (0);
	}
	if (ft_strcmp(builtin, "echo") == 0)
		ft_echo(data, fd1);
	else if (ft_strcmp(builtin, "pwd") == 0)
		ft_pwd(data, fd1);
	else if (ft_strcmp(builtin, "env") == 0)
	{
		if (!ft_env(data, fd1))
			return (0);
	}
	else if (ft_strcmp(builtin, "exit") == 0)
		return (1);
	else if (!ft_strcmp(builtin, "unset")
		|| !ft_strcmp(builtin, "export")
		|| !ft_strcmp(builtin, "cd"))
		env_builtins(data, builtin, fd1);
	return (1);
}
