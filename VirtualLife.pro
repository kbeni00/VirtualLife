QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actions.cpp \
    assets.cpp \
    character.cpp \
    details.cpp \
    initialdata.cpp \
    lottery.cpp \
    main.cpp \
    relationships.cpp \
    virtuallifemodel.cpp \
    virtuallifeview.cpp

HEADERS += \
    actions.h \
    assets.h \
    character.h \
    details.h \
    initialdata.h \
    lottery.h \
    relationships.h \
    virtuallifemodel.h \
    virtuallifeview.h

FORMS += \
    actions.ui \
    assets.ui \
    details.ui \
    initialdata.ui \
    lottery.ui \
    relationships.ui \
    virtuallifeview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
