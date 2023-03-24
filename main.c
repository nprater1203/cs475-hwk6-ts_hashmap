
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "ts_hashmap.h"

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: %s <num threads> <hashmap capacity>\n", argv[0]);
		return 1;
	}
	time_t t;
	srand((unsigned) time(&t));

  	//srand(time(NULL));
	int num_threads = atoi(argv[1]);
	int capacity = (unsigned int) atoi(argv[2]);

	ts_hashmap_t* map = initmap(capacity);

	for(int i = 0; i < capacity; i++)
	{
		int randNum = rand() % 100;
		put(map,randNum,randNum);
	}
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
	// printf("Deleted key 3 value return %d\n", del(map,3));


	printf("Map size: %d\n", map->size);
	printmap(map);

	// TODO: Write your test

	return 0;
}

