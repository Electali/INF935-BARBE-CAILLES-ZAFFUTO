#pragma once

#include "window.hpp"

#include <glm.hpp>

class Camera
{
public:
    Camera(float newFov, glm::vec3 newPosition) : matView(1),
                                                  fov(newFov),
                                                  position(newPosition),
                                                  up(0, 1, 0),
                                                  front(0, 0, -1),
                                                  isDirty(true)
    {
    }

public:
    void moveLeft(float speed, float dt)
    {
        position -= glm::normalize(glm::cross(front, up)) * speed * dt;
        isDirty = true;
    }

    void moveRight(float speed, float dt)
    {
        position += glm::normalize(glm::cross(front, up)) * speed * dt;
        isDirty = true;
    }

    void moveUp(float speed, float dt)
    {
        position += up * speed * dt;
        isDirty = true;
    }

    void moveDown(float speed, float dt)
    {
        position -= up * speed * dt;
        isDirty = true;
    }

    void moveForward(float speed, float dt)
    {
        position += front * speed * dt;
        isDirty = true;
    }

    void moveBackwards(float speed, float dt)
    {
        position -= front * speed * dt;
        isDirty = true;
    }

public:
    glm::mat4 projection(Window &window)
    {
        return glm::perspective(glm::radians(fov), ((float)window.getWidth()) / ((float)window.getHeight()), 0.1f, 100.f);
    }

    glm::mat4 &view()
    {
        if (isDirty)
        {
            matView = glm::lookAt(position, position + front, up);
            isDirty = false;
        }

        return matView;
    }
public:
    float fov;

private:
    glm::mat4 matView;
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    bool isDirty;
};