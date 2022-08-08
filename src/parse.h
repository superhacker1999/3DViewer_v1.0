#ifdef __cplusplus
    extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s21_matrix.h"

#define x_max 0
#define x_min 1
#define y_max 2
#define y_min 3
#define z_max 4
#define z_min 5
#define abs_max 6
#define abs_min 7

void array_def_init(double** dots_array, int** dot_connection, int* dots_size, int* connect_size);
int parse_processing(const char* file_path, double** dots_array, int** dot_connection, int* dots_size, int* connect_size);
void parse(char* array, double** dot_array, int* dot_iterator,
    int** dot_connection, int* con_iterator);
void copy_num(const char* array, int* begin, char* num);
int get_sizes(const char* path, int* dot_size, int* con_dot_size, int* f_counter);
int* promote_f(int** dot_connection, int f_counter, int connect_size);
void shift_x(double** dot_array, int size, double shift);
void shift_y(double** dot_array, int size, double shift);
void shift_z(double** dot_array, int size, double shift);
void get_min_and_max(double* dot_array, int size, double** min_and_max);
void pre_init(double* dot_array, double** min_and_max);
void post_init(double** min_and_max);
void zoom(double** dot_array, int size, double zoom_percent);
void rotation_ox(double** dots_array, int size, double angle);
void rotation_oy(double** dots_array, int size, double angle);
void rotation_oz(double** dots_array, int size, double angle);
void get_array_from_matrix(double** dots_array, matrix_t matrix);
void get_matrix_from_array (double* dots_array, matrix_t* matrix);

#ifdef __cplusplus
    }
 #endif