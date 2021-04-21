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
#define UTILS_H

void	ft_arraycpy(int *dest, int *src, unsigned int n);
int		 **ft_2d_malloc(int row, int column);
void	ft_reset(int **buf, int row, int column);
int		ft_strcmp(char *s1, char *s2);
int		error(char *str);

#endif
