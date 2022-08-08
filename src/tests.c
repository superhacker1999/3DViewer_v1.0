#include <string.h>
#include <stdio.h>
#include <check.h>
#include "parse.h"
#include <stdlib.h>

START_TEST(Test1) {
    char* filepath = {"../datasets/CUB.obj"};
    double* dot_array = NULL;
    int* indexes_array = NULL;
    int dot_size = 0;
    int connect_size = 0;
    int f_counter = parse_processing(filepath, &dot_array, &indexes_array, &dot_size, &connect_size);
    ck_assert_ptr_nonnull(dot_array);
    ck_assert_ptr_nonnull(indexes_array);
    ck_assert_int_eq(dot_size, 24);
    ck_assert_int_eq(connect_size, 48);
    ck_assert_int_eq(f_counter, 4);
    free(dot_array);
    free(indexes_array);
}
END_TEST

START_TEST(Test2) {
    char* filepath = {"../datasets/human.obj"};
    double* dot_array = NULL;
    int* indexes_array = NULL;
    int dot_size = 0;
    int connect_size = 0;
    int f_counter = parse_processing(filepath, &dot_array, &indexes_array, &dot_size, &connect_size);
    ck_assert_ptr_nonnull(dot_array);
    ck_assert_ptr_nonnull(indexes_array);
    ck_assert_int_eq(dot_size, 73383);
    ck_assert_int_eq(connect_size, 195672);
    ck_assert_int_eq(f_counter, 4);
    free(dot_array);
    free(indexes_array);
}
END_TEST

START_TEST(Test3) {
    char* filepath = NULL;
    double* dot_array = NULL;
    int* indexes_array = NULL;
    int dot_size = 0;
    int connect_size = 0;
    int f_counter = parse_processing(filepath, &dot_array, &indexes_array, &dot_size, &connect_size);
    ck_assert_ptr_nonnull(dot_array);
    ck_assert_ptr_nonnull(indexes_array);
    ck_assert_int_eq(dot_size, 24);
    ck_assert_int_eq(connect_size, 48);
    ck_assert_int_eq(f_counter, 0);
    free(dot_array);
    free(indexes_array);
}
END_TEST

START_TEST(Test4) {
    char* filepath = {"../datasets/CUB.obj"};
    double* dot_array = NULL;
    int* indexes_array = NULL;
    int dot_size = 0;
    int connect_size = 0;
    int f_counter = parse_processing(filepath, &dot_array, &indexes_array, &dot_size, &connect_size);
    ck_assert_ptr_nonnull(dot_array);
    ck_assert_ptr_nonnull(indexes_array);
    ck_assert_int_eq(dot_size, 24);
    ck_assert_int_eq(connect_size, 48);
    ck_assert_int_eq(f_counter, 4);
    const double array_dot_res[] = {1.00, 2.00, 2.00, 1.00, 1.00, 2.00, 2.00, 1.00, 2.00, 2.00,
    2.00, 2.00, 1.00, 2.00, 1.00, 1.00, 1.00, 1.00, 2.00, 1.00, 1.00, 2.00, 2.00, 1.00};
    int array_index_res[] = {1, 2, 2, 3, 3, 4, 4, 1, 8, 7, 7, 6, 6, 5, 5, 8, 4, 3, 3, 7, 7, 8,
                            8, 4, 5, 1, 1, 4, 4, 8, 8, 5, 5, 6, 6, 2, 2, 1, 1, 5, 2, 6, 6, 7, 7, 3, 3, 2};
    shift_x(&dot_array, dot_size, 1.0);
    shift_y(&dot_array, dot_size, 1.0);
    shift_z(&dot_array, dot_size, 1.0);
    for (int i = 0; i < dot_size; i++) {
        ck_assert_float_eq(dot_array[i], array_dot_res[i] + 1.0);
    }
    for (int i = 0; i < connect_size; i++) {
        ck_assert_int_eq(indexes_array[i] + 1, array_index_res[i]);
    }
    free(dot_array);
    free(indexes_array);
}
END_TEST

START_TEST(Test5) {
    char* filepath = {"../datasets/CUB.obj"};
    double* dot_array = NULL;
    int* indexes_array = NULL;
    int dot_size = 0;
    int connect_size = 0;
    parse_processing(filepath, &dot_array, &indexes_array, &dot_size, &connect_size);
    double* min_and_max = NULL;
    get_min_and_max(dot_array, dot_size, &min_and_max);
    ck_assert_double_eq(min_and_max[x_max], 2.8);
    ck_assert_double_eq(min_and_max[x_min], 1.4);
    ck_assert_double_eq(min_and_max[y_max], 2.8);
    ck_assert_double_eq(min_and_max[y_min], 1.4);
    ck_assert_double_eq(min_and_max[z_max], 2.8);
    ck_assert_double_eq(min_and_max[z_min], 4);
    ck_assert_double_eq(min_and_max[abs_max], 4);
    ck_assert_double_eq(min_and_max[abs_min], 2);
    free(dot_array);
    free(indexes_array);
    free(min_and_max);
}
END_TEST

START_TEST(Test6) {
    char* filepath = {"../datasets/CUB.obj"};
    double* dot_array = NULL;
    int* indexes_array = NULL;
    int dot_size = 0;
    int connect_size = 0;
    double array_dot_res[] = {1.00, 2.00, 2.00, 1.00, 1.00, 2.00, 2.00, 1.00, 2.00,
                                2.00, 2.00, 2.00, 1.00, 2.00, 1.00, 1.00, 1.00, 1.00, 2.00,
                                1.00, 1.00, 2.00, 2.00, 1.00};
    double* p_array = &array_dot_res[0];
    parse_processing(filepath, &dot_array, &indexes_array, &dot_size, &connect_size);
    rotation_ox(&dot_array, dot_size, 15);
    rotation_ox(&p_array, dot_size, 15);
    for (int i = 0; i < dot_size; i++) {
        ck_assert_double_eq(dot_array[i], array_dot_res[i]);
    }
    free(dot_array);
    free(indexes_array);
}
END_TEST

START_TEST(Test7) {
    char* filepath = {"../datasets/CUB.obj"};
    double* dot_array = NULL;
    int* indexes_array = NULL;
    int dot_size = 0;
    int connect_size = 0;
    double array_dot_res[] = {1.00, 2.00, 2.00, 1.00, 1.00, 2.00, 2.00, 1.00, 2.00,
                                2.00, 2.00, 2.00, 1.00, 2.00, 1.00, 1.00, 1.00, 1.00,
                                2.00, 1.00, 1.00, 2.00, 2.00, 1.00};
    double* p_array = &array_dot_res[0];
    parse_processing(filepath, &dot_array, &indexes_array, &dot_size, &connect_size);
    rotation_oy(&dot_array, dot_size, 15);
    rotation_oy(&p_array, dot_size, 15);
    for (int i = 0; i < dot_size; i++) {
        ck_assert_double_eq(dot_array[i], array_dot_res[i]);
    }
    free(dot_array);
    free(indexes_array);
}
END_TEST

START_TEST(Test8) {
    char* filepath = {"../datasets/CUB.obj"};
    double* dot_array = NULL;
    int* indexes_array = NULL;
    int dot_size = 0;
    int connect_size = 0;
    double array_dot_res[] = {1.00, 2.00, 2.00, 1.00, 1.00, 2.00, 2.00, 1.00, 2.00,
                                2.00, 2.00, 2.00, 1.00, 2.00, 1.00, 1.00, 1.00, 1.00,
                                2.00, 1.00, 1.00, 2.00, 2.00, 1.00};
    double* p_array = &array_dot_res[0];
    parse_processing(filepath, &dot_array, &indexes_array, &dot_size, &connect_size);
    rotation_oz(&dot_array, dot_size, 15);
    rotation_oz(&p_array, dot_size, 15);
    for (int i = 0; i < dot_size; i++) {
        ck_assert_double_eq(dot_array[i], array_dot_res[i]);
    }
    free(dot_array);
    free(indexes_array);
}
END_TEST

Suite *s21_math_tests_create() {
    Suite *s21_math = suite_create("s21_math");
    TCase *s21_math_tests = tcase_create("S21_MATH");
    tcase_add_test(s21_math_tests, Test1);
    tcase_add_test(s21_math_tests, Test2);
    tcase_add_test(s21_math_tests, Test3);
    tcase_add_test(s21_math_tests, Test4);
    tcase_add_test(s21_math_tests, Test5);
    tcase_add_test(s21_math_tests, Test6);
    tcase_add_test(s21_math_tests, Test7);
    tcase_add_test(s21_math_tests, Test8);
    suite_add_tcase(s21_math, s21_math_tests);
    return s21_math;
}

int main() {
    Suite *s21_math = s21_math_tests_create();
    SRunner *s21_math_runner = srunner_create(s21_math);
    int number_failed;
    srunner_run_all(s21_math_runner, FP_NORMAL);
    number_failed = srunner_ntests_failed(s21_math_runner);
    srunner_free(s21_math_runner);

    return number_failed == 0 ? 0 : 1;
}
