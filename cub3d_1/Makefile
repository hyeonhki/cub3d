# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonhki <hyeonhki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/02 19:22:31 by hyeonhki          #+#    #+#              #
#    Updated: 2021/05/02 19:22:33 by hyeonhki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRCS	= main.c cub3d.c bmp.c \
		utils/utils.c \
		config/config.c config/player_init.c config/map_making.c config/map_check.c config/map_parse.c config/parsing_line.c config/valid_map_player.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c \
		game/game.c game/ready_sprite.c game/game_ready.c game/texture_image.c \
		game/raycast_floor_ceiling.c game/wall_raycast.c game/sprite_raycast.c \
		game/key_press.c
OBJS	= $(SRCS:.c=.o)
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -I.
LIBS	= -L./mlx -lmlx -framework OpenGL -framework AppKit
MLX		= libmlx.a
CST_DIR	= ./minilibx_opengl_custom

$(MLX):
				@$(MAKE) -C mlx

$(NAME):	$(MLX) $(OBJS)
				$(MAKE) -C $(CST_DIR) all
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

all:	$(NAME)

clean:
				@$(MAKE) -C mlx clean
				@$(MAKE) -C minilibx_opengl_custom clean
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
