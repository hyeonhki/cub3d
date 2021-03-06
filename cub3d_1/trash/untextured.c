/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:52:48 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/03/23 16:52:49 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_EXIT 17

#define KEY_A 0
#define KEY_D 2
#define KEY_W 13
#define KEY_S 1
#define KEY_ESC 53

typedef struct s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void *mlx;
	void *win;
	double moveSpeed;
	double rotSpeed;
} t_info;

void verLine(t_info *info, int x, int y1, int y2, int color)
{
	int y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(info->mlx, info->win, x, y, color);
		y++;
	}
}

int worldMap[mapWidth][mapHeight] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void calc(t_info *info)
{
	/*
	double posX = 22;
	double posY = 12; //posX, posY ??? ??????????????? ?????? ????????????
	double dirX = -1;
	double dirY = 0; //???????????? ?????? ????????????
	double planeX = 0;
	double planeY = 0.66; //?????? ????????? ????????? ??????????????? ???????????????
	double time = 0;	  //?????? ????????? ??????
	double oldTime = 0;	  //?????? ????????? ??????

	void *mlx;
	void *win;
	t_info *info;

	//	screen(screenWidth, screenHeight, 0, "Raycaster"); //????????? ????????? ????????????
	mlx = mlx_init();
	win = mlx_new_window(mlx, screenWidth, screenHeight, "cub3d");

	mlx_loop(mlx);
	*/
	int w;
	w = screenWidth;
	int x = 0;
	while (x < w)
	{
		//for (int x = 0; x < w; x++) //w ????????? width??? ???
		//{
		double cameraX = 2 * x / (double)w - 1; //????????????????????? ????????? x ??????
		//cameraX??? ?????? ????????? ????????? ??????
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX; //x????????? ??????????????? ??? ?????????????
		//rayDir??? ????????? ????????????

		//mapX, mapY??? ?????? ????????? ??????, ????????? ?????? ??? ???(square)??????.
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//????????? ~ ????????? x or y?????? ????????? ???????????? ????????? ????????????
		double sideDistX;
		double sideDistY;

		//????????? x or y??? ?????? ?????? ?????? x or y ???????????? ?????? ????????????
		double deltaDistX = fabs(1 / rayDirX); //abs?????? fabs
		double deltaDistY = fabs(1 / rayDirY);

		//????????? ????????? ??????????????? ???????????? ??? ??????
		double perpWallDist;

		//DDA??????????????? ?????? ??????
		//????????? ????????? ?????? ?????? ???????????? ???????????? ??? ??????????????? ??? ????????? ??????
		//+1, -1??? ????????????. ?????? ??????
		int stepX;
		int stepY;

		//??????????????? ?????? x??? ?????? y?????? ??????????????? ????????? ?????? ????????? ???????????? ????????????
		//hit??? ?????? ????????? ??????(?????? ??????)
		//????????? ?????? x????????? y???????????? ??? side??? 0, 1
		int hit = 0;
		int side;

		//stepX, stepY??? ???????????? sideDist
		//?????? rayDirX??? ?????? ???????????? stepX??? ?????? +1, ???????????? -1
		//rayDirX??? ?????? 0????????? stepX??? ???????????? ???????????? ?????? ?????? ?????? ??????X
		//stepY??? ?????????
		//sideDistX??? rayDirX??? ????????? ??????, ????????? ??????????????? ??????????????? ???????????? ??????????????? x???????????? ??????
		//mapX, mapY??? ?????????
		if (rayDirX < 0)
		{
			stepX = -1;
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
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
			//DDA????????? ?????? ????????? ??????????????? ???????????? ???????????? ????????????
		}
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		//????????? ??????(perpWallDist)??? ?????? ????????? ??????????????? ?????? ?????? ?????????
		int h = screenHeight;
		int lineHeight = (int)(h / perpWallDist);
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;
		//Color RGB ?????? ???????????? 2021.03.23
		//????????? ??????
		int color;
		if (worldMap[mapX][mapY] == 1)
			color = 0xFF0000;
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		//x?????? y?????? ????????? ??????????????? ??????????????? ??????
		if (side == 1)
			color = color / 2;
		//???????????? ????????? ????????????
		verLine(info, x, drawStart, drawEnd, color);
		x++;
	}
}

int key_press(int key, t_info *info)
{
	//W??? ?????????
	//???????????? ????????? ??????????????? ?????? posX?????? dirx, posy?????? diry??? ????????????
	//????????? ????????? ???????????? ???????????? ?????????(?????? ???????????????) (map == 0 ????????? ???????????????)
	if (key == KEY_W)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//S??? ??????
	if (key == KEY_S)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	//A??? D??? ????????? ???????????? ??????????????? ????????? ??????????????? ??????????????? ????????? ???????????????.
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (key == KEY_D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

int main_loop(t_info *info)
{
	calc(info);

	return (0);
}

int main(void)
{
	t_info info;

	info.mlx = mlx_init();
	info.posX = 12;
	info.posY = 5; //posX, posY ??? ??????????????? ?????? ????????????
	info.dirX = -1;
	info.dirY = 0; //???????????? ?????? ????????????
	info.planeX = 0;
	info.planeY = 0.66; //?????? ????????? ????????? ??????????????? ???????????????
	//mlx??? ?????????????????? ???????????? ??????? ????????? ??????????????? speed??? ?????? ?????? ?????? ???
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;

	info.win = mlx_new_window(info.mlx, screenWidth, screenHeight, "mlx");

	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop_hook(info.mlx, &main_loop, &info);

	mlx_loop(info.mlx);
}
