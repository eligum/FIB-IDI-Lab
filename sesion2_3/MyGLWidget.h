// MyGLWidget.h
#include "Bl2GLWidget.h"
#include "model.h"

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
    virtual void mousePressEvent(QMouseEvent* evt) override;
    virtual void mouseReleaseEvent(QMouseEvent* evt) override;
    virtual void mouseMoveEvent(QMouseEvent* evt) override;
    virtual void wheelEvent(QWheelEvent* evt) override;

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

    void InitCamera(float aspect_ratio, const glm::vec3& max_point, const glm::vec3& min_point);
    void ProjectTransform();
    void ViewTransform();

protected:
    Model model;

    GLuint patricioVAO;
    Volume patricio;

    GLuint terraVAO;
    Volume terra;

    // Shader data
    int projLoc, viewLoc;

    // Camera controls and data
    enum class CameraAction { NONE = 0, ROTATE, PAN };
    enum class ProjectionType { ORTHO = 0, PERSPECTIVE };
    CameraAction action;
    ProjectionType projType;
    int xClickPos, yClickPos;

    float yaw, pitch, roll;
    float yawClick, pitchClick;
    float radiEscena;
    float FOV, aFOV, ar, zNear, zFar;
    float left, right, bottom, top;

private:
    int printOglError(const char file[], int line, const char func[]);
};
