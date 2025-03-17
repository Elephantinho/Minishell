/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:40:32 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:40:35 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_token *data, int fd)
{
	int	i;

	if (data->value[1])
	{
		ft_putstr_fd("No arguments accepted for env\n", 2);
		data->env->exit_stat = EXIT_FAILURE;
		return (0);
	}
	i = 0;
	while (data->env->var[i])
	{
		if (ft_strchr(data->env->var[i], '='))
		{
			ft_putstr_fd(data->env->var[i++], fd);
			ft_putchar_fd('\n', fd);
		}
		else
			i++;
	}
	data->env->exit_stat = 0;
	return (1);
}
