/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:08:26 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/23 13:08:27 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int		is_player(int p)
{
	if (p == 'N' || p == 'S' || p == 'W' || p == 'E')
		return (1);
	else
		return (0);
}

void	player_init(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			if (is_player(map->w_map[i][j]))
			{
				map->player.x = i;
				map->player.y = j;
				map->player.dir = map->w_map[i][j];
				map->w_map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}
