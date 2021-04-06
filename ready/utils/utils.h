/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:37:33 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/06 14:37:34 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include <string.h>

void	ft_reset(int **buf, int row, int column);
int		**ft_make_2darray(int row, int column);
void	ft_arraycpy(int *dest, int *src, unsigned int n);
int		**ft_2d_malloc(int row, int column);


#endif
