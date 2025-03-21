/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:24:16 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/29 20:26:42 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// cerca quante stringhe vanno create
static int	n_of_st(char const *s, char c, int *flag, int *j)
{
	int	count;

	*flag = 0;
	*j = 0;
	count = 0;
	if (*s == '\0')
		return (0);
	while (*(s + 1) != '\0')
	{
		if (*s != c && *(s + 1) == c)
			count++;
		s++;
	}
	if (*s != c && *(s + 1) == '\0')
		count++;
	return (count);
}

static int	st_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static char	**free_malloc(char **arr)
{
	int	j;

	j = 0;
	while (arr[j] != NULL)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

static char	**write_word(char **arrst, char const *s, char c, int i)
{
	int	j;

	j = 0;
	arrst[i] = malloc((st_len(s, c) + 1) * sizeof(char));
	if (arrst[i] == NULL)
	{
		arrst = free_malloc(arrst);
		return (arrst);
	}
	while (s[j] != c && s[j] != '\0')
	{
		arrst[i][j] = s[j];
		j++;
	}
	arrst[i][j] = '\0';
	return (arrst);
}

char	**ft_split(char const *s, char c)
{
	char	**arrst;
	int		i;
	int		flag;
	int		j;

	i = 0;
	arrst = malloc((n_of_st(s, c, &flag, &j) + 1) * sizeof(char *));
	if (!arrst)
		return (0);
	while (s[j] != '\0')
	{
		if (s[j] != c && (flag == 1 || j == 0))
		{
			arrst = write_word(arrst, &s[j], c, i);
			if (arrst == NULL)
				return (NULL);
			i++;
			flag = 0;
		}
		if (s[j] == c)
			flag = 1;
		j++;
	}
	arrst[i] = 0;
	return (arrst);
}
//maybe i should not put the arrst[i] = 0 before the return at the end
/*
int	main(void)
{
	char	str[] = "aaa a aab aa";
	char	c = ' ';
	int		i = 0;

	char **ar = ft_split(str, c);
	while(ar[i] != 0)
	{
		printf("%s\n", ar[i]);
		printf("%d\n", i);
		free(ar[i]);
		i++;
	}
	i = 0;
	free(ar);
} */
