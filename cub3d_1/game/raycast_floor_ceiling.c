/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor_ceiling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:02:36 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/24 16:02:37 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	floor_ceiling_raycast(t_info *info)
{
	int		x;
	int		y;

	y = 0;
	while (y < info->config.height)
	{
		x = 0;
		while (x < info->config.width)
		{
			info->screen[y][x] = info->map.fl_color;
			info->screen[info->config.height - y - 1][x] = info->map.ce_color;
			x++;
		}
		y++;
	}
}
