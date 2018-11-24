#include "mainwindow.h"
#include "ui_Main.h"
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

// julkiset muuttujat
int netti=0;
int soi=0;
int blob=-4;
bool debug=true;
pid_t PID=-1;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string volumeGet(std::string cmd) {



    std::string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
    }
    return data;
}


void radio(int i)
{
    PID=fork();
    if(PID == -1){
        puts("Fatalisti meni vituks");
    }
    if(PID != 0 ){
        std::cout << PID << "\n";
    }

    if(PID == 0){
        switch (i) {
        case 1: {
            execl("/usr/bin/mpv", "mpv", "/home/janze/Music/ylex.m3u8",NULL);
            break;
        }
        case 2: {
            execl("/usr/bin/mpv", "mpv", "http://cdn.nrjaudio.fm/adwz1/fi/35001/mp3_128.mp3",NULL);
            break;
        }
        case 3: {
            execl("/usr/bin/mpv", "mpv", "https://digitacdn.akamaized.net/hls/live/629243/radiorock/master-128000.m3u8",NULL);
            break;
        }
        case 4: {
            execl("/usr/bin/mpv", "mpv", "https://digitacdn.akamaized.net/hls/live/629243/radiosuomipop/master.m3u8",NULL);
            break;
        }
        case 5: {
            execl("/usr/bin/mpv", "mpv", "https://digitacdn.akamaized.net/hls/live/629243/loop/master-128000.m3u8",NULL);
            break;
        }
        case 6: {
            execl("/usr/bin/mpv", "mpv", "https://digitacdn.akamaized.net/hls/live/629243/hitmix/master-128000.m3u8",NULL);
            break;
        }

            /*
                https://digitacdn.akamaized.net/hls/live/629243/radiosuomipop/master.m3u8
                https://digitacdn.akamaized.net/hls/live/629243/loop/master-128000.m3u8
                https://digitacdn.akamaized.net/hls/live/629243/hitmix/master-128000.m3u8


            */
        }
    }
}


void loadnetti(){
    char tmuxRun[]="tmux send-keys -t tetherUSB.0 'adb shell' ENTER";
    char tmuxRun2[]="tmux send-keys -t tetherUSB.0 'service call connectivity 34 i32 1 s16 text' ENTER";
    char tmuxRun3[]="tmux send-keys -t tetherUSB.0 'exit' ENTER";
    std::system("tmux new -d -s tetherUSB");
    sleep(1);
    std::system(tmuxRun);
    sleep(1);
    std::system(tmuxRun2);
    sleep(1);
    std::system(tmuxRun3);
    usleep(100000);
    std::system(tmuxRun3);
    netti=1;
    if((debug=true)){
    std::cout << "Ladattu netti \n";
    }
}

void MainWindow::nuppiSetti(){
    int i=std::stoi( volumeGet("pamixer --get-volume") );
    ui->dial->setValue(i);
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
            std::string whatToKill=("kill -3 "+std::to_string(PID));
            char const *killMe = whatToKill.c_str();
            std::system(killMe);
            soi=false;
        }
        else if( soi != 0){
            std::string whatToKill=("kill -3 "+std::to_string(PID));
            char const *killMe = whatToKill.c_str();
            std::system(killMe);
            soi=kanava;
            radio(kanava);
        }
        else{
            puts("todo netin lataus!! && launch mpv");
        }
}



void MainWindow::on_dial_valueChanged(int value)
{
    if (system(nullptr));
        else exit (EXIT_FAILURE);
    std::string pamixer = "pamixer --set-volume ";
    std::string arvo = pamixer +  std::to_string(value);
    char const *muutetaan = arvo.c_str();
    // system command
    std::system(muutetaan);
}


void MainWindow::on_exit_pressed()
{
    QCoreApplication::quit();
}
void MainWindow::on_mute_pressed()
{
    int isItMuted = std::system("pamixer --get-mute");
    std::cout << isItMuted;

    if(isItMuted == 256){
        std::system("pamixer -m");
        }
    else {
        std::system("pamixer -u");
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

void MainWindow::on_exit_2_pressed()
{
    nuppiSetti();
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    nuppiSetti();
}
