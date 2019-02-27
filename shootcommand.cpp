#include "shootcommand.h"
#include "mainwindow.h"
#include <QThread>
#include <QString>
#include <qdebug.h>
#include <stdio.h>
#include <stdlib.h>


shootCommand::shootCommand(){
}
shootCommand::~shootCommand(){
}

void shootCommand::mitavittua(){
    std::system("echo hello");
    std::system("echo ... > /tmp/toimii");
    emit finished();
}

void shootCommand::inttiboi(int i){
    std::system("echo hello");
    std::system("echo ... > /tmp/toimii");
    emit finished();
}

void shootCommand::suoritaKomento(const char* komento){
        std::system(komento);
        qDebug("Hello World!");
        emit finished();
}
