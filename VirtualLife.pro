QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achievements.cpp \
    actions.cpp \
    assets.cpp \
    character.cpp \
    crawlinggame.cpp \
    crawlinggameparts.cpp \
    difficulty.cpp \
    huntinggame.cpp \
    huntinggameparts.cpp \
    initialdata.cpp \
    lottery.cpp \
    main.cpp \
    memorycard.cpp \
    purchase.cpp \
    spaceinvaders.cpp \
    spaceinvadersparts.cpp \
    virtuallifedataaccess.cpp \
    virtuallifemodel.cpp \
    virtuallifeview.cpp \
    whackamole.cpp \
    whackamoleparts.cpp

HEADERS += \
    achievements.h \
    actions.h \
    assets.h \
    character.h \
    crawlinggame.h \
    crawlinggameparts.h \
    difficulty.h \
    huntinggame.h \
    huntinggameparts.h \
    initialdata.h \
    lottery.h \
    memorycard.h \
    purchase.h \
    spaceinvaders.h \
    spaceinvadersparts.h \
    virtuallifedataaccess.h \
    virtuallifemodel.h \
    virtuallifeview.h \
    whackamole.h \
    whackamoleparts.h

FORMS += \
    achievements.ui \
    actions.ui \
    assets.ui \
    difficulty.ui \
    initialdata.ui \
    lottery.ui \
    memorycard.ui \
    purchase.ui \
    virtuallifeview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
