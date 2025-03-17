/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:27:31 by mchiaram          #+#    #+#             */
/*   Updated: 2024/06/21 11:27:32 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char **dst, const char *src)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!src)
		return (0);
	i = 0;
	j = 0;
	if (*dst)
	{
		str = ft_calloc(((ft_strlen(*dst) + ft_strlen(src)) + 1), sizeof(char));
		if (!str)
			return (0);
		while ((*dst)[j])
			str[i++] = (*dst)[j++];
		free ((*dst));
	}
	else
		str = ft_calloc((ft_strlen(src) + 1), sizeof (char));
	while (*src)
	{
		str[i++] = *src;
		src++;
	}
	return (str);
}
