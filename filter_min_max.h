/*
 * Author: Tobiasz Mandziuk
 * Description: Sliding window min max filter
 * no dynamic memory allocation
 * Limitaitons: maximum window width is determined by
 * DEQUE_MAX_WINDOW_SIZE defined in deque.h
 * maximum sample number UINT32_t (for continuous use
 * it has to be modified)
 * thread safety not guaranteed!
 */

#ifndef FILTER_MIN_MAX_H
#define FILTER_MIN_MAX_H
#include "deque.h"
#include <inttypes.h>

typedef struct {
  uint32_t sample_iter;
  uint32_t win_width;
  deque_t deque_max;
  deque_t deque_min;
} filter_min_max_t;

/**
 * @brief initiates min_max filter
 *
 * @param filt pointer to a filter instance
 * @param window_width width of the filter window
 * @return 0 - success, 1 - error (to large window for allocated memory)
 */
uint8_t filter_min_max_init(filter_min_max_t *filt, uint32_t window_width);

/**
 * @brief runs sliding window min_max filter calculations
 *
 * @param filt pointer to filter instance
 * @param sample input value for the filter
 */
void filter_min_max_process(filter_min_max_t *filt, float sample);

/**
 * @brief getter of calculated min value
 *
 * @param filt pointer to filter instance
 * @return filtered value (minimum value from the current filter window)
 */
float filter_min_max_get_min(const filter_min_max_t *filt);

/**
 * @brief getter of calculated max value
 *
 * @param filt pointer to filter instance
 * @return filtered value (maximum value from the current filter window)
 */
float filter_min_max_get_max(const filter_min_max_t *filt);

#endif