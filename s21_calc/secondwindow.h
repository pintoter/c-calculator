#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QVector>

#ifdef __cplusplus
extern "C"
{
#endif
#include "../s21_smartcalc.h"
#ifdef __cplusplus
}
#endif

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();
    void setLabel(const QString& str);

private slots:
    void makePlot();
    void getXYvalues();
    void on_button_replot_clicked();
    void on_button_close_clicked();

private:
    Ui::SecondWindow *ui;

    double Xmin;
    double Xmax;
    double Ymin;
    double Ymax;
    double h;
    double X;
    double var;
    int N;

    QVector<double> x,y;

    QString m_vvod;
};

#endif // SECONDWINDOW_H
