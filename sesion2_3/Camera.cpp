#include "Camera.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(float aspectRatio)
    : Yaw(0.0f), Pitch(0.0f), m_Direction(glm::vec3(0.0f, 0.0f, 1.0f)), m_ProjType(PERSPECTIVE),
      VRP(0.0f), OBS(0.0f, 0.0f, 2.0f), up(0.0f, 1.0f, 0.0f), radius(1.0f),
      FOV(glm::radians(60.0f)), ar(aspectRatio), zNear(0.1f), zFar(10.0f),
      left(-4.0f), right(4.0f), bottom(-4.0f), top(4.0f)
{
    RecalculateProj();
    RecalculateView();
}

Camera::~Camera()
{
}

void Camera::Init(float aspect_ratio, const glm::vec3& max_point, const glm::vec3& min_point)
{
    glm::vec3 center = (min_point + max_point) / 2.0f;
    radius = glm::length(max_point - center);
    float dist = 2.0f * radius;
    float alpha = glm::asin(radius / dist);

    VRP = glm::vec3(0.0f);
    OBS = VRP + m_Direction * dist;
    up  = glm::vec3(0.0f, 1.0f, 0.0f);

    FOV = 2.0f * alpha;
    ar = aspect_ratio;
    zNear = dist - radius;
    zFar  = dist + radius;

    left   = -radius * ar;
    right  = radius * ar;
    bottom = -radius;
    top    = radius;

    if (ar >= 1.0f)
    {
        RecalculateProj();
        RecalculateView();
    }
    else
        ChangeAspectRatio(ar);
}

void Camera::ChangeAspectRatio(float newAspectRatio)
{
    if (m_ProjType == PERSPECTIVE)
    {
        float aFOV = FOV;
        if (newAspectRatio < 1.0f)
            aFOV = 2.0f * glm::atan(glm::tan(FOV / 2.0f) / newAspectRatio);
        m_ProjMatrix = glm::perspective(aFOV, newAspectRatio, zNear, zFar);
    }
    else
    {
        if (newAspectRatio >= 1.0f)
        {
            left = -radius * newAspectRatio;
            right = radius * newAspectRatio;
        }
        else
        {
            left = -radius;
            right = radius;
            bottom = -radius / newAspectRatio;
            top = radius / newAspectRatio;
        }
        RecalculateProj();
    }
    ar = newAspectRatio;
}

void Camera::SetProjectionType(int proj_type)
{
    m_ProjType = proj_type;
    RecalculateProj();
}

void Camera::ModifyPitch(float pitch_offset)
{
    Pitch += pitch_offset;
    glm::vec3 dir;
    dir.x = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw));
    dir.y = glm::sin(glm::radians(Pitch));
    dir.z = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
    m_Direction = dir;
    RecalculateView();
}
void Camera::ModifyYaw(float yaw_offset)
{
    Yaw += yaw_offset;
    glm::vec3 dir;
    dir.x = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw));
    dir.y = glm::sin(glm::radians(Pitch));
    dir.z = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
    m_Direction = dir;
    RecalculateView();
}

void Camera::RecalculateProj()
{
    switch (m_ProjType)
    {
        case PERSPECTIVE:
            m_ProjMatrix = glm::perspective(FOV, ar, zNear, zFar);
            break;
        case ORTHO:
            m_ProjMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
            break;
    }
}

void Camera::RecalculateView()
{
    OBS = VRP + m_Direction * 2.0f * radius;
    m_ViewMatrix = glm::lookAt(OBS, VRP, up);
}
