/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 09:31:11 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/06 09:31:34 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <math.h>
#include "../mlx/mlx.h"
#include "../config/config.h"

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17

typedef struct s_img
{
	void *img;
	int *data;

	int size_l;
	int bpp;
	int endian;
	int img_width;
	int img_height;

}	t_img;

typedef struct s_info
{
	t_img img;
	t_config config;

	double posX;
	double posY;

	double dirX;
	double dirY;

	double planeX;
	double planeY;

	void *mlx;
	void *win;

	int **screen;
	int **texture;

}	t_info;

#endif
