/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 08:50:47 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/06 08:50:49 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_screen(t_info *info)
{
	if (!(info->screen = ft_2d_malloc(info->config.height, info->config.width)))
		return (0);
	ft_reset(info->screen, info->config.height, info->config.width);
	return (1);
}

int		set_texture(t_info *info)
{
	if (!(info->texture = ft_2d_malloc(info->config.texnum, info->config.texsize)))
		return (0);
	ft_reset(info->texture, info->config.texnum, info->config.texsize);
	return (1);
}


void game_init(t_info *info)
{
	info->mlx = mlx_init();
	set_screen(info);
	set_texture(info);
	info->win
		= mlx_new_window(info->mlx, info->config.width, info->config.height, "cub3d");
	
}

void image_init(t_info *info)
{
	info->img.img
		= mlx_new_image(info->mlx, info->config.width, info->config.height);
	info->img.data
		= (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
}

void load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img
		= mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data
		= (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	ft_arraycpy(texture, img->data, img->img_height * img->img_width);
	mlx_destroy_image(info->mlx, img->img);
}

void load_texture(t_info *info)
{
	t_img img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
}

int main(int argc, char *argv[])
{
	t_info	info;

	//사용자의 위치 및 카메라평면은 어디서?
	info.posX = 22.0;
	info.posY = 11.5;
	info.dirX = -1.0;
	info.dirY= 0.0;
	info.planeX = 0.0;
	info.planeY = 0.66;
	config_init(&info.config); //스크린 크기 등의 환경설정
	game_init(&info); // 스크린
	load_texture(&info);
	image_init(&info);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop(info.mlx);
}
