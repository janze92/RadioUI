#include "usbctl.h"
#include <QThread>
#include <QString>
#include <qdebug.h>
#include "iostream"
#include <stdexcept>
#include <stdio.h>
#include <string>

static int iplinkN=0;

usbctl::usbctl(){
}
usbctl::~usbctl(){
}
void usbctl::loadPhone(){
    std::cout << "IP link load: " << iplinkN << std::endl; // for testing only

    // TODO: legit check that adb is running and every command get executed
    //  check up what android version is device running
    //
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

    char puskuri[128];
    std::string muutaINT = "";
    FILE* pipe = popen("ip link|wc -l", "r");
    if(!pipe) throw std::runtime_error("popen() fiasco :(");
    try {
        while(fgets(puskuri, sizeof puskuri, pipe) != nullptr){
            iplinkN = std::stoi(puskuri);

        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
}


void usbctl::startUp() { // bugi: iplinkN arvo muuttuu 10 -> 6 function loputtua :o
    bool ladattu=false;
    system("adb start-server");

    char puskuri[128];
    std::string muutaINT = "";
    FILE* pipe = popen("ip link|wc -l", "r");
    if(!pipe) throw std::runtime_error("popen() fiasco :(");
    try {
        while(fgets(puskuri, sizeof puskuri, pipe) != nullptr){
            iplinkN = std::stoi(puskuri);
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }

    std::cout << "IP link: " << iplinkN << std::endl; // for testing only
    while (true) {
        int usbdeviceID = system("lsusb -d 2e04:c026");
        usleep(1000000);
        std::cout << "looppaa" << std::endl;
        std::cout << "IP link: " << iplinkN << std::endl; // for testing only

        if(usbdeviceID == 0 && ladattu==false){
            ladattu = true;
            //cout << "ladataan laite" << endl;
            loadPhone();
            std::cout << " lol emitteddi" << std::endl;
            emit loaded();
            // emit loadPhone tai lataa suoraa
            }
        if(ladattu == true)
            break;
    }

}

void usbctl::status(){ // bugi QTcreatorissa ?

    while (true) {
        msleep(5000);
        std::cout << "IP link status: " << iplinkN << std::endl; // for testing only

        int usbdeviceID=0;
        char puskuri[128];
        std::string muutaINT = "";
        FILE* pipe = popen("ip link|wc -l", "r");
        if(!pipe) throw std::runtime_error("popen() fiasco :(");
        try {
            while(fgets(puskuri, sizeof puskuri, pipe) != nullptr){
                usbdeviceID = std::stoi(puskuri);

            }
        } catch (...) {
            pclose(pipe);
            throw;
        }



//        int usbdeviceID = system("lsusb -d 2e04:c008 &> /dev/null"); // paree versio laite hallintaan..

        if(usbdeviceID == iplinkN){
            emit loaded();
            }
        if(usbdeviceID != iplinkN){
            // not loaded
            //startUp();
            std::cout << "usbD " << usbdeviceID << "iplinkN " << iplinkN << std::endl;
            //sleep(60);
        }
        if(usbdeviceID == -1){
            break; // for compiler warn  silence
        }
    }
}


