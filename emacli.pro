QT += core
QT += network
QT -= gui

CONFIG += c++14

TARGET = emacli
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    email/protocol_adapters/pop3/pop3adapter.cpp

HEADERS += \
    email/protocol_adapters/pop3/pop3adapter.h
