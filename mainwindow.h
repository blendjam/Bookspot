#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <ctime>
#include <vector>
#include <QSqlQuery>

#include "box.h"
#include "login.h"
#include "user.h"

namespace Ui
{
    class MainWindow;
} // namespace Ui

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString username, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_book_clicked();
    void on_pushButton_close_clicked();

private:
    void setupSpots(int row, int column);
    int **getBookedBoxes(QString username);
    void disableSpots(QString spot);
    QString getSpotCoor();

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<Box *>> m_myBoxes;
    User m_user;
    Login m_userInfo;
    int **bookedBoxes;
};

#endif // MAINWINDOW_H
