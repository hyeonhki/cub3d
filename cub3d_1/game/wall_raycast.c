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

static void	set_variables(t_info *info, t_game *game, int i)
{
	game->rayw.camerax = 2 * i / (double)info->config.width - 1;
	game->rayw.raydirx = game->dirx + game->planex * game->rayw.camerax;
	game->rayw.raydiry =game->diry + game->planey * game->rayw.camerax; 
	game->rayw.mapx = (int)game->posx;
	game->rayw.mapy = (int)game->posy;
	game->rayw.deltadistx = fabs(1 / game->rayw.raydirx); //abs대신 fabs
	game->rayw.deltadisty = fabs(1 / game->rayw.raydiry);
	
	game->rayw.hit = 0;
}
void	wall_raycast(t_info *info, t_game *game)
{
	set_etc(info);
//	while (info->etc.x < info->config.width)
//	{
	//	x++;
//	}

	for (int x = 0; x < info->config.width; x ++)
	{
		set_variables(info, game, x);

		double sideDistx;
		double sideDisty;

		double perpWallDist;

		int side;

		int stepx;
		int stepy;

		//함수 둘
		if (game->rayw.raydirx < 0)
		{
			stepx = -1;
			//double		double		int(info->posx)
			sideDistx = (game->posx - game->rayw.mapx) * game->rayw.deltadistx;
		}
		else
		{
			stepx = 1;
			sideDistx = (game->rayw.mapx + 1.0 - game->posx) * game->rayw.deltadistx;
		}
		if (game->rayw.raydiry < 0)
		{
			stepy = -1;
			sideDisty = (game->posy - game->rayw.mapy) * game->rayw.deltadisty;
		}
		else
		{
			stepy = 1;
			sideDisty = (game->rayw.mapy + 1.0 - game->posy) * game->rayw.deltadisty;
		}
		
		//함수 셋
		//DDA 알고리즘 시작
		while (game->rayw.hit == 0)
		{
			if (sideDistx < sideDisty)
			{
				sideDistx += game->rayw.deltadistx;
				game->rayw.mapx += stepx;
				side = 0;
			}
			else
			{
				sideDisty += game->rayw.deltadisty;
				game->rayw.mapy += stepy;
				side = 1;
			}
			if (info->map.w_map[game->rayw.mapx][game->rayw.mapy] == '1') //이래야 2가 스프라이트로 출력되지 않을까?
				game->rayw.hit = 1;
			//DDA완료를 통해 광선의 시작점에서 벽까지의 이동거리 계산완료
		}
		//어안렌즈 효과의 해결
		//보정코드 추가 없이 방지하는 방법
		//perpwalldist는 광선의 이동거리(수직거리)
		if (side == 0) //처음으로 부딪힌 면이 x면이라면, 광선이 x 방향으로 몇 칸 갔는 지 나타내는 수
			perpWallDist = (game->rayw.mapx - game->posx + (1 - stepx) / 2) / game->rayw.raydirx;
		else //y면에 부딪혔을 때
			perpWallDist = (game->rayw.mapy - game->posy + (1 - stepy) / 2) / game->rayw.raydiry;

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
			wallx = game->posy + perpWallDist * game->rayw.raydiry;
		else
			wallx = game->posx + perpWallDist * game->rayw.raydirx;
		//floor는 내림함수
		wallx -= floor(wallx);
		//이러면 wallx는 1이하 소수점만 남는다?
		//텍스처의 x좌표 나타내기
		int texx = (int)(wallx * (double)info->config.texwidth);
		if (side == 0 && game->rayw.raydirx > 0)
			texx = info->config.texwidth - texx - 1;
		if (side == 1 && game->rayw.raydiry < 0)
			texx = info->config.texwidth - texx - 1;
		
		double step = 1.0 * info->config.texheight / lineheight;
		double texPos = (drawStart - info->config.height / 2 + lineheight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texy = (int)texPos & (info->config.texheight - 1); //갑자기 비트연산 &?
			texPos += step;

			int color;
			// = info->texture[texNum][info->config.texheight * texy + texx];
			if (side == 1 && game->rayw.raydiry > 0)
				color = info->texture[0][info->config.texheight * texy + texx];
			else if (side == 1 && game->rayw.raydiry < 0)
				color = info->texture[1][info->config.texheight * texy + texx];
			else if (side == 0 && game->rayw.raydirx > 0)
				color = info->texture[2][info->config.texheight * texy + texx];
			if (side == 0 && game->rayw.raydirx < 0)
				color = info->texture[3][info->config.texheight * texy + texx];
			//	color = (color >> 1) & 8355711;

		info->screen[y][x] = color;
		}
		info->zBuffer[x] = perpWallDist;
	}
}
