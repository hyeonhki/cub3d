/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:37:18 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/06 14:37:20 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_reset(int **buf, int row, int column)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < row)
	{
		while (j < column)
		{
			buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

int		**ft_make_2darray(int row, int column)
{
	int		**temp;
	int		i;

	i = 0;
	if (!(temp = (int **)malloc(sizeof(int *) * row)))
		return (0);
	while (i < row)
	{
		temp[i] = (int *)malloc(sizeof(int) * column);
		i++;
	}
	return (temp);
}

void	ft_arraycpy(int *dest, int *src, unsigned int n)
{
	int		i;
	
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