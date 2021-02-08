#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

	char hello[14] = "Hello, World!";

	int fd = open("lab2_2.txt", O_RDWR | O_CREAT, 0666);
	
	if (fd < 0)
	{
		perror("Can't open file");
		exit(1);
	}
	else 
	{
		write(fd, hello, sizeof(hello));
	}
	
	close(fd);
	return 0;
}
