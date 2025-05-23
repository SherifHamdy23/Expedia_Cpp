QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
SOURCES += \
    addflight.cpp \
    CustomerWindow.cpp \
    Expedia.cpp \
    flightswindow.cpp \
    hotelswindow.cpp \
    loginwindow.cpp \
    main.cpp \
    managerwindow.cpp \
    mybookings.cpp \
    payment.cpp \
    searchflights.cpp \
    searchhotels.cpp \
    signupwindow.cpp
HEADERS += \
    addflight.h \
    CustomerWindow.h \
    Expedia.hpp \
    flightswindow.h \
    hotelswindow.h \
    loginwindow.h \
    managerwindow.h \
    mybookings.h \
    payment.h \
    searchflights.h \
    searchhotels.h \
    signupwindow.h
FORMS += \
    addflight.ui \
    CustomerWindow.ui \
    flightswindow.ui \
    hotelswindow.ui \
    loginwindow.ui \
    managerwindow.ui \
    mybookings.ui \
    payment.ui \
    searchflights.ui \
    searchhotels.ui \
    signupwindow.ui