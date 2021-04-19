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

void maxlen_map(char *maptext, t_map *map)
{
	int len;
	int max;
	int cnt;
	int i;

	i = 0;
	max = 0;
	len = 0;
	cnt = 0;
	while (maptext[i] != '\0')
	{
		if (maptext[i] == '\n')
		{
			cnt += 1;
			if (len > max)
				max = len;
			len = -1;
		}
		len++;
		i++;
	}
	map->column = max;
	map->row = cnt;
}

void substitution_space(char **maptext)
{
	char *ret;
	int i;

	i = 0;
	ret = *maptext;
	while (ret[i] != '\0')
	{
		if (ret[i] == ' ')
			ret[i] = '0';
		i++;
	}
}

void map_init(t_map *map, char *maptext, int height)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
//	substitution_space(&maptext); //추후 삭제해야함
	while (i < height)
	{
		k = 0;
		while (maptext[j] != '\n')
		{
			map->w_map[i][k] = maptext[j];
			k++;
			j++;
		}
		if (maptext[j] == '\n')
		{
			j++;
		}
		i++;
	}
}

void	ft_re2set(t_map *map, int row, int column)
{
	int		i;
	int		j;

	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < column)
		{
			map->w_map[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void set_map(t_map *map)
{
	map->w_map = ft_2d_malloc(map->row, map->column);
	ft_re2set(map, map->row, map->column);
}

int parse_map(t_map *map, char *maptext)
{
	maxlen_map(maptext, map);
	set_map(map); //2차원 배열 할당 및 초기화/
//	if (!valid_wall_check(map, maptext))
//		return (0);
	map_init(map, maptext, map->row); // 한줄씩 복사해서 붙여넣기
	return (1);
}

int	read_color(char *line, int *color, int *cnt)
{
	int rgb;
	int i;

	if ((*cnt)++ != 0)
		return (0);
	rgb = 0;
	i = 2;
	while (line[i] == ' ')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
		rgb = rgb * 10 + (line[i++] - '0');
	*color = rgb * 256 * 256;
	if (line[i] == ',')
		i += 1;
	else
		return (0);
	while (line[i] == ' ')
		i++;
	rgb = 0;
	while (line[i] >= '0' && line[i] <= '9')
		rgb = rgb * 10 + (line[i++] - '0');
	*color += rgb * 256;
	if (line[i] == ',')
		i += 1;
	else
		return (0);
	while (line[i] == ' ')
		i++;
	rgb = 0;
	while (line[i] >= '0' && line[i] <= '9')
		rgb = rgb * 10 + (line[i++] - '0');
	*color += rgb;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int read_size(t_map *map, char *line)
{
	int i;

	if (map->r_check++ != 0)
		return (0);
	i = 0;
	if (line[i] == 'R' && line[i+1] == ' ')
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

int parse_texture_path(char **path, char *line)
{
	int i;

	i = 0;
	if (*path != 0)
		return (0);
	if (line[i] == 'N' && line[i+1] == 'O')
		i += 2;
	else if (line[i] == 'S' && line[i+1] == 'O')
		i += 2;
	else if (line[i] == 'W' && line[i+1] == 'E')
		i += 2;
	else if (line[i] == 'E' && line[i+1] == 'A')
		i += 2;
	else if (line[i] == 'S' && line[i+1] == ' ')
		i += 2;
	else
		return (0);
	while (line[i] == ' ')
		i++;
	*path = line + i;
	return (1);
}

int map_order_check(t_map *map)
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

int line_check(t_map *map,char *line, char **maptext)
{
	if (*line == 'R')
		return (read_size(map, line));
	else if (*line == 'N')
		return (parse_texture_path(&map->no, line));
	else if (*line == 'S')
		if (*(line + 1) == 'O')
			return (parse_texture_path(&map->so, line));
		else
			return (parse_texture_path(&map->sp, line));
	else if (*line == 'W')
		return (parse_texture_path(&map->we, line));
	else if (*line == 'E')
		return (parse_texture_path(&map->ea, line));
	else if (*line == 'F')
		return (read_color(line, &map->fl_color, &map->fl_check));
	else if (*line == 'C')
		return (read_color(line, &map->ce_color, &map->ce_check));
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

int	is_player(int p)
{
	if (p == 'N' || p == 'S' || p == 'W' || p == 'E')
		return (1);
	else
		return (0);
}

void player_init(t_map *map)
{
	int i;
	int j;
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			if (is_player(map->w_map[i][j]))
			{
				map->player.x = i;
				map->player.y = j;
				map->player.dir = map->w_map[i][j];
				map->w_map[i][j] = 0;
			}
			j++;
		}
		i++;
	}
}

int error(void)
{
	printf("Error\n");
	return (0);
}

void reset_params(t_map *map)
{
	map->r_check = 0;
	map->no = 0;
	map->so = 0;
	map->we = 0;
	map->ea = 0;
	map->sp = 0;
	map->ce_check = 0;
	map->fl_check = 0;
}
int check_NSWE(int c, int *cnt)
{
	if (*cnt != 0)
		return (0);
	if (c == 'N')
	{
		*cnt += 1;
		return (1);
	}
	if (c == 'W')
	{
		*cnt += 1;
		return (1);
	}
	if (c == 'S')
	{
		*cnt += 1;
		return (1);
	}
	if (c == 'E')
	{
		*cnt += 1;
		return (1);
	}
	return (0);
}

int check_012(int c)
{
	if (c >= '0' && c <= '2')
		return (1);
	if (c == ' ')
		return (1);
	else
		return (0);
}

int map_element_check(t_map *map)
{
	int i;
	int j;
	int c;
	int cnt;

	c = 0;
	cnt = 0;
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->column)
		{
			c = map->w_map[i][j];
			if (!(check_NSWE(c, &cnt) || check_012(c)))
				return (0);
			j++;
		}
		i++;
	}
	if (cnt == 0)
		return (0);
	return (1);
}

int map_check(t_map *map)
{
	if (map_element_check(map) == 0)
		return (0);
	return (1);
}

int config_map(t_map *map, char *path)
{
	int fd;
	int ret;
	char *line;
	char *maptext;

	reset_params(map);
	maptext = 0;
	fd = open(path, O_RDONLY);
	while ((ret = get_next_line(fd, &line) > 0))
	{
		if (!line_check(map, line, &maptext))
			return (error());
			
	}
	//두번 해야지 마지막줄까지나온다. ret=0 으로 EOF 되어서 반복문이 종료될 경우, line에 마지막 줄이 남아있기 때문에!
	line_check(map, line, &maptext); //막줄 저장용
	if (!parse_map(map, maptext))
		return (error());
	if (!map_check(map))
		return (error());
	if (!valid_wall_check(map, map->w_map))
		return (error());
	player_init(map);
	return (1);
}
