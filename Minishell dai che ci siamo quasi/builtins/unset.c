/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:37:04 by mshahein          #+#    #+#             */
/*   Updated: 2025/03/21 21:16:18 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(char **args, char ***env)
{
	int		i;
	int		j;
	char	*name;
	char	**new_env;

	// Alloca un nuovo array per l'ambiente
	new_env = (char **)malloc(sizeof(char *) * (ft_env_size(*env) + 1)); // +1 per NULL finale
	if (!new_env)
		return; // Gestione dell'errore di malloc

	// Cicla attraverso gli argomenti da rimuovere
	i = 1;  // Inizia a 1 per saltare il nome del comando (es. "unset")
	j = 0;
	while (args[i])
	{
		name = args[i];

		// Copia tutte le variabili d'ambiente, eccetto quella da rimuovere
		for (int k = 0; (*env)[k]; k++)
		{
			if (ft_strncmp((*env)[k], name, ft_strlen(name)) != 0)
			{
				new_env[j] = ft_strdup((*env)[k]);
				if (!new_env[j])
				{
					// Gestione dell'errore di strdup (libera la memoria precedentemente allocata)
					while (j > 0)
						free(new_env[--j]);
					free(new_env);
					return;
				}
				j++;
			}
		}
		i++;
	}

	new_env[j] = NULL;

	free_env(*env);

	*env = new_env;
}


