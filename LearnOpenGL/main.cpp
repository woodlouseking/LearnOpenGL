//
//  main.cpp
//  LearnOpenGL
//
//  Created by www on 2019/11/2.
//  Copyright © 2019年 woodlouse. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "const/const.h"
#include "render/render.h"
#include <iostream>
#include "shader.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
#include "stb_image.h"
#include "userInput.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//用户输入
userInput userInputHandler;
//处理鼠标的输入
void mouseCallBack(GLFWwindow *window, double xPos, double yPos)
{
    userInputHandler.mouseCallBack(window, xPos, yPos);
}
//处理鼠标滚动
void scrollCallBack(GLFWwindow *window, double xoff, double yoff)
{
    userInputHandler.mouseScroll(window, xoff, yoff);
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow *window = glfwCreateWindow(LEARN_OPEN_GL::SCR_WIDTH,
                                          LEARN_OPEN_GL::SCR_HEIGHT,
                                          LEARN_OPEN_GL::SCR_TLE,
                                          NULL,
                                          NULL);
    
    if (!window) {
        std::cout<<"Create Window fail"<<std::endl;
        glfwTerminate();
        return -1;
    }

    //设置当前上下文环境
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"GLAD FAIL"<<std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scrollCallBack);
    
//    twoTriangleByDifferentAB render; // 使用不同的VAO VBO绘制两个三角行
//    drawRectangleByIndex render; // 使用索引绘制一个矩形
//    drawTriangle render; // 绘制三角形
//    neighborTriangle render; // 绘制相邻两个三角形
//    drawTriangleWithColor render; // 绘制指定顶点颜色的三角形
//    drawRectanleWithTex render; // 使用箱子纹理
//    drawRectanleWithTwoTex render; // 使用箱子和笑脸的纹理
//    drawRectanleWithGLM render;  // 矩阵变幻
//    draw3D_0 render; // 第一个3D图像
//    draw3D_cube render; // 立方体渲染器
//    draw3D_moreCube render; // 10个立方体
//    draw3DCubeWithAutogyrationCamera render; //自旋转摄像机
//    manualCamera render; // 手动控制摄像机
//    lightColor render; // 光照场景
//    AmbientLight render; // 环境光照
//    DiffuseLighting render; // 漫反射光照
    ReflectLighting render; // 镜面反射光照
    render.init();
    
    if (render.getCamera()) {
        userInputHandler.addHandler(render.getCamera());
    }
    
    // 捕捉鼠标
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallBack);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        userInputHandler.processInput(window);
        
        render.Rendering();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    render.clear();
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
