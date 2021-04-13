// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>

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

MyGLWidget::~MyGLWidget()
{
}

//----------------------------------------------------------------------------//
//--- My Stuff ---------------------------------------------------------------//
//----------------------------------------------------------------------------//

/**
 * The data type of the container must be comparable.
 * Returns first MAXIMUM and then MINIMUM points.
 */
template <typename T>
std::tuple<glm::vec3, glm::vec3>
CalculateBoxCoords(const T* model_vertices, std::size_t count, std::size_t offset)
{
    float max_x, min_x, max_y, min_y, max_z, min_z;
    max_x = min_x = model_vertices[0];
    max_y = min_y = model_vertices[1];
    max_z = min_z = model_vertices[2];
    for (std::size_t i = 0; i < count; i += offset)
    {
        // Check max
        if (model_vertices[i] > max_x) max_x = model_vertices[i];
        if (model_vertices[i + 1] > max_y) max_y = model_vertices[i + 1];
        if (model_vertices[i + 2] > max_z) max_z = model_vertices[i + 2];
        // Check min
        if (model_vertices[i] < min_x) min_x = model_vertices[i];
        if (model_vertices[i + 1] < min_y) min_y = model_vertices[i + 1];
        if (model_vertices[i + 2] < min_z) min_z = model_vertices[i + 2];
    }

    return { { max_x, max_y, max_z }, { min_x, min_y, min_z } };
}

void MyGLWidget::initializeGL()
{
    // Cal inicialitzar l'ús de les funcions d'OpenGL
    initializeOpenGLFunctions();

    glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    carregaShaders();
    creaBuffers();

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);

    // Initialize models
    auto [maxP, minP] = CalculateBoxCoords(model.vertices().data(), model.vertices().size(), 3);

    patricio.ModelBase = glm::vec3((maxP.x + minP.x) / 2.0f, minP.y, (maxP.z + minP.z) / 2.0f);
    patricio.ModelCenter = (maxP + minP) / 2.0f;
    patricio.ModelSize = maxP - minP;

    camera.Init(1.0f, { -2.5f, 0.0f, -2.5f }, { 2.0f, 4.0f, 2.5f });
}

void MyGLWidget::creaBuffers()
{
    model.load("models/Patricio.obj");

    /*** Homer ***/
    glGenVertexArrays(1, &patricioVAO);
    glBindVertexArray(patricioVAO);

    GLuint homerVBO[2];
    glGenBuffers(2, homerVBO);

    glBindBuffer(GL_ARRAY_BUFFER, homerVBO[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * model.faces().size() * 3 * 3,
                 model.VBO_vertices(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(0));

    glBindBuffer(GL_ARRAY_BUFFER, homerVBO[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * model.faces().size() * 3 * 3,
                 model.VBO_matdiff(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(0));

    glBindVertexArray(0);

    /*** Terra ***/
    glGenVertexArrays(1, &terraVAO);
    glBindVertexArray(terraVAO);

    GLuint terraVBO[2];
    glGenBuffers(2, terraVBO);

    float terraVert[6 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, terraVBO[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(terraVert),
                 terraVert,
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(0));

    float terraColor[6 * 3] = {
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, terraVBO[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(terraColor),
                 terraColor,
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(0));

    glBindVertexArray(0);
}

/*****************************************************************************/
void MyGLWidget::UploadMat4(const std::string& varName, const glm::mat4& matrix)
{
    int location = glGetUniformLocation(program->programId(), varName.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
void MyGLWidget::UploadFloat4(const std::string& varName, const glm::vec4& vector)
{
    int location = glGetUniformLocation(program->programId(), varName.c_str());
    glUniform4fv(location, 1, glm::value_ptr(vector));
}
void MyGLWidget::UploadFloat3(const std::string& varName, const glm::vec3& vector)
{
    int location = glGetUniformLocation(program->programId(), varName.c_str());
    glUniform3fv(location, 1, glm::value_ptr(vector));
}
void MyGLWidget::UploadInt(const std::string& varName, int value)
{
    int location = glGetUniformLocation(program->programId(), varName.c_str());
    glUniform1i(location, value);
}
/*****************************************************************************/

void MyGLWidget::carregaShaders()
{
    Bl2GLWidget::carregaShaders();
    // projLoc = glGetUniformLocation(program->programId(), "u_Proj");
    // viewLoc = glGetUniformLocation(program->programId(), "u_View");
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
    makeCurrent();
    switch (event->key()) {
        case Qt::Key_A: {
            camera.ModifyYaw(5.0f);
            break;
        }
        case Qt::Key_D: {
            camera.ModifyYaw(-5.0f);
            break;
        }
        case Qt::Key_S: {
            camera.ModifyPitch(5.0f);
            break;
        }
        case Qt::Key_W: {
            camera.ModifyPitch(-5.0f);
            break;
        }
        case Qt::Key_O: {
            if (cameraOptic)
                camera.SetProjectionType(Camera::ORTHO);
            else
                camera.SetProjectionType(Camera::PERSPECTIVE);
            cameraOptic = !cameraOptic;
            break;
        }
        default: event->ignore(); break;
    }
    update();
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Logic
    glm::mat4 patricioTG(1.0f);
    patricioTG = glm::translate(patricioTG, glm::vec3(0.0f, -2.0f, 0.0f));
    patricioTG = glm::scale(patricioTG, glm::vec3(4.0f / patricio.ModelSize.y));
    patricioTG = glm::translate(patricioTG, -patricio.ModelBase);

    glm::mat4 terraTG(1.0f);
    terraTG = glm::translate(terraTG, glm::vec3(0.0f, -2.0f, 0.0f));
    terraTG = glm::rotate(terraTG, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    terraTG = glm::scale(terraTG, glm::vec3(5.0f));

    // Render
    UploadMat4("u_View", camera.GetViewMatrix());
    UploadMat4("u_Proj", camera.GetProjMatrix());

    UploadMat4("u_TG", patricioTG);
    glBindVertexArray(patricioVAO);
    glDrawArrays(GL_TRIANGLES, 0, model.faces().size() * 3);

    UploadMat4("u_TG", terraTG);
    glBindVertexArray(terraVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void MyGLWidget::resizeGL(int width, int height)
{
    ample = width;
    alt = height;
    camera.ChangeAspectRatio(static_cast<float>(width) / static_cast<float>(height));
}































