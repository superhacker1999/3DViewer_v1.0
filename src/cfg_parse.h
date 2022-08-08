#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* cfg_parse(const char* filepath, float** lines_color, double* lines_thickness, float** back_color, int* line_type, float** tops_color, int* display_tops, double* tops_size);
void copy_num_arr (char* array, float** data);
void copy_num_single (char* array, double* data);
void save_settings(FILE* file, float* lines_color, double lines_thickness, float* back_color, int line_type, float* tops_color, int display_tops, double tops_size);
void get_def_settings(const char* filepath);