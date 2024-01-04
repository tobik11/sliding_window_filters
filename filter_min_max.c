#include "filter_min_max.h"
#include "deque.h"
#include <stdio.h>

uint8_t filter_min_max_init(filter_min_max_t *filt, uint32_t window_width) {
  if (window_width > DEQUE_MAX_WINDOW_SIZE) {
    return 1;
  }
  deque_init(&filt->deque_max);
  deque_init(&filt->deque_min);
  filt->sample_iter = 0;
  filt->win_width = window_width;
  return 0;
}

void filter_min_max_process(filter_min_max_t *filt, float sample) {
  while (
      (filt->deque_max.size > 0) &&
      (filt->sample_iter - filt->deque_max.buffer[filt->deque_max.back].index >=
       filt->win_width)) {
    deque_pop_back(&filt->deque_max);
  }
  while ((filt->deque_max.size > 0) &&
         (deque_get_front(&filt->deque_max) <= sample)) {
    deque_pop_front(&filt->deque_max);
  }
  deque_push_front(&filt->deque_max, sample, filt->sample_iter);

  while (
      (filt->deque_min.size > 0) &&
      (filt->sample_iter - filt->deque_min.buffer[filt->deque_min.back].index >=
       filt->win_width)) {
    deque_pop_back(&filt->deque_min);
  }
  while ((filt->deque_min.size > 0) &&
         (deque_get_front(&filt->deque_min) >= sample)) {
    deque_pop_front(&filt->deque_min);
  }
  deque_push_front(&filt->deque_min, sample, filt->sample_iter);
  filt->sample_iter++;
}

float filter_min_max_get_min(const filter_min_max_t *filt) {
  return deque_get_back(&filt->deque_min);
}

float filter_min_max_get_max(const filter_min_max_t *filt) {
  return deque_get_back(&filt->deque_max);
}
