/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:29:50 by ade-ross          #+#    #+#             */
/*   Updated: 2024/12/18 21:28:55 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*check_for_word(char *fin_buffer, int	*i)
{
	char	*buffer;

	*i = 0;
	if (fin_buffer == NULL)
		return (NULL);
	while (fin_buffer[*i] != '\0')
	{
		if (fin_buffer[*i] == '\n')
		{
			*i = *i + 1;
			buffer = ft_substr_mod(fin_buffer, 0, (*i));
			return (buffer);
		}
		else
			*i = *i + 1;
	}
	return (NULL);
}

char	*new_read(char *fin_buffer, int *buffercheck, int fd)
{
	char	*buffer;
	char	*temp;

	buffer = ft_calloc_mod((BUFFER_SIZE + 1), sizeof(char));
	if (buffer == NULL)
	{
		free(fin_buffer);
		return (NULL);
	}
	*buffercheck = read(fd, buffer, BUFFER_SIZE);
	if (*buffercheck == -1)
	{
		free(fin_buffer);
		free(buffer);
		return (NULL);
	}
	temp = fin_buffer;
	fin_buffer = ft_strjoin_mod(fin_buffer, buffer);
	free(temp);
	free(buffer);
	return (fin_buffer);
}

char	*final_checks(char **fin_buffer)
{
	char			*buffer;

	if (ft_strlen_mod(*fin_buffer) != 0)
	{
		buffer = ft_strdup_mod(*fin_buffer);
		free(*fin_buffer);
		*fin_buffer = NULL;
		return (buffer);
	}
	else
	{
		free(fin_buffer);
		return (NULL);
	}
}

// questa funzione controlla sia il caso in cui il malloc di ritorno da 
// check_for_wordfallisca sia aggiorna il fin buffer se check_for_word 
//trova \n
char	*check_buf_or_upd_f_buf(char **fin_buffer, int i, char *buffer)
{
	char	*temp;

	if (!buffer)
	{
		free(*fin_buffer);
		return (NULL);
	}
	temp = ft_substr_mod(*fin_buffer, i, ft_strlen_mod(*fin_buffer) - i);
	free(*fin_buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*f_buffer[FOPEN_MAX];
	char		*buffer;
	int			i;
	int			buffercheck;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = check_for_word(f_buffer[fd], &i);
	if (buffer == NULL && f_buffer[fd] != NULL && f_buffer[fd][i - 1] == '\n')
		return (check_buf_or_upd_f_buf(&f_buffer[fd], i, buffer));
	if (buffer != NULL && f_buffer[fd][i - 1] == '\n')
	{
		f_buffer[fd] = check_buf_or_upd_f_buf(&f_buffer[fd], i, (char *)1);
		return (buffer);
	}
	f_buffer[fd] = new_read(f_buffer[fd], &buffercheck, fd);
	if (!f_buffer[fd])
		return (NULL);
	else if (buffercheck > 0 && ft_strlen_mod(f_buffer[fd]) != 0)
		buffer = get_next_line(fd);
	else
		buffer = final_checks(&f_buffer[fd]);
	return (buffer);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int fd = open("read_error.txt", O_RDONLY);
	int i = 0;

	char *s = "a";

	//read(fd, s, 4);
	while (s)
	{
		//s = try(fd);
		s = (get_next_line(fd));
		printf("'%s'", s);
		//s++;
		//if (s)
		//s[1] = 0;
		free(s);
	}

	return (0);
} */
