/*
* Author: Tobiasz Mandziuk
* Description: Sliding window avarage filter
* no dynamic memory allocation
* Limitaitons: maximum window width is determined by 
* AVG_WINDOW_MAX_WIDTH defined in this file
* thread safety not guaranteed!
*/

#ifndef FILTER_AVG_H
#define FILTER_AVG_H
#include <inttypes.h>

#define AVG_WINDOW_MAX_WIDTH 500

typedef struct {
  float buff[AVG_WINDOW_MAX_WIDTH];
  float sum;
  uint32_t index;
  uint32_t win_width;
  uint32_t current_win_width;
} filter_avg_t;

/**
 * @brief initiates window avarage filter
 *
 * @param filt pointer to filter instance
 * @param window_width width of the filter window
 * @return 0 - success, 1 - error (to large window for allocated memory)
 */
uint8_t filter_avg_init(filter_avg_t *filt, uint32_t window_width);

/**
 * @brief runs sliding window avarage filter calculations
 *
 * @param filt pointer to filter instance
 * @param sample input value for the filter
 * @return filtered value
 */
float filter_avg_calc(filter_avg_t *filt, float sample);

#endif

