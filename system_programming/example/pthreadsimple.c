#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *ptr) {
	char *message;
	message = (char *) ptr;
	printf("%s \n", message);
	pthread_exit((void *)100);
}

int main() {
	pthread_t thread1, thread2;
	const char *message1 = "Thread 1";
	const char *message2 = "Thread 2";
	int ret, status;

	ret = pthread_create(&thread1, NULL, thread_function, (void*)message1);
	printf("%d", ret);
	if (ret == 0) {
		printf("pthread_create returns %d\n", ret);
	} else {
		printf("pthread_create returns error: %d\n", ret);
		exit(1);
	}
	ret = pthread_create(&thread2, NULL, thread_function, (void*)message2);
	if (ret == 0) {
		printf("pthread_create returns %d\n", ret);
	} else {
		printf("pthread_create returns error: %d\n", ret);
		exit(1);
	}
	pthread_join(thread1, (void **)&status);
	printf("thread1 returns: %d\n", status);
	pthread_join(thread2, (void **)&status);
	printf("thread2 returns: %d\n", status);
	return 0;
}
