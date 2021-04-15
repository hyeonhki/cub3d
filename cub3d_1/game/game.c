/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.k>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:16:49 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 17:16:50 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


int		count_sprite(t_map *map)
{
	int i;
	int j;
	int cnt;

	cnt = 0;
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			if (map->worldmap[i][j] == 2)
				cnt++;
			j++;
		}
		i++;
	}
	return (cnt);
}

void	check_sprite(t_info *info, t_map *map)
{
	int cnt;
	int i;
	int j;
	int order;

	cnt = count_sprite(map);
	printf("cnt : %d\n",cnt);
	info->spritenum = cnt;
	info->sprite = malloc(sizeof(t_sprite) * cnt);
	i = 0;
	order = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			if (map->worldmap[i][j] == 2)
			{
				info->sprite[order].x = j + 0.5;
				info->sprite[order].y = i + 0.5;
				info->sprite[order].texture = 4;
				map->worldmap[i][j] = 0;
				order += 1;
			}
			j++;
		}
		i++;
	}
}


void	game_init(t_info *info)
{
	info->mlx = mlx_init();
	ready_screen(info);
	//draw에서 스크린 버퍼에 구현된 픽셀? 그림은 window에 표현될 imgdata로 옮겨진다
	ready_texture(info);
	ready_image(info);
	check_sprite(info, &info->map);
	info->win = mlx_new_window(info->mlx, info->config.width, info->config.height, "mlx");
}

void	ready_screen(t_info *info)
{
	info->screen = ft_2d_malloc(info->config.height, info->config.width);
	ft_reset(info->screen, info->config.height, info->config.width);
}

void	ready_texture(t_info *info)
{
	info->texture = ft_2d_malloc(info->config.texnum, info->config.texheight * info->config.texwidth); //texnum 부분 손보기
	ft_reset(info->texture, info->config.texnum, info->config.texheight*info->config.texwidth);
}

void	ready_image(t_info *info)
{
	info->img.img = mlx_new_image(info->mlx, info->config.width, info->config.height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
}
