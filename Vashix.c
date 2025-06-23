#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* common counters, initial values are 0 */
unsigned long c0, c1, c2, c3;

typedef struct 
{
	long thread_id; 
} created_thread;
created_thread* created_threads;
long numof_created_threads;

typedef struct
{
	int a;
} thread_arg;

thtead_arg* thread_args;

pthread_t* pthread_t_threads;

void* created_thread_routine(void* arg)
{
	printf("thread\n");
	pthread_exit(NULL);
	return NULL;
}

int main(int argc, char* argv[])
{
	numof_created_threads = sysconf(_SC_NPROCESSORS_ONLN) - 1;
	printf("%ld\n", numof_created_threads);
	created_threads = (created_thread*)malloc(sizeof(created_thread)*numof_created_threads);
	pthread_t_threads = (pthread_t*)malloc(sizeof(pthread_t)*numof_created_threads);
	for(c0 = 0;c0 < numof_created_threads;++c0)
	{
		pthread_create(&(pthread_t_threads[c0]), NULL, created_thread_routine, NULL);
	}

	for(c0 = 0;c0 < numof_created_threads;++c0)
	{
		pthread_join(pthread_t_threads[c0] , NULL);
	}
	free(pthread_t_threads);
	free(created_threads);
	printf("Works!\n");
	return 0;
}
