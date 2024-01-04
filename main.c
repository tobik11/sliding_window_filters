/*
 * Author: Tobiasz Mandziuk
 * Description: recruitment task
 * Limitaitons: the maximum number of rows in the csv file is MAX_UINT32
 */

#include "filter_avg.h"
#include "filter_min_max.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILTERING_WINDOW_SIZE 500
#define CSV_FILE_MAX_LINE_LEN 20

/**
 * @brief reads consequtive samples from first column of a csv file
 *
 * @param file pointer to the csv file
 * @param sample pointer to a float where the data will be written
 * @return 0 - no data read, 1 - data read
 */
uint8_t csv_file_read_sample(FILE *file, float *sample) {
  char file_line[CSV_FILE_MAX_LINE_LEN];
  if (fgets(file_line, CSV_FILE_MAX_LINE_LEN, file) != NULL) {
    char *sample_str = strtok(file_line, ";");
    if (sample_str != NULL) {
      *sample = atof(sample_str);
      return 1;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  FILE *input_file, *output_file;
  filter_avg_t filt_avg;
  filter_min_max_t filt_min_max;
  float sample_raw;

  if ((argc - 1) != 2) {
    printf("Wrong number of arguments. ");
    printf("Expected 2, got %d\n", (argc - 1));
    printf("example use:\n");
    printf("main.exe input_file_path.csv output_file_path.csv\n");
    return -1;
  }
  char *input_file_path = argv[1];
  char *output_file_path = argv[2];

  input_file = fopen(input_file_path, "r");
  if (input_file == NULL) {
    fprintf(stderr, "Unable to open intput file: %s\n", input_file_path);
    return -1;
  }
  output_file = fopen(output_file_path, "w");
  if (output_file == NULL) {
    fprintf(stderr, "Unable to open output file: %s\n", output_file_path);
    return -1;
  }

  filter_avg_init(&filt_avg, FILTERING_WINDOW_SIZE);
  filter_min_max_init(&filt_min_max, FILTERING_WINDOW_SIZE);

  while (csv_file_read_sample(input_file, &sample_raw)) {
    filter_min_max_process(&filt_min_max, sample_raw);
    fprintf(output_file, "%.2f; %.2f; %.2f; %.2f;\n", sample_raw,
            filter_avg_calc(&filt_avg, sample_raw),
            filter_min_max_get_max(&filt_min_max),
            filter_min_max_get_min(&filt_min_max));
  }

  fclose(input_file);
  fclose(output_file);
  return 0;
}
