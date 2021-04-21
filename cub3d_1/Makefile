all:
	gcc -fsanitize=address -L./mlx -lmlx -framework OpenGL -framework AppKit main.c \
	cub3d.c bmp.c cub3d.h \
	utils/utils.c \
	config/config.c config/map_parse.c config/valid_map.c \
	gnl/get_next_line.c gnl/get_next_line_utils.c \
	game/game.c game/texture_image.c 
	./a.out maps/map2.cub -save
