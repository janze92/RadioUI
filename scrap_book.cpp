//void test(){
//    const char *homePath = getenv("HOME");
//    if(homePath != nullptr)
//    {
//        QProcess Home;
//        Home.start("echo",QStringList() << homePath);
//        Home.waitForFinished(-1);
//        qDebug() << Home.readAllStandardOutput();
//    }
//}
//void call_from_thread() {
//    while (true) {

//        if(volUP==true){
//            volumeUP();
//            usleep(50000);
//        }
//        if(volDN==true){
//            volumeDN();
//            usleep(50000);
//        }
//        usleep(10000);

//    }
//}
