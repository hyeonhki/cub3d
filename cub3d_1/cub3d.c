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

int exit_hook(t_info *info)
{
	exit(EXIT_SUCCESS);
	return(EXIT_SUCCESS);
}

int	key_press(int key, t_info *info)
{
	t_game *game;
	game = &info->game;
	if (key == KEY_W)
	{
		if (info->map.w_map[(int)(game->posx + game->dirx * info->config.movespeed)][(int)(game->posy)] == '0')
			game->posx += game->dirx * info->config.movespeed;
		if (info->map.w_map[(int)(game->posx)][(int)(game->posy + game->diry * info->config.movespeed)] == '0')
			game->posy += game->diry * info->config.movespeed;
	}
	//move backwards if no wall behind you
	if (key == KEY_S)
	{
		if (info->map.w_map[(int)(game->posx - game->dirx * info->config.movespeed)][(int)(game->posy)] == '0')
			game->posx -= game->dirx * info->config.movespeed;
		if (info->map.w_map[(int)(game->posx)][(int)(game->posy - game->diry * info->config.movespeed)] == '0')
			game->posy -= game->diry * info->config.movespeed;
	}
	//rotate to the right
	if (key == KEY_D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirx = game->dirx;
		game->dirx = game->dirx * cos(-info->config.rotspeed) - game->diry * sin(-info->config.rotspeed);
		game->diry = oldDirx * sin(-info->config.rotspeed) + game->diry * cos(-info->config.rotspeed);
		double oldPlanex = game->planex;
		game->planex = game->planex * cos(-info->config.rotspeed) - game->planey * sin(-info->config.rotspeed);
		game->planey = oldPlanex * sin(-info->config.rotspeed) + game->planey * cos(-info->config.rotspeed);
	}
	//rotate to the left
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirx = game->dirx;
		game->dirx = game->dirx * cos(info->config.rotspeed) - game->diry * sin(info->config.rotspeed);
		game->diry = oldDirx * sin(info->config.rotspeed) + game->diry * cos(info->config.rotspeed);
		double oldPlanex = game->planex;
		game->planex = game->planex * cos(info->config.rotspeed) - game->planey * sin(info->config.rotspeed);
		game->planey = oldPlanex * sin(info->config.rotspeed) + game->planey * cos(info->config.rotspeed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}



void	calc(t_info *info, t_game *game)
{
	//천장 바닥 
	floor_ceiling_raycast(info);
	//벽 캐스팅
	wall_raycast(info, game);
	sprite_raycast(info, game);
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
	calc(info, &info->game);
	draw(info);
	return (0);
}