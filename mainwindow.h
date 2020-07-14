#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "box.h"
#include <QDebug>
#include <QMainWindow>
#include <QGridLayout>
#include <chrono>
#include <vector>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    const char* getDurationString(std::chrono::duration<float> dur);

private slots:

    void on_pushButton_book_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<Box *>> myBoxes;
    std::chrono::_V2::system_clock::time_point bookStartTime;
    std::chrono::_V2::system_clock::time_point bookEndTime;
};

#endif // MAINWINDOW_H
