#-------------------------------------------------
#
# Project created by QtCreator 2015-09-24T19:55:44
#
#-------------------------------------------------

QT       += core gui
QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paint
TEMPLATE = app


SOURCES += main.cpp\
    MathPart/circle.cpp \
    MathPart/graph.cpp \
    MathPart/interval.cpp \
    MathPart/line_segment.cpp \
    MathPart/point.cpp \
    MathPart/prm.cpp \
    MathPart/shortest_path.cpp \
    MathPart/triangle.cpp \
    MathPart/util.cpp \
    MathPart/vector.cpp \
        paint.cpp \
    paintscene.cpp

HEADERS  += paint.h \
    MathPart/circle.h \
    MathPart/graph.h \
    MathPart/interval.h \
    MathPart/line_segment.h \
    MathPart/objects.h \
    MathPart/point.h \
    MathPart/prm.h \
    MathPart/shortest_path.h \
    MathPart/triangle.h \
    MathPart/util.h \
    MathPart/vector.h \
    paintscene.h

FORMS    += paint.ui
