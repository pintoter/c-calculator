#ifndef XWINDOW_H
#define XWINDOW_H

#include <QDialog>

namespace Ui {
class XWindow;
}

class XWindow : public QDialog
{
    Q_OBJECT

public:
    explicit XWindow(QWidget *parent = nullptr);
    ~XWindow();

private slots:
    void on_button_send_clicked();
    int isCorrect();

signals:
    void signalForm(double a);

private:
    Ui::XWindow *ui;
};

#endif // XWINDOW_H
