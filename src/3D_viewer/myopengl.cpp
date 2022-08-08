#include "myopengl.h"
#include <QDebug>
#include <QApplication>

myopengl::myopengl(QWidget *parent)
    :QOpenGLWidget(parent)
{
    QString path = QCoreApplication::applicationDirPath();
    path.replace("3D_viewer.app/Contents/MacOS", "cfg.txt");
    char_path = path.toLocal8Bit().data();
    file = cfg_parse(char_path, &lines_color1, &lines_thickness1, &back_color1, &line_type1, &tops_color1, &display_tops1, &tops_size1);
    start_proccess();
}

void myopengl::change_lines_color() {
//    float r = 0;
//    float g = 0;
//    float b = 0;
//    if (lines_color.isValid()) {
//        lines_color.getRgbF(&r, &g, &b);
//        glColor3d(r, g, b);
//    } else {
//        glColor3d(1, 0, 0);
//    }
    if (lines_color.isValid()) {
        lines_color.getRgbF(&lines_color1[0], &lines_color1[1], &lines_color1[2]);
        glColor3d(lines_color1[0], lines_color1[1], lines_color1[2]);
    } else {
        glColor3d(lines_color1[0], lines_color1[1], lines_color1[2]);
    }
}

void myopengl::change_back_color() {
//    float r = 0;
//    float g = 0;
//    float b = 0;
//    if (back_color.isValid()) {
//        back_color.getRgbF(&r, &g, &b);
//        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//        f->glClearColor(r, g, b, 0.0f);
//        f->glClear(GL_COLOR_BUFFER_BIT);
//    } else {
//        glClearColor(0, 0, 0, 0.0f);
//    }
    if (back_color.isValid()) {
        back_color.getRgbF(&back_color1[0], &back_color1[1], &back_color1[2]);
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(back_color1[0], back_color1[1], back_color1[2], back_color1[3]);
        f->glClear(GL_COLOR_BUFFER_BIT);
    } else {
        glClearColor(back_color1[0], back_color1[1], back_color1[2], back_color1[3]);
    }
}

void myopengl::choose_line_type() {
//    if (is_stripple) {
//        glLineStipple(1, 0x3F07);
//        glEnable(GL_LINE_STIPPLE);
//    } else {
//        glDisable(GL_LINE_STIPPLE);
//    }
    if (line_type1 == 1) {
        glLineStipple(1, 0x3F07);
        glEnable(GL_LINE_STIPPLE);
    } else {
        glDisable(GL_LINE_STIPPLE);
    }

}

void myopengl::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-min_and_max[abs_max], min_and_max[abs_max], -min_and_max[abs_max], min_and_max[abs_max], min_and_max[abs_max], -min_and_max[abs_max]);
    glLineWidth(1);
}

void myopengl::resizeGL(int w, int h) {
    glViewport(0, 0, 800, 600);
}

void myopengl::change_points() {
//    if (display_tops > 0) {
//        glPointSize(tops_size);
//        if (display_tops == 2) {
//            glEnable(GL_POINT_SMOOTH);
//        }
//        float r = 0;
//        float g = 0;
//        float b = 0;
//        if (tops_color.isValid()) {
//            tops_color.getRgbF(&r, &g, &b);
//            glColor3d(r, g, b);
//        } else {
//            glColor3d(0, 1, 0);
//        }
//        glDrawElements(GL_POINTS, edges_counter, GL_UNSIGNED_INT, indexes_array);
//    }
    if (display_tops1 > 0) {
        glPointSize(tops_size1);
        if (display_tops1 == 2) {
            glEnable(GL_POINT_SMOOTH);
        }
        if (tops_color.isValid()) {
            tops_color.getRgbF(&tops_color1[0], &tops_color1[1], &tops_color1[2]);
            glColor3d(tops_color1[0], tops_color1[1], tops_color1[2]);
        } else {
            glColor3d(tops_color1[0], tops_color1[1], tops_color1[2]);
        }
        glDrawElements(GL_POINTS, edges_counter, GL_UNSIGNED_INT, indexes_array);
    }

}

void myopengl::paintGL() {
    change_back_color();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-min_and_max[abs_max], min_and_max[abs_max], -min_and_max[abs_max], min_and_max[abs_max], min_and_max[abs_max], -min_and_max[abs_max]);

    glBegin(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    // lines
    change_lines_color();
    glVertexPointer(3, GL_DOUBLE, 0, vertex_array);
    choose_line_type();
    glLineWidth(lines_thickness1);
    glDrawElements(GL_LINES, edges_counter, GL_UNSIGNED_INT, indexes_array);

    //points
    change_points();
    glDisableClientState(GL_VERTEX_ARRAY);
    glEnd();
    update();
}

void myopengl::start_proccess() {
    f_counter = parse_processing(filepath, &vertex_array, &indexes_array, &dots_counter, &edges_counter);
    get_min_and_max(vertex_array, dots_counter, &min_and_max);
}
