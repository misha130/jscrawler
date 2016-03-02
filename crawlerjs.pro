QT += core
QT -= gui
QT += network
QT += script
QT += sql
CONFIG += c++11

TARGET = crawlerjs
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    crawler.cpp \
    linkslooker.cpp \
    sqlhandle.cpp

HEADERS += \
    crawler.h \
    linkslooker.h \
    sqlhandle.h
