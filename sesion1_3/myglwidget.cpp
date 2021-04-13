#include "myglwidget.h"
#include <glm/gtc/type_ptr.hpp>

MyGLWidget::MyGLWidget(QWidget* parent)
    : QOpenGLWidget(parent), program(nullptr)
{
    setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
    if (program != nullptr)
        delete program;
}

void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor (0.5f, 0.7f, 1.0f, 1.0f); // defineix color de fons (d'esborrat)
    carregaShaders();
    creaBuffers();
}

void MyGLWidget::paintGL()
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
    GLint vp[4];
    glGetIntegerv (GL_VIEWPORT, vp);
    ample = vp[2];
    alt = vp[3];
#endif

    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, m_Width, m_Height);

    modelTransform();
    glBindVertexArray(m_VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
}

void MyGLWidget::resizeGL(int width, int height)
{
    m_Width = width;
    m_Height = height;
}

void MyGLWidget::keyPressEvent(QKeyEvent* e)
{
    makeCurrent();
    switch (e->key())
    {
        case Qt::Key_D:
            m_Value += 0.1f;
            break;
        case Qt::Key_A:
            m_Value -= 0.1f;
            break;
        default:
            e->ignore();
    }
    update();
}

void MyGLWidget::modelTransform()
{
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(m_Value, 0.0f, 0.0f));
    glUniformMatrix4fv(m_TransLocation, 1, GL_FALSE, glm::value_ptr(TG));
}

void MyGLWidget::creaBuffers()
{
    glm::vec3 Vertices_pos[3] = {
        glm::vec3( 0.0,  1.0, 0.0),
        glm::vec3(-1.0, -1.0, 0.0),
        glm::vec3( 1.0, -1.0, 0.0)
    };

    glm::vec3 Vertices_col[3] = {
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    };

    // Creació del Vertex Array Object (VAO) que usarem per pintar
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    // Creació del buffer amb les dades dels vèrtexs
    GLuint VBO_pos;
    glGenBuffers(1, &VBO_pos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_pos), Vertices_pos, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint VBO_color;
    glGenBuffers(1, &VBO_color);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_col), Vertices_col, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
    // Creem els shaders per al fragment shader i el vertex shader
    QOpenGLShader fs(QOpenGLShader::Fragment, this);
    QOpenGLShader vs(QOpenGLShader::Vertex, this);
    // Carreguem el codi dels fitxers i els compilem
    fs.compileSourceFile("assets/shaders/basic.frag");
    vs.compileSourceFile("assets/shaders/basic.vert");
    // Creem el program
    program = new QOpenGLShaderProgram(this);
    // Li afegim els shaders corresponents
    program->addShader(&fs);
    program->addShader(&vs);
    // Linkem el program
    program->link();
    // Indiquem que aquest és el program que volem usar
    program->bind();

    // Obtenim identificador per a l'atribut “vertex” del vertex shader
    // vertexLoc = glGetAttribLocation (program->programId(), "vertex");
    // vertexCol = glGetAttribLocation (program->programId(), "aColor");

    // Uniforms
    m_TransLocation = glGetUniformLocation(program->programId(), "uTG");
}
























