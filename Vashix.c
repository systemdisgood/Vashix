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
	int this_thread_number;
} thread_arg;

thread_arg* threads_args;

pthread_barrier_t barrier;

void* created_thread_routine(void* arg)
{
	thread_arg this_thread_arg;
	int barrier_rc;

	this_thread_arg = *((thread_arg*)arg);
	printf("%d ",this_thread_arg.this_thread_number);
	printf("thread\n");

	printf("thread %d: reached the barrier.\n", this_thread_arg.this_thread_number);
    barrier_rc = pthread_barrier_wait(&barrier);

    if (barrier_rc == PTHREAD_BARRIER_SERIAL_THREAD) {
        printf("thread: %d\nbarrier state: serial\n\n", this_thread_arg.this_thread_number);
    } else if (barrier_rc == 0) {
        printf("thread: %d\nbarrier state: all\n\n", this_thread_arg.this_thread_number);
    } else {
        fprintf(stderr, "barrier error %d\n", barrier_rc);
    }

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
		threads_args[c0].this_thread_number = c0;
	}

	pthread_barrier_init(&barrier, NULL, numof_created_threads);
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
	free(threads_args);
	free(created_threads);
	printf("Works!\n");
	return 0;
}
