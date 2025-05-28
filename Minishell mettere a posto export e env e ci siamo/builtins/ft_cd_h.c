/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:31:05 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/28 16:38:31 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd_pars(char **args, char ***envp)
{
	if (args == NULL || args[0] == NULL)
	{
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
