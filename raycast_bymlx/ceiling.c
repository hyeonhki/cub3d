#include "../mlx/mlx.h"

#include "keycode.h"

#include <math.h>
#include <string.h>
#include <stdio.h> //왜?
#include <stdlib.h>

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17

#define texwidth 64
#define texheight 64
//지도 크기
#define mapwidth 24
#define mapheight 24
//스크린 크기
#define width 640
#define height 480

typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

typedef struct s_info
{
	//사용자의 위치
	double	posX;
	double	posY;

	double	dirX;
	double	dirY;
	
	double	planeX;
	double	planeY;

	void	*mlx;
	void	*win;
	
	t_img	img;
	
	int		buf[height][width];
	int		**texture;
	
	double	moveSpeed;
	double	rotSpeed;
}	t_info;


int main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{

	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	//xpm의 임지 변환, width와 height에 자동으로 너비와 높이가 저장된다.
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	//생성된 이미지의 정보를 리턴해서 수정 등에 용이하게
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x ++)
		{
			//생성된 xpm데이터를 담은 이미지 데이터를 texture로 옮김
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	//새로운 이미지 구조체를 생성
	t_img	img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
}



int main(void)
{
	t_info info;
	info.mlx = mlx_init();

	info.posX = 22.0;
	info.posY = 11.5;
	info.dirX = -1.0;
	info.dirY= 0.0;
	info.planeX = 0.0;
	info.planeY = 0.66;

//스크린 버퍼의 초기화
	for (int i = 0; i <height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			info.buf[i][j] = 0;
		}
	}

	if (!(info.texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	for (int i = 0; i < 8; i++)
	{
		if (!(info.texture[i] = (int *)malloc(sizeof(int))))
			return (-1);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < texheight * texwidth; j++)
		{
			info.texture[i][j] = 0;
		}
	}

	load_texture(&info);

	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;

	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

	//기본 유지되는 hook (계산하고 그리기)
	mlx_loop_hook(info.mlx, &main_loop, &info);
	//이벤트를 받는 hook
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);

	mlx_loop(info.mlx);
}