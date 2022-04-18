#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MSGSIZE 255

char* msg = "Hello Chile Process!";
int main()
{
	char buf[255];
	int fd[2], pid, nbytes;
	if (pipe(fd) < 0)
		exit(1);
	pid = fork();
	if (pid > 0) {
		printf("parent PID:%d, child PID:%d\n", getpid(), pid);
		write(fd[1], msg, MSGSIZE);
		exit(0);
	}
	else {
		printf("child PID:%d\n", getpid());
		nbytes = read(fd[0], buf, MSGSIZE);
		printf("%d %s\n", nbytes, buf);
		exit(0);
	}
	return 0;
}
