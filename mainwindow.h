#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <ctime>
#include <vector>
#include <QSqlQuery>

#include "box.h"
#include "login.h"

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
    void executeQuery(QString queryCommand);

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<Box *>> myBoxes;
    std::time_t bookStartTime;
    QString username;
    int boxCount;
    Login userInfo;
};

#endif // MAINWINDOW_H
