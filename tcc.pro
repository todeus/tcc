# -------------------------------------------------
# Project created by QtCreator 2010-02-15T11:18:36
# -------------------------------------------------
QT -= gui
TARGET = tcc
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    scanner.cpp \
    token.cpp \
    parser.cpp \
    node.cpp
HEADERS += scanner.h \
    KA.h \
    token.h \
    struct.h \
    myEx.h \
    parser.h \
    node.h
OTHER_FILES += test11.txt \
    README \
    Makefile
