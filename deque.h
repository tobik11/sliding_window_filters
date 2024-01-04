/*
* Author: Tobiasz Mandziuk
* Description: double ended queue for application in 
* min_max filter
* no dynamic memory allocation
* Limitaitons: maximum window width is determined by 
* DEQUE_MAX_WINDOW_SIZE defined in deque.h
* DEQUE_MAX_WINDOW_SIZE cannot exceed MAX_UINT32
* thread safety not guaranteed!
* adding elements only allowed from the front of the queue
*/
#ifndef DEQUE_H
#define DEQUE_H
#include <inttypes.h>

#define DEQUE_MAX_WINDOW_SIZE 500

typedef struct {
  float value;
  uint32_t index;
} node_t;

typedef struct {
  node_t buffer[DEQUE_MAX_WINDOW_SIZE];
  uint32_t front;
  uint32_t back;
  uint32_t size;
} deque_t;

void deque_init(deque_t *deque);

uint8_t deque_push_front(deque_t *deque, float value, uint32_t index);

uint8_t deque_pop_front(deque_t *deque);

float deque_get_front(const deque_t *deque);

uint8_t deque_pop_back(deque_t *deque);

float deque_get_back(const deque_t *deque);

#endif