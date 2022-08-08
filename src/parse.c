#include "parse.h"

int parse_processing(const char* file_path, double** dots_array,
                    int** dot_connection, int* dots_size, int* connect_size) {
    int dot_size = 0;
    int f_counter = 0;
    if (get_sizes(file_path, &dot_size, connect_size, &f_counter) == 0) {
        dot_size *= 3;
        char buffer[100];
        memset(&buffer, 0, 100);
        FILE *file = fopen(file_path, "r");
        *dots_array = calloc(dot_size , sizeof(double));
        *dot_connection = calloc(*connect_size, sizeof(int));
        if (*dots_array != NULL && *dot_connection != NULL) {
            int i = 0;
            int j = 0;
            if (file) {
                while (!feof(file)) {
                    fgets(buffer, 100, file);
                    if (buffer[0] != 'X') {
                    if ((buffer[0] == 'v' && buffer[1] == ' ') || (buffer[0] == 'f'))
                        parse(buffer, dots_array, &i, dot_connection, &j);
                    }
                    buffer[0] = 'X';
                }
            } else {
                array_def_init(dots_array, dot_connection, dots_size, connect_size);
            }
            *dot_connection = promote_f(dot_connection, f_counter, *connect_size);
            *connect_size *= 2;
            *dots_size = dot_size;
            fclose(file);
        } else {
            array_def_init(dots_array, dot_connection, dots_size, connect_size);
            if (file) {
                fclose(file);
            }
        }
    } else {
        array_def_init(dots_array, dot_connection, dots_size, connect_size);
    }
    return f_counter;
}

void array_def_init(double** dots_array, int** dot_connection, int* dots_size, int* connect_size) {
    *dots_size = 24;
    *connect_size = 48;
    *dots_array = calloc(*dots_size , sizeof(double));
    *dot_connection = calloc(*connect_size, sizeof(int));
    for (int i = 0; i < *dots_size; i++) {
        (*dots_array)[i] = 0.0;
    }

    for (int i = 0; i < *connect_size; i++) {
        (*dot_connection)[i] = 0.0;
    }
}

void parse(char* array, double** dot_array, int* dot_iterator,
    int** dot_connection, int* con_iterator) {
    int i = 0;
    char num[100];
    char* pnum = &num[0];
    while (array[i] && array[i] != EOF) {
        memset(pnum, 0, 100);
        if (array[i] == '\n') {
            i++;
            continue;
        }
        if ((array[i] >= '0' && array[i] <= '9') || (array[i] == '-')) {
            if (array[0] == 'v' && array[1] == ' ') {
                copy_num(array, &i, pnum);
                (*dot_array)[*dot_iterator] = atof(pnum);
                *dot_iterator = *dot_iterator + 1;
            } else if (array[0] == 'f') {
                copy_num(array, &i, pnum);
                (*dot_connection)[*con_iterator] = atoi(pnum);
                *con_iterator  = *con_iterator + 1;
            }
            i--;
        } else if (array[i] == 'v') {
            i++;
        } else if (array[i] == '/') {
            while (array[i] != ' ') {
                i++;
            }
            i--;
        }
        i++;
    }
}

void copy_num(const char* array, int* begin, char* num) {
    int i = 0;
    while ((array[*begin] >= '0' && array[*begin] <= '9') || array[*begin] == '.' || array[*begin] == '-') {
        num[i] = array[*begin];
        *begin += 1;
        i++;
    }
}

int get_sizes(const char* path, int* dot_size, int* con_dot_size, int* f_counter) {
    FILE *file = NULL;
    int result = 0;
    *f_counter = 0;
    *dot_size = 0;
    *con_dot_size = 0;
    int f_lines = 0;
    char buffer[1000];
    memset(buffer, 0, 1000);
    int flag = 0;
    if (path) {
        file = fopen(path, "r");
    }
    if (file) {
        while (!feof(file)) {
            int i = 0;
            fgets(buffer, 1000, file);
            if (buffer[0] != 'X') {
                if (buffer[0] == 'v' && buffer[1] == ' ') {
                    *dot_size += 1;
                } else if (buffer[0] == 'f') {
                    i++;
                    f_lines++;
                    while (buffer[i]) {
                        if (buffer[i] == ' ' && buffer[i+1] >= '0' && buffer[i+1] <= '9') {
                            *con_dot_size += 1;
                            if (flag == 0) *f_counter += 1;
                        }
                        i++;
                    }
                    flag = 1;
                }
            }
            buffer[0] = 'X';
        }
        fclose(file);
    } else {
        result = 1;
    }
    return result;
}

int* promote_f(int** dot_connection, int f_counter, int connect_size) {
    int* new_array = calloc(connect_size * 2, sizeof(int));
    int i = 0;
    int j = 0;
    int f_tmp = 0;
    int first_flag = 0;
    while (i < connect_size) {
        if (i == 0 || i % f_counter == 0) {
            f_tmp = (*dot_connection)[i];
            new_array[j++] = (*dot_connection)[i++] - 1;
        } else if ((i % (f_counter - 1) == 0 && first_flag == 0)
                    || (((i + 1) % f_counter) == 0 && first_flag == 1)) {
            new_array[j++] = (*dot_connection)[i] - 1;
            new_array[j++] = (*dot_connection)[i++] - 1;
            new_array[j++] = f_tmp - 1;
            first_flag = 1;
        } else {
            new_array[j++] = (*dot_connection)[i] - 1;
            new_array[j++] = (*dot_connection)[i++] - 1;
        }
    }
    free(*dot_connection);
    return new_array;
}

void shift_x(double** dot_array, int size, double shift) {
    for (int i = 0; i < size; i++) {
        if (i % 3 == 0 || i == 0) {
            (*dot_array)[i] = (*dot_array)[i] + shift;
        }
    }
}

void shift_y(double** dot_array, int size, double shift) {
    for (int i = 0; i < size; i++) {
        if (i == 1 || (i - 1) % 3 == 0) {
            (*dot_array)[i] = (*dot_array)[i] + shift;
        }
    }
}

void shift_z(double** dot_array, int size, double shift) {
    for (int i = 0; i < size; i++) {
        if (i == 2 || (i + 1) % 3 == 0) {
            (*dot_array)[i] = (*dot_array)[i] + shift;
        }
    }
}

void get_min_and_max(double* dot_array, int size, double** min_and_max) {
    if (dot_array) {
        *min_and_max = (double*)calloc(8, sizeof(double));
        pre_init(dot_array, min_and_max);
        for (int i = 0; i < size; i++) {
            if (dot_array[i] > (*min_and_max)[abs_max]) {
                (*min_and_max)[abs_max] = dot_array[i];
            }
            if (dot_array[i] < (*min_and_max)[abs_min]) {
                (*min_and_max)[abs_min] = dot_array[i];
            }
            if (i == 0 || i % 3 == 0) {
                if (dot_array[i] > (*min_and_max)[x_max])
                    (*min_and_max)[x_max] = dot_array[i];
                if (dot_array[i] < (*min_and_max)[x_min])
                    (*min_and_max)[x_min] = dot_array[i];
            } else if (i == 1 || (i - 1) % 3 == 0) {
                if (dot_array[i] > (*min_and_max)[y_max])
                    (*min_and_max)[y_max] = dot_array[i];
                if (dot_array[i] < (*min_and_max)[y_min])
                    (*min_and_max)[y_min] = dot_array[i];
            } else if (i == 2 || (i + 1) % 3 == 0) {
                if (dot_array[i] > (*min_and_max)[z_max])
                    (*min_and_max)[z_max] = dot_array[i];
                if (dot_array[i] < (*min_and_max)[z_min])
                    (*min_and_max)[z_min] = dot_array[i];
            }
        }
        post_init(min_and_max);
    } else {
        printf("array was not alloc.");
    }
}

void pre_init(double* dot_array, double** min_and_max) {
        (*min_and_max)[x_max] = dot_array[0];
        (*min_and_max)[x_min] = dot_array[0];
        (*min_and_max)[y_max] = dot_array[1];
        (*min_and_max)[y_min] = dot_array[1];
        (*min_and_max)[z_max] = dot_array[2];
        (*min_and_max)[z_min] = dot_array[2];

        (*min_and_max)[abs_max] = dot_array[0];
        (*min_and_max)[abs_min] = dot_array[0];
}

void post_init(double** min_and_max) {
        (*min_and_max)[x_max] *= 1.4;
        (*min_and_max)[x_min] *= 1.4;
        (*min_and_max)[y_max] *= 1.4;
        (*min_and_max)[y_min] *= 1.4;
        (*min_and_max)[z_max] *= 1.4;
        (*min_and_max)[z_min] *= 2;
        (*min_and_max)[z_min] *= 2;
        (*min_and_max)[abs_max] *= 2;
        (*min_and_max)[abs_min] *= 2;
}

void zoom(double** dot_array, int size, double zoom_percent) {
    if (dot_array) {
        for (int i = 0; i < size; i++) {
             (*dot_array)[i] *= zoom_percent;
        }
    } else {
        printf("array was no alloc.");
    }
}

void rotation_ox(double** dots_array, int size, double angle) {
    matrix_t matrix;
    s21_create_matrix(size / 3,  3, &matrix);
    get_matrix_from_array(*dots_array, &matrix);
    angle = angle * M_PI / 180.0;
    for (int i = 0; i < matrix.rows; i++) {
        double temp_y = matrix.matrix[i][1];
        double temp_z = matrix.matrix[i][2];
        matrix.matrix[i][1] = cos(angle) * temp_y + sin(angle) * temp_z;
        matrix.matrix[i][2] = sin(angle) * (-temp_y) + cos(angle) * temp_z;
    }
    get_array_from_matrix(dots_array, matrix);
    s21_remove_matrix(&matrix);
}

void rotation_oy(double** dots_array, int size, double angle) {
    matrix_t matrix;
    s21_create_matrix(size / 3,  3, &matrix);
    get_matrix_from_array(*dots_array, &matrix);
    angle = angle * M_PI / 180.0;
    for (int i = 0; i < matrix.rows; i++) {
        double temp_x = matrix.matrix[i][0];
        double temp_z = matrix.matrix[i][2];
        matrix.matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_z;
        matrix.matrix[i][2] = sin(angle) * (-temp_x) + cos(angle) * temp_z;
    }
    get_array_from_matrix(dots_array, matrix);
    s21_remove_matrix(&matrix);
}

void rotation_oz(double** dots_array, int size, double angle) {
    matrix_t matrix;
    s21_create_matrix(size / 3,  3, &matrix);
    get_matrix_from_array(*dots_array, &matrix);
    angle = angle * M_PI / 180.0;
    for (int i = 0; i < matrix.rows; i++) {
        double temp_x = matrix.matrix[i][0];
        double temp_y = matrix.matrix[i][1];
        matrix.matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_y;
        matrix.matrix[i][1] = sin(angle) * (-temp_x) + cos(angle) * temp_y;
    }
    get_array_from_matrix(dots_array, matrix);
    s21_remove_matrix(&matrix);
}

void get_array_from_matrix(double** dots_array, matrix_t matrix) {
    int k = 0;
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++, k++) {
            (*dots_array)[k] = matrix.matrix[i][j];
        }
    }
}

void get_matrix_from_array(double* dots_array, matrix_t* matrix) {
    int k = 0;
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++, k++) {
            matrix->matrix[i][j] = dots_array[k];
        }
    }
}
