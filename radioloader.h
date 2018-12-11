#ifndef RADIOLOADER_H
#define RADIOLOADER_H


class radioloader
{
public:
    int Player(int PID, const char *kanava, int soiko);
    int controll(int PID, const char *kanavapath, int nbr);
    void stop(int PID);
};

#endif // RADIOLOADER_H
