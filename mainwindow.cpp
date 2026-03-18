#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QString>

double memoryNumber;
QChar pendingOperation;
bool waitingForNewNumber = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    connect(ui->button_0, &QPushButton::clicked,this, &MainWindow::digit_pressed);
    connect(ui->button_1, &QPushButton::clicked,this, &MainWindow::digit_pressed);
    connect(ui->button_2, &QPushButton::clicked,this, &MainWindow::digit_pressed);
    connect(ui->button_3, &QPushButton::clicked,this, &MainWindow::digit_pressed);
    connect(ui->button_4, &QPushButton::clicked,this, &MainWindow::digit_pressed);
    connect(ui->button_5, &QPushButton::clicked,this, &MainWindow::digit_pressed);
    connect(ui->button_6, &QPushButton::clicked,this, &MainWindow::digit_pressed);
    connect(ui->button_7, &QPushButton::clicked,this, &MainWindow::digit_pressed);
    connect(ui->button_8, &QPushButton::clicked,this, &MainWindow::digit_pressed);
    connect(ui->button_9, &QPushButton::clicked,this, &MainWindow::digit_pressed);

    connect(ui->percent_button, &QPushButton::clicked, this, &MainWindow::unary_operators);
    connect(ui->plus_minus_button, &QPushButton::clicked, this, &MainWindow::unary_operators);

    connect(ui->divide_button, &QPushButton::clicked, this, &MainWindow::signal_operators);
    connect(ui->multiply_button, &QPushButton::clicked, this, &MainWindow::signal_operators);
    connect(ui->minus_button, &QPushButton::clicked, this, &MainWindow::signal_operators);
    connect(ui->plus_button, &QPushButton::clicked, this, &MainWindow::signal_operators);
    connect(ui->equal_button, &QPushButton::clicked, this, &MainWindow::signal_operators);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed(){
    QPushButton * button = (QPushButton*)sender();
    double labelNumber;
    QString newLabel;

    if (waitingForNewNumber){
        newLabel = button->text ();
        waitingForNewNumber = false;
    } else {
        labelNumber = (ui->label->text() + button->text()).toDouble();
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }

    ui->label->setText (newLabel);
}

void MainWindow::on_decimal_button_clicked()
{
    ui->label->setText(ui->label->text () + ".");
}

void MainWindow::on_clear_button_clicked()
{
    memoryNumber = 0;
    ui->label->setText ("0");
}

void MainWindow::unary_operators()
{
    QPushButton * button = (QPushButton*)sender();
    double labelNumber;
    QString newLabel;

    labelNumber = ui->label->text ().toDouble ();

    if (button->text() == "+/-"){labelNumber = labelNumber * -1;}
    else {labelNumber = labelNumber / 100;}

    newLabel = QString::number(labelNumber, 'g', 15);
    ui->label->setText (newLabel);
}

void MainWindow::signal_operators(){
    QPushButton * button = (QPushButton* )sender();
    QChar c = button->text()[0];
    double labelNumber;

    labelNumber = ui->label->text().toDouble ();

    switch (c.unicode ()) {
    case '/':
        memoryNumber = labelNumber;
        pendingOperation = '/';
        waitingForNewNumber = true;
        break;

    case 'x':
        memoryNumber = labelNumber;
        pendingOperation = 'x';
        waitingForNewNumber = true;
        break;

    case '+':
        memoryNumber = labelNumber;
        pendingOperation = '+';
        waitingForNewNumber = true;

        break;

    case '-':
        memoryNumber = labelNumber;
        pendingOperation = '-';
        waitingForNewNumber = true;
        break;

    case '=':
        double result;
        result = 0;

        if (pendingOperation == '/'){result = memoryNumber / labelNumber;}
        if (pendingOperation == 'x'){result = memoryNumber * labelNumber;}
        if (pendingOperation == '+'){result = memoryNumber + labelNumber;}
        if (pendingOperation == '-'){result = memoryNumber - labelNumber;}

        ui->label->setText(QString::number(result));
        break;

    default:
        break;
    }
}
