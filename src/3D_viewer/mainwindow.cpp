#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->x_add, SIGNAL(clicked()), this, SLOT(shift()));
    connect(ui->y_add, SIGNAL(clicked()), this, SLOT(shift()));
    connect(ui->z_add, SIGNAL(clicked()), this, SLOT(shift()));
    connect(ui->x_sub, SIGNAL(clicked()), this, SLOT(shift()));
    connect(ui->y_sub, SIGNAL(clicked()), this, SLOT(shift()));
    connect(ui->z_sub, SIGNAL(clicked()), this, SLOT(shift()));

    connect(ui->zoom_add, SIGNAL(clicked()), this, SLOT(zoom_change()));
    connect(ui->zoom_sub, SIGNAL(clicked()), this, SLOT(zoom_change()));

    connect(ui->x_rot_add, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->x_rot_sub, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->y_rot_add, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->y_rot_sub, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->z_rot_add, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->z_rot_sub, SIGNAL(clicked()), this, SLOT(rotation()));

    connect(ui->get_screen, SIGNAL(clicked()), this, SLOT(make_screenshot()));

    connect(ui->lines_colour, SIGNAL(clicked()), this, SLOT(change_colour()));

    connect(ui->back_colour, SIGNAL(clicked()), this, SLOT(change_colour()));

    connect(ui->line_type, SIGNAL(currentTextChanged(QString)), this, SLOT(change_lines_type()));
    connect(ui->line_thickness, SIGNAL(valueChanged(int)), this, SLOT(change_line_thickness()));
    connect(ui->tops_colour, SIGNAL(clicked()), this, SLOT(change_colour()));

    connect(ui->tops_type, SIGNAL(currentTextChanged(QString)), this, SLOT(change_tops_type()));
    connect(ui->tops_size, SIGNAL(valueChanged(int)), this, SLOT(change_tops_size()));

    connect(ui->get_file_button, SIGNAL(clicked()), this, SLOT(choose_file()));
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(set_start_settings()));
    timer->start(10);

}

MainWindow::~MainWindow()
{
    free(ui->widget->indexes_array);
    free(ui->widget->vertex_array);
    save_settings(ui->widget->file, ui->widget->lines_color1, ui->widget->lines_thickness1, ui->widget->back_color1, ui->widget->line_type1, ui->widget->tops_color1, ui->widget->display_tops1, ui->widget->tops_size1);
    delete ui;
}

void MainWindow::change_line_thickness() {
    ui->widget->lines_thickness1 = ui->line_thickness->value();
}

void MainWindow::change_lines_type() {
    if (ui->line_type->currentText() == "пунктирная") {
        ui->widget->line_type1 = 1;
    } else if (ui->line_type->currentText() == "сплошная") {
        ui->widget->line_type1 = 0;
    }
}

void MainWindow::change_tops_type() {
    if  (ui->tops_type->currentText() == "отсутствуют") {
        ui->widget->display_tops1 = 0;
    } else if (ui->tops_type->currentText() == "квадратные"){
        ui->widget->display_tops1 = 1;
    } else {
        ui->widget->display_tops1 = 2;
    }
}

void MainWindow::change_tops_size() {
    ui->widget->tops_size1 = ui->tops_size->value();
}

void MainWindow::change_colour() {
    QPushButton *button = (QPushButton *)sender();
    if (button == ui->lines_colour) {
        ui->widget->lines_color = QColorDialog::getColor(Qt::red, this, tr("colors"));
    } else if (button == ui->back_colour) {
        ui->widget->back_color = QColorDialog::getColor(Qt::red, this, tr("colors"));
    } else {
        ui->widget->tops_color = QColorDialog::getColor(Qt::red, this, tr("colors"));
    }
}

void MainWindow::make_screenshot() {
    QString format;
    if (ui->format->currentText() == ".jpeg") {
        format = "*.jpeg";
    } else if (ui->format->currentText() == ".bmp") {
        format = "*.bmp";
    }
    QString str = QFileDialog::getSaveFileName(0, "Сохранить файл как", "", format);
    if (!str.isEmpty()) {
        ui->widget->grab().save(str);
    }
}

void MainWindow::shift() {
//    double shift = 0.05 * qFabs(ui->widget->max - ui->widget->min);
    double shift = 0.05 * qFabs(ui->widget->min_and_max[abs_max] - ui->widget->min_and_max[abs_min]);
    QPushButton* button = (QPushButton*)sender();
    if (button == ui->x_add) {
        ui->x_value->setText(QString::number(ui->x_value->text().toDouble() + shift));
        shift_x(&(ui->widget->vertex_array), ui->widget->dots_counter, shift);
    } else if (button == ui->x_sub) {
        ui->x_value->setText(QString::number(ui->x_value->text().toDouble() - shift));
        shift_x(&(ui->widget->vertex_array), ui->widget->dots_counter, -shift);
    } else if (button == ui->y_add) {
        ui->y_value->setText(QString::number(ui->y_value->text().toDouble() + shift));
        shift_y(&(ui->widget->vertex_array), ui->widget->dots_counter, shift);
    } else if (button == ui->y_sub) {
        ui->y_value->setText(QString::number(ui->y_value->text().toDouble() - shift));
        shift_y(&(ui->widget->vertex_array), ui->widget->dots_counter, -shift);
    } else if (button == ui->z_add) {
        ui->z_value->setText(QString::number(ui->z_value->text().toDouble() + shift));
        shift_z(&(ui->widget->vertex_array), ui->widget->dots_counter, shift);
    } else if (button == ui->z_sub) {
        ui->z_value->setText(QString::number(ui->z_value->text().toDouble() - shift));
        shift_z(&(ui->widget->vertex_array), ui->widget->dots_counter, -shift);
    }
}

void MainWindow::zoom_change() {
    QPushButton* button = (QPushButton*)sender();
    if (button == ui->zoom_add) {
        double zoom_percent = 1.1;
        ui->zoom_value->setText(QString::number(ui->zoom_value->text().toDouble() + zoom_percent));
        zoom(&(ui->widget->vertex_array), ui->widget->dots_counter, zoom_percent);
    } else if (button == ui->zoom_sub) {
        double zoom_percent = 0.9;
        ui->zoom_value->setText(QString::number(ui->zoom_value->text().toDouble() - zoom_percent));
        zoom(&(ui->widget->vertex_array), ui->widget->dots_counter, zoom_percent);
    }
}

void MainWindow::rotation() {
    QPushButton* button = (QPushButton*)sender();
    double angle = 15;
    if (button == ui->x_rot_add) {
        rotation_ox(&(ui->widget->vertex_array), ui->widget->dots_counter, angle);
        ui->x_rot_value->setText(QString::number(ui->x_rot_value->text().toDouble() + 15));
    } else if (button == ui->x_rot_sub) {
        rotation_ox(&(ui->widget->vertex_array), ui->widget->dots_counter, -angle);
        ui->x_rot_value->setText(QString::number(ui->x_rot_value->text().toDouble() - 15));
    } else if (button == ui->y_rot_add) {
        rotation_oy(&(ui->widget->vertex_array), ui->widget->dots_counter, angle);
        ui->y_rot_value->setText(QString::number(ui->y_rot_value->text().toDouble() + 15));
    } else if (button == ui->y_rot_sub) {
        rotation_oy(&(ui->widget->vertex_array), ui->widget->dots_counter, -angle);
        ui->y_rot_value->setText(QString::number(ui->y_rot_value->text().toDouble() - 15));
    } else if (button == ui->z_rot_add) {
        rotation_oz(&(ui->widget->vertex_array), ui->widget->dots_counter, angle);
        ui->z_rot_value->setText(QString::number(ui->z_rot_value->text().toDouble() + 15));
    } else if (button == ui->z_rot_sub) {
        rotation_oz(&(ui->widget->vertex_array), ui->widget->dots_counter, -angle);
        ui->z_rot_value->setText(QString::number(ui->z_rot_value->text().toDouble() - 15));
    }
}

void MainWindow::choose_file() {
    QString str = QFileDialog::getOpenFileName(0, "Выбрать файл", "", "*.obj");
    QByteArray file_path = str.toLocal8Bit();
    ui->widget->filepath = file_path.data();
    ui->widget->start_proccess();
    if (str == "") {
        ui->filepath_dots->setText("Выберите файл.");
    } else {
        ui->filepath_dots->setText("Файл: " + str + "\nКоличество вершин: " + QString::number(ui->widget->dots_counter) + "\nКоличество ребер: " + QString::number(ui->widget->edges_counter / ui->widget->f_counter));
    }
}

void MainWindow::set_start_settings() {
    ui->line_thickness->setValue(ui->widget->lines_thickness1);
    ui->line_type->setCurrentIndex(ui->widget->line_type1 == 0 ? 0 : 1);
    ui->tops_type->setCurrentIndex(ui->widget->display_tops1 == 0 ? 0 : ui->widget->display_tops1 == 1 ? 1 : 2);
    ui->tops_size->setValue(ui->widget->tops_size1);
    timer->stop();
}

