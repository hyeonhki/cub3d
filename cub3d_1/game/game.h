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
#define GAME_H

#include "../mlx/mlx.h"
#include "../utils/utils.h"
#include "../config/config.h"

typedef struct s_sprite
{
	double x;
	double y;
	int texture;
}	t_sprite;

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

typedef struct	s_etc
{
	int			x;
	int			y;
	int			i;
	int			j;
	int			k;
	int			cnt;
	int			order;
}				t_etc;

typedef struct s_info
{
	//save opt
	int		save_opt;
	//사용자의 위치
	double	posx;
	double	posy;
	//플레이어의 초기 방향벡터 (카메라 평면의 수직)
	double	dirx;
	double	diry;
	//카메라평면 (왜 X,Y 두개지?)
	double	planex;
	double	planey;

	void	*mlx;
	void	*win;
	
	t_img	img;
	t_config	config;
	t_etc	etc;

	int		spritenum;
	t_map	map;
	t_sprite	*sprite;
	
	int		**screen;
	int		**texture;

	double zBuffer[1024];

}	t_info;

void	ready_screen(t_info *info);
void	ready_texture(t_info *info);
void	ready_image(t_info *info);
void	check_sprite(t_info *info, t_map *map);
void	game_init(t_info *info);

void	set_etc(t_info *info);

void	load_texture(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);

void	config_to_game(t_info *info, t_map *map);

void	floor_ceiling_raycast(t_info *info);

#endif
