QT += core gui widgets

TARGET = TimerList
TEMPLATE = app

QT_QPA_PLATFORM = wayland
RESOURCES += qdarkstyle/dark/style.qrc
RESOURCES += qdarkstyle/light/style.qrc
DESTDIR = bin

HEADERS += \
    FormMain.h \
    Timer.h \
    TimerListModel.h \
    TimerListView.h \
    TimerListWidget.h \
    TimerPlayer.h \
    Utilities.h

SOURCES += \
    FormMain.cpp \
    main.cpp \
    Timer.cpp \
    TimerListModel.cpp \
    TimerListView.cpp \
    TimerListWidget.cpp \
    TimerPlayer.cpp \
    Utilities.cpp
