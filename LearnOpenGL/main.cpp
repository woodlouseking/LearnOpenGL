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
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

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
    
    
    // 读取图片
    int width, height, nrChannels;
    unsigned char *data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    //设置环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 设置过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //设置数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //释放图片数据
    stbi_image_free(data);
    
//    twoTriangleByDifferentAB render; // 使用不同的VAO VBO绘制两个三角行
//    drawRectangleByIndex render; // 使用索引绘制一个矩形
//    drawTriangle render; // 绘制三角形
//    neighborTriangle render; // 绘制相邻两个三角形
//    drawTriangleWithColor render; // 绘制指定顶点颜色的三角形
    drawRectanleWithTex render;
    render.init();
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        
        render.draw();
        
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
