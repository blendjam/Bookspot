#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QString username, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), username(username)
{
    ui->setupUi(this);

    if (!userInfo.dbOpen())
        ui->label->setText("Failed");
    else
        ui->label->setText("Opened");
    setupSpots(3, 5);
}

void MainWindow::setupSpots(int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        myBoxes.push_back(std::vector<Box *>());
        for (int j = 0; j < column; j++)
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
    userInfo.dbClose();
}

void MainWindow::on_pushButton_book_clicked()
{
    bookStartTime = std::time(0);
    QString s = QString::number(bookStartTime);
    QString commandString = "UPDATE main SET start=" + s + " WHERE username = '" + username + "'";
    ui->label->setText(s);

    QSqlQuery query;
    query.exec(commandString);
}

void MainWindow::on_pushButton_close_clicked()
{
    std::time_t bookEndTime = std::time(0);

    auto difference = bookEndTime - bookStartTime;

    std::string s = std::to_string(difference);
    const char *timeChar = s.c_str();

    ui->label->setText(timeChar);
}
