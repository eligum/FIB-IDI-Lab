#pragma once

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    explicit MyGLWidget(QWidget* parent = nullptr);
    ~MyGLWidget();

protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL() override;

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL() override;

    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL(int width, int height) override;

    virtual void keyPressEvent(QKeyEvent* e) override;

    void modelTransform();

private:
    void creaBuffers();
    void carregaShaders();
private:
    QOpenGLShaderProgram* program;

    uint32_t m_VertexArray;
    int m_Width, m_Height;
    int m_TransLocation;
    float m_Value = 0.0f;
};
