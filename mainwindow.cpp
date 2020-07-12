#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < 3; i++) {
        myBoxes.push_back(std::vector<Box*>());
        for (int j = 0; j < 5; j++) {
            Box* newBox = new Box("", this);
            newBox->setFixedSize(QSize(100, 100));
            myBoxes[i].push_back(newBox);
            ui->gridLayout->addWidget(myBoxes[i][j], i, j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_close_clicked()
{
}
