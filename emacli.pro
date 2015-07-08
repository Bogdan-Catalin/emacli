QT += core gui network widgets

CONFIG += c++11
CONFIG += console

TARGET = emacli
TEMPLATE = app

SOURCES += main.cpp \
    email/protocol_adapters/pop3/pop3adapter.cpp \
    ui/start_screen/startscreen.cpp \
    email/protocol_adapters/exceptions/servernotrespondingexception.cpp \
    email/protocol_adapters/exceptions/servercannotbereachedexception.cpp \
    email/protocol_adapters/exceptions/unathenticatedexception.cpp \
    email/protocol_adapters/exceptions/authenticationfailedexception.cpp

HEADERS += \
    email/protocol_adapters/pop3/pop3adapter.h \
    ui/start_screen/startscreen.h \
    email/protocol_adapters/exceptions/servernotrespondingexception.h \
    email/protocol_adapters/exceptions/servercannotbereachedexception.h \
    email/protocol_adapters/exceptions/unathenticatedexception.h \
    email/protocol_adapters/exceptions/authenticationfailedexception.h

FORMS += \
    ui/start_screen/startscreen.ui
