/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_forks_h.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:24:12 by ale               #+#    #+#             */
/*   Updated: 2025/05/25 17:15:58 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	transl_exit_code(int exit_code)
{
	if (WIFEXITED(exit_code))
	{
		exit_code = WEXITSTATUS(exit_code);
		return (exit_code);
	}
	else if (WIFSIGNALED(exit_code))
	{
		exit_code = WTERMSIG(exit_code);
		return (128 + exit_code);
	}
	else if (WIFSTOPPED(exit_code))
	{
		exit_code = WSTOPSIG(exit_code);
		return (128 + exit_code);
	}
	else if (WIFCONTINUED(exit_code))
		return (0);
	else
		return (1);
}

void	modify_exitcode(char ***env, int exit_code)
{
	char	*temp;

	if (g_exit_status == 130)
		exit_code = 33280;
	if (g_exit_status == 131)
		exit_code = 33536;
	if (ft_getenv("last_ex_cd", *env))
	{
		temp = ft_itoa(exit_code);
		ft_setenv("last_ex_cd", temp, env);
		free(temp);
	}
	else
	{
		temp = ft_itoa(exit_code);
		ft_addenv("last_ex_cd", temp, env);
		free(temp);
	}
}
