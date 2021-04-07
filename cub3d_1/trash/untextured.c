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
	double posY = 12; //posX, posY 는 플레이어의 초기 위치벡터
	double dirX = -1;
	double dirY = 0; //플레이어 초기 방향벡터
	double planeX = 0;
	double planeY = 0.66; //방향 벡터와 수직인 플레이어의 카메라평면
	double time = 0;	  //현재 프레임 시간
	double oldTime = 0;	  //이전 프레임 시간

	void *mlx;
	void *win;
	t_info *info;

	//	screen(screenWidth, screenHeight, 0, "Raycaster"); //해상도 지정후 화면생성
	mlx = mlx_init();
	win = mlx_new_window(mlx, screenWidth, screenHeight, "cub3d");

	mlx_loop(mlx);
	*/
	int w;
	w = screenWidth;
	int x = 0;
	while (x < w)
	{
		//for (int x = 0; x < w; x++) //w 스크린 width인 듯
		//{
		double cameraX = 2 * x / (double)w - 1; //카메라평면에서 위치의 x 좌표
		//cameraX를 통해 광선의 방향을 계산
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX; //x좌표에 의존한다는 게 이런걸까?
		//rayDir는 광선의 방향벡터

		//mapX, mapY는 현재 광선의 위치, 광선이 있는 한 칸(square)이다.
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//시작점 ~ 첫번째 x or y면을 만나는 점까지의 광선의 이동거리
		double sideDistX;
		double sideDistY;

		//첫번째 x or y면 부터 바로 다음 x or y 면까지의 광선 이동거리
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

		//stepX, stepY의 초기값과 sideDist
		//만약 rayDirX의 값이 양수라면 stepX의 값은 +1, 음수라면 -1
		//rayDirX의 값이 0이라면 stepX는 사용되지 않으므로 어떤 값을 갖든 상관X
		//stepY도 똑같이
		//sideDistX는 rayDirX가 양수일 경우, 광선의 시작점부터 오른쪽으로 이동하다 처음만나는 x면까지의 거리
		//mapX, mapY는 정수값
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

		//DDA 알고리즘 시작
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
			//DDA완료를 통해 광선의 시작점에서 벽까지의 이동거리 계산완료
		}
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		//계산한 거리(perpWallDist)를 통해 화면에 그려야하는 선의 높이 구하기
		int h = screenHeight;
		int lineHeight = (int)(h / perpWallDist);
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;
		//Color RGB 부터 시작하기 2021.03.23
		//벽색깔 선정
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
		//x면과 y면의 벽색을 다르게해서 입체적으로 표현
		if (side == 1)
			color = color / 2;
		//픽셀별로 이미지 그려내기
		verLine(info, x, drawStart, drawEnd, color);
		x++;
	}
}

int key_press(int key, t_info *info)
{
	//W키 입력시
	//플레이어 앞으로 이동시켜야 해서 posX에는 dirx, posy에는 diry를 더해준다
	//새로운 위치가 벽이라면 이동하지 못한다(벽에 가로막히게) (map == 0 일때만 움직인단말)
	if (key == KEY_W)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//S키 입력
	if (key == KEY_S)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	//A와 D는 회전을 고려하여 회전행렬을 곱해서 방향벡터와 카메라평면 모두를 회전시킨다.
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
	info.posY = 5; //posX, posY 는 플레이어의 초기 위치벡터
	info.dirX = -1;
	info.dirY = 0; //플레이어 초기 방향벡터
	info.planeX = 0;
	info.planeY = 0.66; //방향 벡터와 수직인 플레이어의 카메라평면
	//mlx는 프레임타임을 계산하지 않나? 예제와 다른부분은 speed에 값을 넣는 다는 것
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;

	info.win = mlx_new_window(info.mlx, screenWidth, screenHeight, "mlx");

	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop_hook(info.mlx, &main_loop, &info);

	mlx_loop(info.mlx);
}
