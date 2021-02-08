#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;

pthread_mutex_t mtx;

int decrease_count(int count)
{
	if (available_resources < count)
		return -1;
	else
		available_resources -= count;
	return 0;
}

int increase_count(int count) 
{
	available_resources += count;
	return 0;
}

void *calcul(void *nr)
{
	int *n = (int*) nr;

    pthread_mutex_lock(&mtx);
	if(decrease_count(*n) > -1)
	{
	    printf("Got %d resources %d remaining \n", *n, available_resources);
		increase_count(*n);
		printf("Released %d resources %d remaining \n", *n, available_resources);
	}
	pthread_mutex_unlock(&mtx);
	return n;
}

int main()
{
	printf("MAX_RESOURCES = 5");
	pthread_t threads[5];

	if(pthread_mutex_init(&mtx,NULL))
	{
		perror("NULL");
		return errno;
	}
	
	int resurse[5] = {1, 2, 3, 2, 1};
	for(int i = 0; i < 5; i++)
	{
		int *nr_resurse=malloc(sizeof(int));
		*nr_resurse=resurse[i];
		if(pthread_create(&threads[i],NULL,calcul,nr_resurse))
		{
			perror("NULL");
			return errno;
		}
		printf("Got %d resources %d remaining \n", *nr_resurse, 5-*nr_resurse);
	}
	
	for(int i = 0; i < 5; i++)
	{
		if(pthread_join(threads[i],NULL))
		{
			perror("NULL");
			return errno;
		}
	}
	
	if(pthread_mutex_destroy(&mtx))
	{
		perror(NULL);
		return errno;
	}

	return 0;
}