/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:15:24 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/24 16:15:25 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	wall_raycast(t_info *info, t_game *game)
{
	for (int x = 0; x < info->config.width; x ++)
	{
		double camerax = 2 * x / (double)info->config.width - 1; 
		double rayDirx = game->dirx + game->planex * camerax;
		double rayDiry = game->diry + game->planey * camerax; 
		int mapx = (int)game->posx;
		int mapy = (int)game->posy;
		double sideDistx;
		double sideDisty;
		double deltaDistx = fabs(1 / rayDirx); //abs대신 fabs
		double deltaDisty = fabs(1 / rayDiry);
		double perpWallDist;
		int stepx;
		int stepy;
		int hit = 0;
		int side;
		if (rayDirx < 0)
		{
			stepx = -1;
			//double		double		int(info->posx)
			sideDistx = (game->posx - mapx) * deltaDistx;
		}
		else
		{
			stepx = 1;
			sideDistx = (mapx + 1.0 - game->posx) * deltaDistx;
		}
		if (rayDiry < 0)
		{
			stepy = -1;
			sideDisty = (game->posy - mapy) * deltaDisty;
		}
		else
		{
			stepy = 1;
			sideDisty = (mapy + 1.0 - game->posy) * deltaDisty;
		}
		
		//DDA 알고리즘 시작
		while (hit == 0)
		{
			if (sideDistx < sideDisty)
			{
				sideDistx += deltaDistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sideDisty += deltaDisty;
				mapy += stepy;
				side = 1;
			}
			if (info->map.w_map[mapx][mapy] == '1') //이래야 2가 스프라이트로 출력되지 않을까?
				hit = 1;
			//DDA완료를 통해 광선의 시작점에서 벽까지의 이동거리 계산완료
		}
		//어안렌즈 효과의 해결
		//보정코드 추가 없이 방지하는 방법
		//perpwalldist는 광선의 이동거리(수직거리)
		if (side == 0) //처음으로 부딪힌 면이 x면이라면, 광선이 x 방향으로 몇 칸 갔는 지 나타내는 수
			perpWallDist = (mapx - game->posx + (1 - stepx) / 2) / rayDirx;
		else //y면에 부딪혔을 때
			perpWallDist = (mapy - game->posy + (1 - stepy) / 2) / rayDiry;

		//화면까지의 수직거리를 통해 그려낼 벽 길이 잡기
		int lineheight = (int)(info->config.height / perpWallDist);

		//벽 그릴 시작 y위치
		int drawStart = -lineheight / 2 + info->config.height / 2;
		// 0 이하면 화면맨끝부터 벽
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineheight / 2 + info->config.height / 2;
		if (drawEnd >= info->config.height)
			drawEnd = info->config.height - 1;

		// 텍스터 계산
	//	int texNum = info->map.w_map[mapx][mapy] - 1;
		//1을 빼주는 이유는 지도에 0부터 8까지로 채워놨는데
		//0은 없는 거고 1부터 8까지 텍스처라 1빼서 0부터 7까지로

		double wallx; //광선이 부딪힌 벽의 정확한 위치
		if (side == 0)
			wallx = game->posy + perpWallDist * rayDiry;
		else
			wallx = game->posx + perpWallDist * rayDirx;
		//floor는 내림함수
		wallx -= floor(wallx);
		//이러면 wallx는 1이하 소수점만 남는다?
		//텍스처의 x좌표 나타내기
		int texx = (int)(wallx * (double)info->config.texwidth);
		if (side == 0 && rayDirx > 0)
			texx = info->config.texwidth - texx - 1;
		if (side == 1 && rayDiry < 0)
			texx = info->config.texwidth - texx - 1;
		
		double step = 1.0 * info->config.texheight / lineheight;
		double texPos = (drawStart - info->config.height / 2 + lineheight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texy = (int)texPos & (info->config.texheight - 1); //갑자기 비트연산 &?
			texPos += step;

			int color;
			// = info->texture[texNum][info->config.texheight * texy + texx];
			if (side == 1 && rayDiry > 0)
				color = info->texture[0][info->config.texheight * texy + texx];
			else if (side == 1 && rayDiry < 0)
				color = info->texture[1][info->config.texheight * texy + texx];
			else if (side == 0 && rayDirx > 0)
				color = info->texture[2][info->config.texheight * texy + texx];
			if (side == 0 && rayDirx < 0)
				color = info->texture[3][info->config.texheight * texy + texx];
			//	color = (color >> 1) & 8355711;

		info->screen[y][x] = color;
		}
		info->zBuffer[x] = perpWallDist;
	}
}
