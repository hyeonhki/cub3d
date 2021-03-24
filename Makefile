all:
	gcc -L./mlx -lmlx -framework OpenGL -framework AppKit cub3d.c
	./a.out
