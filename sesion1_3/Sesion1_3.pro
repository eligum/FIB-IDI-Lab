QT          += core gui opengl
QT          += widgets

CONFIG      += c++17

INCLUDEPATH += /usr/include/glm \
               /usr/local/include/glm

FORMS       += myform.ui

HEADERS     += myform.h \
               myglwidget.h

SOURCES     += main.cpp \
               myform.cpp \
               myglwidget.cpp
