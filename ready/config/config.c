/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:26:05 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/06 15:26:05 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "../game/game.h"

void config_init(t_config *config)
{
	config->height = 480;
	config->width = 640;

	config->texnum = 4;
	config->texwidth = 64;
	config->texheight = 64;
	config->texsize = (config->texwidth) * (config->texheight);

	config->movespeed = 0.15;
	config->rotspeed = 0.15;
}
