#include "usbctl.h"

usbctl::usbctl()
{

}
//void loadnetti(){
//    // TODO: legit check that adb is running and every command get executed
//    char tmuxRun[]="tmux send-keys -t tetherUSB.0 'adb shell' ENTER";
//    char tmuxRun2[]="tmux send-keys -t tetherUSB.0 'service call connectivity 34 i32 1 s16 text' ENTER";
//    char tmuxRun3[]="tmux send-keys -t tetherUSB.0 'exit' ENTER";
//    system("tmux new -d -s tetherUSB");
//    sleep(1);
//    system(tmuxRun);
//    sleep(1);
//    system(tmuxRun2);
//    sleep(1);
//    system(tmuxRun3);
//    usleep(100000);
//    system(tmuxRun3);
//    netti=1;
//    if((debug=true)){
//    cout << "Ladattu netti \n";
//    }
//}


//void usbdevcheck() {
//    bool ladattu=false;
//    system("adb start-server");
//    while (true) {
//        int usbdeviceID = system("lsusb -d 2e04:c026");
//        usleep(1000000);
//        cout << "looppaa" << endl;
//        if(usbdeviceID == 0 && ladattu==false){
//            ladattu = true;
//            cout << "ladataan laite" << endl;
//            loadnetti();
//            }
//        if(ladattu == true)
//            break;

//    }
//}
