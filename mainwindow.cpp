#include "mainwindow.h"
#include "pahallinta.h"
#include "radioloader.h"
#include "threading.h"
#include "usbctl.h"
#include "blthallinta.h"
#include "shootcommand.h"
#include "ui_Main.h"
#include "stdlib.h"  /* system lib */
#include "stdio.h"
#include "unistd.h"
#include "iostream"
#include "string"
#include "sstream" // blah
#include "fcntl.h"
#include "errno.h"
#include "sys/wait.h"
#include "fstream"
#include <list>
#include <iterator>
#include <QTimer>
#include <QByteArray>
#include <cstdlib>
#include <QProcess>
#include <QDebug>
#include <pthread.h>
#include <thread>
#include "QThread"
#include <QString>
#include <qpalette.h>

#include <QtWebKit/QWebHistory>
#include <QtWebKit/QWebHistoryItem>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebPage>

// for signal passing testing
#include <QAction>


 using namespace std;

// julkiset muuttujat
static bool debug=true;

static char xmmsHack[16]="bash watcher.sh";
static char xmmsTouch[24]="touch /tmp/todoxmms.txt";

// static int netti=0;
static pid_t pidi=-1;
static string kanavalista[6];
static std::string kanavanimet[5];
static bool volUP=false;
static bool volDN=false;
static bool startting=true;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QTimer::singleShot(100,this,SLOT(config()));
    ui->setupUi(this);
    if(debug == false){
    QTimer::singleShot(1000, this, SLOT(showFullScreen()));
    }
    this->setStyleSheet("background-color: #5d5b59;");
    QTimer::singleShot(10,this, SLOT(on_tabWidget_tabBarClicked()));

    if(startting == true){
     // Prepairing for local player controll hack..
     system(xmmsTouch);
     //
     QThread* xmms = new QThread; // nimeä tähän sillee et ymmärtää mistä menee minne päin bitti
     shootCommand* xmmsSaije = new shootCommand(xmmsHack);
     xmmsSaije->moveToThread(xmms);
     connect(xmms, SIGNAL(started()), xmmsSaije, SLOT(runRun())); // jääkö while looppaava ns odottamaan loopin loppua ennen uuden
     connect(xmmsSaije, SIGNAL(finished()), xmms, SLOT(quit()));  // funktion aloitusta?? // tekeekö muistivuodon jos ei kutsu ikinä quit();
     connect(xmmsSaije, SIGNAL(finished()), xmmsSaije, SLOT(deleteLater()));
     connect(xmms, SIGNAL(finished()), xmms, SLOT(deleteLater()));
     xmms->start();
     //
    QThread* kissa = new QThread;
    threading* koira = new threading();  // header jolta huudetaan funktio ja jonka nimi näemmä on tuo threading...... :D
    koira->moveToThread(kissa);
    connect(koira, SIGNAL(VolumeChanged()), this, SLOT(on_tabWidget_tabBarClicked())); // ohjataan signaali volume changed -> on_tab..
   // connect(koira, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(kissa, SIGNAL(started()), koira, SLOT(suorita())); //functio threading.cpp alla = run()...
    connect(koira, SIGNAL(finished()), kissa, SLOT(quit())); // hallitaan koiran koppiin paluu..
    connect(koira, SIGNAL(finished()), koira, SLOT(deleteLater()));
    connect(kissa, SIGNAL(finished()), kissa, SLOT(deleteLater()));
    kissa->start();
//    QThread* robotti = new QThread;
//    usbctl* robotinSaije = new usbctl();
//    robotinSaije->moveToThread(robotti);
//    connect(robotinSaije, SIGNAL(loaded()), this, SLOT(signal_handler()));
//    connect(robotti, SIGNAL(started()), robotinSaije, SLOT(startUp()));
//    robotti->start();
//    QThread* doge = new QThread;
//    usbctl* dogeSaije = new usbctl();
//    dogeSaije->moveToThread(doge);
//    connect(dogeSaije, SIGNAL(loaded()), this, SLOT(signal_handler()));
//    connect(doge, SIGNAL(started()), dogeSaije, SLOT(status()));
//    doge->start();
    startting=false;
    }

    // testataas tähän pääloopin sisään laittaa .. haisee pahalle idealle :P

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::signal_handler(){
    // hallitaas robotilta tulevaa signaalia
}

void MainWindow::workHorse(int wut){
    if (wut == 1){

    }
    else {
        // no defined what want to do
//        char i[]="";
//        shootCommand kommari(i);
//        kommari.stop();
    }
}

void MainWindow::on_pushButton_pressed()
{
    radioloader obj;
    pidi = obj.controll(pidi,kanavalista[0].c_str(),0);
    std::cout << "Pid: " << pidi << std::endl;
}
void MainWindow::on_pushButton_2_pressed()
{
    radioloader obj;
    pidi = obj.controll(pidi,kanavalista[1].c_str(),1);
    std::cout << "Pid: " << pidi << std::endl;
}

void MainWindow::on_pushButton_3_pressed()
{
    radioloader obj;
    pidi = obj.controll(pidi,kanavalista[2].c_str(),2);
    std::cout << "Pid: " << pidi << std::endl;
}

void MainWindow::on_pushButton_4_pressed()
{
    radioloader obj;
    pidi = obj.controll(pidi,kanavalista[3].c_str(),3);
    std::cout << "Pid: " << pidi << std::endl;
}

void MainWindow::on_pushButton_5_pressed()
{
    radioloader obj;
    pidi = obj.controll(pidi,kanavalista[4].c_str(),4);
    std::cout << "Pid: " << pidi << std::endl;
}

void MainWindow::on_pushButton_6_pressed()
{
    radioloader obj;
    pidi = obj.controll(pidi,kanavalista[5].c_str(),5);
    std::cout << "Pid: " << pidi << std::endl;
}

void MainWindow::on_mute_pressed()
{
    pahallinta pah;
    ui->volumeSlider->setValue(pah.mute());
}

void MainWindow::on_usbnet_pressed()
{
    QThread* robotti = new QThread;
    usbctl* robotinSaije = new usbctl();
    robotinSaije->moveToThread(robotti);
    connect(robotinSaije, SIGNAL(loaded()), this, SLOT(signal_handler()));  // joku netti iconi etu sivulle
    connect(robotti, SIGNAL(started()), robotinSaije, SLOT(loadPhone()));
    robotti->start();
}

void MainWindow::on_tabWidget_tabBarClicked()
{
    pahallinta paha;
    ui->volumeSlider->setValue(paha.volumeGet());
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    pahallinta vola;
    vola.volumelvl(value);
}

void MainWindow::on_volumeUp_pressed()
{
    volUP=true;
    threading Fola;
    Fola.volumeUP(1);
}

void MainWindow::on_volumeUp_released()
{
    volUP=false;
    threading Fola;
    Fola.volumeUP(0);
}

void MainWindow::on_volumeDown_pressed()
{
    volDN=true;
    threading Fola;
    Fola.volumeDown(1);
}

void MainWindow::on_volumeDown_released()
{
    volDN=false;
    threading Fola;
    Fola.volumeDown(0);
}


void MainWindow::on_button_quit_pressed()
{
    if(pidi !=-1){
    string whatToKill=("kill -3 "+to_string(pidi));
    char const *killMe = whatToKill.c_str();
    system(killMe);
}
    //mpv quit check
    QCoreApplication::quit();
}

void MainWindow::on_power_released()
{
    if(debug == false){
    system("poweroff");
    }
    else{
        system("echo sammuttas mutta on debug päällä..");
        on_button_quit_pressed();
    }
}

void MainWindow::store_line(std::string nimi, std::string osoite, int i){
    kanavalista[i]=osoite;
    kanavanimet[i]=nimi;
    switch (i) {
    case 0 : {
        const char *nt = kanavanimet[i].c_str();
        ui->pushButton->setText(nt);
        break;
    }
    case 1 : {
        const char *nt = kanavanimet[i].c_str();
        ui->pushButton_2->setText(nt);
        break;
    }
    case 2 : {
        const char *nt = kanavanimet[i].c_str();
        ui->pushButton_3->setText(nt);
        break;
    }
    case 3 : {
        const char *nt = kanavanimet[i].c_str();
        ui->pushButton_4->setText(nt);
        break;
    }
    case 4 : {
        const char *nt = kanavanimet[i].c_str();
        ui->pushButton_5->setText(nt);
        break;
    }
    case 5 : {
        const char *nt = kanavanimet[i].c_str();
        ui->pushButton_6->setText(nt);
        break;
    }
    }
}

void MainWindow::config(){

    std::ifstream is_file("config.conf");

    std::string line;
    int i = 0;
    while( std::getline(is_file, line) )
    {
      std::istringstream is_line(line);
      std::string key;
      if( std::getline(is_line, key, '=') )
      {
        std::string value;
        if( std::getline(is_line, value) )
          store_line(key, value, i);
      }
      i++;
    }
}


void MainWindow::on_delay_power_pressed()
{
    QTimer::singleShot(60000, this, SLOT(on_power_released()));
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        this->setStyleSheet("background-color: #35322f;");
    }
    if(arg1 == 0){
        this->setStyleSheet("background-color: #5d5b59;");
        //5d5b59 868482
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    std::cout <<  "Index="<< index << std::endl;
    if (index == 1){
        workHorse(1);
    }
}

void MainWindow::on_emitteri_clicked()
{
    char i[]="";
    shootCommand kommari(i);
    kommari.stop();
}

void MainWindow::on_emittest_pressed()
{
    char i[]="";
    shootCommand kommari(i);
    kommari.runAgen();
}
