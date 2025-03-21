/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:34 by mshahein          #+#    #+#             */
/*   Updated: 2025/03/21 21:15:49 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// env
char	**copy_env(char **envp);
char	**ft_addenv(char *name, char *value, char **env);
char	*ft_getenv(char *name, char **env);
void	ft_setenv(char *name, char *value, char ***env);
void	print_env(char **env);
void	free_env(char **env);
int		ft_env_size(char **env);

// builtins
void	ft_export(char **args, char ***env);
void	ft_env(char **env);
void	ft_unset(char **args, char ***env);



















#endif
