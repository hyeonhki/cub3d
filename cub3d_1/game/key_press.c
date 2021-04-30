/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 11:40:41 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/26 11:40:41 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ws_press(t_info *info, int i)
{
	t_game	*game;

	game = &info->game;
	if (info->map.w_map[(int)(game->posx + i * game->dirx * info->config.movespeed)][(int)(game->posy)] == '0')
		game->posx += i * game->dirx * info->config.movespeed;
	if (info->map.w_map[(int)(game->posx)][(int)(game->posy + i * game->diry * info->config.movespeed)] == '0')
		game->posy += i * game->diry * info->config.movespeed;
}

void	da_press(t_info *info, int i)
{
	t_game	*game;
	double	olddirx;
	double	oldplanex;

	game = &info->game;
	olddirx = game->dirx;
	oldplanex = game->planex;
	game->dirx = game->dirx * cos(i * info->config.rotspeed) - game->diry * sin(i * info->config.rotspeed);
	game->diry = olddirx * sin(i * info->config.rotspeed) + game->diry * cos(i * info->config.rotspeed);
	game->planex = game->planex * cos(i * info->config.rotspeed) - game->planey * sin(i * info->config.rotspeed);
	game->planey = oldplanex * sin(i * info->config.rotspeed) + game->planey * cos(i * info->config.rotspeed);
}

int	key_press(int key, t_info *info)
{
	t_game	*game;

	game = &info->game;
	if (key == KEY_W)
		ws_press(info, 1);
	if (key == KEY_S)
		ws_press(info, -1);
	if (key == KEY_D)
		da_press(info, -1);
	if (key == KEY_A)
		da_press(info, 1);
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (0);
}