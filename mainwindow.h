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


    void on_mute_pressed();

    void on_ylex_pressed();

    void on_usbnet_pressed();

    void on_nrj_pressed();

    void on_rock_pressed();

    void on_suomipop_pressed();

    void on_radioloop_pressed();

    void on_hitmix_pressed();

    void nuppiSetti();

    void on_tabWidget_tabBarClicked();

    void on_reload_pressed();

    void readConfigFile(const char* filename, std::list<std::string>& lines);

    void test();

    void on_blobbi_nappo_pressed();

    void on_volumeSlider_valueChanged(int value);

    void on_volumeUp_pressed();

    void on_button_quit_pressed();

    void on_volumeUp_released();

    void backRunnerCall();

    void on_volumeDown_pressed();

    void on_volumeDown_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
