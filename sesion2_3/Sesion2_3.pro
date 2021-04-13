TEMPLATE    = app
QT         += opengl
CONFIG     += c++17

INCLUDEPATH +=  /usr/include/glm \
                /usr/local/include/glm \
                Model

FORMS += MyForm.ui

HEADERS += MyForm.h Bl2GLWidget.h MyGLWidget.h \
           Model/model.h

SOURCES += main.cpp MyForm.cpp \
           Bl2GLWidget.cpp MyGLWidget.cpp \
           Model/model.cpp
