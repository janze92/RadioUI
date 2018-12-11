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

class blthallinta;
class usbctl;
class radioloader;
class pahallinta;
class threading;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
     void on_volumeSlider_valueChanged(int value);

     void on_tabWidget_tabBarClicked();

signals:
     void arvoMuuttunut(int arvo);

private slots:
    void store_line(std::string nimi, std::string osoite, int i);

    void config();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_pushButton_6_pressed();

    void on_mute_pressed();

    void on_usbnet_pressed();

    void on_volumeUp_pressed();

    void on_button_quit_pressed();

    void on_volumeUp_released();

    void on_volumeDown_pressed();

    void on_volumeDown_released();

    void on_power_released();

    void on_delay_power_pressed();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#include "blthallinta.h"
#include "usbctl.h"
#include "radioloader.h"

#endif // MAINWINDOW_H
