QT += core gui
QT += widgets
QT += network

TARGET = QtBabel

TEMPLATE = app

INCLUDEPATH += .

LIBS += -lportaudio -L./lib -lopus

SOURCES += main.cpp \
    QtGui.cpp \
    QtNet.cpp \
    BabelClient.cpp \
    mainwindow.cpp \
    Event.cpp \
    contact.cpp \
    QtCircularBuffer.cpp \
    Message.cpp \
    QtUdpSocket.cpp \
    VoiceInterpreter.cpp \
    RingBuffer.cpp

HEADERS += \
    QtGui.h \
    QtNet.h \
    BabelClient.h \
    IGui.hpp \
    INetwork.hpp \
    ICircularBuffer.hpp \
    IUdpSocket.hpp \
    Event.hpp \
    mainwindow.h \
    Contact.h \
    QtCircularBuffer.h \
    Message.h \
    QtUdpSocket.h

FORMS += \
    mainwindow.ui \
    MainWindow.ui

QMAKE_CXXFLAGS += -std=c++11
