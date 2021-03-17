#include <stdio.h>
#include <string.h>

int main(void)
{
	int errno;

	errno = 1;
	printf("error message : %s\n", strerror(errno));
	return (0);
}