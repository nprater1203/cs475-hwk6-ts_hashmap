#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "ts_hashmap.h"

pthread_mutex_t **locks;
ts_hashmap_t *map;
int capacity;
//int intArray[100];
//int tempInd;


void* putThread(void* args)
{

	//pthread_mutex_lock(locks);
	//printf("This is a put thread\n");
	//time_t t;

	for(int i = 0; i < 30; i++)
	{
		int randNum = rand() % 100;
		//intArray[]
		put(map,randNum,randNum);
		// Everu 5th key gets a new value
		if(i % 5 == 0)
		{
			put(map,randNum,randNum+100);
		}
	}
	
	//pthread_mutex_unlock(locks);
	return NULL;
}

void* delThread(void* args)
{
	//pthread_mutex_lock(locks);
	//printf("This is a del thread\n");
	for(int i = 0; i < 30; i++)
	{
		int randNum = rand() % 100;
		if(get(map, randNum) != INT_MAX)
		{
			del(map,randNum);
		}
	}
	//pthread_mutex_unlock(locks);

	return NULL;
}

void* getThread(void* args)
{
	//pthread_mutex_lock(locks);
	//printf("This is a get thread\n");
	for(int i = 0; i < 30; i++)
	{
		int randNum = rand() % 100;
		printf("Getting %d -- %d\n", randNum, get(map, randNum));
	}
	//pthread_mutex_unlock(locks);

	return NULL;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: %s <num threads> <hashmap capacity>\n", argv[0]);
		return 1;
	}
	//time_t t;
	// srand((unsigned) time(&t));

  	//srand(time(NULL));
	int num_threads = atoi(argv[1]);
	capacity = (unsigned int) atoi(argv[2]);

	time_t t;

	srand((unsigned) time(&t));

	map = initmap(capacity);
	locks = (pthread_mutex_t**) malloc(capacity * sizeof(pthread_mutex_t*));
	for(int i = 0; i < capacity; i++)
	{
		locks[i] = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(locks[i],NULL);
	}
	//pthread_mutex_init(locks, NULL);	
	pthread_t *threads = (pthread_t*) malloc(num_threads * sizeof(pthread_t));

	//tempInd = 0;
	//thread_args *args = (thread_args*) malloc(numThreads * sizeof(thread_args));

	for (int i = 0; i < num_threads; i++) {
		//printf("Creating Thread %d\nnum threads /3 = %d\n",i,num_threads/3);
		if(i % 3 == 0)
		{
			//printf("Creating putThread\n");
			//PUT

			pthread_create(&threads[i], NULL, putThread, NULL);
		}
		else if(i % 3 == 1)
		{
			//printf("Creating getTHread\n");
			//GET
			pthread_create(&threads[i], NULL, getThread, NULL);
		}
		else
		{
			//printf("Creating delThread\n");

			//DEL
			pthread_create(&threads[i], NULL, delThread, NULL);
		}
	}

	// wait for threads to finish; combine partially computed sum
	for (int i = 0; i < num_threads; i++) 
	{
		pthread_join(threads[i], NULL);
	}

	// for(int i = 0; i < capacity; i++)
	// {
	// 	int randNum = rand() % 100;
	// 	put(map,randNum,randNum);
	// }
	// put(map,0,0);
	// put(map,1,1);
	// put(map,2,2);
	// put(map,3,3);
	// put(map,4,4);
	// put(map,5,5);
	// put(map, 2,4);
	// put(map, 3,4);

	// printf("Testing get %d: %d\n", 1 , get(map,1));
	// printf("Testing get %d: %d\n", 2 , get(map,2));
	// printf("Testing get %d: %d\n", 3 , get(map,3));

	//printf("Deleted key 2 value return %d\n", del(map,2));
	//printf("Deleted key 3 value return %d\n", del(map,3));


	printf("Map size: %d\n", map->size);
	printmap(map);

	// TODO: Write your test



	ts_entry_t *tempPtr , *tempPtrNext;
	for(int i = 0; i < capacity; i++)
	{

		pthread_mutex_destroy(locks[i]);
		free(locks[i]);
		locks[i] = NULL;

		tempPtr = map->table[i];
		if(tempPtr != NULL)
		{
			tempPtrNext = tempPtr->next;
			while(tempPtrNext != NULL)
			{
				free(tempPtr);
				tempPtr = NULL;
				tempPtr = tempPtrNext;
				tempPtrNext = tempPtrNext->next;
			}
			free(tempPtr);
			tempPtr = NULL;
		}
	}
	free(map);
	map = NULL;

	free(locks);
	locks = NULL;

	free(threads);
	threads = NULL;
	return 0;
}

