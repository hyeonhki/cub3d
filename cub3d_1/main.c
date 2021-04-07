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

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{

	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	//xpm의 임지 변환, width와 height에 자동으로 너비와 높이가 저장된다.
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	//생성된 이미지의 정보를 리턴해서 수정 등에 용이하게
	
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x ++)
		{
			//생성된 xpm데이터를 담은 이미지 데이터를 texture로 옮김
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	//ft_arraycpy(texture, img->data, img->img_height * img->img_width);
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	//새로운 이미지 구조체를 생성
	t_img	img;
	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
//	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
//	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
//	load_image(info, info->texture[6], "textures/wood.xpm", &img);
//	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
}


void instead_mapparsing(t_info *info)
{
	info->posX = 22.0;
	info->posY = 11.5;
	info->dirX = -1.0;
	info->dirY= 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
}

void	ready_screen(t_info *info)
{
	info->screen = ft_2d_malloc(info->config.height, info->config.width);
	ft_reset(info->screen, info->config.height, info->config.width);
}

void	ready_texture(t_info *info)
{
	info->texture = ft_2d_malloc(4, info->config.texheight * info->config.texwidth);
	ft_reset(info->texture, 4, info->config.texheight*info->config.texwidth);
}

void	ready_image(t_info *info)
{
	info->img.img = mlx_new_image(info->mlx, info->config.width, info->config.height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
}

void	game_init(t_info *info)
{
	info->mlx = mlx_init();
	ready_screen(info);
	//draw에서 스크린 버퍼에 구현된 픽셀? 그림은 window에 표현될 imgdata로 옮겨진다
	ready_texture(info);
	ready_image(info);
	info->win = mlx_new_window(info->mlx, info->config.width, info->config.height, "mlx");
}

int main(void)
{
	t_info info;
	config_init(&info.config);
	game_init(&info);
	load_texture(&info);
	instead_mapparsing(&info); //추후 지도를 읽어오면서 지워야 할 부분
	//기본 유지되는 hook (계산하고 그리기)
	mlx_loop_hook(info.mlx, &main_loop, &info);
	//이벤트를 받는 hook
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop(info.mlx);
}
