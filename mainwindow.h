#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "box.h"
#include <QDebug>
#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_close_clicked();

private:
    Ui::MainWindow* ui;
    std::vector<std::vector<Box*>> myBoxes;
};

#endif // MAINWINDOW_H
