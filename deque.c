#include "deque.h"
#include <stdio.h>

void deque_init(deque_t *deque) {
  deque->front = 0;
  deque->back = 1;
  deque->size = 0;
}

uint8_t deque_push_front(deque_t *deque, float value, uint32_t index) {
  if (deque->size == DEQUE_MAX_WINDOW_SIZE) {
    return 1;
  }
  deque->front = (deque->front + 1);
  if(deque->front == DEQUE_MAX_WINDOW_SIZE){
    deque->front = 0;
  }
  deque->buffer[deque->front].value = value;
  deque->buffer[deque->front].index = index;
  deque->size++;
  return 0;
}

uint8_t deque_pop_front(deque_t *deque) {
  if (deque->size == 0) {
    return 1;
  }
  deque->front = (deque->front - 1);
  if(deque->front == UINT32_MAX){
    deque->front = DEQUE_MAX_WINDOW_SIZE - 1;
  }
  deque->size--;
  return 0;
}

float deque_get_front(const deque_t *deque) {
  if (deque->size == 0) {
    return 0.0;
  }
  return deque->buffer[deque->front].value;
}

uint8_t deque_pop_back(deque_t *deque) {
  if (deque->size == 0) {
    return 1;
  }
  deque->back = (deque->back + 1);
  if(deque->back == DEQUE_MAX_WINDOW_SIZE){
    deque->back = 0;
  }
  deque->size--;
  return 0;
}

float deque_get_back(const deque_t *deque) {
  if (deque->size == 0) {
    return 0.0;
  }
  return deque->buffer[deque->back].value;
}
