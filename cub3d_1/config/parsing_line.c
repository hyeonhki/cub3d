/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:53:15 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/23 12:53:16 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int		read_size(t_map *map, char *line)
{
	int		i;

	if (map->r_check++ != 0)
		return (0);
	i = 0;
	if (line[i] == 'R' && line[i + 1] == ' ')
		i += 2;
	else
		return (0);
	map->width = 0;
	map->height = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
		map->width = map->width * 10 + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
		map->height = map->height * 10 + (line[i++] - '0');
	if (line[i] != '\0')
		return (0);
	return (1);
}

int		read_color(t_map *map, char *line, int *color, int *cnt)
{
	if ((*cnt)++ != 0)
		return (0);
	map->j = 3;
	map->i = 2;
	while (map->j > 0)
	{
		map->rgb = 0;
		while (line[map->i] == ' ')
			map->i++;
		while (line[map->i] >= '0' && line[map->i] <= '9')
			map->rgb = map->rgb * 10 + (line[map->i++] - '0');
		*color += map->rgb * pow(256, (map->j) - 1);
		if (map->j != 1)
		{
			if (line[map->i] == ',')
				map->i += 1;
			else
				return (0);
		}
		map->j--;
	}
	if (line[map->i] != '\0')
		return (0);
	return (1);
}

int		parse_texture_path(t_map *map, char *line)
{
	int		i;
	char	**path;

	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O')
		path = &map->no;
	else if (line[i] == 'S' && line[i + 1] == 'O')
		path = &map->so;
	else if (line[i] == 'W' && line[i + 1] == 'E')
		path = &map->we;
	else if (line[i] == 'E' && line[i + 1] == 'A')
		path = &map->ea;
	else if (line[i] == 'S' && line[i + 1] == ' ')
		path = &map->sp;
	else
		return (0);
	i += 2;
	while (line[i] == ' ')
		i++;
	if (*path != 0)
		return (0);
	*path = line + i;
	return (1);
}

int		map_order_check(t_map *map)
{
	if (map->r_check == 0)
		return (0);
	else if (map->no == 0)
		return (0);
	else if (map->so == 0)
		return (0);
	else if (map->we == 0)
		return (0);
	else if (map->ea == 0)
		return (0);
	else if (map->sp == 0)
		return (0);
	else if (map->ce_check == 0)
		return (0);
	else if (map->fl_check == 0)
		return (0);
	return (1);
}

int		line_check(t_map *map, char *line, char **maptext)
{
	if (*line == 'R')
		return (read_size(map, line));
	else if (*line == 'N' || *line == 'S' || *line == 'W' \
	|| *line == 'W' || *line == 'E')
		return (parse_texture_path(map, line));
	else if (*line == 'F')
		return (read_color(map, line, &map->fl_color, &map->fl_check));
	else if (*line == 'C')
		return (read_color(map, line, &map->ce_color, &map->ce_check));
	else if (*line >= ' ' && *line <= '9')
	{
		if (!(map_order_check(map)))
			return (0);
		*maptext = ft_strjoin(*maptext, line);
		*maptext = ft_strjoin(*maptext, "\n");
	}
	else if (*line == '\0')
		return (1);
	else
		return (0);
	return (1);
}
