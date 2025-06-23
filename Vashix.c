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

thread_arg* threads_args;



void* created_thread_routine(void* arg)
{
	thread_arg this_thread_arg;

	this_thread_arg = *((thread_arg*)arg);
	printf("%d ",this_thread_arg.a);
	printf("thread\n");
	pthread_exit(NULL);
	return NULL;
}

pthread_t* pthread_t_threads;

int main(int argc, char* argv[])
{
	numof_created_threads = sysconf(_SC_NPROCESSORS_ONLN) - 1;
	printf("%ld\n", numof_created_threads);
	created_threads = (created_thread*)malloc(sizeof(created_thread)*numof_created_threads);
	
	threads_args = (thread_arg*)malloc(sizeof(thread_arg)*numof_created_threads);
	for(c0 = 0;c0 < numof_created_threads;++c0)
	{
		threads_args[c0].a = c0;
	}

	pthread_t_threads = (pthread_t*)malloc(sizeof(pthread_t)*numof_created_threads);
	for(c0 = 0;c0 < numof_created_threads;++c0)
	{
		pthread_create(&(pthread_t_threads[c0]), NULL, created_thread_routine, (void*)(&(threads_args[c0])));
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
