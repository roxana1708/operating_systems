#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

void seq(int n, int *start) {
	int i = 0; 
	while(n != 1) {
		start[i] = n;
                if(n % 2 == 0)
                        n = n/2;
                else
                        n = 3*n + 1;
        	i = i+1;
		printf("%d", n);
	}
	printf("%s", "\n");
        start[i] = n;
	start[0] = i;

}

int main(int argc, char* argv[]){
	const char *space = "bbb";
	const char *nl = "\n";
	char shm_name[] = "myshm2";
	int shm_fd;

	shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if(shm_fd < 0) {
		perror(NULL);
		return errno;
	}

	size_t shm_size = 4096;

	if(ftruncate(shm_fd, shm_size) == -1) {
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}


	void *shm_ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(shm_ptr == MAP_FAILED) {
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}
	
	printf("%d", atoi(argv[1]));
	printf("%d", atoi(argv[2]));
	printf("%d", argc);
	for(int i = 1; i < argc; i++) {
		printf("%s", "aaaa ");
		pid_t pid = fork();
		if(pid < 0){return 1;}
		if(pid == 0) {
		seq(atoi(argv[i]), (int *) (shm_ptr+1024*(i-1)/sizeof(int)));
		exit(0);
		}
		else {
		wait(NULL);
		}
	}
	
	int l = 0;
	while(l < (argc-1)*1024) {
		int m = ((int *) shm_ptr)[l];
		printf("%d", ((int *) shm_ptr)[l]);
		printf("%s", nl);
		for(int i = 1; i < m; i++) {
			printf("%d", ((int *) shm_ptr)[l+i]);
		}
		l += 1024;
	}
	return 0;
}
