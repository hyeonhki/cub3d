/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:15:24 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/24 16:15:25 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	set_variables(t_info *info, t_game *game, int x)
{
	game->rayw.camerax = 2 * x / (double)info->config.width - 1;
	game->rayw.raydirx = game->dirx + game->planex * game->rayw.camerax;
	game->rayw.raydiry =game->diry + game->planey * game->rayw.camerax; 
	game->rayw.mapx = (int)game->posx;
	game->rayw.mapy = (int)game->posy;
	game->rayw.deltadistx = fabs(1 / game->rayw.raydirx);
	game->rayw.deltadisty = fabs(1 / game->rayw.raydiry);
	game->rayw.hit = 0;
	game->rayw.stepx = 1;
	game->rayw.sidedistx = (game->rayw.mapx + 1.0 - game->posx) * game->rayw.deltadistx;
	if (game->rayw.raydirx < 0)
	{
		game->rayw.stepx = -1;
		game->rayw.sidedistx = (game->posx - game->rayw.mapx) * game->rayw.deltadistx;
	}
	game->rayw.stepy = 1;
	game->rayw.sidedisty = (game->rayw.mapy + 1.0 - game->posy) * game->rayw.deltadisty;
	if (game->rayw.raydiry < 0)
	{
		game->rayw.stepy = -1;
		game->rayw.sidedisty = (game->posy - game->rayw.mapy) * game->rayw.deltadisty;
	}
}

void	dda_algorithm(t_info *info, t_game *game)
{
	while (game->rayw.hit == 0)
	{
		if (game->rayw.sidedistx < game->rayw.sidedisty)
		{
			game->rayw.sidedistx += game->rayw.deltadistx;
			game->rayw.mapx += game->rayw.stepx;
			game->rayw.side = 0;
		}
		else
		{
			game->rayw.sidedisty += game->rayw.deltadisty;
			game->rayw.mapy += game->rayw.stepy;
			game->rayw.side = 1;
		}
		if (info->map.w_map[game->rayw.mapx][game->rayw.mapy] == '1')
			game->rayw.hit = 1;
	}
	if (game->rayw.side == 0)
		game->rayw.perpwalldist = (game->rayw.mapx - game->posx + (1 - game->rayw.stepx) / 2) / game->rayw.raydirx;
	else
		game->rayw.perpwalldist = (game->rayw.mapy - game->posy + (1 - game->rayw.stepy) / 2) / game->rayw.raydiry;
}

void	set_wall(t_info *info, t_game *game)
{
	game->rayw.lineheight = (int)(info->config.height / game->rayw.perpwalldist);
	game->rayw.drawstart = -game->rayw.lineheight / 2 + info->config.height / 2;
	if (game->rayw.drawstart < 0)
		game->rayw.drawstart = 0;
	game->rayw.drawend = game->rayw.lineheight / 2 + info->config.height / 2;
	if (game->rayw.drawend >= info->config.height)
		game->rayw.drawend = info->config.height - 1;
	if (game->rayw.side == 0)
		game->rayw.wallx = game->posy + game->rayw.perpwalldist * game->rayw.raydiry;
	else
		game->rayw.wallx = game->posx + game->rayw.perpwalldist * game->rayw.raydirx;
	game->rayw.wallx -= floor(game->rayw.wallx);
}

void	texture_wall(t_info *info, t_game *game, int x)
{
	game->rayw.texx = (int)(game->rayw.wallx * (double)info->config.texwidth);
	if (game->rayw.side == 0 && game->rayw.raydirx > 0)
		game->rayw.texx = info->config.texwidth - game->rayw.texx - 1;
	if (game->rayw.side == 1 && game->rayw.raydiry < 0)
		game->rayw.texx = info->config.texwidth - game->rayw.texx - 1;
	game->rayw.step = 1.0 * info->config.texheight / game->rayw.lineheight;
	game->rayw.texpos = (game->rayw.drawstart - info->config.height / 2 + game->rayw.lineheight / 2) * game->rayw.step;
	info->etc.y = game->rayw.drawstart;
	while (info->etc.y < game->rayw.drawend)
	{
		game->rayw.texy = (int)game->rayw.texpos & (info->config.texheight - 1);
		game->rayw.texpos += game->rayw.step;
		if (game->rayw.side == 1 && game->rayw.raydiry > 0)
			game->rayw.color = info->texture[0][info->config.texheight * game->rayw.texy + game->rayw.texx];
		else if (game->rayw.side == 1 && game->rayw.raydiry < 0)
			game->rayw.color = info->texture[1][info->config.texheight * game->rayw.texy + game->rayw.texx];
		else if (game->rayw.side == 0 && game->rayw.raydirx > 0)
			game->rayw.color = info->texture[2][info->config.texheight * game->rayw.texy + game->rayw.texx];
		if (game->rayw.side == 0 && game->rayw.raydirx < 0)
			game->rayw.color = info->texture[3][info->config.texheight * game->rayw.texy + game->rayw.texx];
		info->screen[info->etc.y][x] = game->rayw.color;
		info->etc.y++;
	}
}

void	wall_raycast(t_info *info, t_game *game)
{
	info->zbuffer = malloc(info->config.width * sizeof(double));
	set_etc(info);
	for (int x = 0; x < info->config.width; x ++)
	{
		set_variables(info, game, x);
		dda_algorithm(info, game);
		set_wall(info, game);
		texture_wall(info, game, x);
		info->zbuffer[x] = game->rayw.perpwalldist;
	}
}
