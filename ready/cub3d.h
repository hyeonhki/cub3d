/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 08:51:18 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/06 08:51:21 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include "config/config.h"
#include "game/game.h"
#include "keycode.h"
#include "utils/utils.h"

#define mapwidth 24
#define mapheight 24

int main_loop(t_info *info);
int	key_press(int key, t_info *info, t_config *config);



#endif
