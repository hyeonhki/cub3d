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

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

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
		if (info->map.w_map[(int)(info->posX + info->dirX * info->config.movespeed)][(int)(info->posY)] == '0')
			info->posX += info->dirX * info->config.movespeed;
		if (info->map.w_map[(int)(info->posX)][(int)(info->posY + info->dirY * info->config.movespeed)] == '0')
			info->posY += info->dirY * info->config.movespeed;
	}
	//move backwards if no wall behind you
	if (key == KEY_S)
	{
		if (info->map.w_map[(int)(info->posX - info->dirX * info->config.movespeed)][(int)(info->posY)] == '0')
			info->posX -= info->dirX * info->config.movespeed;
		if (info->map.w_map[(int)(info->posX)][(int)(info->posY - info->dirY * info->config.movespeed)] == '0')
			info->posY -= info->dirY * info->config.movespeed;
	}
	//rotate to the right
	if (key == KEY_D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->config.rotspeed) - info->dirY * sin(-info->config.rotspeed);
		info->dirY = oldDirX * sin(-info->config.rotspeed) + info->dirY * cos(-info->config.rotspeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->config.rotspeed) - info->planeY * sin(-info->config.rotspeed);
		info->planeY = oldPlaneX * sin(-info->config.rotspeed) + info->planeY * cos(-info->config.rotspeed);
	}
	//rotate to the left
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->config.rotspeed) - info->dirY * sin(info->config.rotspeed);
		info->dirY = oldDirX * sin(info->config.rotspeed) + info->dirY * cos(info->config.rotspeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->config.rotspeed) - info->planeY * sin(info->config.rotspeed);
		info->planeY = oldPlaneX * sin(info->config.rotspeed) + info->planeY * cos(info->config.rotspeed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

void	floor_ceiling_raycast(t_info *info)
{
	for(int y = 0; y < info->config.height; y++)
	{
		for(int x = 0; x < info->config.width; ++x)
		{	
			info->screen[y][x] = info->map.fl_color;
			info->screen[info->config.height - y - 1][x] = info->map.ce_color;
		}
	}
}


void	calc(t_info *info)
{
	//?????? ?????? 
	floor_ceiling_raycast(info);
	//??? ?????????
	for (int x = 0; x < info->config.width; x ++)
	{
		double cameraX = 2 * x / (double)info->config.width - 1; 
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX; 
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;
		double sideDistX;
		double sideDistY;
		double deltaDistX = fabs(1 / rayDirX); //abs?????? fabs
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;
		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			//double		double		int(info->posX)
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}
		
		//DDA ???????????? ??????
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (info->map.w_map[mapX][mapY] == '1') //????????? 2??? ?????????????????? ???????????? ??????????
				hit = 1;
			//DDA????????? ?????? ????????? ??????????????? ???????????? ???????????? ????????????
		}
		//???????????? ????????? ??????
		//???????????? ?????? ?????? ???????????? ??????
		//perpwalldist??? ????????? ????????????(????????????)
		if (side == 0) //???????????? ????????? ?????? x????????????, ????????? x ???????????? ??? ??? ?????? ??? ???????????? ???
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else //y?????? ???????????? ???
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		//??????????????? ??????????????? ?????? ????????? ??? ?????? ??????
		int lineheight = (int)(info->config.height / perpWallDist);

		//??? ?????? ?????? y??????
		int drawStart = -lineheight / 2 + info->config.height / 2;
		// 0 ????????? ?????????????????? ???
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineheight / 2 + info->config.height / 2;
		if (drawEnd >= info->config.height)
			drawEnd = info->config.height - 1;

		// ????????? ??????
	//	int texNum = info->map.w_map[mapX][mapY] - 1;
		//1??? ????????? ????????? ????????? 0?????? 8????????? ???????????????
		//0??? ?????? ?????? 1?????? 8?????? ???????????? 1?????? 0?????? 7?????????

		double wallX; //????????? ????????? ?????? ????????? ??????
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		//floor??? ????????????
		wallX -= floor(wallX);
		//????????? wallX??? 1?????? ???????????? ??????????
		//???????????? x?????? ????????????
		int texX = (int)(wallX * (double)info->config.texwidth);
		if (side == 0 && rayDirX > 0)
			texX = info->config.texwidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = info->config.texwidth - texX - 1;
		
		double step = 1.0 * info->config.texheight / lineheight;
		double texPos = (drawStart - info->config.height / 2 + lineheight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (info->config.texheight - 1); //????????? ???????????? &?
			texPos += step;

			int color;
			// = info->texture[texNum][info->config.texheight * texY + texX];
			if (side == 1 && rayDirY > 0)
				color = info->texture[0][info->config.texheight * texY + texX];
			else if (side == 1 && rayDirY < 0)
				color = info->texture[1][info->config.texheight * texY + texX];
			else if (side == 0 && rayDirX > 0)
				color = info->texture[2][info->config.texheight * texY + texX];
			if (side == 0 && rayDirX < 0)
				color = info->texture[3][info->config.texheight * texY + texX];
			//	color = (color >> 1) & 8355711;

		info->screen[y][x] = color;
		}
		info->zBuffer[x] = perpWallDist;
	}
	//SPRITE CASTING
	//sort sprites from far to close
	int		spriteOrder[info->spritenum];
	double	spriteDistance[info->spritenum];
	for(int i = 0; i < info->spritenum; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((info->posX - info->sprite[i].x) * (info->posX - info->sprite[i].x) + (info->posY - info->sprite[i].y) * (info->posY - info->sprite[i].y)); //sqrt not taken, unneeded
	}
	//??????????????? ????????? ?????? ???????????? ???
	sortSprites(spriteOrder, spriteDistance, info->spritenum);
	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < info->spritenum; i++)
	{
			//translate sprite position to relative to camera
			double spriteX = info->sprite[spriteOrder[i]].x - info->posX;
			double spriteY = info->sprite[spriteOrder[i]].y - info->posY;

			//transform sprite with the inverse camera matrix
			// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
			// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
			// [ planeY   dirY ]                                          [ -planeY  planeX ]

			double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); //required for correct matrix multiplication

			double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
			double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

			int spriteScreenX = (int)((info->config.width / 2) * (1 + transformX / transformY));

			//parameters for scaling and moving the sprites
			#define uDiv 1
			#define vDiv 1
			#define vMove 0.0
			int vMoveScreen = (int)(vMove / transformY);

			//calculate height of the sprite on screen
			int spriteHeight = (int)fabs((info->config.height / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
			//calculate lowest and highest pixel to fill in current stripe
			int drawStartY = -spriteHeight / 2 + info->config.height / 2 + vMoveScreen;
			if(drawStartY < 0) drawStartY = 0;
			int drawEndY = spriteHeight / 2 + info->config.height / 2 + vMoveScreen;
			if(drawEndY >= info->config.height) drawEndY = info->config.height - 1;

			//calculate width of the sprite
			int spriteWidth = (int)fabs((info->config.height / transformY) / uDiv);
			int drawStartX = -spriteWidth / 2 + spriteScreenX;
			if(drawStartX < 0) drawStartX = 0;
			int drawEndX = spriteWidth / 2 + spriteScreenX;
			if(drawEndX >= info->config.width) drawEndX = info->config.width - 1;

		//	printf("%d, %d\n",drawStartX, drawEndX);
			//loop through every vertical stripe of the sprite on screen
			for(int stripe = drawStartX; stripe < drawEndX; stripe++)
			{
				int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * info->config.texwidth / spriteWidth) / 256);
				//the conditions in the if are:
				//1) it's in front of camera plane so you don't see things behind you
				//2) it's on the screen (left)
				//3) it's on the screen (right)
				//4) ZBuffer, with perpendicular distance
				if(transformY > 0 && stripe > 0 && stripe < info->config.width && transformY < info->zBuffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y-vMoveScreen) * 256 - info->config.height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * info->config.texheight) / spriteHeight) / 256;
					int color = info->texture[info->sprite[spriteOrder[i]].texture][info->config.texwidth * texY + texX]; //get current color from the texture
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