QT       += core gui
QT       += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    archive.cpp \
    background.cpp \
    barriers.cpp \
    boss.cpp \
    bossbarriers.cpp \
    bossintro.cpp \
    bossmode.cpp \
    bossplayer.cpp \
    character.cpp \
    dino.cpp \
    ground.cpp \
    home.cpp \
    introduction.cpp \
    main.cpp \
    mainwindow.cpp \
    prop.cpp \
    store.cpp

HEADERS += \
    archive.h \
    background.h \
    barriers.h \
    boss.h \
    bossbarriers.h \
    bossintro.h \
    bossmode.h \
    bossplayer.h \
    character.h \
    config.h \
    dino.h \
    ground.h \
    home.h \
    introduction.h \
    mainwindow.h \
    prop.h \
    store.h

FORMS += \
    archive.ui \
    background.ui \
    boss.ui \
    bossintro.ui \
    bossmode.ui \
    character.ui \
    home.ui \
    introduction.ui \
    mainwindow.ui \
    prop.ui \
    store.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
