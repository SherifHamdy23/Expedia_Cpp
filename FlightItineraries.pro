QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomerWindow.cpp \
    Expedia.cpp \
    addflight.cpp \
    flightswindow.cpp \
    hotelswindow.cpp \
    layout.cpp \
    loginwindow.cpp \
    main.cpp \
    managerwindow.cpp \
    signupwindow.cpp

HEADERS += \
    CustomerWindow.h \
    Expedia.hpp \
    addflight.h \
    flightswindow.h \
    hotelswindow.h \
    layout.h \
    loginwindow.h \
    managerwindow.h \
    signupwindow.h

FORMS += \
    CustomerWindow.ui \
    addflight.ui \
    flightswindow.ui \
    hotelswindow.ui \
    layout.ui \
    loginwindow.ui \
    managerwindow.ui \
    signupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
