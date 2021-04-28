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

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_img
{
	void		*img;
	int			*data;

	int			size_l;
	int			bpp;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

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

typedef struct	s_raysp
{
	int			*spriteorder;
	double		*spritedistance;

	double		spritex;
	double		spritey;

	double		invDet;
	double		transformx;
	double		transformy;

	int			spriteScreenx;

	int			vMoveScreen;
	int			spriteHeight;
	int			drawStarty;
	int			drawEndy;
	int			spriteWidth;
	int			drawStartx;
	int			drawEndx;

	int			texx;
	int			texy;
	int			d;
	int			color;
}				t_raysp;

typedef struct	s_rayw
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;

	double	sidedistx;
	double	sidedisty;
	int		stepx;
	int		stepy;

	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		hit;
	int		side;

	int		lineheight;
	int		drawstart;
	int		drawend;

	double	wallx;

	int		texx;
	double	step;
	double	texpos;
	int		texy;
	int		color;
}				t_rayw;

typedef struct	s_game
{
	//사용자의 위치
	double	posx;
	double	posy;
	//플레이어의 초기 방향벡터 (카메라 평면의 수직)
	double	dirx;
	double	diry;
	//카메라평면 (왜 X,Y 두개지?)
	double	planex;
	double	planey;

	t_raysp	raysp;
	t_rayw	rayw;
}				t_game;

typedef struct	s_info
{
	//save opt
	int			save_opt;

	void		*mlx;
	void		*win;

	t_img		img;
	t_config	config;
	t_etc		etc;
	t_game		game;

	int			spritenum;
	t_map		map;
	t_sprite	*sprite;

	int			**screen;
	int			**texture;

	double		zBuffer[1500];

}				t_info;

int		mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

void	ready_screen(t_info *info);
void	ready_texture(t_info *info);
void	ready_image(t_info *info);
void	check_sprite(t_info *info, t_map *map);
void	game_init(t_info *info);

void	set_etc(t_info *info);

int		load_texture(t_info *info);

void	config_to_game(t_info *info, t_map *map);

void	floor_ceiling_raycast(t_info *info);
void	wall_raycast(t_info *info, t_game *game);
void	sprite_raycast(t_info *info, t_game *game);
#endif
