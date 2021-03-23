#include <stdio.h>
#include <stdlib.h>
#include "./mlx/mlx.h"

#define X_EVENT_KEY_PRESS 2	  //X11 이벤트 KEY_PRESS는 입력할 때와 입력하는 동안
#define X_EVENT_KEY_release 3 //키 땔 떼
#define X_EVENT_KEY_EXIT 17	  //윈도우 exit

#define KEY_ESC 53
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2

typedef struct s_data
{
	int x;
	int y;
} t_data;

int key_press(int keycode, t_data *data)
{
	if (keycode == KEY_A)
		data->x--;
	if (keycode == KEY_D)
		data->x++;
	if (keycode == KEY_W)
		data->y++;
	if (keycode == KEY_S)
		data->y--;
	printf("x:y = %d:%d\n", data->x, data->y);
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int key_release(int keycode, t_data *data)
{
	printf("key release : %d\n %d:%d \n", keycode, data->x, data->y);
	return (0);
}

int key_exit(int keycode, t_data *data)
{
	printf("exit");
	return (0);
}

int main()
{
	void *mlx;
	void *win;
	t_data data;
	data.x = 0;
	data.y = 0;

	mlx = mlx_init();							   //소프트웨어 디스플레이 연결
	win = mlx_new_window(mlx, 800, 600, "tester"); //윈도우 창 생성
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, key_press, &data);
	mlx_hook(win, X_EVENT_KEY_release, 0, key_release, &data);
	mlx_hook(win, X_EVENT_KEY_EXIT, 0, key_exit, &data);
	mlx_loop(mlx);
	return (0);
}
