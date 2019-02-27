#ifndef SHOOTCOMMAND_H
#define SHOOTCOMMAND_H
#include <QThread>
#include <QString>




class shootCommand : public QThread
{
        Q_OBJECT
public:
    shootCommand();
    ~shootCommand();

public slots:
    void suoritaKomento(const char* komento);
    void mitavittua();
    void inttiboi(int i);

signals:
    void finished();
    void error(QString err);
};

#endif // SHOOTCOMMAND_H
