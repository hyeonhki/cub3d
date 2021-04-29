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

void	sort_sprites(t_game *game, int amount)
{
	int		i;
	int		j;
	int		tmp_order;
	double	tmp_distance;

	i = 0;
	while (i < amount)
	{
		j = i + 1;
		while (j < amount)
		{
			if (game->raysp.spritedistance[i] < game->raysp.spritedistance[j])
			{
				tmp_distance = game->raysp.spritedistance[i];
				tmp_order = game->raysp.spriteorder[i];
				game->raysp.spritedistance[i] = game->raysp.spritedistance[j];
				game->raysp.spriteorder[i] = game->raysp.spriteorder[j];
				game->raysp.spritedistance[j] = tmp_distance;
				game->raysp.spriteorder[j] = tmp_order;
			}
			j++;
		}
		i++;
	}
}

static void	set_variables(t_info *info, t_game *game, int i)
{
	t_raysp	*sp;

	sp = &game->raysp;
	//translate sprite position to relative to camera
	sp->spritex = info->sprite[game->raysp.spriteorder[i]].x - game->posx;
	sp->spritey = info->sprite[game->raysp.spriteorder[i]].y - game->posy;
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
	if(sp->drawStarty < 0)
		sp->drawStarty = 0;
	sp->drawEndy = sp->spriteHeight / 2 + info->config.height / 2 + sp->vMoveScreen;
	if(sp->drawEndy >= info->config.height)
		sp->drawEndy = info->config.height - 1;

	//calculate width of the sprite
	sp->spriteWidth = (int)fabs((info->config.height / sp->transformy) / uDiv);
	sp->drawStartx = -sp->spriteWidth / 2 + sp->spriteScreenx;
	if(sp->drawStartx < 0)
		sp->drawStartx = 0;
	sp->drawEndx = sp->spriteWidth / 2 + sp->spriteScreenx;
	if(sp->drawEndx >= info->config.width)
		sp->drawEndx = info->config.width - 1;
}

void	sprite_screen(t_info *info, t_game *game, int i)
{
	int stripe;
	int y;

	stripe = game->raysp.drawStartx;
	while (stripe < game->raysp.drawEndx)
	{
		game->raysp.texx =  (int)((256 * (stripe - (-game->raysp.spriteWidth / 2 + game->raysp.spriteScreenx)) * info->config.texwidth / game->raysp.spriteWidth) / 256);
		if (game->raysp.transformy > 0 && stripe > 0 && stripe < info->config.width && game->raysp.transformy < info->zbuffer[stripe])
		{
			y = game->raysp.drawStarty;
			while (y < game->raysp.drawEndy)
			{
				game->raysp.d = (y-game->raysp.vMoveScreen) * 256 - info->config.height * 128 + game->raysp.spriteHeight * 128; //256 and 128 factors to avoid floats
				game->raysp.texy = ((game->raysp.d * info->config.texheight) / game->raysp.spriteHeight) / 256;
				game->raysp.color = info->texture[info->sprite[game->raysp.spriteorder[i]].texture][info->config.texwidth * game->raysp.texy + game->raysp.texx]; //get current color from the texture
				if((game->raysp.color & 0x00FFFFFF) != 0)
					info->screen[y][stripe] = game->raysp.color; //paint pixel if it isn't black, black is the invisible color
				y++;
			}
		}
		stripe++;
	}
/*	for(int stripe = game->raysp.drawStartx; stripe < game->raysp.drawEndx; stripe++)
	{
		int texX = (int)((256 * (stripe - (-game->raysp.spriteWidth / 2 + game->raysp.spriteScreenx)) * info->config.texwidth / game->raysp.spriteWidth) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
		if(game->raysp.transformy > 0 && stripe > 0 && stripe < info->config.width && game->raysp.transformy < info->zBuffer[stripe])
		{
			for(int y = game->raysp.drawStarty; y < game->raysp.drawEndy; y++) //for every pixel of the current stripe
			{
				int d = (y-game->raysp.vMoveScreen) * 256 - info->config.height * 128 + game->raysp.spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * info->config.texheight) / game->raysp.spriteHeight) / 256;
				int color = info->texture[info->sprite[game->raysp.spriteorder[i]].texture][info->config.texwidth * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0) info->screen[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
	}*/
}

void	sprite_raycast(t_info *info, t_game *game)
{
//SPRITE CASTING
	//sort sprites from far to close
//	int		spriteOrder[info->spritenum];
//	double	spriteDistance[info->spritenum];
	int		i;

	game->raysp.spriteorder = malloc((info->spritenum) * sizeof(int));
	game->raysp.spritedistance = malloc((info->spritenum) * sizeof(double));
	i = 0;
	while (i < info->spritenum)
	{
		game->raysp.spriteorder[i] = i;
		game->raysp.spritedistance[i] = ((game->posx - info->sprite[i].x) * (game->posx - info->sprite[i].x) + (game->posy - info->sprite[i].y) * (game->posy - info->sprite[i].y)); //sqrt not taken, unneeded
		i++;
	}
	//스프라이트 하나라 정렬 필요없는 듯
	i = 0;
//	while (i < info->spritenum)
//	{
//		printf("before\n");
//		i++;
//	}
//	sortSprites(game, info->spritenum);
	sort_sprites(game, info->spritenum);
	i = 0;
//	while (i < info->spritenum)
//	{
//		printf("after\n");
//		printf("[%d].x : %f [%d].y : %f\n",i,info->sprite[i].x, i,info->sprite[i].y);
//		i++;
//	}
	//after sorting the sprites, do the projection and draw them
	i = 0;
	while (i < info->spritenum)
	{
		set_variables(info, game, i);
		sprite_screen(info, game, i);
/*		for(int stripe = game->raysp.drawStartx; stripe < game->raysp.drawEndx; stripe++)
			{
				int texX = (int)((256 * (stripe - (-game->raysp.spriteWidth / 2 + game->raysp.spriteScreenx)) * info->config.texwidth / game->raysp.spriteWidth) / 256);
				//the conditions in the if are:
				//1) it's in front of camera plane so you don't see things behind you
				//2) it's on the screen (left)
				//3) it's on the screen (right)
				//4) ZBuffer, with perpendicular distance
				if(game->raysp.transformy > 0 && stripe > 0 && stripe < info->config.width && game->raysp.transformy < info->zBuffer[stripe])
				{
					for(int y = game->raysp.drawStarty; y < game->raysp.drawEndy; y++) //for every pixel of the current stripe
					{
						int d = (y-game->raysp.vMoveScreen) * 256 - info->config.height * 128 + game->raysp.spriteHeight * 128; //256 and 128 factors to avoid floats
						int texY = ((d * info->config.texheight) / game->raysp.spriteHeight) / 256;
						int color = info->texture[info->sprite[game->raysp.spriteorder[i]].texture][info->config.texwidth * texY + texX]; //get current color from the texture
						if((color & 0x00FFFFFF) != 0) info->screen[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
					}
				}
			}
*/
//		sprite_screen(info, game, i);
		i++;
	}
}