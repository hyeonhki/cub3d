/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 08:50:54 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/06 08:50:55 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int cub3dmap[mapwidth][mapheight]=
{
  {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,7},
  {3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {3,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {3,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,7},
  {3,0,3,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,7},
  {3,0,3,0,0,0,0,3,0,3,0,3,0,3,0,3,3,0,0,0,3,3,3,1},
  {3,0,3,0,0,0,0,3,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,8},
  {3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,1},
  {3,0,1,0,0,0,0,3,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,8},
  {3,0,0,0,0,0,0,3,0,0,0,0,0,0,0,3,3,0,0,0,3,3,3,1},
  {3,0,0,0,0,0,0,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,1},
  {3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,6},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {3,3,3,3,3,3,0,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,6},
  {3,3,3,3,3,3,0,3,3,3,3,0,3,2,2,2,2,2,2,2,2,2,2,3},
  {3,0,0,0,0,0,0,0,0,3,3,0,3,2,0,0,0,0,0,2,0,0,0,2},
  {3,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0,3,0,0,2,0,0,0,2},
  {3,0,0,0,0,0,0,0,0,3,3,0,3,2,0,0,0,0,0,2,2,0,2,2},
  {3,0,3,0,3,0,0,0,0,3,3,0,0,0,0,0,3,0,0,0,0,0,0,2},
  {3,0,0,3,0,0,0,0,0,3,3,0,3,2,0,0,0,0,0,2,2,0,2,2},
  {3,0,3,0,3,0,0,0,0,3,3,0,3,2,0,0,3,0,0,2,0,0,0,2},
  {3,0,0,0,0,0,0,0,0,3,3,0,3,2,0,0,0,0,0,2,0,0,0,2},
  {3,3,3,3,3,3,3,3,3,3,1,1,1,2,2,2,2,2,2,2,2,2,2,3}
};



void	draw(t_info *info)
{
	for (int y = 0; y < info->config.height; y++)
	{
		for (int x = 0; x < info->config.width; x++)
		{
			info->img.data[y * info->config.width + x] = info->screen[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info, t_config *config)
{
	//FLOOR CASTING
	for(int y = 0; y < config->height; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = info->dirX - info->planeX;
		float rayDirY0 = info->dirY - info->planeY;
		float rayDirX1 = info->dirX + info->planeX;
		float rayDirY1 = info->dirY + info->planeY;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - config->height / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * config->height;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / config->width;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / config->width;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = info->posX + rowDistance * rayDirX0;
		float floorY = info->posY + rowDistance * rayDirY0;

		for(int x = 0; x < config->width; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(config->texwidth * (floorX - cellX)) & (config->texwidth - 1);
			int ty = (int)(config->texheight * (floorY - cellY)) & (config->texheight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;

			int color;

			// floor
			color = info->texture[floorTexture][config->texwidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			info->screen[y][x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = info->texture[ceilingTexture][config->texwidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			info->screen[config->height - y - 1][x] = color;
		}
	}

	//벽 캐스팅
	for (int x = 0; x < config->width; x ++)
	{
		//카메라가 평면에서 차지하는 x좌표 (-1 ~ 1)
		double cameraX = 2 * x / (double)config->width - 1; 
		//cameraX를 통해 광선의 방향을 계산

		//rayDir 는 광선의 방향벡터
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX; 
		//광선의 방향벡터는 방햑벡터 + 카메라평면 * 배수로 계산된다.
		//방햑벡터야 카메라평면의 수직이니 당연히 더해서 계산 가능

		//mapX, mapY는 현재 광선의 위치
		//광선이 있는 한 칸이다.
		//광선이 맵상 어느칸에 있는지, 어디쯤 있는지까지 알 수 있지만 int로 간단하게 표기
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//시작점 ~ 첫번째 x or y면을 만나는 점까지의 광선의 이동거리
		double sideDistX;
		double sideDistY;

		//첫번째 x or y면 부터 바로 다음 x or y 면까지의 광선 이동거리
		//한번 찾으면 계속 동일한 값을 가진다.
		double deltaDistX = fabs(1 / rayDirX); //abs대신 fabs
		double deltaDistY = fabs(1 / rayDirY);

		//나중에 광선의 이동거리를 계산하는 데 사용
		double perpWallDist;

		//DDA알고리즘을 위해 사용
		//광선의 방향에 따라 어느 방향으로 건너뛰는 지 달라지는데 그 정보를 저장
		//+1, -1로 저장된다. 추후 설명
		int stepX;
		int stepY;

		//마지막으로 벽의 x면 또는 y면과 부딪쳤는지 여부에 따라 루프를 종료할지 결정한다
		//hit은 벽과 부딪힌 여부(루프 종료)
		//부딪힌 곳이 x면이냐 y면이냐에 따 side값 0, 1
		int hit = 0;
		int side;

		//광선의 x방향이 양수라면 stepx = +1, 아니면 - 1
		//y방향도
		//sideDist는 시작점에서 첫번째 x , y 면을 만나는 점까지의 광선의 이동거리
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
		
		//DDA 알고리즘 시작
		//벽에 부딪힐 때 까지 반복! 한칸씩!
		//벽에 부딪히면 그만(hit == 1)
		//x 면에 부딪히는 거리와 y면에 부딪히는 거리 계산해서 한칸씩만 이동함
		//정수형 mapX,Y 변수에 +1 씩 더해서 다음칸이 벽이나 물체인지 마지막에 확인하고 hit 넣어줌
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
			if (cub3dmap[mapX][mapY] > 0)
				hit = 1;
			//DDA완료를 통해 광선의 시작점에서 벽까지의 이동거리 계산완료
		}
		//어안렌즈 효과의 해결
		//보정코드 추가 없이 방지하는 방법
		//perpwalldist는 광선의 이동거리(수직거리)
		if (side == 0) //처음으로 부딪힌 면이 x면이라면, 광선이 x 방향으로 몇 칸 갔는 지 나타내는 수
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else //y면에 부딪혔을 때
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		//화면까지의 수직거리를 통해 그려낼 벽 길이 잡기
		int lineheight = (int)(config->height / perpWallDist);

		//벽 그릴 시작 y위치
		int drawStart = -lineheight / 2 + config->height / 2;
		// 0 이하면 화면맨끝부터 벽
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineheight / 2 + config->height / 2;
		if (drawEnd >= config->height)
			drawEnd = config->height - 1;

		// 텍스터 계산
		int texNum = cub3dmap[mapX][mapY] - 1;
		//1을 빼주는 이유는 지도에 0부터 8까지로 채워놨는데
		//0은 없는 거고 1부터 8까지 텍스처라 1빼서 0부터 7까지로

		double wallX; //광선이 부딪힌 벽의 정확한 위치
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		//floor는 내림함수
		wallX -= floor(wallX);
		//이러면 wallX는 1이하 소수점만 남는다?
		//텍스처의 x좌표 나타내기
		int texX = (int)(wallX * (double)config->texwidth);
		if (side == 0 && rayDirX > 0)
			texX = config->texwidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = config->texwidth - texX - 1;
		
		double step = 1.0 * config->texheight / lineheight;
		double texPos = (drawStart - config->height / 2 + lineheight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (config->texheight - 1); //갑자기 비트연산 &?
			texPos += step;

			int color = info->texture[texNum][config->texheight * texY + texX];

			if (side == 1)
				color = (color >> 1) & 8355711;

			info->screen[y][x] = color;
		}


		//FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

		//4 different wall directions possible
		if(side == 0 && rayDirX > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if(side == 0 && rayDirX < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if(side == 1 && rayDirY > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0) drawEnd = config->height; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(int y = drawEnd + 1; y < config->height; y++)
		{
			currentDist = config->height / (2.0 * y - config->height); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorXWall + (1.0 - weight) * info->posX;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * info->posY;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * config->texwidth) % config->texwidth;
			floorTexY = (int)(currentFloorY * config->texheight) % config->texheight;

			int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
			int floorTexture;
			if(checkerBoardPattern == 0) floorTexture = 3;
			else floorTexture = 4;

			//floor
			info->screen[y][x] = (info->texture[floorTexture][config->texwidth * floorTexY + floorTexX] >> 1) & 8355711;
			//ceiling (symmetrical!)
			info->screen[config->height - y][x] = info->texture[6][config->texwidth * floorTexY + floorTexX];
		}
	}
}

int main_loop(t_info *info)
{
	calc(info, &info->config);
	draw(info);
	return (0);
}

int key_press(int key, t_info *info, t_config *config)
{
	if (key == KEY_W)
	{
		if (!cub3dmap[(int)(info->posX + info->dirX * config->movespeed)][(int)(info->posY)])
			info->posX += info->dirX * config->movespeed;
		if (!cub3dmap[(int)(info->posX)][(int)(info->posY + info->dirY * config->movespeed)])
			info->posY += info->dirY * config->movespeed;
	}
	if (key == KEY_S)
	{
		if (!cub3dmap[(int)(info->posX - info->dirX * config->movespeed)][(int)(info->posY)])
			info->posX -= info->dirX * config->movespeed;
		if (!cub3dmap[(int)(info->posX)][(int)(info->posY - info->dirY * config->movespeed)])
			info->posY -= info->dirY * config->movespeed;
	}
	if (key == KEY_D)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-config->rotspeed) - info->dirY * sin(-config->rotspeed);
		info->dirY = oldDirX * sin(-config->rotspeed) + info->dirY * cos(-config->rotspeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-config->rotspeed) - info->planeY * sin(-config->rotspeed);
		info->planeY = oldPlaneX * sin(-config->rotspeed) + info->planeY * cos(-config->rotspeed);
	}
	if (key == KEY_A)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(config->rotspeed) - info->dirY * sin(config->rotspeed);
		info->dirY = oldDirX * sin(config->rotspeed) + info->dirY * cos(config->rotspeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(config->rotspeed) - info->planeY * sin(config->rotspeed);
		info->planeY = oldPlaneX * sin(config->rotspeed) + info->planeY * cos(config->rotspeed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}