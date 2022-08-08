#ifndef MYOPENGL_H
#define MYOPENGL_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QColorDialog>
#include <QOpenGLFunctions>

extern "C" {
    #include "../parse.h"
    #include "../cfg_parse.h"
}

class myopengl:public QOpenGLWidget
{
public:
    myopengl(QWidget *parent = nullptr);
//    const char* filepath = {"/Users/rubiezzy/Desktop/C8_3DViewer_v1.0-0/src/CUB.obj"};
    const char* filepath = NULL;
    double* vertex_array = NULL;
    int* indexes_array = NULL;
    int edges_counter = 0;
    int dots_counter = 0;
    int f_counter = 0;
    double* min_and_max = NULL;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void start_proccess();
    void change_lines_color();
    FILE* file;
    char *char_path;
    QColor lines_color;
    QColor back_color;
    void change_back_color();
//    double lines_thickness = 1;
//    bool is_stripple = false;
    void choose_line_type();
    QColor tops_color;
    void change_points();
//    int display_tops = 0;
//    double tops_size;

    float* lines_color1 = (float*)calloc(3, sizeof(float));
    double lines_thickness1;
    float* back_color1 = (float*)calloc(4, sizeof(float));
    int line_type1;
    float* tops_color1 = (float*)calloc(3, sizeof(float));
    int display_tops1;
    double tops_size1;



};

#endif // MYOPENGL_H
