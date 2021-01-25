QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comboBoxColor.cpp \
    gamegraphicsview.cpp \
    gameview.cpp \
    helpView.cpp \
    keyIcon.cpp \
    localView.cpp \
    main.cpp \
    scorewidget.cpp \
    tracexclient.cpp \
    mainMenuView.cpp \
    networkView.cpp \
    stackedlayout.cpp \
    widgetplayer.cpp

HEADERS += \
    gamegraphicsview.h \
    scorewidget.h \
    tracexclient.h \
    comboBoxColor.h \
    constants.h \
    gameview.h \
    helpView.h \
    keyIcon.h \
    localView.h \
    mainMenuView.h \
    networkView.h \
    stackedlayout.h \
    widgetplayer.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
