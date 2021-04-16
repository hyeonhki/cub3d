/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:53:59 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 15:54:00 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void config_init(t_config *config)
{
	config->texnum = 5;
	config->texwidth = 64;
	config->texheight = 64;
	config->moveSpeed = 0.3;
	config->rotSpeed = 0.3;
}
