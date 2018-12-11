#ifndef THREADING_H
#define THREADING_H
#include <QThread>
#include <QString>

class threading : public QThread
{
    Q_OBJECT
public:
    threading();
    ~threading();

public slots:
    void suorita();
    void volumeDown(int suunta);
    void volumeUP(int suunta);

signals:
    void finished();
    void error(QString err);
    void VolumeChanged();

private:
    QString name;
};


#endif // THREADING_H
