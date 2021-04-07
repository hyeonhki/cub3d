/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:34:44 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 09:34:45 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "keycode.h"

# include "game/game.h"
# include "utils/utils.h"
# include "config/config.h"

# include "../mlx/mlx.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	draw(t_info *info);
void	calc(t_info *info);
int main_loop(t_info *info);
int	key_press(int key, t_info *info);


#endif