/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:20:44 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 15:20:45 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void instead_mapparsing(t_info *info)
{
	info->posX = 1.5; //22.0; 지도에서 row
	info->posY = 7.5; //11.5; 지도에서 column;
	info->dirX = -1.0; //-1.0;
	info->dirY = 0.0; //0.0;
	info->planeX = 0.0; //0.0
	info->planeY = 0.66; //0.66;
}

void config_to_game(t_info *info, t_player *player)
{
	info->posX = player->x + 0.5;
	info->posY = player->y + 0.5;
	if (player->dir == 'N')
	{
		info->dirX = -1.0;
		info->planeY = 0.66;
	}
	if (player->dir == 'S')
	{
		info->dirX = 1.0;
		info->planeY = -0.66;
	}
	if (player->dir == 'E')
	{
		info->dirY = 1.0;
		info->planeX = 0.66;
	}
	if (player->dir == 'W')
	{
		info->dirY = -1.0;
		info->planeX = -0.66;
	}
}

int main(int argc, char *argv[])
{
	t_info info;

	config_init(&info.config);
	config_map(&info.map, argv[1]);
	config_to_game(&info, &info.map.player);
	game_init(&info);
	load_texture(&info);
//	instead_mapparsing(&info); //추후 지도를 읽어오면서 지워야 할 부분
	//기본 유지되는 hook (계산하고 그리기)
	mlx_loop_hook(info.mlx, &main_loop, &info);
	//이벤트를 받는 hook
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop(info.mlx);
}