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
#define width 1024
#define height 512

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
	//플레이어의 초기 방향벡터 (카메라 평면의 수직)
	double	dirX;
	double	dirY;
	//카메라평면 (왜 X,Y 두개지?)
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

int worldMap[mapwidth][mapheight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};


void	calc(t_info *info)
{
	//FLOOR CASTING
	for(int y = 0; y < height; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = info->dirX - info->planeX;
		float rayDirY0 = info->dirY - info->planeY;
		float rayDirX1 = info->dirX + info->planeX;
		float rayDirY1 = info->dirY + info->planeY;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - height / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * height;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / width;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / width;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = info->posX + rowDistance * rayDirX0;
		float floorY = info->posY + rowDistance * rayDirY0;

		for(int x = 0; x < width; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(texwidth * (floorX - cellX)) & (texwidth - 1);
			int ty = (int)(texheight * (floorY - cellY)) & (texheight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;

			int color;

			// floor
			color = info->texture[floorTexture][texwidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			info->buf[y][x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = info->texture[ceilingTexture][texwidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			info->buf[height - y - 1][x] = color;
		}
	}

	//벽 캐스팅
	for (int x = 0; x < width; x ++)
	{
		//카메라가 평면에서 차지하는 x좌표 (-1 ~ 1)
		double cameraX = 2 * x / (double)width - 1; 
		//cameraX를 통해 광선의 방향을 계산

		//rayDir 는 광선의 방향벡터
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX; 
		//광선의 방향벡터는 방햑벡터 + 카메라평면 * 배수로 계산된다.
		//방햑벡터야 카메라평면의 수직이니 당연히 더해서 계산 가능

		//mapX, mapY는 현재 광선의 위치
		//광선이 있는 한 칸이다.
		//광선이 맵상 어느칸에 있는지, 어디쯤 있는지까지 알 수 있지만 int로 간단하게 표기
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//시작점 ~ 첫번째 x or y면을 만나는 점까지의 광선의 이동거리
		double sideDistX;
		double sideDistY;

		//첫번째 x or y면 부터 바로 다음 x or y 면까지의 광선 이동거리
		//한번 찾으면 계속 동일한 값을 가진다.
		double deltaDistX = fabs(1 / rayDirX); //abs대신 fabs
		double deltaDistY = fabs(1 / rayDirY);

		//나중에 광선의 이동거리를 계산하는 데 사용
		double perpWallDist;

		//DDA알고리즘을 위해 사용
		//광선의 방향에 따라 어느 방향으로 건너뛰는 지 달라지는데 그 정보를 저장
		//+1, -1로 저장된다. 추후 설명
		int stepX;
		int stepY;

		//마지막으로 벽의 x면 또는 y면과 부딪쳤는지 여부에 따라 루프를 종료할지 결정한다
		//hit은 벽과 부딪힌 여부(루프 종료)
		//부딪힌 곳이 x면이냐 y면이냐에 따 side값 0, 1
		int hit = 0;
		int side;

		//광선의 x방향이 양수라면 stepx = +1, 아니면 - 1
		//y방향도
		//sideDist는 시작점에서 첫번째 x , y 면을 만나는 점까지의 광선의 이동거리
		if (rayDirX < 0)
		{
			stepX = -1;
			//double		double		int(info->posX)
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}
		
		//DDA 알고리즘 시작
		//벽에 부딪힐 때 까지 반복! 한칸씩!
		//벽에 부딪히면 그만(hit == 1)
		//x 면에 부딪히는 거리와 y면에 부딪히는 거리 계산해서 한칸씩만 이동함
		//정수형 mapX,Y 변수에 +1 씩 더해서 다음칸이 벽이나 물체인지 마지막에 확인하고 hit 넣어줌
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
			//DDA완료를 통해 광선의 시작점에서 벽까지의 이동거리 계산완료
		}
		//어안렌즈 효과의 해결
		//보정코드 추가 없이 방지하는 방법
		//perpwalldist는 광선의 이동거리(수직거리)
		if (side == 0) //처음으로 부딪힌 면이 x면이라면, 광선이 x 방향으로 몇 칸 갔는 지 나타내는 수
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else //y면에 부딪혔을 때
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		//화면까지의 수직거리를 통해 그려낼 벽 길이 잡기
		int lineheight = (int)(height / perpWallDist);

		//벽 그릴 시작 y위치
		int drawStart = -lineheight / 2 + height / 2;
		// 0 이하면 화면맨끝부터 벽
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineheight / 2 + height / 2;
		if (drawEnd >= height)
			drawEnd = height - 1;

		// 텍스터 계산
		int texNum = worldMap[mapX][mapY] - 1;
		//1을 빼주는 이유는 지도에 0부터 8까지로 채워놨는데
		//0은 없는 거고 1부터 8까지 텍스처라 1빼서 0부터 7까지로

		double wallX; //광선이 부딪힌 벽의 정확한 위치
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		//floor는 내림함수
		wallX -= floor(wallX);
		//이러면 wallX는 1이하 소수점만 남는다?
		//텍스처의 x좌표 나타내기
		int texX = (int)(wallX * (double)texwidth);
		if (side == 0 && rayDirX > 0)
			texX = texwidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texwidth - texX - 1;
		
		double step = 1.0 * texheight / lineheight;
		double texPos = (drawStart - height / 2 + lineheight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (texheight - 1); //갑자기 비트연산 &?
			texPos += step;

			int color = info->texture[texNum][texheight * texY + texX];

			if (side == 1)
				color = (color >> 1) & 8355711;

			info->buf[y][x] = color;
		}


		//FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

		//4 different wall directions possible
		if(side == 0 && rayDirX > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if(side == 0 && rayDirX < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if(side == 1 && rayDirY > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0) drawEnd = height; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(int y = drawEnd + 1; y < height; y++)
		{
			currentDist = height / (2.0 * y - height); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorXWall + (1.0 - weight) * info->posX;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * info->posY;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * texwidth) % texwidth;
			floorTexY = (int)(currentFloorY * texheight) % texheight;

			int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
			int floorTexture;
			if(checkerBoardPattern == 0) floorTexture = 3;
			else floorTexture = 4;

			//floor
			info->buf[y][x] = (info->texture[floorTexture][texwidth * floorTexY + floorTexX] >> 1) & 8355711;
			//ceiling (symmetrical!)
			info->buf[height - y][x] = info->texture[6][texwidth * floorTexY + floorTexX];
		}
	}
}

void	draw(t_info *info)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			info->img.data[y * width + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return (0);
}

void	ft_arraycpy(int *dest, int *src, unsigned int n)
{
	int i;
	
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
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
	//ft_arraycpy(texture, img->data, img->img_height * img->img_width);
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	//새로운 이미지 구조체를 생성
	t_img	img;
	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
}

int	key_press(int key, t_info *info)
{
	if (key == KEY_W)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == KEY_S)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	//rotate to the right
	if (key == KEY_D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

int **ft_2d_malloc(int row, int column)
{
	int **temp;
	if (!(temp = (int **)malloc(sizeof(int *) * row)))
		return (0);
	int i;

	i = 0 ;
	while (i < row)
	{
		temp[i] = (int *)malloc(sizeof(int) * column);
		i++;
	}
	return (temp);
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
	info.texture = ft_2d_malloc(8, texheight * texwidth);
//	if (!(info.texture = (int **)malloc(sizeof(int *) * 8)))
//		return (-1);
//	for (int i = 0; i < 8; i++)
//	{
//		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texheight * texwidth))))
//			return (-1);
//	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < texheight * texwidth; j++)
		{
			info.texture[i][j] = 0;
		}
	}
	load_texture(&info);
	info.moveSpeed = 0.15;
	info.rotSpeed = 0.15;

	info.win = mlx_new_window(info.mlx, width, height, "mlx");
	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);
	//기본 유지되는 hook (계산하고 그리기)
	mlx_loop_hook(info.mlx, &main_loop, &info);
	//이벤트를 받는 hook
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);

	mlx_loop(info.mlx);
}