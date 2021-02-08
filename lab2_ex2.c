#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd1, fd2;
	char buff[4096];
	int rd;
	
	fd1 = open("input1.txt", O_RDONLY);
	fd2 = open("output1.txt", O_RDWR);
	 
	if ((fd1 < 0) || (fd2 < 0))
	{
		perror("Can't open files");
		return 1;
	}
	
	while ((rd = read(fd1, buff, 4096)) > 0) 
	{
	
		if(write(fd2, buff, rd) != rd)
		{
			perror("Writing problem");
			return 1;
		}
	}
	
	lseek(fd2, 0, SEEK_SET);
	

	while(read(fd2, buff, sizeof(buff)) > 0)
	{
		printf("%s", buff);
	}
	
	close(fd1);
	close(fd2);
	return 0;
}
