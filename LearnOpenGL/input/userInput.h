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
};

#endif /* userInput_h */
