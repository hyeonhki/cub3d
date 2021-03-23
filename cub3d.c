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
#include "./mlx/mlx.h"

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

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

int main()
{
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

	//	screen(screenWidth, screenHeight, 0, "Raycaster"); //해상도 지정후 화면생성
	mlx = mlx_init();
	win = mlx_new_window(mlx, screenWidth, screenHeight, "cub3d");

	mlx_loop(mlx);
	int w;
	w = screenWidth;
	while (1)
	{
		for (int x = 0; x < w; x++) //w 스크린 width인 듯
		{
			double cameraX = 2 * x / (double)w - 1; //카메라평면에서 위치의 x 좌표
			//cameraX를 통해 광선의 방향을 계산
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX; //x좌표에 의존한다는 게 이런걸까?
			//rayDir는 광선의 방향벡터

			//mapX, mapY는 현재 광선의 위치, 광선이 있는 한 칸(square)이다.
			int mapX = (int)posX;
			int mapY = (int)posY;

			//시작점 ~ 첫번째 x or y면을 만나는 점까지의 광선의 이동거리
			double sideDistX;
			double sideDistY;

			//첫번째 x or y면 부터 바로 다음 x or y 면까지의 광선 이동거리
			double deltaDistX = abs(1 / rayDirX);
			double deltaDistY = abs(1 / rayDirY);

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
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
				if (side == 0)
					perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
				else
					perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

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
			}
		}
	}
}
