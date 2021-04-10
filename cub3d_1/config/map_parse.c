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
			ret[i] = '1';
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
	substitution_space(&maptext);
	while (i < height)
	{
		k = 0;
		while (maptext[j] != '\n')
		{
			map->worldmap[i][k] = maptext[j] - '0';
			printf("%d", map->worldmap[i][k]); //추후 삭제
			k++;
			j++;
		}
		if (maptext[j] == '\n')
		{
			printf("\n"); //추후삭제
			j++;
		}
		i++;
	}
}

void set_map(t_map *map)
{
	map->worldmap = ft_2d_malloc(map->row, map->column);
	ft_reset(map->worldmap, map->row, map->column);
}

void parse_map(t_map *map, char *maptext)
{
	maxlen_map(maptext, map);
	set_map(map); //2차원 배열 할당 및 초기화/	
	map_init(map, maptext, map->row); // 한줄씩 복사해서 붙여넣기
}

void line_check(char *line, char **maptext)
{
	if (*line == 'R')
		printf("R\n");
	else if (*line == 'N')
		printf("N\n");
	else if (*line == 'S')
		printf("S\n");
	else if (*line == 'W')
		printf("W\n");
	else if (*line == 'E')
		printf("E\n");
	else if (*line == 'F')
		printf("F\n");
	else if (*line == 'C')
		printf("C\n");
	else if (*line == ' ' || (*line >= '0' && *line <= '9'))
	{
		*maptext = ft_strjoin(*maptext, line);
		*maptext = ft_strjoin(*maptext, "\n");
	}
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
			if (is_player(map->worldmap[i][j]))
			{
				printf("\n%d %d\n", i , j);
			//	map->player.x = i;
			//	map->player.y = j;
			//	map->player.dir = map->worldmap[i][j];
			//	map->worldmap[i][j] = 0;
			//	printf("\n %d %d\n", map->player.dir, map->worldmap[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

void config_map(t_map *map, char *path)
{
	int fd;
	int ret;
	char *line;
	char *maptext;

	maptext = 0;
	fd = open(path, O_RDONLY);
	while ((ret = get_next_line(fd, &line) > 0))
		line_check(line, &maptext);
	//두번 해야지 마지막줄까지나온다.
	line_check(line, &maptext);
	printf("%s\n",maptext);
	parse_map(map, maptext);
	player_init(map);
}
