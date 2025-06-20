#include <pthread.h>
#include <stdio.h>

void* foo(void* arg)
{
	printf("thread\n");
	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t thread1;
	pthread_create(&thread1, NULL, foo, NULL);
	pthread_join(thread1, NULL);
	printf("Works!\n");
	return 0;
}
