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

#include "../gnl/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void maxlen_map(char *map, int *width, int *height)
{
	int len;
	int max;
	int cnt;
	int i;

	i = 0;
	max = 0;
	len = 0;
	cnt = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			cnt += 1;
			if (len > max)
				max = len;
			len = -1;
		}
		len++;
		i++;
	}
	*width = max;
	*height = cnt;
}


void parse_map(char *map)
{
	int width;
	int height;
	maxlen_map(map, &width, &height);
//	set_map(); //2차원 배열 할당 및 초기화
//	map_init(); // 한줄씩 복사해서 붙여넣기
}

void line_check(char *line, char **map)
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
		*map = ft_strjoin(*map, line);
		*map = ft_strjoin(*map, "\n");
	}
}

void config_map(char *path)
{
	int fd;
	int ret;
	char *line;
	char *map;

	map = 0;
	fd = open(path, O_RDONLY);
	while ((ret = get_next_line(fd, &line) > 0))
		line_check(line, &map);
	//두번 해야지 마지막줄까지나온다.
	line_check(line, &map);
	printf("%s\n",map);
	parse_map(map);
}
