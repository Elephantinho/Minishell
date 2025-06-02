/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:31:05 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/31 18:40:42 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd_pars(char **args, char ***envp, \
			int *exit_code, int is_inside_pipe)
{
	if (args != NULL && args[0] && args[1])
	{
		if (is_inside_pipe == 1)
			*exit_code = 1;
		else
			*exit_code = 256;
		write(2, "Minishell: cd: too many arguments\n", 34);
		return ;
	}
	else if (args != NULL && args[0] != NULL && args[0][0] == '\0')
		return ;
	if (args[0] == NULL)
	{
		ft_cd_null_path(envp, exit_code, is_inside_pipe);
		return ;
	}
	ft_cd(args[0], envp, exit_code, is_inside_pipe);
}

void	print_cd_error(const char *path, int *exit_code, int is_inside_pipe)
{
	if (is_inside_pipe == 1)
		*exit_code = 1;
	else
		*exit_code = 256;
	write(2, "Minishell: cd: ", 15);
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
