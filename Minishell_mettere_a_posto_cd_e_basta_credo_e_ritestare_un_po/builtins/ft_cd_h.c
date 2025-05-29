/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:31:05 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 23:06:56 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd_pars(char **args, char ***envp, int *exit_code, int is_inside_pipe)
{
	if (args == NULL || args[0] == NULL)
	{
		if (is_inside_pipe == 1)
			exit_code = 1;
		else
			//non so quale
		write(2, "no path present\n", 16);
		return ;
	}
	ft_cd(args[1], envp);
}

void	print_cd_error(const char *path)
{
	write(2, "cd: ", 4);
	if (path)
		write(2, path, strlen(path));
	write(2, ": ", 2);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	set_or_add_env(char *name, char *value, char ***envp)
{
	if (ft_getenv(name, *envp))
		ft_setenv(name, value, envp);
	else
		ft_addenv(name, value, envp);
}
