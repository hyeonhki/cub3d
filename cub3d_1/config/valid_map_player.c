/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:34:58 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/22 21:35:03 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
/*
int valid_player_check(t_map *map)
{
	int dir;
	int ret;
	int x;
	int y;
	int temp;
	x = map->player.x;
	y = map->player.y;
	if (x == 0 || y == 0)
		return (0);
	temp = x;
	while (x != temp)
	{
		while (map->w_map[temp][y] != '1' && temp >= 0)
			temp--;
		if (map->w_map[temp][y] == '1')
		{
			while (temp != 0 && map->w_map[temp][y] == '1')
				temp--;
			if (temp != 0)
				x = temp - 1;
			else
				x = temp;
		}
	}
	if (map->w_map[temp][y] != '1')
		return (0);
}*/

void	valid_check(t_map *map, int i, int j)
{
    if (i == -1 || i > map->row || j == -1 || j > map->column)
    {
		printf("not close\n");
		exit(EXIT_SUCCESS);
	}
    if (map->w_map[i][j] == '1' || map->w_map[i][j] == 0 || map->w_map[i][j] == 2)
        return ;
	if (map->w_map[i][j] == '2')
		map->w_map[i][j] = 2;
    else if (map->w_map[i][j] == '0')
        map->w_map[i][j] = 0;
    valid_check(map, i + 1, j);
    valid_check(map, i - 1, j);
    valid_check(map, i, j - 1);
    valid_check(map, i, j + 1);
}