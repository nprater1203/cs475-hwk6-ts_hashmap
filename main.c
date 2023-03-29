/*
	Name: Nicholas Prater
	Course: CS 481 OS
	Professor: Dr. Chiu
	Date: 3/28/23
*/

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "ts_hashmap.h"

pthread_mutex_t **locks;
ts_hashmap_t *map;
int capacity;


void* putThread(void* args)
{
	for(int i = 0; i < 10; i++)
	{
		int randNum = rand() % 100;
		put(map,randNum,randNum);
		// Every 5th key gets a new value
		if(i % 5 == 0)
		{
			put(map,randNum,randNum+100);
		}
	}
	return NULL;
}

void* delThread(void* args)
{
	for(int i = 0; i < 20; i++)
	{
		int randNum = rand() % 100;
		del(map,randNum);
	}
	return NULL;
}

void* getThread(void* args)
{
	for(int i = 0; i < 30; i++)
	{
		int randNum = rand() % 100;
		printf("Getting %d -- %d\n", randNum, get(map, randNum));
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: %s <num threads> <hashmap capacity>\n", argv[0]);
		return 1;
	}

	int num_threads = atoi(argv[1]);
	if(atoi(argv[2]) == 0)
	{
		printf("No capacity\n");
		return 0;
	}
	else
	{
		capacity = (unsigned int) atoi(argv[2]);
	}

	time_t t;
	srand((unsigned) time(&t));

	map = initmap(capacity);
	locks = (pthread_mutex_t**) malloc(capacity * sizeof(pthread_mutex_t*));
	for(int i = 0; i < capacity; i++)
	{
		locks[i] = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(locks[i],NULL);
	}
	pthread_t *threads = (pthread_t*) malloc(num_threads * sizeof(pthread_t));

	for (int i = 0; i < num_threads; i++)
	{
		if(i % 3 == 0)
		{
			pthread_create(&threads[i], NULL, putThread, NULL);
		}
		else if(i % 3 == 1)
		{
			pthread_create(&threads[i], NULL, getThread, NULL);
		}
		else
		{
			pthread_create(&threads[i], NULL, delThread, NULL);
		}
	}

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

	// printf("Deleted key 2 value return %d\n", del(map,2));
	// printf("Deleted key 1 value return %d\n", del(map,1));
	// printf("Deleted key 4 value return %d\n", del(map,4));


	printf("\nMap size: %d\n", map->size);
	printmap(map);

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
	free(map->table);
	map->table = NULL;

	free(map);
	map = NULL;

	free(locks);
	locks = NULL;

	free(threads);
	threads = NULL;
	return 0;
}

