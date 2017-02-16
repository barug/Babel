QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4):   QT += widgets
                                    QT += network

TARGET = clientTest

TEMPLATE = app
  
SOURCES += clientTest.cpp \
../Event.cpp \
../QtNet.cpp \
../Message.cpp \
../QtCircularBuffer.cpp

HEADERS += ../Event.hpp \
../QtNet.h \
../QTCircularBuffer.h \
../Message.h

FORMS += 

QMAKE_CXXFLAGS += -std=c++11
