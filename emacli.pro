QT += core gui widgets network

CONFIG += c++11

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
