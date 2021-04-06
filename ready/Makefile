all:
	gcc -fsanitize=address -L../mlx -lmlx -framework OpenGL -framework AppKit main.c utils/utils.c config/config.c cub3d.c
	./a.out
