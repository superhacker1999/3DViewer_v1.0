#include "s21_matrix.h"


// int main() {
//     matrix_t num1;
//     if (num1.matrix != NULL) {
//         printf("sega");
//     }
// }

// создание матрицы
// 0 - ok, 1 - неверные заданные данные
int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int create_res = CORRECT_MATRIX;
    if (rows > 0 && columns > 0) {
        result->columns = columns;
        result->rows = rows;
        result->matrix = (double**)calloc(rows, sizeof(double*));
        for (int i = 0; i < rows; i++) {
            result->matrix[i] = (double*)calloc(columns, sizeof(double));
        }
    } else {
        create_res = INCORRECT_MATRIX;
    }
    return create_res;
}

// удаление матрицы
void s21_remove_matrix(matrix_t *A) {
    if (A->matrix != NULL) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
    }
}

// Вычисляет равны ли матрицы, 0 - равны, 1 - не равны, 2 - одна из матриц не сущ. либо
// кол-во колонок или столбцов не равно
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int eq_res = SUCCESS;
    if (A->matrix != NULL && B->matrix != NULL) {
        if (A->columns == B->columns && A->rows == B->rows) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 0.00000001) {
                        eq_res = FAILURE;
                        break;
                    }
                }
            }
        } else {
            eq_res = FAILURE;
        }
    } else {
        eq_res = FAILURE;
    }
    return eq_res;
}

// Сложение матриц
// 0 - ок, 1 - NULL, 2 - несовпадающие размеры матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int sum_res = CORRECT_MATRIX;
    if (A->matrix != NULL && B->matrix != NULL
    && A->rows > 0 && A->columns > 0
    && B->rows > 0 && B->columns > 0) {
        if (A->columns == B->columns && A->rows == B->rows) {
            s21_create_matrix(A->rows, A->columns, result);
            if (result->matrix != NULL) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                    }
                }
            } else {
                sum_res = ERROR;
            }
        } else {
            sum_res = INCORRECT_MATRIX;
        }
    } else {
        sum_res = ERROR;
    }
    return sum_res;
}

// Вычитание матриц
// 0 - ок, 1 - NULL, 2 - несовпадающие размеры матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int sub_res = CORRECT_MATRIX;
    if (A->matrix != NULL && B->matrix != NULL
    && A->rows > 0 && A->columns > 0
    && B->rows > 0 && B->columns > 0) {
        if (A->columns == B->columns && A->rows == B->rows) {
            s21_create_matrix(A->rows, A->columns, result);
            if (result->matrix != NULL) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                    }
                }
            } else {
                sub_res = ERROR;
            }
        } else {
            sub_res = INCORRECT_MATRIX;
        }
    } else {
        sub_res = ERROR;
    }
    return sub_res;
}

// Умножение матрицы на число
// 0 - ок, 1 - NULL
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int mult_res = CORRECT_MATRIX;
    if (A->matrix != NULL && A->columns > 0 && A->rows > 0) {
        s21_create_matrix(A->rows, A->columns, result);
        if (result->matrix != NULL && result->columns > 0 && result->rows > 0) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] * number;
                }
            }
        } else {
            mult_res = ERROR;
        }
    } else {
        mult_res = ERROR;
    }
    return mult_res;
}

// Умножение матрицы на матрицу
// 0 - ок, 1 - NULL, 2 - не подходящие размеры матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int mult_res = CORRECT_MATRIX;
    if (A->matrix != NULL && B->matrix != NULL
    && A->columns > 0 && A->rows > 0
    && B->columns > 0 && B->rows > 0) {
        if (A->columns == B->rows) {
            s21_create_matrix(A->rows, B->columns, result);
            if (result->matrix != NULL && result->columns > 0 && result->rows > 0) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < B->columns; j++) {
                        result->matrix[i][j] = 0;
                        for (int k = 0; k < A->columns; k++) {
                            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                        }
                    }
                }
            } else {
                mult_res = ERROR;
            }
        } else {
            mult_res = INCORRECT_MATRIX;
        }
    } else {
        mult_res = ERROR;
    }
    return mult_res;
}

// Транспорнирование матрицы
// 0 - ок, 1 - NULL
int s21_transpose(matrix_t *A, matrix_t *result) {
    int trans_res = CORRECT_MATRIX;
    if (A->matrix != NULL && A->columns > 0 && A->rows > 0) {
        s21_create_matrix(A->columns, A->rows, result);
        if (result->matrix != NULL && result->columns > 0 && result->rows > 0) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[j][i] = A->matrix[i][j];
                }
            }
        } else {
            trans_res = ERROR;
        }
    } else {
        trans_res = ERROR;
    }
    return trans_res;
}

// Высчитывает матрицу алгебраических дополнений
// 0 - ок, 1 - NULL, 2 - не квадратная матрица
int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int complements_res = CORRECT_MATRIX;
    if (A->matrix != NULL && A->columns > 0 && A->rows > 0) {
        if (A->columns == A->rows) {
            s21_create_matrix(A->rows, A->columns, result);
            if (result->matrix != NULL && result->columns > 0 && result->rows > 0) {
                matrix_t minor;
                minor.matrix = NULL;
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        double determ = 0;
                        s21_minor(A, i, j, &minor);
                        s21_determinant(&minor, &determ);
                        s21_remove_matrix(&minor);
                        result->matrix[i][j] = pow(-1, i + j + 2) * determ;
                    }
                }
            } else {
                complements_res = ERROR;
            }
        } else {
            complements_res = INCORRECT_MATRIX;
        }
    } else {
        complements_res = ERROR;
    }
    return complements_res;
}

// Находит минор матрицы
void s21_minor(matrix_t *A, int row, int col, matrix_t *minor) {
    s21_create_matrix(A->rows - 1, A->columns - 1, minor);
    if (minor->matrix != NULL) {
       for (int i = 0, x = 0; i < A->rows; i++) {
           if (i != row) {
               for (int j = 0, y = 0; j < A->columns; j++) {
                   if (j != col) {
                       minor->matrix[x][y] = A->matrix[i][j];
                       y++;
                    }
                }
                x++;
            }
        }
    }
}

// Высчитывает детерминант матрицы
int s21_determinant(matrix_t *A, double *result) {
    int determ_res = CORRECT_MATRIX;
    if (A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        if (A->columns == A->rows) {
            *result = 0;
            if (A->rows == 2) {
                *result = (A->matrix[0][0] * A->matrix[1][1])
                    - (A->matrix[0][1] * A->matrix[1][0]);
            } else if (A->rows == 1) {
                *result = A->matrix[0][0];
            } else {
                matrix_t minor;
                minor.matrix = NULL;
                for (int i = 0; i < A->columns; i++) {
                    double tmp = 0;
                    s21_minor(A, 0, i, &minor);
                    s21_determinant(&minor, &tmp);
                    tmp = pow(-1, i + 2) * tmp;
                    *result += (A->matrix[0][i]) * tmp;
                    s21_remove_matrix(&minor);
                }
            }
        } else {
            determ_res = ERROR;
        }
    } else {
        determ_res = ERROR;
    }
    return determ_res;
}

// Высчитывает обратную матрицу
// 0 - ок, 1 - NULL, 2 - determ = 0 или матрица не квадратная
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int inverse_res = CORRECT_MATRIX;
    if (A->matrix != NULL && A->columns > 0 && A->rows > 0) {
        if (A->columns == A->rows) {

            double determ;
            s21_determinant(A, &determ);
            if (determ < 0) {
                matrix_t compl;
                matrix_t transp;
                compl.matrix = NULL;
                transp.matrix = NULL;
                s21_transpose(A, &transp);
                s21_calc_complements(&transp, &compl);
                s21_mult_number(&compl, 1.0/determ, result);
                s21_remove_matrix(&compl);
                s21_remove_matrix(&transp);
            } else {
                inverse_res = ERROR;
            }
        } else {
            inverse_res = INCORRECT_MATRIX;
        }
    } else {
        inverse_res = ERROR;
    }
    return inverse_res;
}

void print_matrix(matrix_t A) {
    for (int i = 0; i < A.rows; i++) {
            for (int j = 0; j < A.columns; j++) {
                printf("%.3f ", A.matrix[i][j]);
            }
            printf("\n");
        }
}
