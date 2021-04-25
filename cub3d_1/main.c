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

int main(int argc, char *argv[])
{
	t_info	info;
	int		save_opt;

	info.save_opt = (argc > 2 && ft_strcmp(argv[2], "-save"));
	if (argc < 2 || argc > 3)
		return (exit_error("argc error"));
	config_init(&info.config);
	if (!config_map(&info.map, argv[1]))
		return (0);
	config_to_game(&info, &info.game, &info.map);
	game_init(&info);
	load_texture(&info);
	//기본 유지되는 hook (계산하고 그리기)
	mlx_loop_hook(info.mlx, &main_loop, &info);
	//이벤트를 받는 hook
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_EXIT, 0, &exit_hook, &info);
	mlx_loop(info.mlx);
}