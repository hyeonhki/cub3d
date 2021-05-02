#all:
#	gcc -Wall -Wextra -Werror -fsanitize=address -L./mlx -lmlx -framework OpenGL -framework AppKit main.c \
	cub3d.c bmp.c cub3d.h \
	utils/utils.c \
	config/config.c config/player_init.c config/map_making.c config/map_check.c config/map_parse.c config/parsing_line.c config/valid_map_player.c \
	gnl/get_next_line.c gnl/get_next_line_utils.c \
	game/game.c game/ready_sprite.c game/game_ready.c game/texture_image.c \
	game/raycast_floor_ceiling.c game/wall_raycast.c game/sprite_raycast.c \
	game/key_press.c
#	./a.out maps/map2.cub

NAME = cub3D
SRCS = main.c cub3d.c bmp.c \
	utils/utils.c \
	config/config.c config/player_init.c config/map_making.c config/map_check.c config/map_parse.c config/parsing_line.c config/valid_map_player.c \
	gnl/get_next_line.c gnl/get_next_line_utils.c \
	game/game.c game/ready_sprite.c game/game_ready.c game/texture_image.c \
	game/raycast_floor_ceiling.c game/wall_raycast.c game/sprite_raycast.c \
	game/key_press.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -L./mlx -lmlx -framework OpenGL -framework AppKit

MLX_NAME = mlx
MLX_DIR = ./mlx