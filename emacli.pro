QT += core gui network widgets

CONFIG += c++11
CONFIG += console

TARGET = emacli
TEMPLATE = app

SOURCES += main.cpp \
    email/protocol_adapters/pop3/pop3adapter.cpp \
    ui/start_screen/startscreen.cpp

HEADERS += \
    email/protocol_adapters/pop3/pop3adapter.h \
    ui/start_screen/startscreen.h

FORMS += \
    ui/start_screen/startscreen.ui
