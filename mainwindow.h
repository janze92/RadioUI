#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdlib.h"  /* system lib */
#include "stdio.h"
#include "unistd.h"
#include "iostream"
#include "string"
#include "thread"
#include "sstream" // blah
#include "fcntl.h"
#include "errno.h"
#include "sys/wait.h"
#include "fstream"
#include <list>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_dial_valueChanged(int value);

    void on_exit_pressed();

    void on_mute_pressed();

    void on_ylex_pressed();

    void on_usbnet_pressed();

    void on_nrj_pressed();

    void on_rock_pressed();

    void on_suomipop_pressed();

    void on_radioloop_pressed();

    void on_hitmix_pressed();

    void nuppiSetti();

    void on_exit_2_pressed();

    void on_tabWidget_tabBarClicked();

    void on_reload_pressed();

    void readConfigFile(const char* filename, std::list<std::string>& lines);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
