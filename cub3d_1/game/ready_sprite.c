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
	info->etc.cnt = count_sprite(map);
	info->spritenum = info->etc.cnt;
	info->sprite = malloc(sizeof(t_sprite) * info->etc.cnt);
	while (info->etc.i < map->row)
	{
		info->etc.j = 0;
		while (info->etc.j < map->column)
		{
			if (map->w_map[info->etc.i][info->etc.j] == '2')
			{
				info->sprite[info->etc.order].y = info->etc.j + 0.5;
				info->sprite[info->etc.order].x = info->etc.i + 0.5;
				info->sprite[info->etc.order].texture = 4;
				map->w_map[info->etc.i][info->etc.j] = '0';
				info->etc.order += 1;
			}
			info->etc.j++;
		}
		info->etc.i++;
	}
	set_etc(info);
}
