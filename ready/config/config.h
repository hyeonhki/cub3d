/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 09:56:29 by hyeonhki          #+#    #+#             */
/*   Updated: 2021/04/06 09:56:31 by hyeonhki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CONFIG_H
#define CONFIG_H

typedef struct s_config
{
	int		height;
	int		width;

	int		texnum;
	int		texwidth;
	int		texheight;
	int		texsize;

	double		movespeed;
	double		rotspeed;
}	t_config;

void config_init(t_config *config);

#endif
