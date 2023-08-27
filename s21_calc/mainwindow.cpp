#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "xwindow.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->output->setAlignment(Qt::AlignRight);
    ui->output->setWordWrap(false);
    ui->input->setAlignment(Qt::AlignRight);

    connect(ui->button_0, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_1, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_2, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_3, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_4, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_5, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_6, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_7, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_8, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_9, SIGNAL(clicked()), this, SLOT(createNumber()));
    connect(ui->button_open_bracket, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_closed_bracket, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_plus, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_minus, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_multiply, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_divide, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_arccos, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_arcsin, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_arctan, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_log, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_pow, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_sqrt, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(addAction()));
    connect(ui->button_x, SIGNAL(clicked()), this, SLOT(add_button_x()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createString()
{
    QByteArray convert_input = ui->output->text().toLocal8Bit();
    const char* char_input = convert_input.data();

    if(ui->output->text().contains('x', Qt::CaseInsensitive)) {
        get_value_x();
    } else {
        x = 0;
    };

    int err = s21_validator(char_input);;

    if (!err) {
        double res = s21_smartcalc(char_input, x, &err);
        if (!err) ui->output->setText(QString::number(res, 'g', 7));
        else ui->output->setText("Error!");
    }
    else
        ui->output->setText("Error!");
}

void MainWindow::createNumber()
{
    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString new_text;

    if (ui->input->text().isEmpty() && (check_last_elem() || ui->output->text() == "Error!"))
        ui->output->clear();

    if (ui->input->text().contains(".") && button->text() == "0") {
        new_text = ui->input->text() + button->text();
    } else {
        all_numbers = (ui->input->text() + button->text()).toDouble();
        new_text = QString::number(all_numbers,'g', 15);
    }

    ui->input->setText(new_text);
}

void MainWindow::addAction()
{
    QPushButton *button = (QPushButton *)sender();

    if (!ui->input->text().isEmpty() && (check_last_elem() || ui->output->text() == "Error!")) {
        ui->output->clear();
        ui->output->setText(ui->input->text() + button->text());
    } else {
        ui->output->setText(ui->output->text() + ui->input->text() + button->text());
    }

    ui->input->clear();
}

void MainWindow::on_button_dot_clicked()
{
    if (!(ui->input->text().contains('.')))
        ui->input->setText(ui->input->text() + ".");
}


void MainWindow::on_button_end_clicked()
{
    if (!ui->input->text().isEmpty()) {
        ui->output->setText(ui->output->text() + ui->input->text());
        ui->input->clear();
    }

    if (!ui->output->text().isEmpty()) {
        ui->output->setText(ui->output->text() + "\0");
        createString();
    }
}

void MainWindow::on_button_clear_clicked()
{
    ui->input->clear();
    ui->output->clear();
}

void MainWindow::on_button_delete_elem_clicked()
{
    QString text;

    if (ui->input->text().length() > 0)
    {
        text = ui->input->text();
        text.chop(1);
        ui->input->setText(text);
    }
    else if (ui->output->text().length() > 0)
    {
        text = ui->output->text();
        text.chop(1);
        ui->output->setText(text);
    }
}


void MainWindow::on_button_plot_clicked()
{
    if(!ui->input->text().isEmpty()) {
        ui->output->setText(ui->output->text() + ui->input->text());
        ui->input->clear();
    }
    if (!ui->output->text().isEmpty()) {
        SecondWindow graph;
        graph.setModal(true);
        QString temp = ui->output->text();
        graph.setLabel(temp);
        graph.exec();
        on_button_clear_clicked();
    }
}
// Добавить еще проверку на параметры если что написать: QMessageBox::warning(this, "Uncorrect data", "Vi na avtorizirovalis"
// clear() все параметры с графиком

void MainWindow::add_button_x()
{
    if (ui->input->text().isEmpty() && (check_last_elem() || ui->output->text() == "Error!"))
        ui->output->clear();

    if(!check_last_elem() && ui->input->text().isEmpty()) {
        ui->output->setText(ui->output->text() + "x");
    } else {
        ui->output->clear();
        ui->input->clear();
        ui->output->setText("x");
    }
}

int MainWindow::check_last_elem()
{
    QString temp;
    QChar temp1;
    if (!ui->output->text().isEmpty()) {
        temp = ui->output->text();
        temp1 = temp[temp.length()-1];
    }

    return temp1.isDigit() || temp1 == 'x';
}

void MainWindow::get_value_x()
{
    XWindow xw;
    connect(&xw, &XWindow::signalForm, this, &MainWindow::slotForm);
    xw.setModal(true);
    xw.exec();
}

void MainWindow::slotForm(double a)
{
    x = a;
}

void MainWindow::on_button_res_clicked()
{
    if (ui->line_summ->value() > 0 && ui->line_percent->value() > 0.00 && ui->line_time->value() > 0 && (ui->radioButton->isChecked() || ui->radioButton_2->isChecked())) {
        type_payment type;
        if (ui->radioButton->isChecked()) {
            type = annuitive;
        } else {
            type = differentiated;
        }
        credit_res res = s21_credit(type, ui->line_summ->value(), ui->line_percent->value(), ui->line_time->value());
        if (!(res.err)) {
            ui->label_monthpay->setText(QString::fromLocal8Bit(res.monthly_payment) + " руб.");
            ui->label_overpay->setText(QString::number(res.interest_charges, 'f', 2) + " руб.");
            ui->label_summ->setText(QString::number(res.summary, 'f', 2) + " руб.");
        }
    } else
        QMessageBox::warning(this, "Некорретные данные", "Введите реальные значения!");
}


void MainWindow::on_pushButton_clicked()
{
    ui->label_summ->clear();
    ui->label_monthpay->clear();
    ui->label_overpay->clear();
    ui->line_summ->cleanText();
    ui->line_percent->cleanText();
    ui->line_time->cleanText();
}

