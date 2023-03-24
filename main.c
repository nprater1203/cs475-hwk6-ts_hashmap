
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "ts_hashmap.h"

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: %s <num threads> <hashmap capacity>\n", argv[0]);
		return 1;
	}

  	srand(time(NULL));
	int num_threads = atoi(argv[1]);
	int capacity = (unsigned int) atoi(argv[2]);

	ts_hashmap_t* map = initmap(capacity);
	put(map,0,0);
	put(map,1,1);
	put(map,2,2);
	put(map,3,3);
	put(map, 2,4);
	put(map, 3,4);

	printf("Value with key %d: %d\n", 1 , get(map,1));
	printf("Map size: %d\n", map->size);
	printmap(map);

	// TODO: Write your test

	return 0;
}

