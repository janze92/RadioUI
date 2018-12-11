#include "threading.h"
#include <QThread>
#include <QString>
#include <qdebug.h>
#include "pahallinta.h"
#include "mainwindow.h"
static bool volUP=false;
static bool volDN=false;

threading::threading(){

}

threading::~threading(){

}


void threading::suorita(){
        pahallinta m;
        while (true) {

            if(volUP==true){
                m.volumeUP();
                usleep(10000);
                emit VolumeChanged();
                usleep(40000);
            }
            if(volDN==true){
                m.volumeDN();
                usleep(10000);
                emit VolumeChanged();
                usleep(40000);
            }
            usleep(10000);
            if(volDN == true && volUP == true){
                break;
            }
        }
        qDebug("Hello World!");
        emit finished();
}

void threading::volumeUP(int suunta){
    if(suunta == 1){
        volUP = true;
    }
    else {
        volUP=false;
    }
}
void threading::volumeDown(int suunta){
    if(suunta == 1){
        volDN = true;
    }
    else {
        volDN=false;
    }
}
