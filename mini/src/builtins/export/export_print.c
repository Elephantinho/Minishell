/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:39:46 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:39:49 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var(char *var, int fd)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		write(fd, &var[i++], 1);
	if (var[i] == '=')
	{
		write (fd, &var[i++], 1);
		write(fd, "\"", 1);
		while (var[i])
			write (fd, &var[i++], 1);
		write(fd, "\"", 1);
	}
	write(fd, "\n", 1);
}

void	print_export_env(char **env, int fd)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
	{
		i++;
		if (ft_strncmp(env[i - 1], env[i], ft_strlen(env[i])) > 0)
		{
			temp = env[i - 1];
			env[i - 1] = env[i];
			env[i] = temp;
			i = 0;
		}
	}
	i = 0;
	while (env[i])
	{
		ft_putstr_fd("\033[38;5;214mexport\033[0m ", fd);
		print_var(env[i++], fd);
	}
}
