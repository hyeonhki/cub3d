/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.k>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:16:49 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 17:16:50 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	config_to_game(t_info *info, t_game *game, t_map *map)
{
	info->config.width = map->width;
	info->config.height = map->height;
	game->posx = map->player.x + 0.5;
	game->posy = map->player.y + 0.5;
	if (map->player.dir == 'N')
	{
		game->dirx = -1.0;
		game->planey = 0.66;
	}
	if (map->player.dir == 'S')
	{
		game->dirx = 1.0;
		game->planey = -0.66;
	}
	if (map->player.dir == 'E')
	{
		game->diry = 1.0;
		game->planex = 0.66;
	}
	if (map->player.dir == 'W')
	{
		game->diry = -1.0;
		game->planex = -0.66;
	}
}

void	game_init(t_info *info)
{
	info->mlx = mlx_init();
	set_etc(info);
	ready_screen(info);
	ready_texture(info);
	ready_image(info);
	check_sprite(info, &info->map);
	info->win = \
	mlx_new_window(info->mlx, info->config.width, info->config.height, "mlx");
}
