QT += core gui widgets

TARGET = TimerList
TEMPLATE = app

QT_QPA_PLATFORM=wayland

DESTDIR = bin

HEADERS += \
    FormMain.h \
    Timer.h \
    TimerListModel.h \
    TimerListView.h \
    TimerListWidget.h \
    TimerPlayer.h

SOURCES += \
    FormMain.cpp \
    main.cpp \
    Timer.cpp \
    TimerListModel.cpp \
    TimerListView.cpp \
    TimerListWidget.cpp \
    TimerPlayer.cpp
