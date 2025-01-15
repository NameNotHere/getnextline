
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("wewe.txt", 0);
	char *ret = NULL;
	int i = 0;
	if (fd < 0)
	{
   		perror("Error opening file");
    	return 1;
	}

	while ((ret = get_next_line(fd)))
	{
		printf("%d %s", ++i, ret);
		free(ret);
		if (ret == NULL)
			break;
	}
}