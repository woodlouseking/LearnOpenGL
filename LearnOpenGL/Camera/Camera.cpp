//
//  camera.cpp
//  LearnOpenGL
//
//  Created by www on 2019/11/25.
//  Copyright © 2019年 woodlouse. All rights reserved.
//

#include "Camera.h"
#include "matrix_transform.hpp"
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 worldUP, float zoom, float pitch, float yaw):
m_cameraPos(pos),
m_cameraFront(front),
m_zoom(zoom),
m_WorldUp(worldUP),
m_yaw(yaw),
m_pitch(pitch)
{
    updateCameraVectors();
}

Camera::~Camera()
{
    
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(m_cameraPos, m_cameraPos+m_cameraFront, m_up);
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(front);
    
    //right and up
    m_Right = glm::normalize(glm::cross(m_cameraFront, m_WorldUp));
    m_up = glm::normalize(glm::cross(m_Right, m_cameraFront));
}


// 鼠标移动的监听
void Camera::onMouseMoving(float xOffset, float yOffset)
{
    //鼠标的处理
    float sensitivity = 0.05;
    xOffset *= sensitivity;
    yOffset *= sensitivity;
    
    m_yaw += xOffset;
    m_pitch += yOffset;
    
    if (m_pitch > 89.0f) {
        m_pitch = 89.0f;
    }
    if (m_pitch < -89.0f) {
        m_pitch = -89;
    }
    
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(front);
    
    updateCameraVectors();
}

//鼠标轮滚动的监听处理
void Camera::onMouseScroll(float xOffset, float yOffset)
{
    //滚轮处理
    if (m_zoom>=1.0f && m_zoom<=45.0f) {
        m_zoom -= yOffset;
    }
    if (m_zoom <= 1.0f) {
        m_zoom = 1.0f;
    }
    if (m_zoom >= 45.0f) {
        m_zoom = 45.0f;
    }
    
    updateCameraVectors();
}

//键盘的监听
void Camera::onKeyBoard(userInput *obj)
{
    //按键的处理
    float speed = 5.0f * (*m_pDeltaTime);
    if (obj->isPress(GLFW_KEY_W)) {
        m_cameraPos += speed * m_cameraFront;
    } else if(obj->isPress(GLFW_KEY_S)) {
        m_cameraPos -= speed * m_cameraFront;
    } else if(obj->isPress(GLFW_KEY_A)) {
        m_cameraPos -= m_Right * speed;
    } else if(obj->isPress(GLFW_KEY_D)) {
        m_cameraPos += m_Right * speed;
    }
}
