#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h> 
#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;
int decrease_count(int count)
{
	if(available_resources < count)
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

void *fct(void *arg)
{
	for(int i = 0; i < 5; i++)
	{
		if(i % 3 == 1)
		{
			pthread_mutex_lock(&mtx);
			if(!decrease_count(1))
			{
				printf("Got %d resources %d remaining \n", 1, available_resources);
				increase_count(1);
				printf("Released %d resources %d remaining \n", 1, available_resources);
			}
			pthread_mutex_unlock(&mtx);
		}

		if(i % 3 == 2)
                {
                        pthread_mutex_lock(&mtx);
                        if(!decrease_count(2))
                        {
                                printf("Got %d resources %d remaining \n", 2, available_resources);
                                increase_count(2);
                                printf("Released %d resources %d remaining \n", 2, available_resources);
                        }
                        pthread_mutex_unlock(&mtx);
                }
		else 
		{
			pthread_mutex_lock(&mtx);
                        if(!decrease_count(3))
                        {
                                printf("Got %d resources %d remaining \n", 3, available_resources);
                                increase_count(3);
                                printf("Released %d resources %d remaining \n", 3, available_resources);
                        }
                        pthread_mutex_unlock(&mtx);
		}
	}
	return NULL;
}

int main()
{
	printf("MAX RESOURCES = 5");
	pthread_t threads[4];
	
	if(pthread_mutex_init(&mtx, NULL))
	{
		perror(NULL);
		return errno;
	}

	for(int i = 0; i < 4; i++)
	{
		if(pthread_create(&threads[i], NULL, fct, NULL))
		{
			perror(NULL);
                	return errno;
		}
	}

	for(int i = 0; i < 4; i++)
        {
                if(pthread_join(threads[i], NULL))
                {
                        perror(NULL);
                        return errno;
                }
        }

	if(pthread_mutex_destroy(&mtx))
	{
		perror(NULL);
		return errno;
	}
}
