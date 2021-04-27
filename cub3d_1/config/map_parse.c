/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:56:18 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/08 16:56:18 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	reset_params(t_map *map)
{
	map->r_check = 0;
	map->no = 0;
	map->so = 0;
	map->we = 0;
	map->ea = 0;
	map->sp = 0;
	map->ce_check = 0;
	map->fl_check = 0;
	map->fl_color = 0;
	map->ce_color = 0;
	map->flag = 0;
}

void	map_reset(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			if (map->w_map[i][j] == 0)
				map->w_map[i][j] = '0';
			if (map->w_map[i][j] == 2)
				map->w_map[i][j] = '2';
			j++;
		}
		i++;
	}
}

int		config_map(t_map *map, char *path)
{
	int		fd;
	int		ret;
	char	*line;
	char	*maptext;

	reset_params(map);
	maptext = 0;
	fd = open(path, O_RDONLY);
	while ((ret = get_next_line(fd, &line) > 0))
	{
		if (!line_check(map, line, &maptext))
			return (0);
	}
	line_check(map, line, &maptext);
	parse_map(map, maptext);
	if (!map_element_check(map))
		return (exit_error("map element error"));
	player_init(map);
	valid_map_check(map, map->player.x, map->player.y);
	map_reset(map);
	return (1);
}
