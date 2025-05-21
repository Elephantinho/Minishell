/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_forks_h.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:24:12 by ale               #+#    #+#             */
/*   Updated: 2025/05/21 22:55:22 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	transl_exit_code(int exit_code)
{
	if (WIFEXITED(exit_code))
	{
		// Child terminated normally
		exit_code = WEXITSTATUS(exit_code);
		return (exit_code); // You can propagate the same exit code
	}
	else if (WIFSIGNALED(exit_code))
	{
		// Child terminated by a signal
		exit_code = WTERMSIG(exit_code);
		return (128 + exit_code);
	}
	else if (WIFSTOPPED(exit_code))
	{
		// Child was stopped (not terminated)
		exit_code = WSTOPSIG(exit_code);
		return (128 + exit_code); // Similar convention
	}
	else if (WIFCONTINUED(exit_code))
		return (0); // No error
	else
	{
		// This should rarely happen
		return (1); // Generic error
	}
}

void	modify_exitcode(char ***env, int exit_code)
{
	char	*temp;

	//gestisci exit code dei segnali 
	if (ft_getenv("last_ex_cd", *env))
	{
		temp = ft_itoa(exit_code);
		ft_setenv("last_ex_cd", temp, env);
	//	printf("lastexcdd: %d\n", ft_atoi(ft_getenv("last_ex_cd", *env)));
		free(temp);
	}
	else//serve se per caso cancellano manualmente la variabile
	{
		temp = ft_itoa(exit_code);
		ft_addenv("last_ex_cd", temp, env);
		free(temp);
	}
}
