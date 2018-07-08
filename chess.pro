#-------------------------------------------------
#
# Project created by QtCreator 2018-07-04T09:14:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess
TEMPLATE = app


SOURCES += main.cpp\
  stone.cpp \
        board.cpp \
    singlegame.cpp

HEADERS  += board.h \
    stone.h \
    singlegame.h
