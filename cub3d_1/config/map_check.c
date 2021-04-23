/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:15:41 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/23 13:15:42 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int		check_nswe(int c, int *cnt)
{
	if (*cnt != 0)
		return (0);
	if (c == 'N')
	{
		*cnt += 1;
		return (1);
	}
	if (c == 'W')
	{
		*cnt += 1;
		return (1);
	}
	if (c == 'S')
	{
		*cnt += 1;
		return (1);
	}
	if (c == 'E')
	{
		*cnt += 1;
		return (1);
	}
	return (0);
}

int		check_012(int c)
{
	if (c >= '0' && c <= '2')
		return (1);
	if (c == ' ')
		return (1);
	else
		return (0);
}

int		map_element_check(t_map *map)
{
	int i;
	int j;
	int c;
	int cnt;

	c = 0;
	cnt = 0;
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			c = map->w_map[i][j];
			if (!(check_nswe(c, &cnt) || check_012(c)))
				return (0);
			j++;
		}
		i++;
	}
	if (cnt == 0)
		return (0);
	return (1);
}
