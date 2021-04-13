#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
    enum { PERSPECTIVE, ORTHO };
public:
    Camera(float aspectRatio = 1.0f);
    ~Camera();

    void Init(float aspect_ratio, const glm::vec3& max_point, const glm::vec3& min_point);
    void ChangeAspectRatio(float newAspectRatio);
    void SetProjectionType(int proj_type);
    void ModifyPitch(float pitch_offset);
    void ModifyYaw(float yaw_offset);

    const glm::mat4& GetProjMatrix() const { return m_ProjMatrix; }
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
private:
    void RecalculateProj();
    void RecalculateView();
private:
    glm::mat4 m_ProjMatrix;
    glm::mat4 m_ViewMatrix;
    float Yaw, Pitch;
    glm::vec3 m_Direction;
    int m_ProjType;

    glm::vec3 VRP, OBS, up;
    float radius;
    float FOV, ar, zNear, zFar;
    float left, right, bottom, top;
};
