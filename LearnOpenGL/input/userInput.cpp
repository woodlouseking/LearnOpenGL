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
    
    // 各个检测者处理鼠标移动
    std::vector<inputHandler*>::iterator it = m_inputHandler.begin();
    std::vector<inputHandler*>::iterator end = m_inputHandler.end();
    
    for(; it!=end; it++) {
        (*it)->onMouseMoving(m_xOffset, m_yOffset);
    }
}

void userInput::processInput(GLFWwindow *window)
{
    //检测W S A D
    checkKey(window, GLFW_KEY_W);
    checkKey(window, GLFW_KEY_S);
    checkKey(window, GLFW_KEY_A);
    checkKey(window, GLFW_KEY_D);
    
    std::vector<inputHandler*>::iterator it = m_inputHandler.begin();
    std::vector<inputHandler*>::iterator end = m_inputHandler.end();
    for(; it!=end; it++) {
        (*it)->onKeyBoard(this);
    }
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

//滚轮的处理
void userInput::mouseScroll(GLFWwindow *window, double xoff, double yoff)
{
    m_scrollXoffset = xoff;
    m_scrollYoffset = yoff;
    
    std::vector<inputHandler*>::iterator it = m_inputHandler.begin();
    std::vector<inputHandler*>::iterator end = m_inputHandler.end();
    
    for(; it!=end; ++it) {
        (*it)->onMouseScroll(xoff, yoff);
    }
}

//添加处理者
void userInput::addHandler(inputHandler *handler)
{
    m_inputHandler.push_back(handler);
}

//移除处理者
void userInput::removeHandler(inputHandler *handler)
{
    std::vector<inputHandler*>::iterator it = m_inputHandler.begin();
    std::vector<inputHandler*>::iterator end = m_inputHandler.end();
    for(;it!=end;++it) {
        if (*it == handler) {
            m_inputHandler.erase(it);
            break;
        }
    }
}
