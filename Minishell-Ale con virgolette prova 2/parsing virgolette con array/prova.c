/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prova.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:29:29 by ale               #+#    #+#             */
/*   Updated: 2025/04/08 23:17:29 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_arr_single(char *s, int **arr, int *quotes_left_open, int *i)
{
	(*arr)[*i] = SINGLE_QUOTES;
	(*i)++;
	while (s[*i] != 39 && s[*i] != '\0')
	{
		(*arr)[*i] = SINGLE_QUOTES;
		(*i)++;
	}
	if (s[*i] != '\0')
	{
		(*arr)[*i] = SINGLE_QUOTES;
		(*i)++;
	}
	else
		*quotes_left_open = 1;
}

void	fill_arr_double(char *s, int **arr, int *quotes_left_open, int *i)
{
	(*arr)[*i] = DOUBLE_QUOTES;
	(*i)++;
	while (s[*i] != 34 && s[*i] != '\0')
	{
		(*arr)[*i] = DOUBLE_QUOTES;
		(*i)++;

	}
	if (s[*i] != '\0')
	{
		(*arr)[*i] = DOUBLE_QUOTES;
		(*i)++;
	}
	else
		*quotes_left_open = 1;
}

int	*create_arr(char *s)
{
	int	*arr;
	int	quotes_left_open;
	int	i;


	quotes_left_open = 0;
	arr = malloc(sizeof(int) * ft_strlen(s));
	if (!arr)
	{
		write(2, "malloc failed", 13);
		exit(1);//non so se error code su exit va bene e anche se va bene exit o meglio solo return
	}
	i = 0;
	//printf("s0: %c\n", s[0]);
	while (s[i] != '\0')
	{
		if (s[i] == 39)
			fill_arr_single(s, &arr, &quotes_left_open, &i);
		else if (s[i] == 34)
			fill_arr_double(s, &arr, &quotes_left_open, &i);
		else
		{
			arr[i] = NO_QUOTES;
			i++;
		}
	}
	return (arr);
}

int	main(void)
{
	char		*s;
	int			*arr;

	s = "\"\" ahaha \" ohohoh\'ehe\'\"\"  iii\"\"\"ahah\'\"ww\'\'\'";
	//s = get_next_line(0);
	arr = create_arr(s);

	printf("(%s)\n", s);
	for(int i = 0; i < ft_strlen(s) - 1; i++)
		printf("%d", arr[i]);
	printf("\n");
	free(arr);
	//free (s);
}
