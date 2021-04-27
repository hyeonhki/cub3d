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
# define CONFIG_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../gnl/get_next_line.h"
# include "../utils/utils.h"

typedef struct	s_player
{
	int			x;
	int			y;
	int			dir;
}				t_player;

typedef struct	s_map
{
	int			i;
	int			j;
	int			flag;

	int			**w_map;
	int			**mask;

	int			width;
	int			height;
	int			r_check;
	int			fl_check;
	int			ce_check;

	int			row;
	int			column;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sp;

	int			fl_color;
	int			ce_color;
	int			rgb;

	t_player	player;
}				t_map;

typedef struct	s_config
{
	int			height;
	int			width;
	int			texwidth;
	int			texheight;
	int			texnum;
	double		movespeed;
	double		rotspeed;
}				t_config;

void			config_init(t_config *config);
int				config_map(t_map *map, char *path);
int				valid_wall_check(t_map *map, int **w_map);
void			valid_map_check(t_map *map, int i, int j);
int				line_check(t_map *map, char *line, char **maptext);
void			player_init(t_map *map);
int				map_element_check(t_map *map);
int				parse_map(t_map *map, char *maptext);
#endif
