#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "ts_hashmap.h"

/**
 * Creates a new thread-safe hashmap. 
 *
 * @param capacity initial capacity of the hashmap.
 * @return a pointer to a new thread-safe hashmap.
 */
ts_hashmap_t *initmap(int capacity) {
  // TODO
  ts_hashmap_t* map = (ts_hashmap_t*) malloc(sizeof(ts_hashmap_t)) ;
  map->table = malloc(capacity * sizeof(ts_entry_t*));
  map->size = 0;
  map->capacity = capacity;
  
  
  for(int i = 0; i < capacity; i++)
  {
    map->table[i] = NULL;
    //map->table[i]->next = NULL;
  }


  // for(int i = 0; i < capacity; i++)
  // {
  //   map->table[i] = malloc(capacity * sizeof(struct ts_entry_t));
  //   map->table[i] = NULL;
  // }


  
  
  return map;
}

/**
 * Obtains the value associated with the given key.
 * @param map a pointer to the map
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int get(ts_hashmap_t *map, int key) {
  // TODO

  int index = key % map->capacity;
  ts_entry_t *tempPointer = map->table[index];
  while(tempPointer != NULL)
  {
    if(tempPointer->key == key)
    {
      return tempPointer->value;
    }
    tempPointer = tempPointer->next;
  }
  return INT_MAX;
}

/**
 * Associates a value associated with a given key.
 * @param map a pointer to the map
 * @param key a key
 * @param value a value
 * @return old associated value, or INT_MAX if the key was new
 */
int put(ts_hashmap_t *map, int key, int value) {
  // TODO
  // bool notEnd = true;
    //printf("IN HERE");
    //int counter = 0;
    int index = key % map->capacity;
    ts_entry_t *tempPointer = map->table[index];
    ts_entry_t *newPair = malloc(sizeof(ts_entry_t));
    newPair->key = key;
    newPair->value = value;
    newPair->next = NULL;
    if(tempPointer == NULL)
    {
      //printf("FIRST");
      map->table[index] = newPair;
    }
    else
    {
      //int count =0;

      while(tempPointer->next != NULL)
      {
        //count++;
        printf("TESTING %d against %d\n", tempPointer->key,key);

        if(tempPointer->next->key == key)
        {
          printf("IN HERE\n");
          int oldValue = tempPointer->next->value;
          tempPointer->next->value = value;
          //map->table[index] = tempPointer;
          return oldValue;
        }
        //map->table[index] = map->table[index]->next;
        //printf("Value at %d = %d\n", tempPointer->key,tempPointer->value);
        tempPointer = tempPointer->next;
      }
      //printf("COUNT = %d\n",count);
      //printf("New Pair key , value = %d  ,  %d\n",newPair->key,newPair->value);

      tempPointer->next = newPair;
      //map->table[index]->next = tempPointer;
    }
    //printf("Map value at %d = %d\n", map->table[index]->key,map->table[index]->value);

    map->size++;
  //}
  return INT_MAX;
}

/**
 * Removes an entry in the map
 * @param map a pointer to the map
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int del(ts_hashmap_t *map, int key) {
  // TODO
  int index = key % map->capacity;

  

  return INT_MAX;
}


/**
 * @return the load factor of the given map
 */
double lf(ts_hashmap_t *map) {
  return (double) map->size / map->capacity;
}

/**
 * Prints the contents of the map
 */
void printmap(ts_hashmap_t *map) {
  for (int i = 0; i < map->capacity; i++) {
    printf("[%d] -> ", i);
    ts_entry_t *entry = map->table[i];
    while (entry != NULL) {
      printf("(%d,%d)", entry->key, entry->value);
      if (entry->next != NULL)
        printf(" -> ");
      entry = entry->next;
    }
    printf("\n");
  }
}