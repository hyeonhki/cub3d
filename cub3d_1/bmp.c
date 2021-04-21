/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:52:21 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/21 14:52:21 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static int
	write_bmp_header(int fd, int filesize, t_info *info)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = info->map.width;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = info->map.height;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

static int
	get_color(t_info *info, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(info->img.data
			+ (info->map.width * (info->map.height - 1 - y))
			+ (x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int
	write_bmp_data(int file, t_info *info, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = 0;
	while (i < (int)info->map.height)
	{
		j = 0;
		while (j < (int)info->map.width)
		{
			color = get_color(info, j, i);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
 
int save_bmp(t_info *info)
{
	int filesize;
	int file;
	int pad;

	pad = (4 - (info->map.width * 3) % 4 ) % 4;
	printf("pad : %d\n",pad);
	filesize = 54 + (3 * (info->map.width) * info->map.height);
	printf("check : %d, filesize : %d\n",filesize % 4,filesize);
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
			return (0);
	if (!write_bmp_header(file, filesize, info))
		return (0);
	if (!write_bmp_data(file, info, pad))
		return (0);
	close(file);
	return (1);
}