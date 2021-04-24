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
	img->img = \
	mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = \
	(int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	while (info->etc.y < img->img_height)
	{
		info->etc.x = 0;
		while (info->etc.x < img->img_width)
		{
			texture[img->img_width * info->etc.y + info->etc.x] = \
				img->data[img->img_width * info->etc.y + info->etc.x];
			info->etc.x++;
		}
		info->etc.y++;
	}
	set_etc(info);
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], info->map.no, &img);
	load_image(info, info->texture[1], info->map.so, &img);
	load_image(info, info->texture[2], info->map.we, &img);
	load_image(info, info->texture[3], info->map.ea, &img);
	load_image(info, info->texture[4], info->map.sp, &img);
}
