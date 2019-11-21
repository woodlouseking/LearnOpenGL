//
//  keyBoard.hpp
//  LearnOpenGL
//
//  Created by www on 2019/11/20.
//

#ifndef userInput_h
#define userInput_h

class GLFWwindow;

#include "const.h"

class userInput
{
public:
    userInput();
    
    // 监听鼠标移动的函数
    void mouseCallBack(GLFWwindow *window, double xPos, double yPos);
    //获取鼠标偏移
    void getMouseOffset(float &xOffset, float &yOffset) {
        xOffset = m_xOffset;
        yOffset = m_yOffset;
        //鼠标由运动转为静止后此值不会再更新，取用后就设置为0
        m_xOffset = 0;
        m_yOffset = 0;
    }

    // 处理按键信息
    void processInput(GLFWwindow *window);
    
    //获取某一个按键是否被按下了
    bool isPress(int keyVal) {
        return m_bPress[keyVal];
    }

private:
    //检测一个键的状态
    void checkKey(GLFWwindow *window, int keyVal);
    
private:
    bool m_bPress[LEARN_OPEN_GL::KEY_STATS_LEN];
    
    //鼠标位置
    bool m_bFirstMouse; // 是否是第一次处理鼠标
    double m_lastXPos;
    double m_lastYpos;
    //计算出的偏移量
    float m_xOffset;
    float m_yOffset;
};

#endif /* userInput_h */
