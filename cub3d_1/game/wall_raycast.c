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

static void	set_variables(t_info *info, t_game *game, int x)
{
	game->rayw.camerax = 2 * x / (double)info->config.width - 1;
	game->rayw.raydirx = game->dirx + game->planex * game->rayw.camerax;
	game->rayw.raydiry =game->diry + game->planey * game->rayw.camerax; 
	game->rayw.mapx = (int)game->posx;
	game->rayw.mapy = (int)game->posy;
	game->rayw.deltadistx = fabs(1 / game->rayw.raydirx); //abs대신 fabs
	game->rayw.deltadisty = fabs(1 / game->rayw.raydiry);
	game->rayw.hit = 0;
	//험수길이 축약(else문 제거)
	game->rayw.stepx = 1;
	game->rayw.sidedistx = (game->rayw.mapx + 1.0 - game->posx) * game->rayw.deltadistx;
	if (game->rayw.raydirx < 0)
	{
		game->rayw.stepx = -1;
		game->rayw.sidedistx = (game->posx - game->rayw.mapx) * game->rayw.deltadistx;
	}
	game->rayw.stepy = 1;
	game->rayw.sidedisty = (game->rayw.mapy + 1.0 - game->posy) * game->rayw.deltadisty;
	if (game->rayw.raydiry < 0)
	{
		game->rayw.stepy = -1;
		game->rayw.sidedisty = (game->posy - game->rayw.mapy) * game->rayw.deltadisty;
	}
}

void	dda_algorithm(t_info *info, t_game *game)
{
	while (game->rayw.hit == 0)
	{
		if (game->rayw.sidedistx < game->rayw.sidedisty)
		{
			game->rayw.sidedistx += game->rayw.deltadistx;
			game->rayw.mapx += game->rayw.stepx;
			game->rayw.side = 0;
		}
		else
		{
			game->rayw.sidedisty += game->rayw.deltadisty;
			game->rayw.mapy += game->rayw.stepy;
			game->rayw.side = 1;
		}
		if (info->map.w_map[game->rayw.mapx][game->rayw.mapy] == '1') //이래야 2가 스프라이트로 출력되지 않을까?
			game->rayw.hit = 1;
	}
	//perpwalldist는 광선의 이동거리(수직거리)
	if (game->rayw.side == 0) //처음으로 부딪힌 면이 x면이라면, 광선이 x 방향으로 몇 칸 갔는 지 나타내는 수
		game->rayw.perpwalldist = (game->rayw.mapx - game->posx + (1 - game->rayw.stepx) / 2) / game->rayw.raydirx;
	else //y면에 부딪혔을 때
		game->rayw.perpwalldist = (game->rayw.mapy - game->posy + (1 - game->rayw.stepy) / 2) / game->rayw.raydiry;
}

void	set_wall(t_info *info, t_game *game)
{
	game->rayw.lineheight = (int)(info->config.height / game->rayw.perpwalldist);
	//벽 그릴 시작 y위치
	game->rayw.drawstart = -game->rayw.lineheight / 2 + info->config.height / 2;
	// 0 이하면 화면맨끝부터 벽
	if (game->rayw.drawstart < 0)
		game->rayw.drawstart = 0;
	game->rayw.drawend = game->rayw.lineheight / 2 + info->config.height / 2;
	if (game->rayw.drawend >= info->config.height)
		game->rayw.drawend = info->config.height - 1;
	if (game->rayw.side == 0)
		game->rayw.wallx = game->posy + game->rayw.perpwalldist * game->rayw.raydiry;
	else
		game->rayw.wallx = game->posx + game->rayw.perpwalldist * game->rayw.raydirx;
	//floor는 내림함수
	game->rayw.wallx -= floor(game->rayw.wallx);
	//이러면 wallx는 1이하 소수점만 남는다?
}

void	texture_wall(t_info *info, t_game *game, int x)
{
	game->rayw.texx = (int)(game->rayw.wallx * (double)info->config.texwidth);
	if (game->rayw.side == 0 && game->rayw.raydirx > 0)
		game->rayw.texx = info->config.texwidth - game->rayw.texx - 1;
	if (game->rayw.side == 1 && game->rayw.raydiry < 0)
		game->rayw.texx = info->config.texwidth - game->rayw.texx - 1;
	game->rayw.step = 1.0 * info->config.texheight / game->rayw.lineheight;
	game->rayw.texpos = (game->rayw.drawstart - info->config.height / 2 + game->rayw.lineheight / 2) * game->rayw.step;
	info->etc.y = game->rayw.drawstart;
	while (info->etc.y < game->rayw.drawend)
	{
		game->rayw.texy = (int)game->rayw.texpos & (info->config.texheight - 1); //갑자기 비트연산 &?
		game->rayw.texpos += game->rayw.step;
		// = info->texture[texNum][info->config.texheight * texy + texx];
		if (game->rayw.side == 1 && game->rayw.raydiry > 0)
			game->rayw.color = info->texture[0][info->config.texheight * game->rayw.texy + game->rayw.texx];
		else if (game->rayw.side == 1 && game->rayw.raydiry < 0)
			game->rayw.color = info->texture[1][info->config.texheight * game->rayw.texy + game->rayw.texx];
		else if (game->rayw.side == 0 && game->rayw.raydirx > 0)
			game->rayw.color = info->texture[2][info->config.texheight * game->rayw.texy + game->rayw.texx];
		if (game->rayw.side == 0 && game->rayw.raydirx < 0)
			game->rayw.color = info->texture[3][info->config.texheight * game->rayw.texy + game->rayw.texx];
		//특정 면을 어둡게 만들 수 있는 코드
		//game->rayw.color = (game->rayw.color >> 1) & 8355711;
		info->screen[info->etc.y][x] = game->rayw.color;
		info->etc.y++;
	}
}

void	wall_raycast(t_info *info, t_game *game)
{
	set_etc(info);
	for (int x = 0; x < info->config.width; x ++)
	{
		set_variables(info, game, x);
		//DDA 알고리즘 시작, 어안렌즈해결을 위한 수직거리 계산
		dda_algorithm(info, game);
		//화면까지의 수직거리를 통해 그려낼 벽 길이 잡기
		set_wall(info, game);
		//텍스처의 x좌표 나타내기
		texture_wall(info, game, x);
		//얘는 뭘까? 스프라이트로 연결되던데
		info->zBuffer[x] = game->rayw.perpwalldist;
	}
}
