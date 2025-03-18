/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:07 by mshahein          #+#    #+#             */
/*   Updated: 2025/03/18 18:46:39 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *s;

	while(1)
	{
		s = readline("minishell ");
		if (!s)
			break ;
		add_history(s);
		free(s);
	}
	//rl_clear_history();
	return (0);
}
