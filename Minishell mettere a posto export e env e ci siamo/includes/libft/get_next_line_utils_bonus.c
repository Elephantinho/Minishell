/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:30:16 by ade-ross          #+#    #+#             */
/*   Updated: 2024/12/18 21:25:16 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

size_t	ft_strlen_mod(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	*ft_calloc_mod(size_t nmemb, size_t size)
{
	unsigned char	*arr;
	size_t			i;
	int				tot;

	tot = nmemb * size;
	if (nmemb == 0 || size == 0 || (tot / size != nmemb))
	{
		return (malloc(0));
	}
	arr = malloc(nmemb * size);
	if (!(arr))
	{
		return (NULL);
	}
	i = 0;
	while (i < (nmemb * size))
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*newst;
	int		i;

	i = 0;
	if (s1 == NULL && (s2 == NULL || *s2 == '\0'))
		return (NULL);
	newst = malloc(ft_strlen_mod(s1) + ft_strlen_mod(s2) + 1);
	if (!newst)
		return (NULL);
	while (s1 != NULL && *s1 != '\0')
	{
		newst[i] = *s1;
		i++;
		s1++;
	}
	while (s2 != NULL && *s2 != '\0')
	{
		newst[i] = *s2;
		i++;
		s2++;
	}
	newst[i] = '\0';
	return (newst);
}

char	*ft_strdup_mod(char *src)
{
	int		i;
	char	*new;

	i = 0;
	if (src == NULL)
		return (NULL);
	new = (char *)malloc(ft_strlen_mod(src) * sizeof(char) + 1);
	if (!new)
		return (0);
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_substr_mod(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	slen;

	i = 0;
	if (s == NULL || len == 0)
		return (NULL);
	slen = ft_strlen_mod(s);
	if (start >= slen)
		return (ft_strdup_mod(""));
	if (len > slen - start)
		len = slen - start;
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (substr == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0' && start <= slen)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
