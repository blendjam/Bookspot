#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myBox = new Box("", this);
    myBox->show();
    Box* newBox = new Box("", this);
    newBox->show();
    newBox->move(QPoint(100, 100));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton_2->setIcon(QIcon(":/resourses/img/student.png"));
    ui->pushButton_2->setIconSize(QSize(80, 80));
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton_2->setIcon(QIcon());
}
