/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:24:22 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/20 11:19:46 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_cd_error(char *str, char **path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(*(path), 2);
	ft_putstr_fd(str, 2);
	free (*(path));
	return (0);
}

static char	*expand_home(char **env, char *path)
{
	char	*new_path;
	char	*temp;

	new_path = ft_getenv(env, "HOME");
	temp = ft_substr(path, 1, ft_strlen(path));
	new_path = ft_freejoin(new_path, temp);
	free (temp);
	return (new_path);
}

static void	update_pwd(t_token *data, char *var)
{
	size_t	i;
	char	pwd[1024];
	char	*old_pwd;
	char	**new_env;

	new_env = copy_env(data->env->var);
	getcwd(pwd, sizeof(pwd));
	old_pwd = ft_strjoin(var, pwd);
	free_environment(data->env, 0);
	data->env->var = export_var(new_env, old_pwd);
	i = 0;
	while (new_env[i])
		free (new_env[i++]);
	free (new_env);
	free (old_pwd);
}

int	ft_cd(t_token *data)
{
	char	*path;

	path = NULL;
	if (!data->value[1] || data->value[1][0] == '~')
		path = expand_home(data->env->var, data->value[1]);
	else if (data->value[1][0] == '-' && !data->value[1][1])
	{
		path = ft_getenv(data->env->var, "OLDPWD");
		if (!path)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
	}
	else
		path = ft_strdup(data->value[1]);
	if (!path)
		return (0);
	if (access(path, F_OK))
		return (print_cd_error(": No such file or directory\n", &path));
	if (access(path, X_OK))
		return (print_cd_error(": Permission denied\n", &path));
	update_pwd(data, "OLDPWD=");
	chdir(path);
	update_pwd(data, "PWD=");
	free (path);
	return (1);
}
