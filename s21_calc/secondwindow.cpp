#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QInputDialog>

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::setLabel(const QString& str)
{
    ui->var_line->setText("Plotting graph: y=" + str);
    m_vvod = str;
}

void SecondWindow::makePlot()
{
    getXYvalues();

    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    ui->widget->xAxis->setRange(Xmin,Xmax);
    ui->widget->yAxis->setRange(Ymin,Ymax);

    h = 0.1;
    N = (Xmax - Xmin)/h + 2;

    QByteArray convert_input = m_vvod.toLocal8Bit();
    const char* char_input = convert_input.data();

    int err = s21_validator(char_input);

    if (!err) {
        for (X = Xmin; X <= Xmax; X += h)
        {
            err = 0;

            double temp = s21_smartcalc(char_input, X, &err);

            if (!err) {
                x.push_back(X);
                y.push_back(temp);
            }
        }

        ui->widget->addGraph();
        ui->widget->graph(0)->addData(x,y);
        ui->widget->replot();
    } else {
        this->close();
    }
}

void SecondWindow::getXYvalues()
{
    Xmax = Xmin = QInputDialog::getInt(this, "ATTANTION", "Enter Xmin");
    while (Xmax <= Xmin)
        Xmax = QInputDialog::getInt(this, "ATTANTION", "Enter Xmax");
    Ymax = Ymin = QInputDialog::getInt(this, "ATTANTION", "Enter Ymin");
    while (Ymax <= Ymin)
        Ymax = QInputDialog::getInt(this, "ATTANTION", "Enter Ymax");
}


void SecondWindow::on_button_replot_clicked()
{
    makePlot();
}


void SecondWindow::on_button_close_clicked()
{
    this->close();
}

