#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QString username, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    static int **bookedBoxes = new int *[3];
    for (int i = 0; i < 3; i++)
    {
        bookedBoxes[i] = new int[5];
        for (int j = 0; j < 5; j++)
        {
            bookedBoxes[i][j] = -1;
        }
    }
    if (!m_userInfo.dbOpen())
        ui->label->setText("Failed");
    else
    {
        QSqlQuery query;
        QString queryStirng = "SELECT spot FROM main";
        query.exec(queryStirng);
        while (query.next())
        {
            QSqlRecord record = query.record();
            int i = record.value(0).toInt() / 10;
            int j = record.value(0).toInt() % 10;
            bookedBoxes[i][j] = (QString::number(i) + QString::number(j)).toInt();
        }

        queryStirng = "SELECT spot, start FROM main WHERE username='" + username + "'";
        query.exec(queryStirng);
        while (query.next())
        {
            QSqlRecord record = query.record();
            bool booked = (record.value("spot").toInt() != -1);
            if (booked)
            {
                ui->label->setText("Already Booked");
                ui->pushButton_book->setDisabled(true);
                ui->pushButton_book->setText("Booked");
            }
            else
            {
                ui->label->setText("Please select a parking spot");
                ui->pushButton_book->setDisabled(false);
            }
            m_user = User(username, record.value("spot").toInt(), record.value("start").toInt(), booked);
        }
    }
    setupSpots(bookedBoxes, 3, 5);
}

void MainWindow::setupSpots(int **bookedBoxes, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        m_myBoxes.push_back(std::vector<Box *>());
        for (int j = 0; j < column; j++)
        {
            int spot = (QString::number(i) + QString::number(j)).toInt();
            Box *newBox = new Box(this);
            newBox->setFixedSize(QSize(100, 150));
            if (m_user.isBooked)
            {
                newBox->setCheckable(false);
                newBox->setCursor(Qt::ArrowCursor);
            }

            if (spot == bookedBoxes[i][j])
            {
                newBox->setDisabled(true);
                newBox->setActive(true);
            }
            m_myBoxes[i].push_back(newBox);
            ui->gridLayout->addWidget(m_myBoxes[i][j], i, j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    m_userInfo.dbClose();
}

QString MainWindow::getSpotCoor()
{
    for (int i = 0; i < m_myBoxes.size(); i++)
    {
        for (int j = 0; j < m_myBoxes[i].size(); j++)
        {
            if (m_myBoxes[i][j]->isChecked())
            {
                return QString::number(i) + QString::number(j);
            }
        }
    }
    return "";
}

void MainWindow::on_pushButton_book_clicked()
{
    std::time_t now = std::time(0);
    QString s = QString::number(now);
    QString spot = getSpotCoor();
    QString commandString = "UPDATE main SET spot='" + spot + "', start=" + s + " WHERE username = '" + m_user.username + "'";
    QSqlQuery query;
    query.exec(commandString);
    this->close();
}

void MainWindow::on_pushButton_close_clicked()
{
    std::time_t bookEndTime = std::time(0);
    auto difference = bookEndTime - m_user.bookStartTime;
    QString timeString = QString::number(difference);
    ui->label->setText(timeString);

    QString dialogMessage = "Your parked time is: " + QString::number(difference);
    auto reply = QMessageBox::information(this, "Close Spot", dialogMessage, QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QString commandString = "UPDATE main SET spot= -1, start= -1 WHERE username = '" + m_user.username + "'";
        QSqlQuery query;
        query.exec(commandString);
        this->close();
    }
}
