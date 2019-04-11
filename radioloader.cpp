#include "radioloader.h"
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
static int muisti=-1;
static int onoff=-1;

int radioloader::controll(int PID, const char *kanavapath, int nbr, int FM){
    int hPID=-1;
    if(onoff==-1){
       hPID = Player(PID,kanavapath,nbr,FM);
    }
    else if(muisti == nbr){
       stop(PID);
       hPID=-1;
    }
    else{
        stop(PID);
        usleep(1000);
        hPID = Player(-1,kanavapath,nbr,FM);
    }

    return hPID;
}
void radioloader::stop(int PID){
        if(PID != -1){
        system("killall rtl_fm");
        std::string whatToKill=("kill -3 "+std::to_string(PID));
        char const *killMe = whatToKill.c_str();
        system(killMe);
        muisti=-1;
        onoff=-1;
        }
        else
            std::cout << "ei tääne kuulu mennä.." << std::endl;
}

int radioloader::Player(int PID, const char *kanava, int soiko, int FM){
        if(PID == -1){
            PID=fork();
        }

        if(PID == 0){
            if(FM == 0){
                execl("/usr/bin/mpv", "mpv",kanava, nullptr);
            }
            else {
                // radio rtl_fm -f 90.1M -M fm -s 800k -o 4 -A fast -r 48000 -l 0 -E deemp - | aplay -D pulse  -r 48000 -f S16_LE
                // Kanavaan koko helvetin rtl taajuus rimpsu
                std::cout << kanava << std::endl;
                //execl("/usr/bin/rtl_fm", "rtl_fm",kanava, nullptr); uudelleen ohjaus????
                system(kanava);
            }
        }
        muisti=soiko;
        onoff=1;
        return PID;
}
