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
#include <iostream>

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
    
    // 顶点着色器的处理
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &LEARN_OPEN_GL::vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[LEARN_OPEN_GL::LOG_INFO_LEN];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 获取编译信息
        glGetShaderInfoLog(vertexShader, LEARN_OPEN_GL::LOG_INFO_LEN, NULL, infoLog);
        std::cout<<"Compile vertex shader failed : info "<<infoLog<<std::endl;
        return -1;
    }
    
    // 片段着色器的编译
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &LEARN_OPEN_GL::fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, LEARN_OPEN_GL::LOG_INFO_LEN, NULL, infoLog);
        std::cout<<"Compile fragment shader failed:info"<<infoLog<<std::endl;
        return -1;
    }
    
    // 着色器程序
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderProgram, LEARN_OPEN_GL::LOG_INFO_LEN, NULL, infoLog);
        std::cout<<"Link shader failed : info " <<infoLog<<std::endl;
        return -1;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // 三角形顶点的处理，使用索引缓存
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::vertices),
                 LEARN_OPEN_GL::vertices,
                 GL_STATIC_DRAW);
    
    //  绑定缓存
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::indices),
                 LEARN_OPEN_GL::indices,
                 GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClearColor(0.5f, 0.2, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
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
