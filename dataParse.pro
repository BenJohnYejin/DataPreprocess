QT += core
QT -= gui

CONFIG += c++11

TARGET = dataParse
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    parsehex.cpp \
    fuctioncmn.cpp \
    nema0183.cpp \
    parse38sa08.cpp

HEADERS += \
    parsehex.h \
    fuctioncmn.h \
    nema0183.h \
    parse38sa08.h
