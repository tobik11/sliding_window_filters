#include "filter_avg.h"

uint8_t filter_avg_init(filter_avg_t *filt, uint32_t window_width) {
  if (window_width > AVG_WINDOW_MAX_WIDTH) {
    return 1;
  }
  filt->sum = 0;
  filt->index = 0;
  filt->win_width = window_width;
  filt->current_win_width = 0;
  return 0;
}

float filter_avg_calc(filter_avg_t *filt, float sample) {
  filt->index++;
  if (filt->index == filt->win_width) {
    filt->index = 0;
  }

  if (filt->current_win_width < filt->win_width) {
    filt->current_win_width++;
  } else {
    filt->sum -= filt->buff[filt->index];
  }
  filt->buff[filt->index] = sample;
  filt->sum += filt->buff[filt->index];
  return filt->sum / (float)filt->current_win_width;
}
