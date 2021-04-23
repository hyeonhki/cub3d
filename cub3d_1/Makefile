all:
	gcc -fsanitize=address -L./mlx -lmlx -framework OpenGL -framework AppKit main.c \
	cub3d.c sprite.c bmp.c sprite.c cub3d.h \
	utils/utils.c \
	config/config.c config/player_init.c config/map_making.c config/map_check.c config/map_parse.c config/parsing_line.c config/valid_map_player.c \
	gnl/get_next_line.c gnl/get_next_line_utils.c \
	game/game.c game/texture_image.c 
	./a.out maps/map2.cub
