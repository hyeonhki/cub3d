/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:44:12 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/22 19:44:13 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bmp.h"

unsigned char	*bmp_fileheader(t_bmp *bmp, int height, int stride)
{
	int				filesize;
	filesize = bmp->header_size + bmp->info_size + (stride * height);

	static unsigned char header[] = {
		0, 0,     /// signature
		0, 0, 0, 0, /// image file size in bytes
		0, 0, 0, 0, /// reserved
		0, 0, 0, 0, /// start of pixel array
	};

	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(filesize);
	header[3] = (unsigned char)(filesize >> 8);
	header[4] = (unsigned char)(filesize >> 16);
	header[5] = (unsigned char)(filesize >> 24);
	header[10] = (unsigned char)(bmp->header_size + bmp->info_size);
	return (header);
}

unsigned char	*bmp_infoheader(t_bmp *bmp, int height, int width)
{
	static unsigned char info[] = {0, 0, 0, 0, /// header size
		0, 0, 0, 0, /// image width
		0, 0, 0, 0, /// image height
		0, 0,     /// number of color planes
		0, 0,     /// bits per pixel
		0, 0, 0, 0, /// compression
		0, 0, 0, 0, /// image size
		0, 0, 0, 0, /// horizontal resolution
		0, 0, 0, 0, /// vertical resolution
		0, 0, 0, 0, /// colors in color table
		0, 0, 0, 0, /// important color count
	};

	info[0] = (unsigned char)(bmp->info_size);
	info[4] = (unsigned char)(width);
	info[5] = (unsigned char)(width >> 8);
	info[6] = (unsigned char)(width >> 16);
	info[7] = (unsigned char)(width >> 24);
	info[8] = (unsigned char)(height);
	info[9] = (unsigned char)(height >> 8);
	info[10] = (unsigned char)(height >> 16);
	info[11] = (unsigned char)(height >> 24);
	info[12] = (unsigned char)(1);
	info[14] = (unsigned char)(bmp->bpp * 8);
	return (info);
}

void			generate_image(unsigned char *image, t_bmp *bmp)
{
	FILE			*imagefile;
	int				i;
	unsigned char	padding[3] = {0, 0, 0};

	imagefile = fopen(bmp->filename, "wb");
	bmp->fileheader = bmp_fileheader(bmp, bmp->height, bmp->stride);
	fwrite(bmp->fileheader, 1, bmp->header_size, imagefile);
	bmp->infoheader = bmp_infoheader(bmp, bmp->height, bmp->width);
	fwrite(bmp->infoheader, 1, bmp->info_size, imagefile);
	i = bmp->height - 1;
	while (i >= 0)
	{
		fwrite(image + (i * bmp->widthinbytes), \
						bmp->bpp, bmp->width, imagefile);
		fwrite(padding, 1, bmp->paddingsize, imagefile);
		i--;
	}
	fclose(imagefile);
}

void			ready_variables(t_info *info, t_bmp *bmp)
{
	bmp->bpp = 3;
	bmp->header_size = 14;
	bmp->info_size = 40;
	bmp->filename = "bitmap.bmp";
	bmp->width = info->map.width;
	bmp->height = info->map.height;
	bmp->widthinbytes = bmp->width * bmp->bpp;
	bmp->paddingsize = (4 - (bmp->widthinbytes) % 4) % 4;
	bmp->stride = (bmp->widthinbytes) + bmp->paddingsize;
}

int				save_bmp(t_info *info)
{
	t_bmp			bmp;
	unsigned char	image[info->map.height][info->map.width][3];
	int				i;
	int				j;

	ready_variables(info, &bmp);
	i = 0;
	while (i < bmp.height)
	{
		j = 0;
		while (j < bmp.width)
		{
			image[i][j][2] = (info->screen[i][j] >> 16) & 0xFF;///red
			image[i][j][1] = (info->screen[i][j] >> 8) & 0xFF;///green
			image[i][j][0] = (info->screen[i][j]) & 0xFF; ///blue
			j++;
		}
		i++;
	}
	generate_image((unsigned char *)image, &bmp);
	printf("Image generated!!");
	return (1);
}
