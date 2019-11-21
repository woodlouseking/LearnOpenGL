//
//  keyBoard.cpp
//  LearnOpenGL
//
//  Created by www on 2019/11/20.
//

#include <GLFW/glfw3.h>
#include <iostream>
#include "userInput.h"

userInput::userInput():
m_bFirstMouse(true),
m_lastYpos(LEARN_OPEN_GL::SCR_HEIGHT/2),
m_lastXPos(LEARN_OPEN_GL::SCR_WIDTH/2),
m_xOffset(0),
m_yOffset(0)
{
    
}

//鼠标的处理
void userInput::mouseCallBack(GLFWwindow *window, double xPos, double yPos)
{
    if(m_bFirstMouse) {
        m_bFirstMouse = false;
        m_lastYpos = yPos;
        m_lastXPos = xPos;
    }
    
    // 计算鼠标偏移
    m_xOffset = xPos - m_lastXPos;
    m_yOffset = m_lastYpos - yPos;
    
    m_lastXPos = xPos;
    m_lastYpos = yPos;
}

void userInput::processInput(GLFWwindow *window)
{
    //检测W S A D
    checkKey(window, GLFW_KEY_W);
    checkKey(window, GLFW_KEY_S);
    checkKey(window, GLFW_KEY_A);
    checkKey(window, GLFW_KEY_D);
}

void userInput::checkKey(GLFWwindow *window, int keyVal)
{
    int status = glfwGetKey(window, keyVal);
    if (status == GLFW_PRESS) {
        m_bPress[keyVal] = true;
        return;
    }
    
    m_bPress[keyVal] = false;
}
