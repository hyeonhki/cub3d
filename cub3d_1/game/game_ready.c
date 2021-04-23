/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ready.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:27:33 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/23 16:27:34 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ready_screen(t_info *info)
{
	info->screen = ft_2d_malloc(info->config.height, info->config.width);
	ft_reset(info->screen, info->config.height, info->config.width);
}

void	ready_texture(t_info *info)
{
	info->texture = ft_2d_malloc(info->config.texnum, info->config.texheight * info->config.texwidth);
	ft_reset(info->texture, info->config.texnum, info->config.texheight*info->config.texwidth);
}

void	ready_image(t_info *info)
{
	info->img.img = mlx_new_image(info->mlx, info->config.width, info->config.height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
}
