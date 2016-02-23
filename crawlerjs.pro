QT += core
QT -= gui
QT += network
QT+= script
CONFIG += c++11

TARGET = crawlerjs
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    crawler.cpp \
    linkslooker.cpp

HEADERS += \
    crawler.h \
    linkslooker.h
