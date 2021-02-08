#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>

int main() {
	int n;
	scanf("%d", &n);
	printf("%d: ", n);
	pid_t pid = fork();
	if(pid < 0)
		return errno;
	else if(pid == 0)
	{
		while(n != 1) {
			printf("%d ", n);
			if(n % 2 == 0)
				n = n/2;
			else
				n = 3*n + 1;
		}
		printf("%d\n", n);
	}
}
