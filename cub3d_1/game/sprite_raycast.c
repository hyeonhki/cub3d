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

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;
	
	i = 0;
	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

static void	set_variables(t_info *info, t_game *game, int i)
{
	t_raysp	*sp;

	sp = &game->raysp;
	//translate sprite position to relative to camera
	sp->spritex = info->sprite[i].x - game->posx;
	sp->spritey = info->sprite[i].y - game->posy;
	//transform sprite with the inverse camera matrix
	// [ planex   dirx ] -1                                       [ diry      -dirx ]
	// [               ]       =  1/(planex*diry-dirx*planey) *   [                 ]
	// [ planey   diry ]                                          [ -planey  planex ]

	sp->invDet = 1.0 / (game->planex * game->diry - game->dirx * game->planey); //required for correct matrix multiplication
	sp->transformx = sp->invDet * (game->diry * sp->spritex - game->dirx * sp->spritey);
	sp->transformy = sp->invDet * (-game->planey * sp->spritex + game->planex * sp->spritey); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
		
	sp->spriteScreenx = (int)((info->config.width / 2) * (1 + sp->transformx / sp->transformy));
	//parameters for scaling and moving the sprites
	#define uDiv 1
	#define vDiv 1
	#define vMove 0.0
	sp->vMoveScreen = (int)(vMove / sp->transformy);

	//calculate height of the sprite on screen
	sp->spriteHeight = (int)fabs((info->config.height / sp->transformy) / vDiv); //using "transformy" instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	sp->drawStarty = -sp->spriteHeight / 2 + info->config.height / 2 + sp->vMoveScreen;
	if(sp->drawStarty < 0) sp->drawStarty = 0;
	sp->drawEndy = sp->spriteHeight / 2 + info->config.height / 2 + sp->vMoveScreen;
	if(sp->drawEndy >= info->config.height) sp->drawEndy = info->config.height - 1;

	//calculate width of the sprite
	sp->spriteWidth = (int)fabs((info->config.height / sp->transformy) / uDiv);
	sp->drawStartx = -sp->spriteWidth / 2 + sp->spriteScreenx;
	if(sp->drawStartx < 0) sp->drawStartx = 0;
	sp->drawEndx = sp->spriteWidth / 2 + sp->spriteScreenx;
	if(sp->drawEndx >= info->config.width) sp->drawEndx = info->config.width - 1;
}

void	sprite_screen(t_info *info, t_game *game, int i)
{
	for(int stripe = game->raysp.drawStartx; stripe < game->raysp.drawEndx; stripe++)
	{
		int texx = (int)((256 * (stripe - (-game->raysp.spriteWidth / 2 + game->raysp.spriteScreenx)) * info->config.texwidth / game->raysp.spriteWidth) / 256);
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if(game->raysp.transformy > 0 && stripe > 0 && stripe < info->config.width && game->raysp.transformy < info->zBuffer[stripe])
		for(int y = game->raysp.drawStarty; y < game->raysp.drawEndy; y++) //for every pixel of the current stripe
		{
				int d = (y-game->raysp.vMoveScreen) * 256 - info->config.height * 128 + game->raysp.spriteHeight * 128; //256 and 128 factors to avoid floats
				int texy = ((d * info->config.texheight) / game->raysp.spriteHeight) / 256;
				int color = info->texture[info->sprite[i].texture][info->config.texwidth * texy + texx]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0) info->screen[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
}

void	sprite_raycast(t_info *info, t_game *game)
{
//SPRITE CASTING
	//sort sprites from far to close
	int		spriteOrder[info->spritenum];
	double	spriteDistance[info->spritenum];
	int		i;

	i = 0;
	while (i < info->spritenum)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((game->posx - info->sprite[i].x) * (game->posx - info->sprite[i].x) + (game->posy - info->sprite[i].y) * (game->posy - info->sprite[i].y)); //sqrt not taken, unneeded
		i++;
	}
	//스프라이트 하나라 정렬 필요없는 듯
	sortSprites(spriteOrder, spriteDistance, info->spritenum);
	//after sorting the sprites, do the projection and draw them
	i = 0;
	while (i < info->spritenum)
	{
		set_variables(info, game, i);
		sprite_screen(info, game, i);
		i++;
	}
}