/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:11:51 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/26 16:29:46 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	slen;

	i = 0;
	if (s == 0)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (substr == 0)
		return (0);
	while (i < len && s[start + i] != '\0' && start <= slen)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
int main()
{
	const char	st[] = "ciaociaociao";
	char	*sb = ft_substr(st, 443434, 4443343);
	printf("%s\n", sb);
	return 0;
	free(sb);
	return (0);
} */
