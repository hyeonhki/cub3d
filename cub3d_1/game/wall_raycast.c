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

static void	set_variables(t_info *info, t_game *game, t_rayw *r, int x)
{
	r->camerax = 2 * x / (double)info->config.width - 1;
	r->raydirx = game->dirx + game->planex * r->camerax;
	r->raydiry = game->diry + game->planey * r->camerax;
	r->mapx = (int)game->posx;
	r->mapy = (int)game->posy;
	r->deltadistx = fabs(1 / r->raydirx);
	r->deltadisty = fabs(1 / r->raydiry);
	r->hit = 0;
	r->stepx = 1;
	r->sidedistx = (r->mapx + 1.0 - game->posx) * r->deltadistx;
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (game->posx - r->mapx) * r->deltadistx;
	}
	r->stepy = 1;
	r->sidedisty = (r->mapy + 1.0 - game->posy) * r->deltadisty;
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (game->posy - r->mapy) * r->deltadisty;
	}
}

void		dda_algorithm(t_info *info, t_game *game, t_rayw *r)
{
	while (r->hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (info->map.w_map[r->mapx][r->mapy] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->perpwalldist = \
			(r->mapx - game->posx + (1 - r->stepx) / 2) / r->raydirx;
	else
		r->perpwalldist = \
			(r->mapy - game->posy + (1 - r->stepy) / 2) / r->raydiry;
}

void		set_wall(t_info *info, t_game *game)
{
	game->rayw.lineheight = \
		(int)(info->config.height / game->rayw.perpwalldist);
	game->rayw.drawstart = -game->rayw.lineheight / 2 + info->config.height / 2;
	if (game->rayw.drawstart < 0)
		game->rayw.drawstart = 0;
	game->rayw.drawend = game->rayw.lineheight / 2 + info->config.height / 2;
	if (game->rayw.drawend >= info->config.height)
		game->rayw.drawend = info->config.height - 1;
	if (game->rayw.side == 0)
		game->rayw.wallx = \
			game->posy + game->rayw.perpwalldist * game->rayw.raydiry;
	else
		game->rayw.wallx = \
			game->posx + game->rayw.perpwalldist * game->rayw.raydirx;
	game->rayw.wallx -= floor(game->rayw.wallx);
}

void		texture_wall(t_info *info, t_config *c, t_rayw *r, int x)
{
	r->texx = (int)(r->wallx * (double)c->texwidth);
	if (r->side == 0 && r->raydirx > 0)
		r->texx = c->texwidth - r->texx - 1;
	if (r->side == 1 && r->raydiry < 0)
		r->texx = c->texwidth - r->texx - 1;
	r->step = 1.0 * c->texheight / r->lineheight;
	r->texpos = (r->drawstart - c->height / 2 + r->lineheight / 2) * r->step;
	info->etc.y = r->drawstart;
	while (info->etc.y < r->drawend)
	{
		r->texy = (int)r->texpos & (c->texheight - 1);
		r->texpos += r->step;
		if (r->side == 1 && r->raydiry > 0)
			r->color = info->texture[0][c->texheight * r->texy + r->texx];
		else if (r->side == 1 && r->raydiry < 0)
			r->color = info->texture[1][c->texheight * r->texy + r->texx];
		else if (r->side == 0 && r->raydirx > 0)
			r->color = info->texture[2][c->texheight * r->texy + r->texx];
		if (r->side == 0 && r->raydirx < 0)
			r->color = info->texture[3][c->texheight * r->texy + r->texx];
		info->screen[info->etc.y][x] = r->color;
		info->etc.y++;
	}
}

void		wall_raycast(t_info *info, t_game *game)
{
	int		x;

	x = 0;
	info->zbuffer = malloc(info->config.width * sizeof(double));
	set_etc(info);
	while (x < info->config.width)
	{
		set_variables(info, game, &game->rayw, x);
		dda_algorithm(info, game, &game->rayw);
		set_wall(info, game);
		texture_wall(info, &info->config, &game->rayw, x);
		info->zbuffer[x] = game->rayw.perpwalldist;
		x++;
	}
}
