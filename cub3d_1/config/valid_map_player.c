/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:03:45 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/23 16:03:52 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	valid_map_check(t_map *map, int i, int j)
{
	if (i == -1 || i > map->row || j == -1 || j > map->column)
	{
		printf("not close\n");
		exit(EXIT_SUCCESS);
	}
	if (map->w_map[i][j] == '1' || map->w_map[i][j] == 0 \
	|| map->w_map[i][j] == 2)
		return ;
	if (map->w_map[i][j] == '2')
		map->w_map[i][j] = 2;
	else if (map->w_map[i][j] == '0')
		map->w_map[i][j] = 0;
	valid_map_check(map, i + 1, j);
	valid_map_check(map, i - 1, j);
	valid_map_check(map, i, j - 1);
	valid_map_check(map, i, j + 1);
}
