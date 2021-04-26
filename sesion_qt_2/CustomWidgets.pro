TEMPLATE     = app
QT          += widgets

INCLUDEPATH += /usr/include/glm \
               /usr/local/include/glm

FORMS       += MyForm.ui

HEADERS     += MyForm.h MyLineEdit.h
# MyGLWidget.h

SOURCES     += main.cpp MyForm.cpp MyLineEdit.cpp
# MyGLWidget.cpp
