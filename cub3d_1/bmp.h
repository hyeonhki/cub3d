/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:37:56 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/05/01 14:37:57 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# define BYTES_PER_PIXEL	3
# define FILE_HEADER_SIZE	14
# define INFO_HEADER_SIZE	40

typedef struct		s_bmp
{
	int				bpp;
	int				header_size;
	int				info_size;
	char			*filename;

	int				width;
	int				height;

	unsigned char	*padding;
	int				paddingsize;
	int				stride;
	int				widthinbytes;

	unsigned char	*fileheader;
	unsigned char	*infoheader;

}					t_bmp;
#endif
