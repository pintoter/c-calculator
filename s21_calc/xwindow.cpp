#include "xwindow.h"
#include "ui_xwindow.h"

XWindow::XWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::XWindow)
{
    ui->setupUi(this);
}

XWindow::~XWindow()
{
    delete ui;
}


void XWindow::on_button_send_clicked()
{
    if (isCorrect()) {
        emit signalForm(ui->line_var->text().toDouble());
        this->close();
    } else {
        ui->line_var->clear();
    }
}

int XWindow::isCorrect()
{
    int res = 1;
    if (!ui->line_var->text().isEmpty()) {
        QString text = ui->line_var->text();
        for (int i = 0; i < text.size(); i++) {
            if (!(text[i].isDigit() || text[i] == '.')) {
                res = 0;
                break;
            }
        }
    }
    return res;
}

