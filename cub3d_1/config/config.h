/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:53:49 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/07 15:53:50 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_config
{
	int ren_width;
	int ren_height;

	char *no;
	char *so;
	char *we;
	char *ea;
	char *fl;
	char *ce;

	int height; //512
	int width; //1024
	int texwidth; //64
	int texheight; //64
	double	moveSpeed;
	double	rotSpeed;

}	t_config;

void config_init(t_config *config);
void config_map(char *path);

#endif