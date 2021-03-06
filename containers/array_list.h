#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>

#include <commons/string_utils.h>
#include <commons/log.h>

#define COLLECTION_MODE_SYNCHRONIZED        1
#define COLLECTION_MODE_ASYNCHRONIZED       2

//=====================================================
// structures
//=====================================================

//typedef int (*array_list_compare_fn)(const void *, const void *);

//typedef struct array_list_item {
//  void *type;
//  void *data;
//} void;

//-----------------------------------------------------

typedef struct array_list {
  size_t capacity;
  size_t size;
  float realloc_factor;
  int mode;
  int flag;

//  array_list_compare_fn compare_fn;
  int (*compare_fn)(const void *, const void *);
//  int writers;
//  int inserting;
//  int removing;

  pthread_mutex_t lock;
  pthread_cond_t condition;

  void **items;

} array_list_t;


/**
 * array_list items functions
 */
//void *array_list_item_new(void *type, void *item_p);
//
//void array_list_item_free(void *item_p);


/**
 * array_list functions
 */

array_list_t* array_list_new(size_t initial_capacity, float realloc_factor, int SYNC_MODE);

//void array_list_init(size_t initial_capacity, float realloc_factor, int SYNC_MODE, array_list_t* array_list_p);

void array_list_free(array_list_t* list_p, void (*data_callback) (void* data));



size_t array_list_capacity(array_list_t *array_list_p);

size_t array_list_size(array_list_t *array_list_p);

size_t array_list_index_of(void *item, array_list_t *array_list_p);

int array_list_contains(void* item, array_list_t *array_list_p);

int array_list_clear(array_list_t* array_list_p, void (*data_callback) (void* data));



int array_list_insert(void* item_p, array_list_t *array_list_p);

int array_list_insert_at(size_t index, void* item_p, array_list_t *array_list_p);


int array_list_insert_all(void** item_p, size_t num_items, array_list_t *array_list_p);

int array_list_insert_all_at(size_t index, void** item_p, size_t num_items, array_list_t* array_list_p);



void* array_list_remove(void *item, array_list_t *array_list_p);

void* array_list_remove_at(size_t index, array_list_t *array_list_p);

void** array_list_remove_range(size_t start, size_t end, array_list_t* array_list_p);



void* array_list_get(size_t index, array_list_t *array_list_p);

array_list_t* array_list_sublist(size_t start, size_t end, array_list_t *array_list_p, array_list_t *sublist);

void* array_list_set(size_t index, void* new_item, array_list_t *array_list_p);



void array_list_print(array_list_t *array_list_p);

// void **list_to_array(array_list_t *array_list_p);

static array_list_t *reallocate(array_list_t * array_list_p, size_t inc_size);

static int compare_items(const void *item1, const void *item2);

//int list_set_writers(int writers, list_t* list_p);
//int list_get_writers(list_t* list_p);
//int list_incr_writers(list_t* list_p);
//int list_decr_writers(list_t* list_p);

int array_list_swap(const int pos1, const int pos2, array_list_t *array_list_p);


void array_list_set_flag(int flag, array_list_t *array_list_p);
int array_list_get_flag(array_list_t *array_list_p);

#endif /* ARRAY_LIST_H */
