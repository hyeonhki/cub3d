/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:19:17 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/18 13:19:17 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

//E = cvt 1, W = cvt -1

static int check(t_map *map, int i, int j)
{
	if (i <= 0)
		return (0);
	if (i >= 13)
		return (0);
	if (j <= 0)
		return (0);
	if (j >= 32)
		return (0);
	return (1);
}

int move_EW(t_map *map, int *i, int *j, int *direct, int cvt)
{
	if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j] == '1')
		{
			*i -= (1 * cvt);
			*direct = 8 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j += (1 * cvt);
			*direct = 9 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i][*j + (1 * cvt)] == '1')
		{
			*j += (1 * cvt);
			*direct = 6 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i + (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j += (1 * cvt);
			*direct = 3 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i + (1 * cvt)][*j] == '1')
		{
			*i += (1 * cvt);
			*direct = -8 * cvt;
		}
	else
		return (0);
	return (1);
}

// N : cvt 1, S : cvt -1, direct = 8;
int move_NS(t_map *map, int *i, int *j, int *direct, int cvt)
{
	if (check(map, *i, *j) && map->w_map[*i][*j - (1 * cvt)] == '1')
		{
			*j -= (1 * cvt);
			*direct = -6 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j - (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j -= (1 * cvt);
			*direct = -3 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j] == '1')
		{
			*i -= (1 * cvt);
			*direct = 8 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j += (1 * cvt);
			*direct = 9 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i][*j + (1 * cvt)] == '1')
		{
			*j += (1 * cvt);
			*direct = 6 * cvt;
		}
	else
		return (0);
	return (1);
}
// NE : cvt 1, 9 SW : cvt -1, -9
int move_NESW(t_map *map, int *i, int *j, int *direct, int cvt)
{
	if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j - (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j -= (1 * cvt);
			*direct = -3 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j] == '1')
		{
			*i -= (1 * cvt);
			*direct = 8 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j += (1 * cvt);
			*direct = 9 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i][*j + (1 * cvt)] == '1')
		{
			*j += (1 * cvt);
			*direct = 6 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i + (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i += (1 * cvt);
			*j += (1 * cvt);
			*direct = 3 * cvt;
		}
	else
		return (0);
	return (1);
}
//NW : -3, cvt 1 SE : 3, cvt -1
int move_NWSE(t_map *map, int *i, int *j, int *direct, int cvt)
{
	if (check(map, *i, *j) && map->w_map[*i + (1 * cvt)][*j - (1 * cvt)] == '1')
		{
			*i += (1 * cvt);
			*j -= (1 * cvt);
			*direct = -9 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i][*j - (1 * cvt)] == '1')
		{
			*j -= (1 * cvt);
			*direct = -6 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j - (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j -= (1 * cvt);
			*direct = -3 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j] == '1')
		{
			*i -= (1 * cvt);
			*direct = 8 * cvt;
		}
	else if (check(map, *i, *j) && map->w_map[*i - (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j += (1 * cvt);
			*direct = 9 * cvt;
		}
	else
		return (0);
	return (1);
}

int map_check_clock(t_map *map, int **w_map, int *i, int *j, int start)
{
	int direct;
	int ret;

	direct = 6;
	printf("map[%d][%d] : %c\n",*i,*j,w_map[*i][*j]);
	move_EW(map, i, j, &direct, 1);
	printf("map[%d][%d] : %c\n",*i,*j,w_map[*i][*j]);
	while (!(*i == 0 && *j == start))
	{
		if (direct == 6)
			ret = move_EW(map, i, j, &direct, 1);
		else if (direct == -6)
			ret = move_EW(map, i, j, &direct, -1);
		else if (direct == 8)
			ret = move_NS(map, i, j, &direct, 1);
		else if (direct == -8)
			ret = move_NS(map, i, j, &direct, -1);
		else if (direct == 9)
			ret = move_NESW(map, i, j, &direct, 1);
		else if (direct == -9)
			ret = move_NESW(map, i, j, &direct, -1);
		else if (direct == -3)
			ret = move_NWSE(map, i, j, &direct, 1);
		else if (direct == 3)
			ret = move_NWSE(map, i, j, &direct, -1);
		printf("direct : %d, map[%d][%d] : %c\n",direct,*i,*j,w_map[*i][*j]);
		if (ret == 0)
		{
			printf("map error\n");
			return (0);
		}
	}
	return (1);
}

int valid_wall_check(t_map *map, int **w_map)
{
	int i;
	int j;
	int start;
	
	i = 0;
	j = 0;
	//첫 시작 점 잡기
	while (w_map[0][j] != '1')
		j++;
	start = j;
	if (!(map_check_clock(map, w_map, &i, &j, start)))
		return (0);
	return (1);
}