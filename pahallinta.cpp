#include "pahallinta.h"
#include "stdlib.h"
#include "string"

static int volume;

void pahallinta::volumeUP(){
    system("pamixer --increase 1");
}

void pahallinta::volumeDN(){
    system("pamixer --decrease 1");
}

void pahallinta::volumelvl(int value){
    if (system(nullptr));
        else exit (EXIT_FAILURE);
    std::string pamixer = "pamixer --set-volume ";
    std::string arvo = pamixer +  std::to_string(value);
    char const *muutetaan = arvo.c_str();
    // system command
    system(muutetaan);
}

int pahallinta::volumeGet() {
    std::string volume = "pamixer --get-volume";
    std::string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    volume.append(" 2>&1");

    stream = popen(volume.c_str(), "r");
    if (stream) {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != nullptr) data.append(buffer);
    pclose(stream);
    }
    int i=stoi( data );
    return i;
}

int pahallinta::mute(){
    int isItMuted = system("pamixer --get-mute");
    if(isItMuted == 256){
        volume = volumeGet();
        system("pamixer -m");
        return 0;
    }
    else {
        system("pamixer -u");
        return volume;
    }
}
