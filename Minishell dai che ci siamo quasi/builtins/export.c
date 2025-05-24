/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:48:25 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/24 20:50:23 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int verify(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	if (!((str[i] >= 'a' && str[i] <= 'z') ||
	      (str[i] >= 'A' && str[i] <= 'Z') ||
	       str[i] == '_'))
		return (-1);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z') ||
			(str[i] >= '0' && str[i] <= '9') ||
			str[i] == '_' ||
			str[i] == '"' ||
			str[i] == '\''))
			return (-1);
		i++;
	}
	return (0);
}

char *form_str(char *str)
{
	int i;
	int j;
	int count;
	char *changed;
	int len;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			count++;
		i++;
	}
	if (count == 0)
		return (strdup(str));
	len = (int)strlen(str) - count;
	changed = malloc(len + 1);
	if (!changed)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			changed[j] = str[i];
			j++;
		}
		i++;
	}
	changed[j] = '\0';
	return (changed);
}

int exisit(char **env, char *arg)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	while (env && env[i])
	{
		if (strncmp(env[i], arg, len) == 0 &&
		    (env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void free_mat(char **mat)
{
	int i;

	i = 0;
	if (!mat)
		return ;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

char **ft_copy_matrix(char **matrix)
{
	int i;
	char **copy;

	i = 0;
	if (!matrix)
		return (NULL);
	while (matrix[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		copy[i] = strdup(matrix[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int append_or_replace(char **matrix, char *arg)
{
	int pos;

	pos = exisit(matrix, arg);
	if (pos != -1)
	{
		free(matrix[pos]);
		matrix[pos] = strdup(arg);
		return (1);
	}
	return (0);
}

char **matrix_join(char **env, char **args, int new_size)
{
	int i;
	int j;
	int k;
	char **new;

	i = 0;
	j = 0;
	k = 0;
	new = malloc(sizeof(char *) * (new_size + 1));
	if (!new)
		return (NULL);
	while (k <= new_size)
	{
		new[k] = NULL;
		k++;
	}
	k = 0;
	while (env && env[i])
	{
		new[k] = strdup(env[i]);
		i++;
		k++;
	}
	j = 0;
	while (args[j])
	{
		if (!append_or_replace(new, args[j]))
		{
			new[k] = strdup(args[j]);
			k++;
		}
		j++;
	}
	new[k] = NULL;
	free_mat(env);
	return (new);
}

void swap(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void sort_env(char **env)
{
	int sorted;
	int i;

	if (!env)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (env[i] && env[i + 1])
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				swap(&env[i], &env[i + 1]);
				sorted = 0;
			}
			i++;
		}
	}
}

void print_export(char **env)
{
	int i;
	int j;
	int flag;
	char quote;
	char *str;

	i = 0;
	quote = '"';
	if (!env)
		return ;
	str = NULL;
	char **copy;

	copy = ft_copy_matrix(env);
	if (!copy)
		return ;
	sort_env(copy);
	while (copy[i])
	{
		if (strncmp(copy[i], "_=", 2) == 0)
		{
			i++;
			continue;
		}
		flag = 0;
		j = 0;
		write(1, "declare -x ", 11);
		while (copy[i][j])
		{
			if (copy[i][j] == '=' && flag == 0)
			{
				write(1, "=", 1);
				write(1, &quote, 1);
				flag = 1;
				j++;
				continue;
			}
			write(1, &copy[i][j], 1);
			j++;
		}
		if (flag)
			write(1, &quote, 1);
		write(1, "\n", 1);
		i++;
	}
	free_mat(copy);
}

// args[0] = "export", args[1..] variabili
// env è puntatore a matrice ambiente (modificabile)
void ft_export(char **args, char ***env)
{
	int i;
	int count;
	char **tmp;
	int j;

	i = 1;
	count = 0;
	if (!args[i])
	{
		print_export(*env);
		return ;
	}

	while (args[i])
	{
		if (verify(args[i]) != 0)
		{
			dprintf(2, "Minishell: export: '%s' : not a valid identifier\n", args[i]);
		}
		else
		{
			count++;
		}
		i++;
	}

	tmp = malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return ;

	i = 1;
	j = 0;
	while (args[i])
	{
		if (verify(args[i]) == 0)
		{
			tmp[j] = form_str(args[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;

	*env = matrix_join(*env, tmp, (j + (int)(*env ? 0 : 0)));

	free_mat(tmp);
}


