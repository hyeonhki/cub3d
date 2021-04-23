/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:31:50 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/23 16:31:51 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int		count_sprite(t_map *map)
{
	int		i;
	int		j;
	int		cnt;

	cnt = 0;
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			if (map->w_map[i][j] == '2')
				cnt++;
			j++;
		}
		i++;
	}
	return (cnt);
}

void	check_sprite(t_info *info, t_map *map)
{
	int		cnt;
	int		i;
	int		j;
	int		order;

	cnt = count_sprite(map);
	info->spritenum = cnt;
	info->sprite = malloc(sizeof(t_sprite) * cnt);
	i = 0;
	order = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			if (map->w_map[i][j] == '2')
			{
				info->sprite[order].y = j + 0.5;
				info->sprite[order].x = i + 0.5;
				info->sprite[order].texture = 4;
				map->w_map[i][j] = '0';
				order += 1;
			}
			j++;
		}
		i++;
	}
}
