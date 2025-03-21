/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:58:11 by ade-ross          #+#    #+#             */
/*   Updated: 2025/03/21 20:43:12 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	ft_cd(char *path)
{
	char	*home;

	if (path == NULL)
	{
		home = getenv("HOME");
		if (!home)
			printf("cd: HOME not set\n");//non so se vada bene sto errore
		chdir(home);
	}
	else if (chdir(path) == -1)
		ft_printf("cd: %s: %s\n", path, strerror(errno));
}
