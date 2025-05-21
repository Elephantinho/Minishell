/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:36:56 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/25 20:25:21 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*st;

	if (!s)
		return (0);
	st = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!st)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		st[i] = f(i, s[i]);
		i++;
	}
	st[i] = '\0';
	return (st);
}
/*
char	piu_uno(unsigned int i, char c)
{
	if (i == 3)
		c = 'a';
	else
		c = c + 1;
	return (c);
}
int	main()
{
	char s[] = "ciazoo";

	char *st = ft_strmapi(s, piu_uno);
	printf("%s\n", st);

}*/
