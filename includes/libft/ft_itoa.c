/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:24:26 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/25 20:05:34 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ilen(int n)
{
	int	len;

	len = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = n * (-1);
		len++;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*n_min(char *str)
{
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

static void	in_to_st(char *s, int i, int n)
{
	char	temp;
	int		j;

	j = 0;
	if (i == 1)
		j++;
	while (n > 0)
	{
		s[i] = (n % 10) + 48;
		n /= 10;
		i++;
	}
	s[i] = '\0';
	i--;
	while (j < i)
	{
		temp = s[j];
		s[j] = s[i];
		s[i] = temp;
		i--;
		j++;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc((ilen(n) + 1) * sizeof(char));
	if (!s)
		return (0);
	if (n == -2147483648)
		return (n_min(s));
	if (n < 0)
	{
		s[i] = '-';
		n = n * (-1);
		i++;
	}
	if (n == 0)
	{
		s[i] = '0';
		i++;
	}
	in_to_st(s, i, n);
	return (s);
}
/*
int	main()
{
	int n = 0;

	char *s = ft_itoa(n);
	printf("%s\n", s);
}*/
