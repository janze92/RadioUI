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

int radioloader::controll(int PID, const char *kanavapath, int nbr){
    int hPID=-1;
    if(onoff==-1){
       hPID = Player(PID,kanavapath,nbr);
    }
    else if(muisti == nbr){
       stop(PID);
       hPID=-1;
    }
    else{
        stop(PID);
        usleep(1000);
        hPID = Player(-1,kanavapath,nbr);
    }

    return hPID;
}
void radioloader::stop(int PID){
        if(PID != -1){
        std::string whatToKill=("kill -3 "+std::to_string(PID));
        char const *killMe = whatToKill.c_str();
        system(killMe);
        muisti=-1;
        onoff=-1;
        }
        else
            std::cout << "ei tääne kuulu mennä.." << std::endl;
}

int radioloader::Player(int PID, const char *kanava, int soiko){
        if(PID == -1){
            PID=fork();
        }

        if(PID == 0){
                execl("/usr/bin/mpv", "mpv",kanava, nullptr);
        }
        muisti=soiko;
        onoff=1;
        return PID;
}
