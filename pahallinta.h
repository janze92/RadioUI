#ifndef PAHALLINTA_H
#define PAHALLINTA_H
#include "string"

class pahallinta
{
public:
    int volumeGet();
    void volumeUP();
    void  volumeDN();
    int mute(); // palauttaa mutelle volume arvo 0, unmutelle volumen arvoksi mikä oli.
    void volumelvl(int value);
};

#endif // PAHALLINTA_H
