/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 09:31:11 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/06 09:31:34 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EGINE.H
# define ENGINE.H

# include <math.h>
#include "../mlx/mlx.h"
#include "../config/config.h"

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
	double posX;
	double posY;

	double dirX;
	double dirY;

	double planeX;
	double planeY;

	void *mlx;
	void *win;

	t_img	img;

	int **buf;
	int **texture;

	double moveSpeed;
	double rotSpeed;

}	t_info;

#endif
