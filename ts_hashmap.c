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
  ts_hashmap_t* map = malloc(capacity * sizeof(struct ts_entry_t)) ;
  map->size = 0;
  map->capacity = capacity;
  
  //map->table = malloc(capacity * sizeof(ts_entry_t));
  // for(int i = 0; i < capacity; i++)
  // {
  //   map->table[i] = malloc(sizeof(struct ts_entry_t));
  // }


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

  for(int i = 0; i < map->capacity; i++)
  {
    if(map->table[i]->key == key)
    {
      return map->table[i]->value;
    }
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

  // if(notEnd)
  // {
  //   for(int i = 0 ; i < map->size; i++)
  //   {
  //     if(map->table[i]->key == key)
  //     {
  //       int returnVal = map->table[i]->value;
  //       map->table[i]->value = value;
  //       return returnVal;
  //       //notEnd = false;
  //     }
  //   }
  // }
  // else
  // {
    printf("IN HERE");
    map->table[map->size]->key = key;
    map->table[map->size]->value = value;
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
  for(int i = 0; i < map->size; i++)
  {
    if(map->table[i]->key == key)
    {
      int returnVal = map->table[i]->value;
      for(int j = i; j > map->size; j++)
      {
        map->table[j]->key = map->table[j]->key;
        map->table[j]->value = map->table[j]->value;
      }
      return returnVal;
    }
  }
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