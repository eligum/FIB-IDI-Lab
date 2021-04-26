
//#include <GL/glew.h>
#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
    setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
    if (program != NULL)
        delete program;
}

void MyGLWidget::initializeGL ()
{
    // Cal inicialitzar l'ús de les funcions d'OpenGL
    initializeOpenGLFunctions();

    glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    carregaShaders();
    creaBuffers();
}

void MyGLWidget::paintGL ()
{
    // Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
    GLint vp[4];
    glGetIntegerv (GL_VIEWPORT, vp);
    ample = vp[2];
    alt = vp[3];
#endif

    // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
    // useu els paràmetres que considereu (els que hi ha són els de per defecte)
    // glViewport (ample/2, alt/2, ample/2, alt/2);

    glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

    // GLuint unif_location_1 = glGetUniformLocation(program->programId(), "u_color");
    // GLuint unif_location_2 = glGetUniformLocation(program->programId(), "u_factor");

    glViewport (0, 0, ample, alt);

    glBindVertexArray(m_Vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Desactivem els VAOs
    glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
    ample = w;
    alt = h;
}

void MyGLWidget::creaBuffers ()
{
    glm::vec3 Vertices_pos[3];  // Tres vèrtexs amb X, Y i Z
    Vertices_pos[0] = glm::vec3(0.0, 1.0, 0.0);
    Vertices_pos[1] = glm::vec3(-1.0, -1.0, 0.0);
    Vertices_pos[2] = glm::vec3(1.0, -1.0, 0.0);

    glm::vec3 Vertices_col[3];  // Tres vèrtexs amb X, Y i Z
    Vertices_col[0] = glm::vec3(1.0, 0.0, 0.0);
    Vertices_col[1] = glm::vec3(0.0, 1.0, 0.0);
    Vertices_col[2] = glm::vec3(0.0, 0.0, 1.0);

    // Creació del Vertex Array Object (VAO) que usarem per pintar
    glGenVertexArrays(1, &m_Vao);
    glBindVertexArray(m_Vao);

    // Creació del buffer amb les dades dels vèrtexs
    GLuint VBO_pos;
    glGenBuffers(1, &VBO_pos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_pos), Vertices_pos, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    GLuint VBO_col;
    glGenBuffers(1, &VBO_col);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_col);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_col), Vertices_col, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glVertexAttribPointer(vertexCol, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexCol);

    glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
    // Creem els shaders per al fragment shader i el vertex shader
    QOpenGLShader fs (QOpenGLShader::Fragment, this);
    QOpenGLShader vs (QOpenGLShader::Vertex, this);
    // Carreguem el codi dels fitxers i els compilem
    fs.compileSourceFile("shaders/basicShader.frag");
    vs.compileSourceFile("shaders/basicShader.vert");
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
    vertexLoc = glGetAttribLocation (program->programId(), "vertex");
    vertexCol = glGetAttribLocation (program->programId(), "aColor");
}
