/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:14:40 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/26 14:14:41 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		sort_sprites(t_game *game, int amount)
{
	int			i;
	int			j;
	int			tmp_order;
	double		tmp_distance;

	i = 0;
	while (i < amount)
	{
		j = i + 1;
		while (j < amount)
		{
			if (game->raysp.spdistance[i] < game->raysp.spdistance[j])
			{
				tmp_distance = game->raysp.spdistance[i];
				tmp_order = game->raysp.sporder[i];
				game->raysp.spdistance[i] = game->raysp.spdistance[j];
				game->raysp.sporder[i] = game->raysp.sporder[j];
				game->raysp.spdistance[j] = tmp_distance;
				game->raysp.sporder[j] = tmp_order;
			}
			j++;
		}
		i++;
	}
}

static void	set_variables(t_info *in, t_game *g, t_raysp *s, int i)
{
	s->vdiv = 1;
	s->udiv = 1;
	s->vmove = 0.0;
	s->spx = in->sprite[s->sporder[i]].x - g->posx;
	s->spy = in->sprite[s->sporder[i]].y - g->posy;
	s->invdet = 1.0 / (g->planex * g->diry - g->dirx * g->planey);
	s->transfx = s->invdet * (g->diry * s->spx - g->dirx * s->spy);
	s->transfy = s->invdet * (-g->planey * s->spx + g->planex * s->spy);
	s->spscreenx = \
	(int)((in->config.width / 2) * (1 + s->transfx / s->transfy));
	s->vmovescreen = (int)(s->vmove / s->transfy);
	s->spheight = (int)fabs((in->config.height / s->transfy) / s->vdiv);
	s->drawstarty = -s->spheight / 2 + in->config.height / 2 + s->vmovescreen;
	if (s->drawstarty < 0)
		s->drawstarty = 0;
	s->drawendy = s->spheight / 2 + in->config.height / 2 + s->vmovescreen;
	if (s->drawendy >= in->config.height)
		s->drawendy = in->config.height - 1;
	s->spwidth = (int)fabs((in->config.height / s->transfy) / s->udiv);
	s->drawstartx = -s->spwidth / 2 + s->spscreenx;
	if (s->drawstartx < 0)
		s->drawstartx = 0;
	s->drawendx = s->spwidth / 2 + s->spscreenx;
	if (s->drawendx >= in->config.width)
		s->drawendx = in->config.width - 1;
}

void		sprite_screen(t_info *info, t_game *game, t_raysp *s, int i)
{
	s->point = s->drawstartx;
	while (s->point < game->raysp.drawendx)
	{
		s->texx = (int)((256 * (s->point - (-s->spwidth / 2 + s->spscreenx)) \
		* info->config.texwidth / s->spwidth) / 256);
		if (s->transfy > 0 && s->point > 0 && s->point < info->config.width \
		&& s->transfy < info->zbuffer[s->point])
		{
			info->etc.y = s->drawstarty;
			while (info->etc.y < s->drawendy)
			{
				s->d = (info->etc.y - s->vmovescreen) * 256 \
				- info->config.height * 128 + s->spheight * 128;
				s->texy = \
				((s->d * info->config.texheight) / s->spheight) / 256;
				s->color = info->texture[info->sprite[s->sporder[i]].texture]\
				[info->config.texwidth * s->texy + s->texx];
				if ((s->color & 0x00FFFFFF) != 0)
					info->screen[info->etc.y][s->point] = s->color;
				info->etc.y++;
			}
		}
		s->point++;
	}
}

void		sprite_raycast(t_info *info, t_game *game)
{
	int			i;
	t_raysp		*s;

	s = &game->raysp;
	s->sporder = malloc((info->spritenum) * sizeof(int));
	s->spdistance = malloc((info->spritenum) * sizeof(double));
	i = 0;
	while (i < info->spritenum)
	{
		s->sporder[i] = i;
		s->spdistance[i] = \
		((game->posx - info->sprite[i].x) * (game->posx - info->sprite[i].x) \
		+ (game->posy - info->sprite[i].y) * (game->posy - info->sprite[i].y));
		i++;
	}
	sort_sprites(game, info->spritenum);
	i = 0;
	while (i < info->spritenum)
	{
		set_variables(info, game, s, i);
		sprite_screen(info, game, s, i);
		i++;
	}
}
