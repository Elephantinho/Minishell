/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:33:08 by ade-ross          #+#    #+#             */
/*   Updated: 2024/12/10 17:33:21 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

size_t	ft_strlen_mod(const char *s);
void	*ft_calloc_mod(size_t nmemb, size_t size);
char	*ft_strjoin_mod(char *s1, char *s2);
char	*ft_strdup_mod(char *src);
char	*ft_substr_mod(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif
