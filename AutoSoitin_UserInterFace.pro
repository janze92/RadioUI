#-------------------------------------------------
#
# Project created by QtCreator 2018-11-17T19:05:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoSoitin_UserInterFace
TEMPLATE = app


## Riippuvuuksia muista ohjelmista:
## Pulseaudio, pamixer, tmux, mpv
##

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 -pthread

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    blthallinta.cpp \
    usbctl.cpp \
    radioloader.cpp \
    pahallinta.cpp \
    scrap_book.cpp \
    threading.cpp

HEADERS += \
        mainwindow.h \
    blthallinta.h \
    usbctl.h \
    radioloader.h \
    pahallinta.h \
    threading.h

FORMS += \
        Main.ui

DISTFILES += \
    /home/janze/Music/ylex.m3u8 \
    /home/janze/Music/suomipop.m3u8 \
    /home/janze/Music/radiorock.m3u8 \
    /home/janze/Music/loop.m3u8 \
    /home/janze/Music/hitmix.m3u8 \
    README.md \
    config.conf

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
