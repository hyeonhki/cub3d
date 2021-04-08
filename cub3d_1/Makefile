all:
	gcc -fsanitize=address -L../mlx -lmlx -framework OpenGL -framework AppKit main.c \
	cub3d.c cub3d.h \
	utils/utils.c \
	config/config.c \
	game/game.c game/texture_image.c
	./a.out
