#include "cfg_parse.h"

FILE* cfg_parse(const char* filepath, float** lines_color, double* lines_thickness,
                    float** back_color, int* line_type, float** tops_color,
                                            int* display_tops, double* tops_size) {
    FILE *file = fopen(filepath, "r+");
    if (file) {
        char buffer[100];
        while (!feof(file)) {
            fgets(buffer, 100, file);
            if (buffer[0] == 'L' && buffer[1] == 'C') {
                copy_num_arr(buffer, lines_color);
            } else if (buffer[0] == 'B' && buffer[1] == 'C') {
                copy_num_arr(buffer, back_color);
            } else if (buffer[0] == 'T' && buffer[1] == 'C') {
                copy_num_arr(buffer, tops_color);
            } else if (buffer[0] == 'L' && buffer[1] == 'T') {
                copy_num_single(buffer, lines_thickness);
            } else if (buffer[0] == 'L' && buffer[1] == 'I') {
                if (buffer[4] == '1') {
                    *line_type = 1;
                } else {
                    *line_type = 0;
                }
            } else if (buffer[0] == 'D' && buffer[1] == 'T') {
                if (buffer[3] == '0') {
                    *display_tops = 0;
                } else if (buffer[3] == '1') {
                    *display_tops = 1;
                } else {
                    *display_tops = 2;
                }
            } else if (buffer[0] == 'T' && buffer[1] == 'S') {
                copy_num_single(buffer, tops_size);
            }
        }
    } else {
        get_def_settings(filepath);
        cfg_parse(filepath, lines_color, lines_thickness, back_color,
                        line_type, tops_color, display_tops, tops_size);
    }
    return file;
}

void copy_num_arr(char* array, float** data) {
    int j = 3, i = 0, k = 0;
    char* num_tmp = calloc(10, sizeof(char));
    while ((array[j] >= '0' && array[j] <= '9') || (array[j] == '.') || (array[j] == ',')) {
        if (array[j] == ',') {
            (*data)[k++] = atof(num_tmp);
            memset(num_tmp, 0, 10);
            i = 0;
        } else {
            num_tmp[i++] = array[j];
        }
        j += 1;
    }
    free(num_tmp);
}

void copy_num_single(char* array, double* data) {
    int j = 3, i = 0;
    char* num_tmp = calloc(10, sizeof(char));
    while ((array[j] >= '0' && array[j] <= '9') || (array[j] == '.')) {
        num_tmp[i++] = array[j++];
    }
    *data = atof(num_tmp);
    free(num_tmp);
}

void save_settings(FILE* file, float* lines_color, double lines_thickness, float* back_color,
                        int line_type, float* tops_color, int display_tops, double tops_size) {
    fprintf(file, "\nLC %.2lf,%.2lf,%.2lf\n", lines_color[0], lines_color[1], lines_color[2]);
    fprintf(file, "LT %.2lf\n", lines_thickness);
    fprintf(file, "BC %.2lf,%.2lf,%.2lf,%.2lf\n", back_color[0], back_color[1], back_color[2], back_color[3]);
    fprintf(file, "LIT %d\n", line_type);
    fprintf(file, "TC %.2lf,%.2lf,%.2lf\n", tops_color[0], tops_color[1], tops_color[2]);
    fprintf(file, "DT %d\n", display_tops);
    fprintf(file, "TS %.2lf\n", tops_size);
    fclose(file);
}

void get_def_settings(const char* filepath) {
    FILE *file = fopen(filepath, "w");
    fprintf(file, "\nLC 1.00,0.00,0.00\n");
    fprintf(file, "LT 1.00\n");
    fprintf(file, "BC 0.00,0.00,0.00,0.00\n");
    fprintf(file, "LIT 0\n");
    fprintf(file, "TC 0.00,1.00,0.00\n");
    fprintf(file, "DT 0\n");
    fprintf(file, "TS 1.00\n");
    fclose(file);
}
