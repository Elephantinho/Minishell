/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:31:05 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/30 15:29:35 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cd_error(const char *path, int *exit_code, int is_inside_pipe)
{
	if (is_inside_pipe == 1)
		*exit_code = 1;
	else
		*exit_code = 256;
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
