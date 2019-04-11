#include "shootcommand.h"
#include "mainwindow.h"
#include <QThread>
#include <QString>
#include <qdebug.h>
#include <stdio.h>
#include <stdlib.h>


static int stopPoit;
static int runTrue;
static bool exitRun;

shootCommand::shootCommand(char aakkonenTaululle[]){
    strcpy(aakkonenT, aakkonenTaululle);
}
shootCommand::~shootCommand(){
}

void shootCommand::runRun(){
    stopPoit=0;
    runTrue=1;
    exitRun=false;
    // Lataa muuttujat constructorista
    while (stopPoit==0) {
        if(exitRun==false){
            while (exitRun==false) {
                // system(aakkonenT);

                qDebug()<< "sisempi Thread: " <<currentThreadId();
                sleep(1);
            }
        }
        sleep(1);
    }
    emit finished();

}

void shootCommand::test(){
    //std::cout << aakkonenT << std::endl;
    qDebug()<< "Test" << " " ;

}

void shootCommand::stop(){
    exitRun=true;
    qDebug()<< "stap" << " " ;
}

void shootCommand::runAgen(){
    exitRun=0;
}
