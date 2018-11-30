#include "mainwindow.h"
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

 using namespace std;

// julkiset muuttujat
static bool debug=true;
static int netti=0;
static int soi=0;
static pid_t PID=-1;
static string kanavalista[6];
static bool volUP=false;
static bool volDN=false;
static const int num_threads = 1;
static int volume;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(debug == false){
    QTimer::singleShot(1000, this, SLOT(showFullScreen()));
    }
    QTimer::singleShot(100,this, SLOT(on_tabWidget_tabBarClicked()));
    QTimer::singleShot(100,this, SLOT(backRunnerCall()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test(){
    const char *homePath = getenv("HOME");
    if(homePath != nullptr)
    {
        QProcess Home;
        Home.start("echo",QStringList() << homePath);
        Home.waitForFinished(-1);
        qDebug() << Home.readAllStandardOutput();
    }
}

void volumeUP(){
    system("pamixer --increase 1");
}

void volumeDN(){
    system("pamixer --decrease 1");
}
string volumeGet(string cmd) {
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != nullptr) data.append(buffer);
    pclose(stream);
    }
    return data;
}

void call_from_thread() {
    while (true) {
        if(volUP==true){
            volumeUP();
            usleep(50000);
        }
        if(volDN==true){
            volumeDN();
            usleep(50000);
        }
        usleep(10000);
    }
}

void MainWindow::backRunnerCall(){
    std::thread t[num_threads];
    t[0] = std::thread(call_from_thread);
    t[0].detach();
}
void MainWindow::readConfigFile(const char* filename, list<string>& lines)
{
    lines.clear();
    ifstream file(filename);
    string s;
    while (getline(file, s))
        lines.push_back(s);
}

void radio(int i)
{
    PID=fork();
    if(PID == -1){
        puts("Fatalisti meni vituks");
    }
    if(PID != 0 ){
        cout << PID << "\n";
    }

    if(PID == 0){
        switch (i) {
        case 1: {
            char const *kanava = kanavalista[0].c_str();
            execl("/usr/bin/mpv", "mpv",kanava ,NULL);
            break;
        }
        case 2: {
            char const *kanava = kanavalista[1].c_str();
            execl("/usr/bin/mpv", "mpv",kanava ,NULL);
            break;
        }
        case 3: {
            char const *kanava = kanavalista[2].c_str();
            execl("/usr/bin/mpv", "mpv",kanava ,NULL);
            break;
        }
        case 4: {
            char const *kanava = kanavalista[3].c_str();
            execl("/usr/bin/mpv", "mpv",kanava ,NULL);
            break;
        }
        case 5: {
            char const *kanava = kanavalista[4].c_str();
            execl("/usr/bin/mpv", "mpv",kanava ,NULL);
            break;
        }
        case 6: {
            char const *kanava = kanavalista[5].c_str();
            execl("/usr/bin/mpv", "mpv",kanava ,NULL);
            break;
        }
        }
    }
}


void loadnetti(){
    // TODO: legit check that adb is running and every command get executed
    char tmuxRun[]="tmux send-keys -t tetherUSB.0 'adb shell' ENTER";
    char tmuxRun2[]="tmux send-keys -t tetherUSB.0 'service call connectivity 34 i32 1 s16 text' ENTER";
    char tmuxRun3[]="tmux send-keys -t tetherUSB.0 'exit' ENTER";
    system("tmux new -d -s tetherUSB");
    sleep(1);
    system(tmuxRun);
    sleep(1);
    system(tmuxRun2);
    sleep(1);
    system(tmuxRun3);
    usleep(100000);
    system(tmuxRun3);
    netti=1;
    if((debug=true)){
    cout << "Ladattu netti \n";
    }
}

void MainWindow::nuppiSetti(){
    int i=stoi( volumeGet("pamixer --get-volume") );
    ui->volumeSlider->setValue(i);

}

void radioCheck(int kanava){
        if(netti == 0){
            netti=1;
            //loadnetti();
        }
        if( soi == 0 ){
            radio(kanava);
            soi=kanava;
        }
        else if( soi == kanava){
            string whatToKill=("kill -3 "+to_string(PID));
            char const *killMe = whatToKill.c_str();
            system(killMe);
            soi=false;
        }
        else if( soi != 0){
            string whatToKill=("kill -3 "+to_string(PID));
            char const *killMe = whatToKill.c_str();
            system(killMe);
            soi=kanava;
            radio(kanava);
        }
        else{
            puts("todo netin lataus!! && launch mpv");
        }
}

void MainWindow::on_mute_pressed()
{
    int isItMuted = system("pamixer --get-mute");
    cout << isItMuted;

    if(isItMuted == 256){
        int i=stoi( volumeGet("pamixer --get-volume") );
        volume = i;
        system("pamixer -m");
        ui->volumeSlider->setValue(0);
        }
    else {
        system("pamixer -u");
        cout << volume << endl;
        ui->volumeSlider->setValue(volume);
    }
}

void MainWindow::on_ylex_pressed()
{
    radioCheck(1);
}

void MainWindow::on_usbnet_pressed()
{
    loadnetti();
}


void MainWindow::on_nrj_pressed()
{
    radioCheck(2);
}

void MainWindow::on_rock_pressed()
{
    radioCheck(3);
}

void MainWindow::on_suomipop_pressed()
{
    radioCheck(4);
}

void MainWindow::on_radioloop_pressed()
{
    radioCheck(5);
}

void MainWindow::on_hitmix_pressed()
{
    radioCheck(6);
}

void MainWindow::on_tabWidget_tabBarClicked()
{
    nuppiSetti();
    on_reload_pressed();
}

void MainWindow::on_reload_pressed()
{
    // TODO update radio string array
   //todo();
   list<string> linesi;
   readConfigFile("config.conf", linesi);
   cout << "read " << linesi.size() << endl;
   //for (const auto& line : linesi)
   //    cout << line << endl;
   int n=0;
   for (const auto& line : linesi){
       kanavalista[n]=line;
       n++;
   }
}

void MainWindow::on_blobbi_nappo_pressed()
{
    test();
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    if (system(nullptr));
        else exit (EXIT_FAILURE);
    string pamixer = "pamixer --set-volume ";
    string arvo = pamixer +  to_string(value);
    char const *muutetaan = arvo.c_str();
    // system command
    system(muutetaan);
}



void MainWindow::on_volumeUp_pressed()
{
    volUP=true;
}

void MainWindow::on_volumeUp_released()
{
    volUP=false;
    nuppiSetti();
}

void MainWindow::on_button_quit_pressed()
{
    //mpv quit check
    QCoreApplication::quit();
}

void MainWindow::on_volumeDown_pressed()
{
    volDN=true;
}

void MainWindow::on_volumeDown_released()
{
    volDN=false;
    nuppiSetti();
}
