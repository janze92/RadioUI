#ifndef USBCTL_H
#define USBCTL_H
#include <QThread>
#include <QString>

class usbctl : public QThread
{
    Q_OBJECT
public:
    usbctl();
    ~usbctl();

public slots:
    void startUp();
    void loadPhone();
    void status();

signals:
    void loaded();
};

#endif // USBCTL_H
