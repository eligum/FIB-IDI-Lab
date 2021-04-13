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
 * Returns first the CENTER, second the BASE and finally the SIZE of the model.
 */
template <typename T>
std::tuple<glm::vec3, glm::vec3, glm::vec3>
CalculateBoxCoords(const T* model_vertices, std::size_t count, std::size_t offset)
{
    float max_x, min_x, max_y, min_y, max_z, min_z;
    max_x = min_x = model_vertices[0];
    max_y = min_y = model_vertices[1];
    max_z = min_z = model_vertices[2];
    for (std::size_t i = 3; i < count; i += offset)
    {
        // Check max
        if (model_vertices[i + 0] > max_x) max_x = model_vertices[i + 0];
        if (model_vertices[i + 1] > max_y) max_y = model_vertices[i + 1];
        if (model_vertices[i + 2] > max_z) max_z = model_vertices[i + 2];
        // Check min
        if (model_vertices[i + 0] < min_x) min_x = model_vertices[i + 0];
        if (model_vertices[i + 1] < min_y) min_y = model_vertices[i + 1];
        if (model_vertices[i + 2] < min_z) min_z = model_vertices[i + 2];
    }

    return {
        { (max_x + min_x) / 2.0f, (max_y + min_y) / 2.0f, (max_z + min_z) / 2.0f }, // Center
        { (max_x + min_x) / 2.0f,          min_y        , (max_z + min_z) / 2.0f }, // Base
        { (max_x - min_x)       , (max_y - min_y)       , (max_z - min_z)        }  // Size
    };
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
    auto [center, base, size] = CalculateBoxCoords(model.vertices().data(), model.vertices().size(), 3);

    patricio.ModelCenter = center;
    patricio.ModelBase   = base;
    patricio.ModelSize   = size;

    InitCamera(1.0f, { 2.5f, 2.0f, 2.5f }, { -2.5f, -2.0f, -2.5f });
}

void MyGLWidget::creaBuffers()
{
    model.load("models/Patricio.obj");

    /*** Homer ***/
    glGenVertexArrays(1, &patricioVAO);
    glBindVertexArray(patricioVAO);

    GLuint patricioVBO[2];
    glGenBuffers(2, patricioVBO);

    glBindBuffer(GL_ARRAY_BUFFER, patricioVBO[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * model.faces().size() * 3 * 3,
                 model.VBO_vertices(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(0));

    glBindBuffer(GL_ARRAY_BUFFER, patricioVBO[1]);
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
    projLoc = glGetUniformLocation(program->programId(), "u_Proj");
    viewLoc = glGetUniformLocation(program->programId(), "u_View");
}

void MyGLWidget::wheelEvent(QWheelEvent* evt)
{
    makeCurrent();
    FOV -= glm::radians(evt->angleDelta().y() / 40.0f);
    FOV = std::max(glm::radians(1.0f), std::min(glm::radians(179.0f), FOV));
    //aFOV = FOV;
    std::cout << glm::degrees(FOV) << std::endl;
    ProjectTransform();
    update();
}

void MyGLWidget::mousePressEvent(QMouseEvent* evt)
{
    xClickPos = evt->x();
    yClickPos = evt->y();
    yawClick = yaw;
    pitchClick = pitch;

    std::cout << "Mouse pressed event! (" << xClickPos << ", " << yClickPos << ")\n";

    if (evt->button() & Qt::LeftButton
        && !(evt->modifiers() & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier)))
    {
        action = CameraAction::ROTATE;
    }
    if (evt->button() & Qt::LeftButton
        && !(evt->modifiers() & (Qt::ShiftModifier | Qt::AltModifier))
        && (evt->modifiers() & Qt::ControlModifier))
    {
        action = CameraAction::PAN;
    }
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent*)
{
    std::cout << "Mouse released event!" << std::endl;
    action = CameraAction::NONE;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent* evt)
{
    makeCurrent();

    const int xOffset = evt->x() - xClickPos;
    const int yOffset = evt->y() - yClickPos;

    if (action == CameraAction::ROTATE)
    {
        std::cout << "(" << xOffset << ", " << yOffset << ")\n";
        yaw = yawClick - glm::radians(xOffset / 5.0f);
        pitch = pitchClick + glm::radians(yOffset / 5.0f);
    }
    update();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
    makeCurrent();
    switch (event->key()) {
        case Qt::Key_R: {
            yaw = pitch = roll = 0.0f;
            break;
        }
        case Qt::Key_O: {
            if (projType == ProjectionType::ORTHO)
                projType = ProjectionType::PERSPECTIVE;
            else
                projType = ProjectionType::ORTHO;
            ProjectTransform();
            break;
        }
        default: event->ignore(); break;
    }
    update();
}

void MyGLWidget::InitCamera(float aspect_ratio, const glm::vec3& max_point, const glm::vec3& min_point)
{
    glm::vec3 center = (min_point + max_point) / 2.0f;
    radiEscena = glm::length(max_point - center);
    float dist = 2.0f * radiEscena;
    float alpha = glm::asin(radiEscena / dist);

    FOV = aFOV = 2.0f * alpha;
    ar = aspect_ratio;
    zNear = dist - radiEscena;
    zFar  = dist + radiEscena;

    left   = -radiEscena * ar;
    right  = radiEscena * ar;
    bottom = -radiEscena;
    top    = radiEscena;

    yaw = pitch = roll = 0.0f;

    projType = ProjectionType::PERSPECTIVE;
    ProjectTransform();
    ViewTransform();
}

void MyGLWidget::ProjectTransform()
{
    glm::mat4 projection;
    if (projType == ProjectionType::PERSPECTIVE)
        projection = glm::perspective(FOV, ar, zNear, zFar);
    else
        projection = glm::ortho(left, right, bottom, top, zNear, zFar);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void MyGLWidget::ViewTransform()
{
    glm::mat4 view{1.0f};
    view = glm::translate(view, glm::vec3{0, 0, -radiEscena * 2.0f});
    view = glm::rotate(view, -roll,  glm::vec3{0, 0, 1});
    view = glm::rotate(view,  pitch, glm::vec3{1, 0, 0});
    view = glm::rotate(view, -yaw,   glm::vec3{0, 1, 0});

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
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

    ViewTransform();

    // Render
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
    ar = static_cast<float>(width) / static_cast<float>(height);

    if (projType == ProjectionType::PERSPECTIVE)
    {
        if (ar < 1.0f)
            FOV = 2.0f * glm::atan(glm::tan(aFOV / 2.0f) / ar);
    }
    else if (projType == ProjectionType::ORTHO)
    {
        if (ar >= 1.0f)
        {
            left = -radiEscena * ar;
            right = radiEscena * ar;
        }
        else
        {
            left = -radiEscena;
            right = radiEscena;
            bottom = -radiEscena / ar;
            top = radiEscena / ar;
        }
    }
    ProjectTransform();
}































