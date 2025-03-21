/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:50:26 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/25 20:23:24 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/* #include "libft.h"
void	piu_uno(unsigned int i, char *s)
{
	while (s[i] != '\0')
	{
		if (i == 3)
			s[i] = 'a';
		else
			s[i] = s[i] + 1;
		i++;
	}
}

int	main()
{
	char s[] = "abcdef";

	ft_striteri(s, piu_uno);
	printf("%s\n", s);

} */
