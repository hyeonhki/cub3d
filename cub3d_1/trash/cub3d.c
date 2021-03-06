/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:42:06 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 09:42:07 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define mapwidth 24
#define mapheight 24

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
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
		}
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

int exit_hook(t_info *info)
{
	exit(EXIT_SUCCESS);
	return(EXIT_SUCCESS);
}

int	key_press(int key, t_info *info)
{
	if (key == KEY_W)
	{
		if (info->map.w_map[(int)(info->game.posx + info->game.dirx * info->config.movespeed)][(int)(info->game.posy)] == '0')
			info->game.posx += info->game.dirx * info->config.movespeed;
		if (info->map.w_map[(int)(info->game.posx)][(int)(info->game.dirx + info->game.diry * info->config.movespeed)] == '0')
			info->game.posy += info->game.diry * info->config.movespeed;
	}
	//move backwards if no wall behind you
	if (key == KEY_S)
	{
		if (info->map.w_map[(int)(info->game.posx - info->game.dirx * info->config.movespeed)][(int)(info->game.posy)] == '0')
			info->game.posx -= info->game.dirx * info->config.movespeed;
		if (info->map.w_map[(int)(info->game.posx)][(int)(info->game.posy - info->game.diry * info->config.movespeed)] == '0')
			info->game.posy -= info->game.diry * info->config.movespeed;
	}
	//rotate to the right
	if (key == KEY_D)
	{
		//both camera direction and camera plane must be rotated
		double olddirx = info->game.dirx;
		info->game.dirx = info->game.dirx * cos(-info->config.rotspeed) - info->game.diry * sin(-info->config.rotspeed);
		info->game.diry = olddirx * sin(-info->config.rotspeed) + info->game.diry * cos(-info->config.rotspeed);
		double oldplanex = info->game.planex;
		info->game.planex = info->game.planex * cos(-info->config.rotspeed) - info->game.planey * sin(-info->config.rotspeed);
		info->game.planey = oldplanex * sin(-info->config.rotspeed) + info->game.planey * cos(-info->config.rotspeed);
	}
	//rotate to the left
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		double olddirx = info->game.dirx;
		info->game.dirx = info->game.dirx * cos(info->config.rotspeed) - info->game.diry * sin(info->config.rotspeed);
		info->game.diry = olddirx * sin(info->config.rotspeed) + info->game.diry * cos(info->config.rotspeed);
		double oldplanex = info->game.planex;
		info->game.planex = info->game.planex * cos(info->config.rotspeed) - info->game.planey * sin(info->config.rotspeed);
		info->game.planey = oldplanex * sin(info->config.rotspeed) + info->game.planey * cos(info->config.rotspeed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

void	calc(t_info *info)
{
	t_game *game;
	game = &info->game;
	//?????? ?????? 
	floor_ceiling_raycast(info);
	//??? ?????????
//	wall_raycast(info, game);
	for (int x = 0; x < info->config.width; x ++)
	{
		double camera_x = 2 * x / (double)info->config.width - 1; 
		double raydir_x = game->dirx + game->planex * camera_x;
		double raydir_y = game->diry + game->planey * camera_x; 
		int map_x = (int)game->posx;
		int map_y = (int)game->posy;
		double sidedist_x;
		double sidedist_y;
		double deltadist_x = fabs(1 / raydir_x); //abs?????? fabs
		double deltadist_y = fabs(1 / raydir_y);
		double perp_walldist;
		int step_x;
		int step_y;
		int hit = 0;
		int side;
		if (raydir_x < 0)
		{
			step_x = -1;
			//double		double		int(info->posx)
			sidedist_x = (game->posx - map_x) * deltadist_x;
		}
		else
		{
			step_x = 1;
			sidedist_x = (map_x + 1.0 - game->posx) * deltadist_x;
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			sidedist_y = (game->posy - map_y) * deltadist_y;
		}
		else
		{
			step_y = 1;
			sidedist_y = (map_y + 1.0 - game->posy) * deltadist_y;
		}
		
		//DDA ???????????? ??????
		while (hit == 0)
		{
			if (sidedist_x < sidedist_y)
			{
				sidedist_x += deltadist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				sidedist_y += deltadist_y;
				map_y += step_y;
				side = 1;
			}
			if (info->map.w_map[map_x][map_y] == '1') //????????? 2??? ?????????????????? ???????????? ??????????
				hit = 1;
			//DDA????????? ?????? ????????? ??????????????? ???????????? ???????????? ????????????
		}
		//???????????? ????????? ??????
		//???????????? ?????? ?????? ???????????? ??????
		//perp_walldist??? ????????? ????????????(????????????)
		if (side == 0) //???????????? ????????? ?????? x????????????, ????????? x ???????????? ??? ??? ?????? ??? ???????????? ???
			perp_walldist = (map_x - game->posx + (1 - step_x) / 2) / raydir_x;
		else //y?????? ???????????? ???
			perp_walldist = (map_y - game->posy + (1 - step_y) / 2) / raydir_y;

		//??????????????? ??????????????? ?????? ????????? ??? ?????? ??????
		int lineheight = (int)(info->config.height / perp_walldist);

		//??? ?????? ?????? y??????
		int drawstart = -lineheight / 2 + info->config.height / 2;
		// 0 ????????? ?????????????????? ???
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + info->config.height / 2;
		if (drawend >= info->config.height)
			drawend = info->config.height - 1;

		// ????????? ??????
	//	int texNum = info->map.w_map[map_x][map_y] - 1;
		//1??? ????????? ????????? ????????? 0?????? 8????????? ???????????????
		//0??? ?????? ?????? 1?????? 8?????? ???????????? 1?????? 0?????? 7?????????

		double wallx; //????????? ????????? ?????? ????????? ??????
		if (side == 0)
			wallx = game->posy + perp_walldist * raydir_y;
		else
			wallx = game->posx + perp_walldist * raydir_x;
		//floor??? ????????????
		wallx -= floor(wallx);
		//????????? wallx??? 1?????? ???????????? ??????????
		//???????????? x?????? ????????????
		int texx = (int)(wallx * (double)info->config.texwidth);
		if (side == 0 && raydir_x > 0)
			texx = info->config.texwidth - texx - 1;
		if (side == 1 && raydir_y < 0)
			texx = info->config.texwidth - texx - 1;
		
		double step = 1.0 * info->config.texheight / lineheight;
		double texPos = (drawstart - info->config.height / 2 + lineheight / 2) * step;
		for (int y = drawstart; y < drawend; y++)
		{
			int texy = (int)texPos & (info->config.texheight - 1); //????????? ???????????? &?
			texPos += step;

			int color;
			// = info->texture[texNum][info->config.texheight * texy + texx];
			if (side == 1 && raydir_y > 0)
				color = info->texture[0][info->config.texheight * texy + texx];
			else if (side == 1 && raydir_y < 0)
				color = info->texture[1][info->config.texheight * texy + texx];
			else if (side == 0 && raydir_x > 0)
				color = info->texture[2][info->config.texheight * texy + texx];
			if (side == 0 && raydir_x < 0)
				color = info->texture[3][info->config.texheight * texy + texx];
			//	color = (color >> 1) & 8355711;

		info->screen[y][x] = color;
		}
		info->zBuffer[x] = perp_walldist;
	}
	//SPRITE CASTING
	//sort sprites from far to close
	int		spriteOrder[info->spritenum];
	double	spriteDistance[info->spritenum];
	for(int i = 0; i < info->spritenum; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((game->posx - info->sprite[i].x) * (game->posx - info->sprite[i].x) + (game->posy - info->sprite[i].y) * (game->posy - info->sprite[i].y)); //sqrt not taken, unneeded
	}
	//??????????????? ????????? ?????? ???????????? ???
	sortSprites(spriteOrder, spriteDistance, info->spritenum);
	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < info->spritenum; i++)
	{
			//translate sprite position to relative to camera
			double spritex = info->sprite[spriteOrder[i]].x - game->posx;
			double spritey = info->sprite[spriteOrder[i]].y - game->posy;

			//transform sprite with the inverse camera matrix
			// [ planex   dirx ] -1                                       [ diry      -dirx ]
			// [               ]       =  1/(planex*diry-dirx*planey) *   [                 ]
			// [ planey   diry ]                                          [ -planey  planex ]

			double invDet = 1.0 / (game->planex * game->diry - game->dirx * game->planey); //required for correct matrix multiplication

			double transformx = invDet * (game->diry * spritex - game->dirx * spritey);
			double transformy = invDet * (-game->planey * spritex + game->planex * spritey); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

			int spriteScreenx = (int)((info->config.width / 2) * (1 + transformx / transformy));

			//parameters for scaling and moving the sprites
			#define uDiv 1
			#define vDiv 1
			#define vMove 0.0
			int vMoveScreen = (int)(vMove / transformy);

			//calculate height of the sprite on screen
			int spriteHeight = (int)fabs((info->config.height / transformy) / vDiv); //using "transformy" instead of the real distance prevents fisheye
			//calculate lowest and highest pixel to fill in current stripe
			int drawstarty = -spriteHeight / 2 + info->config.height / 2 + vMoveScreen;
			if(drawstarty < 0) drawstarty = 0;
			int drawendy = spriteHeight / 2 + info->config.height / 2 + vMoveScreen;
			if(drawendy >= info->config.height) drawendy = info->config.height - 1;

			//calculate width of the sprite
			int spriteWidth = (int)fabs((info->config.height / transformy) / uDiv);
			int drawstartx = -spriteWidth / 2 + spriteScreenx;
			if(drawstartx < 0) drawstartx = 0;
			int drawendx = spriteWidth / 2 + spriteScreenx;
			if(drawendx >= info->config.width) drawendx = info->config.width - 1;

		//	printf("%d, %d\n",drawstartx, drawendx);
			//loop through every vertical stripe of the sprite on screen
			for(int stripe = drawstartx; stripe < drawendx; stripe++)
			{
				int texx = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenx)) * info->config.texwidth / spriteWidth) / 256);
				//the conditions in the if are:
				//1) it's in front of camera plane so you don't see things behind you
				//2) it's on the screen (left)
				//3) it's on the screen (right)
				//4) ZBuffer, with perpendicular distance
				if(transformy > 0 && stripe > 0 && stripe < info->config.width && transformy < info->zBuffer[stripe])
				for(int y = drawstarty; y < drawendy; y++) //for every pixel of the current stripe
				{
					int d = (y-vMoveScreen) * 256 - info->config.height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texy = ((d * info->config.texheight) / spriteHeight) / 256;
					int color = info->texture[info->sprite[spriteOrder[i]].texture][info->config.texwidth * texy + texx]; //get current color from the texture
					if((color & 0x00FFFFFF) != 0) info->screen[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
			}
		}
}

void	draw(t_info *info)
{
	int x;
	int y;

	y = 0;
	while (y < info->config.height)
	{
		x = 0;
		while (x < info->config.width)
		{
			info->img.data[y * info->config.width + x] = info->screen[y][x];
			x++;
		}
		y++;
	}
	if (info->save_opt == 1)
	{
		if (save_bmp(info) == 1)
			exit(EXIT_SUCCESS);
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return (0);
}