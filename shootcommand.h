#ifndef SHOOTCOMMAND_H
#define SHOOTCOMMAND_H
#include <QThread>
#include <QString>




class shootCommand : public QThread
{
        Q_OBJECT
public:
    shootCommand(char aakkonenTaululle[]);
    ~shootCommand();
private:
    char aakkonenT[256];

public slots:
    void runRun();
    void test();
    void stop();
    void runAgen();

signals:
    void finished();
    void error(QString err);
};

#endif // SHOOTCOMMAND_H
