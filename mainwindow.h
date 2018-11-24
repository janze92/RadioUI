#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
