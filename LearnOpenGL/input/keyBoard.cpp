//
//  keyBoard.cpp
//  LearnOpenGL
//
//  Created by www on 2019/11/20.
//

#include <GLFW/glfw3.h>
#include "keyBoard.h"

void keyBoard::processInput(GLFWwindow *window)
{
    //检测W S A D
    checkKey(window, GLFW_KEY_W);
    checkKey(window, GLFW_KEY_S);
    checkKey(window, GLFW_KEY_A);
    checkKey(window, GLFW_KEY_D);
}

void keyBoard::checkKey(GLFWwindow *window, int keyVal)
{
    int status = glfwGetKey(window, keyVal);
    if (status == GLFW_PRESS) {
        m_bPress[keyVal] = true;
        return;
    }
    
    m_bPress[keyVal] = false;
}
