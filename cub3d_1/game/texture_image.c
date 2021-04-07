/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:56:01 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 17:56:02 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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
	load_image(info, info->texture[0], "../textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "../textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "../textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "../textures/greystone.xpm", &img);
//	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
//	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
//	load_image(info, info->texture[6], "textures/wood.xpm", &img);
//	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
}
