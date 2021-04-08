#include "unistd.h"
#include "stdio.h"
#include "fcntl.h"
#include "for_eval_git/get_next_line.h"

typedef struct s_info
{
	int a;
	int b;
	int c;
}	t_info;

void line_check(t_info *info, char *line)
{
	printf("line : %s", line);
}

void config_map(t_info *info, char *path)
{
	int fd;
	int ret;
	char *line;

	printf("b\n");
	fd = open(path, O_RDONLY);
	while ((ret = get_next_line(fd, &line) > 0))
	{
		printf("ret : %d\n", ret);
		printf("line : %s\n", line);
	}
}


int main(int argc, char *argv[])
{
	t_info info;

	printf("a\n");
	config_map(&info, argv[1]);
}