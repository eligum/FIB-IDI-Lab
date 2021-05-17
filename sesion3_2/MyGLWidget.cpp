// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502:
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
               file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    makeCurrent();
    // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
    if (DoingInteractive == ROTATE)
    {
        // Fem la rotació
        angleY += (e->x() - xClick) * M_PI / ample;
        viewTransform ();
    }

    xClick = e->x();
    yClick = e->y();

    update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
    makeCurrent();
    switch (event->key()) {
        
        default: Bl3GLWidget::keyPressEvent(event); break;
    }
    update();
}

void MyGLWidget::InitLlum()
{
    colFocus    = glm::vec3{0.8, 0.8, 0.8};
    llumAmbient = glm::vec3{0.2, 0.2, 0.2};
    posFocus    = glm::vec3{1, 1, 1};
}

void MyGLWidget::UploadVec3(const char* u_name, const glm::vec3& vec)
{
    int location = glGetUniformLocation(this->program->programId(), u_name);
    if (location < 0) {
        std::cerr << "Uniform " << u_name << "not found." << std::endl;
    } else {
        glUniform3f(location, vec.x, vec.y, vec.z);
    }
}

void MyGLWidget::UploadMat4(const char* u_name, const glm::mat4& mat)
{
    int location = glGetUniformLocation(this->program->programId(), u_name);
    if (location < 0) {
        std::cerr << "Uniform " << u_name << "not found." << std::endl;
    } else {
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }
}

void MyGLWidget::UploadFloat(const char* u_name, float value)
{
}















