/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:39:53 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 09:39:55 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include "../../mlx/mlx.h"
#include "../utils/utils.h"

typedef struct s_config
{
	int height; //512
	int width; //1024
	int texwidth; //64
	int texheight; //64
	double	moveSpeed;
	double	rotSpeed;

}	t_config;

typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

typedef struct s_info
{
	
	//사용자의 위치
	double	posX;
	double	posY;
	//플레이어의 초기 방향벡터 (카메라 평면의 수직)
	double	dirX;
	double	dirY;
	//카메라평면 (왜 X,Y 두개지?)
	double	planeX;
	double	planeY;

	void	*mlx;
	void	*win;
	
	t_img	img;
	t_config config;
	
	int		**screen;
	int		**texture;

}	t_info;

void	ready_screen(t_info *info);
void	ready_texture(t_info *info);
void	ready_image(t_info *info);
void	game_init(t_info *info);

void	load_texture(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);


#endif
