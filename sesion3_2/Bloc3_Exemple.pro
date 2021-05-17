TEMPLATE    = app
TARGET		= sesion32
QT         += opengl widgets

INCLUDEPATH +=  /usr/include/glm /usr/local/include/glm
INCLUDEPATH +=  Model

FORMS += MyForm.ui

HEADERS += MyForm.h Bl3GLWidget.h MyGLWidget.h Model/model.h

SOURCES += main.cpp  MyForm.cpp \
        Bl3GLWidget.cpp MyGLWidget.cpp Model/model.cpp
