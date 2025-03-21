/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:05:15 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/26 16:20:15 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	len = ft_strlen(s1);
	if (s1 == 0 || set == 0)
		return (0);
	while (ft_strchr(set, s1[i]))
	{
		i++;
	}
	j = len;
	while (ft_strchr(set, s1[j - 1]))
	{
		j--;
	}
	return (ft_substr(s1, i, (j - i)));
}
/*
int	main()
{
	char	s1[] = "123";
	char	set[] = "";

	char	*new = ft_strtrim(s1, set);
	printf("%s\n", new);
	free(new);
} */
/*
//strtrim fatto come avevo capito si facesse all'inizio
//cioe che leva i caratteri di set non solo a inizio e fine ma dappertutto
{
	char	*sttr;
	int		i;
	int		j;
	int		k;

	j = 0;
	sttr = malloc(ft_strlen(s1) + 1);
	ft_strlcpy(sttr, s1, (ft_strlen(s1) + 1));
	while (set[j] != '\0')
	{
		i = 0;
		k = 0;
		while (sttr[i] != '\0' )
		{
			if (sttr[i] != set[j])
			{
				sttr[k] = sttr[i];
				k++;
			}
			i++;
		}
		sttr[k] = '\0';
		j++;
	}
	return (sttr);
}*/
