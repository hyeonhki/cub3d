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

# include "../mlx/mlx.h"
# include "../utils/utils.h"
# include "../config/config.h"

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

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
	int			i;
	int			j;
	int			k;
	int			x;
	int			y;
	int			cnt;
	int			order;
}				t_etc;

typedef struct	s_wall
{
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		perp_walldist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;

	int			lineheight;
	int			drawstart;
	int			drawend;
	double		wallx;
	int			texx;
	double		step;
	double		texpos;
	int			texy;
	int			color;
}				t_wall;


typedef struct	s_game
{
	//사용자의 위치
	double		posx;
	double		posy;
	//플레이어의 초기 방향벡터 (카메라 평면의 수직)
	double		dirx;
	double		diry;
	//카메라평면 (왜 X,Y 두개지?)
	double		planex;
	double		planey;
	
	t_wall		wall;
}				t_game;



typedef struct	s_info
{
	void		*mlx;
	void		*win;
	//save opt
	int			save_opt;
	
	//잡기들
	t_etc		etc;
	t_img		img;
	t_config	config;
	t_game		game;
	int			spritenum; //cub3d에 5번 info->spritenum
	t_map		map;
	t_sprite	*sprite; //cub3d 7번

	int			**screen; //3번
	int			**texture; //5번

	double		zBuffer[1024]; //벽 캐스팅에서 잰 거리를 저장하고 스프라이트 구현에 사용

}				t_info;

void			ready_screen(t_info *info);
void			ready_texture(t_info *info);
void			ready_image(t_info *info);
void			check_sprite(t_info *info, t_map *map);
void			game_init(t_info *info);

void			set_etc(t_info *info);

void			load_texture(t_info *info);
void			load_image(t_info *info, int *texture, char *path, t_img *img);

void			config_to_game(t_info *info, t_game *game, t_map *map);


void			floor_ceiling_raycast(t_info *info);
void			wall_raycast(t_info *info);
#endif
