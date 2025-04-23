/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:47:45 by ale               #+#    #+#             */
/*   Updated: 2025/04/22 19:14:02 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft/libft.h"

//path

char	*find_path(char *cmd, char ***env, int *exit_code);
char	*getenv_path(char **env);
void	free_paths(char **paths);
char	*build_path(char *dir, char *cmd, int *exit_code);
char	**get_paths_from_env(char ***env, char *cmd, int *exit_code);
char	*find_command_in_paths(char *cmd, char **paths, int *exit_code);
