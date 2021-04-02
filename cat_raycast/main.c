#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../mlx/mlx.h"
#include "../keycode.h"

//EVENT_KYE
#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_EXIT 17

// 화면의 크기
#define WIN_W 1024
#define WIN_H 512

// 블록의 크기
#define TILE_SIZE 64

// 지도
#define ROWS 8
#define COLS 8

//얜뭐지?
#define TO_COORD(X, Y) ((int)floor(Y) * WIN_W/2 + (int)floor(X))

// 플레이어 구조체
typedef struct s_player
{
	float	x;
	float	y;
	int		color;
}	t_player;

// 이미지 구조체
typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}	t_img;

// 화면 구조체
typedef struct s_info
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_img		img;

	int map[ROWS][COLS];
}	t_info;

void map_init(t_info *info)
{
	int		map[8][8] = {
	{1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1},
	{1,0,0,1,0,0,0,1},
	{1,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1}};
	memcpy(info->map, map, sizeof(int) * ROWS * COLS);
}

void	init_player(t_info *info)
{
	//좌표에 색상 픽셀 입력
	mlx_pixel_put(info->mlx, info->win, info->player.x, info->player.y, info->player.color);
}

void	move_ready(t_info *info)
{
	int black;
	black = 0x000000;
	mlx_pixel_put(info->mlx, info->win, info->player.x, info->player.y, black);
}

int		command_player(int key, t_info *info)
{
	if (key == KEY_A)
		info->player.x -= 5;
	else if (key == KEY_D)
		info->player.x += 5;
	else if (key == KEY_W)
		info->player.y -= 5;
	else if (key == KEY_S)
		info->player.y += 5;
	else if (key == KEY_ESC)
		exit(0);
	return (0);
}

void draw_line(t_info *game, double x1, double y1, double x2, double y2)
{
	double deltaX;
	double deltaY;
	double step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		game->img.data[TO_COORD(x1, y1)] = 0xb3b3b3;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void draw_lines(t_info *game)
{
	int i;
	int j;

	i = 0; //세로줄
	while (i < COLS)
	{
		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, WIN_H);
		i++;
	}
	draw_line(game, COLS * TILE_SIZE - 1, 0, COLS * TILE_SIZE - 1, WIN_H);
	j = 0; //가로줄
	while (j < ROWS)
	{
		draw_line(game, 0, j * TILE_SIZE, WIN_W/2, j * TILE_SIZE);
		j++;
	}
	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIN_W/2, ROWS * TILE_SIZE - 1);
}

void draw_rectangle(t_info *info, int x, int y)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			//512 = WIDTH
			info->img.data[(y + i) * 512 + x + j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void draw_rectangles(t_info *info)
{
	int i;
	int j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (info->map[i][j] == 1)
				draw_rectangle(info, j, i);
			j++;
		}
		i++;
	}
}

int main_loop(t_info *info)
{
	draw_rectangles(info);
	draw_lines(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
	init_player(info);
	return (0);
}

int main()
{
	t_info		info;
	

	//지도 넣기
	map_init(&info);
	//창 띄우기
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WIN_W, WIN_H, "cat");

	//플레이어의 위치 및 색상 초기화
	info.player.x = 300;
	info.player.y = 300;
	info.player.color = 0xF0F000;

	//이미지 받을 버퍼 생성
	info.img.img = mlx_new_image(info.mlx, 512, 512);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.bpp);

	//계속 표시해야할 지도, 위치 등 이벤트를 통해 값이 변화하더래도 계속 나와야할 것들은 Loop_hook
	mlx_loop_hook(info.mlx, &main_loop, &info);

	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &command_player, &info);
	mlx_loop(info.mlx);
}