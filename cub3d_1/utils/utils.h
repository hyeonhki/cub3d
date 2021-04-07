/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:02:57 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 10:02:58 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "../cub3d.h"

void	ft_arraycpy(int *dest, int *src, unsigned int n);
int **ft_2d_malloc(int row, int column);
void	ft_reset(int **buf, int row, int column);

#endif
