#include <stdio.h>

int main()
{
	char str[6] = "abcdef";
	char *temp;

	temp = str;
	temp[3] = 'a';
	printf("%s\n",str);
}
