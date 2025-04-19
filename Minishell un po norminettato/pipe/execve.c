/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:51:46 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/09 09:45:31 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *msg)
{
	perror(msg);
	return ;
}

void	execute(char *cmd, char ***env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
		ft_error("Split failed in execute");
	path = find_path(args[0], env);
	if (!path)
	{
		free_paths(args);
		ft_error("Command execution failed");
	}
	execve(path, args, *env);
	perror("Execve failed in execute");
	free(path);
	free_paths(args);
}


