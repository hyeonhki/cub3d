/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_making.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:24:05 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/23 13:24:09 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	maxlen_map(char *maptext, t_map *map)
{
	int len;
	int max;
	int cnt;
	int i;

	i = 0;
	max = 0;
	len = 0;
	cnt = 0;
	while (maptext[i] != '\0')
	{
		if (maptext[i] == '\n')
		{
			cnt += 1;
			if (len > max)
				max = len;
			len = -1;
		}
		len++;
		i++;
	}
	map->column = max;
	map->row = cnt;
}

void	map_init(t_map *map, char *maptext, int height)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < height)
	{
		k = 0;
		while (maptext[j] != '\n')
		{
			map->w_map[i][k] = maptext[j];
			if (maptext[j] == ' ')
				map->w_map[i][k] = '0';
			k++;
			j++;
		}
		if (maptext[j] == '\n')
		{
			j++;
		}
		i++;
	}
}

void	ft_re2set(t_map *map, int row, int column)
{
	int		i;
	int		j;

	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < column)
		{
			map->w_map[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void	set_map(t_map *map)
{
	map->w_map = ft_2d_malloc(map->row, map->column);
	ft_re2set(map, map->row, map->column);
}

int		parse_map(t_map *map, char *maptext)
{
	maxlen_map(maptext, map);
	set_map(map);
	map_init(map, maptext, map->row);
	return (1);
}
