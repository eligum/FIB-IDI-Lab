TEMPLATE     = app
QT          += widgets

INCLUDEPATH += /usr/include/glm \
               /usr/local/include/glm

FORMS       += MyForm.ui

HEADERS     += MyForm.h \
# MyGLWidget.h

SOURCES     += main.cpp MyForm.cpp \
# MyGLWidget.cpp
