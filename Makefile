all:
	gcc -L./mlx -lmlx -framework OpenGL -framework AppKit main.c
#	gcc -L./mlx -lmlx main.c
	./a.out
