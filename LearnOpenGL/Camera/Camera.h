//
//  camera.h
//  LearnOpenGL
//
//  Created by www on 2019/11/25.
//  Copyright © 2019年 woodlouse. All rights reserved.

#ifndef camera_h
#define camera_h

#include "glm.hpp"
#include "userInput.h"

class Camera : public inputHandler
{
public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
           glm::vec3 worldUP = glm::vec3(0.0f, 1.0f, 0.0f),
           float zoom = 45.0f,
           float pitch = 0.0f,
           float yaw = -90.0f);
    
    ~Camera();
    
    glm::mat4 GetViewMatrix();
    
    // 鼠标移动的监听
    void onMouseMoving(float xOffset, float yOffset) override;
    
    //鼠标轮滚动的监听处理
    void onMouseScroll(float xOffset, float yOffset) override;
    
    //键盘的监听
    void onKeyBoard(userInput *obj) override;
    
    float zoom() const{
        return m_zoom;
    }
    
    void setDelta(float *delta) {
        m_pDeltaTime = delta;
    }
    
    glm::vec3 getPos()const {
        return m_cameraPos;
    }
    
    glm::vec3 getFront()const {
        return m_cameraFront;
    }
    
private:
    void updateCameraVectors();
    
private:
    glm::vec3 m_cameraPos; //位置
    glm::vec3 m_cameraFront;
    glm::vec3 m_WorldUp;
    glm::vec3 m_Right;
    glm::vec3 m_up;
    
    
    float m_zoom;
    
    //欧拉角
    float m_pitch; // 俯仰角
    float m_yaw; // 偏航角
    
    // 时间间隔
    float *m_pDeltaTime;
};


#endif /* camera_h */
