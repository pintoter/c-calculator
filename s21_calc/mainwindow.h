#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cstring>
//#include <QVector>
//#include "ui_mainwindow.h"
//#include "form.h"

#include <QMainWindow>

#ifdef __cplusplus
extern "C"
{
#endif
#include "../s21_smartcalc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createString();
    void addAction();
    void createNumber();
    void on_button_dot_clicked();
    void on_button_end_clicked();
    void on_button_clear_clicked();
    void on_button_delete_elem_clicked();
    void on_button_plot_clicked();
    void add_button_x();
    int check_last_elem();
    void get_value_x();

    void on_button_res_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    double x;

public slots:
    void slotForm(double a);
};
#endif // MAINWINDOW_H
