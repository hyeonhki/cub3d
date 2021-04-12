/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:53:49 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 15:53:50 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../gnl/get_next_line.h"
#include "../utils/utils.h"

typedef struct s_player
{
	int	x;
	int	y;
	int dir;
}	t_player;


typedef struct s_map
{
	int **worldmap;

	int width;
	int height;
	
	int	row;
	int column;
	char *no;
	char *so;
	char *we;
	char *ea;

	int fl_color;
	int ce_color;

	t_player player;
} t_map;


typedef struct s_config
{
	int height; //512
	int width; //1024
	int texwidth; //64
	int texheight; //64
	int texnum;
	double	moveSpeed;
	double	rotSpeed;

}	t_config;

void config_init(t_config *config);
void config_map(t_map *map, char *path);

#endif