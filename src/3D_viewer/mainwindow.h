#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myopengl.h"
#include <QGridLayout>
#include <QWidget>
#include <QFileDialog>
#include <QTimer>


extern "C" {
    #include "../parse.h"
    #include "../cfg_parse.h"
}
//#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    myopengl *openglview;
    QTimer *timer;

public slots:
    void shift();
    void zoom_change();
    void rotation();
    void choose_file();
    void make_screenshot();
    void change_colour();
    void change_lines_type();
    void change_line_thickness();
    void change_tops_type();
    void change_tops_size();
    void set_start_settings();

};
#endif // MAINWINDOW_H
