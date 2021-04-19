/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:02:48 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 10:02:49 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_arraycpy(int *dest, int *src, unsigned int n)
{
	unsigned int i;
	
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

int **ft_2d_malloc(int row, int column)
{
	int **temp;
	if (!(temp = (int **)malloc(sizeof(int *) * row)))
		return (0);
	int i;

	i = 0 ;
	while (i < row)
	{
		temp[i] = (int *)malloc(sizeof(int) * column);
		i++;
	}
	return (temp);
}

void	ft_reset(int **buf, int row, int column)
{
	int		i;
	int		j;

	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < column)
		{
			buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != 0 && (s1[i] == s2[i]))
		i++;
	if (s1[i] == s2[i])
		return (1);
	return (0);
}
