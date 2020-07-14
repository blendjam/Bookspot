#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < 3; i++)
    {
        myBoxes.push_back(std::vector<Box *>());
        for (int j = 0; j < 5; j++)
        {
            Box *newBox = new Box("", this);
            newBox->setFixedSize(QSize(100, 150));
            myBoxes[i].push_back(newBox);
            ui->gridLayout->addWidget(myBoxes[i][j], i, j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

const char* MainWindow::getDurationString(std::chrono::duration<float> dur){
    std::string str = std::to_string(dur.count());
    return str.c_str();
}

void MainWindow::on_pushButton_book_clicked()
{
    bookStartTime = std::chrono::high_resolution_clock::now();
}

void MainWindow::on_pushButton_close_clicked()
{
    bookEndTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = bookEndTime - bookStartTime;

    auto durationCharArray = getDurationString(duration);

    ui->label->setText(durationCharArray);
}
