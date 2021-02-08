#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>

int main() {

pid_t pid = fork();

if(pid < 0)
	return errno;
else if (pid == 0)
	{
	//printf("My PID %d  Child PID %d\n", getppid(), getpid());
	char *argv[] = {"ls", NULL};
	execve("/usr/bin/ls", argv, NULL);
	perror(NULL);
	}
else
	printf("My PID %d  Child PID %d\n", getppid(), getpid());
}
