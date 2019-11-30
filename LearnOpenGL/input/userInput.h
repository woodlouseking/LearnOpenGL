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
#include <vector>

class userInput;

class inputHandler
{
public:
    // 鼠标移动的监听
    void virtual onMouseMoving(float xOffset, float yOffset) = 0;
    
    //鼠标轮滚动的监听处理
    void virtual onMouseScroll(float xOffset, float yOffset) = 0;
    
    //键盘的监听
    void virtual onKeyBoard(userInput *obj) = 0;
};

class userInput
{
public:
    userInput();
    
    ~userInput(){
        m_inputHandler.clear();
    }
    
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
    
    void mouseScroll(GLFWwindow *window, double xoff, double yoff);
    
    //获取鼠标滚轮缩放
    void getMouseScroll(float &xoff, float &yoff) {
        xoff = m_scrollXoffset;
        yoff = m_scrollYoffset;
        m_scrollYoffset = 0;
        m_scrollXoffset = 0;
    }

    // 处理按键信息
    void processInput(GLFWwindow *window);
    
    //获取某一个按键是否被按下了
    bool isPress(int keyVal) {
        return m_bPress[keyVal];
    }
    
    //添加、移除处理者
    void addHandler(inputHandler *handler);
    void removeHandler(inputHandler *handler);
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
    
    //鼠标缩放的变量
    float m_scrollXoffset;
    float m_scrollYoffset;
    
    // 监听者
    std::vector<inputHandler*> m_inputHandler;
};

#endif /* userInput_h */
