/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:20:12 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/20 14:27:55 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *cwd, char *user)
{
	size_t	i;
	size_t	j;
	char	*path;
	char	*clean_path;
	char	*user_path;

	user_path = ft_strjoin(user, "/");
	path = ft_strnstr(cwd, user_path, ft_strlen(cwd));
	free (user_path);
	if (!path || !*user)
		clean_path = ft_strdup(cwd);
	else
	{
		i = 1;
		while (i < ft_strlen(user))
			i++;
		clean_path = ft_calloc((ft_strlen(path) - i) + 2, sizeof(char));
		j = 0;
		clean_path[j++] = '~';
		while (path[i])
			clean_path[j++] = path[i++];
	}
	return (clean_path);
}

static char	*get_prompt(t_token *tok)
{
	char	*prompt;
	char	cwd[1024];
	char	*user;
	char	*path;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (NULL);
	}
	user = ft_getenv(tok->env->var, "USER");
	if (!user)
		user = ft_strdup("user");
	path = get_path(cwd, user);
	prompt = ft_strjoin("\033[1;32m", user);
	prompt = ft_freejoin(prompt, "\033[0m:\033[1;34m");
	prompt = ft_freejoin(prompt, path);
	prompt = ft_freejoin(prompt, "\033[0m$ ");
	free (user);
	if (path)
		free (path);
	return (prompt);
}

char	*prompt_init(t_token *tok)
{
	char	*prompt;
	char	*input;

	g_kill_pid = -1;
	prompt = get_prompt(tok);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	free (prompt);
	prompt = NULL;
	input = ft_freetrim(&input, " \t\n");
	g_kill_pid = -2;
	return (input);
}
