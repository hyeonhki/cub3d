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

int	check_screen(t_info *info)
{
	int		x;
	int		y;

	mlx_get_screen_size(info->mlx, &x, &y);
	if (x < info->config.width || y < info->config.height)
		return (exit_error("RENDERING SIZE ERROR!\n"));
	if (info->config.width <= 0 || info->config.height <= 0)
		return (exit_error("RENDERING SIZE ERROR\n"));
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	info.save_opt = (argc > 2 && ft_strcmp(argv[2], "-save"));
	if (argc < 2 || argc > 3)
		return (exit_error("argc error!"));
	if (argc == 3 && info.save_opt != 1)
		return (exit_error("wrong option!"));
	config_init(&info.config);
	if (!config_map(&info.map, argv[1]))
		return (0);
	config_to_game(&info, &info.map);
	check_screen(&info);
	game_init(&info);
	if (!(load_texture(&info)))
		return (0);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_EXIT, 0, &exit_hook, &info);
	mlx_loop(info.mlx);
}
