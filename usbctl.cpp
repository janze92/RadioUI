#include "usbctl.h"
#include <QThread>
#include <QString>
#include <qdebug.h>
#include "iostream"

usbctl::usbctl(){
}
usbctl::~usbctl(){
}
void usbctl::loadPhone(){
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
}


void usbctl::startUp() {
    bool ladattu=false;
    system("adb start-server");
    while (true) {
        int usbdeviceID = system("lsusb -d 2e04:c026");
        usleep(1000000);
        //cout << "looppaa" << endl;
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
        int usbdeviceID = system("lsusb -d 2e04:c008 &> /dev/null"); // paree versio laite hallintaan..
        if(usbdeviceID == 0){
            emit loaded();
            }
        if(usbdeviceID != 0){
            // not loaded
            startUp();
            sleep(60);
        }
        msleep(5000);
        if(usbdeviceID == -1){
            break; // for compiler warn  silence
        }
    }
}


