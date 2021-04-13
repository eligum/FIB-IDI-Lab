// MyGLWidget.h
#include "Bl2GLWidget.h"
#include "model.h"
#include "Camera.h"

struct Volume
{
    glm::vec3 ModelBase;
    glm::vec3 ModelCenter;
    glm::vec3 ModelSize;
};

class MyGLWidget : public Bl2GLWidget
{
    Q_OBJECT

public:
    MyGLWidget(QWidget* parent = nullptr)
        : Bl2GLWidget(parent) {}
    ~MyGLWidget();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void keyPressEvent(QKeyEvent* event) override;

    virtual void creaBuffers() override;
    virtual void carregaShaders() override;
    // virtual void modelTransform() override;

    //----------------------------------------------------------------------------//
    //--- New Stuff --------------------------------------------------------------//
    //----------------------------------------------------------------------------//
    void UploadMat4   (const std::string& varName, const glm::mat4& matrix);
    void UploadFloat4 (const std::string& varName, const glm::vec4& vector);
    void UploadFloat3 (const std::string& varName, const glm::vec3& vector);
    void UploadInt    (const std::string& varName, int value);


protected:
    Camera camera;
    bool cameraOptic = true;
    Model model;

    GLuint patricioVAO;
    Volume patricio;

    GLuint terraVAO;
    Volume terra;

    glm::vec3 terraPos;
    glm::vec3 terraScale;
    float terraSize;

private:
    int printOglError(const char file[], int line, const char func[]);
};
