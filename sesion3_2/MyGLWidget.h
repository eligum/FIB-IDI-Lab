// MyGLWidget.h
#include "Bl3GLWidget.h"
#include <glm/glm.hpp>

class MyGLWidget : public Bl3GLWidget {
    Q_OBJECT
public:
    MyGLWidget(QWidget *parent=0) : Bl3GLWidget(parent) {}
    ~MyGLWidget();
protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    
    void InitLlum();
    void UploadVec3(const char* u_name, const glm::vec3& vec);
    void UploadMat4(const char* u_name, const glm::mat4& mat);
    void UploadFloat(const char* u_name, float value);
protected:
    glm::vec3 matamb;
    glm::vec3 matdiff;
    glm::vec3 matspec;
    float matshin;
    glm::vec3 colFocus;//{0.8, 0.8, 0.8};
    glm::vec3 llumAmbient;// = vec3(0.2, 0.2, 0.2);
    glm::vec3 posFocus;// = vec3(1, 1, 1);  // en SCA
    glm::mat3 NormalMatrix;// = inverse(transpose(mat3(view * TG)));

private:
    int printOglError(const char file[], int line, const char func[]);
};
