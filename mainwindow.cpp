#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    login connection;
    if (!connection.dbOpen()) {
        ui->label_status->setText("Failed to login");
    } else {
        ui->label_status->setText("Success");
    }
}
