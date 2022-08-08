#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define SUCCESS 1
#define FAILURE 0

#define CORRECT_MATRIX 0
#define ERROR 1
#define INCORRECT_MATRIX 2

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

void print_matrix(matrix_t A);
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// helping
void s21_minor(matrix_t *A, int row, int col, matrix_t *minor);

#ifdef __cplusplus
    }
 #endif

#endif  //  SRC_S21_MATRIX_H_