all:
	gcc -L./mlx -lmlx -framework OpenGL -framework AppKit tester.c
	./a.out
