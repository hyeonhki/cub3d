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

static int check(t_map *map, int i, int j, int dir)
{
	if ((dir == 8) && i <= 0)
		return (0);
	if ((dir == 9) && (i <= 0 || j >= map->column - 1))
		return (0);
	if ((dir == 6) && j >= map->column - 1)
		return (0);
	if ((dir == 3) && (j >= map->column - 1 || i >= map->row - 1))
		return (0);
	if ((dir == -8) && i >= map->row - 1)
		return (0);
	if ((dir == -9) && (i >= map->row - 1 || j <= 0))
		return (0);
	if ((dir == -6) && j <= 0)
		return (0);
	if ((dir == -3) && (j <= 0 || i <= 0))
		return (0);
	return (1);
}

int move_EW(t_map *map, int *i, int *j, int *dir, int cvt)
{
	if (check(map, *i, *j, 8 * cvt) && map->w_map[*i - (1 * cvt)][*j] == '1')
		{
			*i -= (1 * cvt);
			*dir = 8 * cvt;
		}
	else if (check(map, *i, *j, 9 * cvt) && map->w_map[*i - (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j += (1 * cvt);
			*dir = 9 * cvt;
		}
	else if (check(map, *i, *j, 6 * cvt) && map->w_map[*i][*j + (1 * cvt)] == '1')
		{
			*j += (1 * cvt);
			*dir = 6 * cvt;
		}
	else if (check(map, *i, *j, 3 * cvt) && map->w_map[*i + (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i += (1 * cvt);
			*j += (1 * cvt);
			*dir = 3 * cvt;
		}
	else if (check(map, *i, *j, -8 * cvt) && map->w_map[*i + (1 * cvt)][*j] == '1')
		{
			*i += (1 * cvt);
			*dir = -8 * cvt;
		}
	else
		return (0);
	return (1);
}

// N : cvt 1, S : cvt -1, dir = 8;
int move_NS(t_map *map, int *i, int *j, int *dir, int cvt)
{
	if (check(map, *i, *j, -6 * cvt) && map->w_map[*i][*j - (1 * cvt)] == '1')
		{
			*j -= (1 * cvt);
			*dir = -6 * cvt;
		}
	else if (check(map, *i, *j, -3 * cvt) && map->w_map[*i - (1 * cvt)][*j - (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j -= (1 * cvt);
			*dir = -3 * cvt;
		}
	else if (check(map, *i, *j, 8 * cvt) && map->w_map[*i - (1 * cvt)][*j] == '1')
		{
			*i -= (1 * cvt);
			*dir = 8 * cvt;
		}
	else if (check(map, *i, *j, 9 * cvt) && map->w_map[*i - (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j += (1 * cvt);
			*dir = 9 * cvt;
		}
	else if (check(map, *i, *j, 6 * cvt) && map->w_map[*i][*j + (1 * cvt)] == '1')
		{
			*j += (1 * cvt);
			*dir = 6 * cvt;
		}
	else
		return (0);
	return (1);
}
// NE : cvt 1, 9 SW : cvt -1, -9
int move_NESW(t_map *map, int *i, int *j, int *dir, int cvt)
{
	if (check(map, *i, *j, -3 * cvt) && map->w_map[*i - (1 * cvt)][*j - (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j -= (1 * cvt);
			*dir = -3 * cvt;
		}
	else if (check(map, *i, *j, 8 * cvt) && map->w_map[*i - (1 * cvt)][*j] == '1')
		{
			*i -= (1 * cvt);
			*dir = 8 * cvt;
		}
	else if (check(map, *i, *j, 9 * cvt) && map->w_map[*i - (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j += (1 * cvt);
			*dir = 9 * cvt;
		}
	else if (check(map, *i, *j, 6 * cvt) && map->w_map[*i][*j + (1 * cvt)] == '1')
		{
			*j += (1 * cvt);
			*dir = 6 * cvt;
		}
	else if (check(map, *i, *j, 3 * cvt) && map->w_map[*i + (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i += (1 * cvt);
			*j += (1 * cvt);
			*dir = 3 * cvt;
		}
	else
		return (0);
	return (1);
}
//NW : -3, cvt 1 SE : 3, cvt -1
int move_NWSE(t_map *map, int *i, int *j, int *dir, int cvt)
{
	if (check(map, *i, *j, -9 * cvt) && map->w_map[*i + (1 * cvt)][*j - (1 * cvt)] == '1')
		{
			*i += (1 * cvt);
			*j -= (1 * cvt);
			*dir = -9 * cvt;
		}
	else if (check(map, *i, *j, -6 * cvt) && map->w_map[*i][*j - (1 * cvt)] == '1')
		{
			*j -= (1 * cvt);
			*dir = -6 * cvt;
		}
	else if (check(map, *i, *j, -3 * cvt) && map->w_map[*i - (1 * cvt)][*j - (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j -= (1 * cvt);
			*dir = -3 * cvt;
		}
	else if (check(map, *i, *j, 8 * cvt) && map->w_map[*i - (1 * cvt)][*j] == '1')
		{
			*i -= (1 * cvt);
			*dir = 8 * cvt;
		}
	else if (check(map, *i, *j, 9 * cvt) && map->w_map[*i - (1 * cvt)][*j + (1 * cvt)] == '1')
		{
			*i -= (1 * cvt);
			*j += (1 * cvt);
			*dir = 9 * cvt;
		}
	else
		return (0);
	return (1);
}

int map_check_clock(t_map *map, int *i, int *j, int start)
{
	int dir;
	int ret;

	dir = 6;
	move_NS(map, i, j, &dir, -1);
	while (!(*i == 0 && *j == start))
	{
		if (dir == 6)
			ret = move_EW(map, i, j, &dir, 1);
		else if (dir == -6)
			ret = move_EW(map, i, j, &dir, -1);
		else if (dir == 8)
			ret = move_NS(map, i, j, &dir, 1);
		else if (dir == -8)
			ret = move_NS(map, i, j, &dir, -1);
		else if (dir == 9)
			ret = move_NESW(map, i, j, &dir, 1);
		else if (dir == -9)
			ret = move_NESW(map, i, j, &dir, -1);
		else if (dir == -3)
			ret = move_NWSE(map, i, j, &dir, 1);
		else if (dir == 3)
			ret = move_NWSE(map, i, j, &dir, -1);
		if (ret == 0)
			return (0);
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
	if (!(map_check_clock(map, &i, &j, start)))
		return (0);
///	if (!(player_check(map, &i, &j, start)))
///		return (0);
	return (1);
}