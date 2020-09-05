#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "locations.h"

MainWindow::MainWindow(QString username, QString locationID, QString city, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), locationID(locationID), city(city)
{
    ui->setupUi(this);
    if (username == "ADMINADMIN") {
        isAdmin = true;
        ui->pushButton_book->hide();
        ui->pushButton_back->setText("Close");
    }
    else{
        isAdmin = false;
    }

    bookedBoxes = new int *[3];
    for (int i = 0; i < 3; i++)
    {
        bookedBoxes[i] = new int[5];
        for (int j = 0; j < 5; j++)
        {
            bookedBoxes[i][j] = -1;
        }
    }

    bookedBoxes = getBookedBoxes();
    QSqlQuery query;
    QString queryStirng = "SELECT spot, start FROM Users WHERE username='" + username + "'";
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

    //    qDebug() << m_user.username << m_user.spot << m_user.bookStartTime << m_user.isBooked;
    setupSpots(3, 5);
}

int **MainWindow::getBookedBoxes()
{
    QSqlQuery query;
    QString queryStirng = "SELECT spot FROM Users WHERE location = '" + locationID + "' AND city = '"+city+"'";
    query.exec(queryStirng);
    while (query.next())
    {
        QSqlRecord record = query.record();
        int i = record.value(0).toInt() / 10;
        int j = record.value(0).toInt() % 10;
        bookedBoxes[i][j] = (QString::number(i) + QString::number(j)).toInt();
    }
    return bookedBoxes;
}

void MainWindow::setupSpots(int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        m_myBoxes.push_back(std::vector<Box *>());
        for (int j = 0; j < column; j++)
        {
            int spot = i * 10 + j;
            Box *newBox = new Box(this);
            newBox->setFixedSize(QSize(100, 150));
            if (m_user.isBooked || isAdmin)
            {
                newBox->setCheckable(false);
                newBox->setCursor(Qt::ArrowCursor);
            }

            if (spot == bookedBoxes[i][j])
            {
                newBox->setDisabled(true);
            }
            m_myBoxes[i].push_back(newBox);
            ui->gridLayout->addWidget(m_myBoxes[i][j], i, j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getSpotCoor()
{
    for (int i = 0; i < (int)m_myBoxes.size(); i++)
    {
        for (int j = 0; j < (int)m_myBoxes[i].size(); j++)
        {
            if (m_myBoxes[i][j]->isChecked())
            {
                return QString::number(i) + QString::number(j);
            }
        }
    }
    return "";
}

void MainWindow::disableSpots(QString spot)
{
    int i = spot.toInt() / 10;
    int j = spot.toInt() % 10;
    m_myBoxes[i][j]->setDisabled(true);

    for (int i = 0; i < (int)m_myBoxes.size(); i++)
    {
        for (int j = 0; j < (int)m_myBoxes[i].size(); j++)
        {
            m_myBoxes[i][j]->setCheckable(false);
            m_myBoxes[i][j]->setCursor(Qt::ArrowCursor);
        }
    }
    ui->pushButton_book->setDisabled(true);
    ui->pushButton_book->setText("Booked");
}

void MainWindow::on_pushButton_book_clicked()
{
    auto reply = QMessageBox::information(this, "Confirmation", "Are you sure?", QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        m_user.bookStartTime = std::time(0);
        QString start = QString::number(m_user.bookStartTime);
        QString spot = getSpotCoor();
        QString commandString = "UPDATE Users SET spot=" + spot + ", start=" + start + ", location = '" + locationID + "', city = '" +city+ "' WHERE username = '" + m_user.username + "'";
        QSqlQuery query;
        query.exec(commandString);
        disableSpots(spot);
    }
}

void MainWindow::on_pushButton_back_clicked()
{
    if (!isAdmin) {
        Locations * locationDialog = new Locations(m_user.username);
        locationDialog->show();
        this->close();
    }
    else {
        this->close();
    }
}
