#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <ctime>
#include <vector>
#include <QSqlQuery>

#include "box.h"
#include "user.h"

namespace Ui
{
    class MainWindow;
} // namespace Ui

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString username, QString locationID, QString city, QString type = "", QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_book_clicked();

    void on_pushButton_back_clicked();

private:
    void setupSpots(int row, int column);
    int **getBookedBoxes();
    void disableSpots(QString spot);
    QString getSpotCoor();

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<Box *>> m_myBoxes;
    User m_user;
    int **bookedBoxes;
    QString locationID;
    QString city;
    QString vehicleType;
    bool isAdmin;
};

#endif // MAINWINDOW_H
