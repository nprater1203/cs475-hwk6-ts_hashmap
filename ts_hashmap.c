/*
	Name: Nicholas Prater
	Course: CS 481 OS
	Professor: Dr. Chiu
	Date: 3/28/23
*/

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
  }

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
  pthread_mutex_lock(locks[index]);

  ts_entry_t *tempPointer = map->table[index];
  while(tempPointer != NULL)
  {
    if(tempPointer->key == key)
    {
      pthread_mutex_unlock(locks[index]);
      return tempPointer->value;
    }
    tempPointer = tempPointer->next;
  }
  pthread_mutex_unlock(locks[index]);
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
    
  int index = key % map->capacity;
  pthread_mutex_lock(locks[index]);
  ts_entry_t *tempPointer = map->table[index];
  ts_entry_t *newPair = malloc(sizeof(ts_entry_t));
  newPair->key = key;
  newPair->value = value;
  newPair->next = NULL;
  if(tempPointer == NULL)
  {
    map->table[index] = newPair;
  }
  else
  {
    while(tempPointer->next != NULL)
    {
      if(tempPointer->next->key == key)
      {
        int oldValue = tempPointer->next->value;
        tempPointer->next->value = value;
        free(newPair);
        newPair = NULL;
        pthread_mutex_unlock(locks[index]);
        return oldValue;
      }
      else if(tempPointer->key == key)
      {
        int oldValue = tempPointer->value;
        tempPointer->value = value;
        free(newPair);
        newPair = NULL;

        pthread_mutex_unlock(locks[index]);
        return oldValue;
      }
      tempPointer = tempPointer->next;
    }
    if(tempPointer->key == key)
    {
        int oldValue = tempPointer->value;
        tempPointer->value = value;
        free(newPair);
        newPair = NULL;
        pthread_mutex_unlock(locks[index]);

        return oldValue;
    }
    tempPointer->next = newPair;
  }
  map->size++;

  pthread_mutex_unlock(locks[index]);

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
  pthread_mutex_lock(locks[index]);
  ts_entry_t *tempPointer = map->table[index];
  if(tempPointer != NULL)
  {
    ts_entry_t *tempPtrNext = tempPointer->next;

    while(tempPtrNext != NULL )
    {
      if(tempPointer->key == key)
      {
        printf("Deleting key %d\n", tempPointer->key);
        int val = tempPointer->value;
        if(tempPointer->key == map->table[index]->key)
        {
          free(tempPointer);
          map->table[index] = tempPtrNext;
        }
        else
        {
          free(tempPointer);
          tempPointer = tempPtrNext;
        }
        map->size--;

        pthread_mutex_unlock(locks[index]);
        return val;
      }
      if(tempPtrNext->key == key)
      {
        printf("Deleting key %d\n", tempPtrNext->key);

        int val = tempPtrNext->value;
        tempPointer->next = tempPtrNext->next;
        free(tempPtrNext);
        tempPtrNext = NULL;
        
        map->size--;

        pthread_mutex_unlock(locks[index]);
        return val;
      }

      tempPointer = tempPtrNext;
      tempPtrNext = tempPtrNext->next;
    }
  }              
  
  pthread_mutex_unlock(locks[index]);
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