//
//  render.cpp
//  LearnOpenGL
//
//  Created by www on 2019/11/5.
//  Copyright © 2019年 woodlouse. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "render.h"

// 编译着色器
void render::_initShader(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    m_pShader = new LEARN_OPEN_GL::Shader(vertexShaderSource, fragmentShaderSource);
}

void render::clearScreen()
{
    glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


/*
    ** 绘制三角形
*/
void drawTriangle::init()
{
    // 着色器
    _initShader();
    // 绑定数据
    _bindData();
}

void drawTriangle::_bindData()
{
    glGenBuffers(1, &m_VBO);
    glGenVertexArrays(1, &m_VAO);
    
    glBindVertexArray(m_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::vertecies),
                 LEARN_OPEN_GL::vertecies,
                 GL_STATIC_DRAW);
    // 链接顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawTriangle::draw()
{
    clearScreen();
    
//    glUseProgram(m_shaderProgram);
    m_pShader->use();
    
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawTriangle::clear()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}



/*
 **绘制两个相邻三角形
*/
void neighborTriangle::init()
{
    _initShader();
    _bindData();
}

void neighborTriangle::_bindData()
{
    glGenBuffers(1, &m_VBO);
    glGenVertexArrays(1, &m_VAO);
    
    glBindVertexArray(m_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::neighborVertecies),
                 LEARN_OPEN_GL::neighborVertecies,
                 GL_STATIC_DRAW);
    
    // 连接顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void neighborTriangle::draw()
{
    clearScreen();
    
    m_pShader->use();
    
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void neighborTriangle::clear()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

/*
 ** 使用索引绘制矩形
*/
void drawRectangleByIndex::init()
{
    // 编译着色器
    _initShader();
    //设置
    _bindData();
}

void drawRectangleByIndex::draw()
{
    // 设置绘制模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 开启线框模式
    
    clearScreen();
    
    m_pShader->use();
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

void drawRectangleByIndex::clear()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_VBO);
}

void drawRectangleByIndex::_bindData()
{
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);
    
    glBindVertexArray(m_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::verticesForRect),
                 LEARN_OPEN_GL::verticesForRect,
                 GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::indices),
                 LEARN_OPEN_GL::indices,
                 GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


/*
 ** 使用不同的VAO/VBO绘制两个三角形
*/
void twoTriangleByDifferentAB::init()
{
    _initShader();
    _bindData();
}

void twoTriangleByDifferentAB::draw()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 开启线框模式
    
    clearScreen();
    
    m_pShader->use();
    glBindVertexArray(m_VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(m_VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void twoTriangleByDifferentAB::clear()
{
    glDeleteVertexArrays(2, m_VAOs);
    glDeleteBuffers(2, m_VBOs);
}

void twoTriangleByDifferentAB::_bindData()
{
    // 三角形顶点的处理，使用索引缓存
    glGenVertexArrays(2, m_VAOs);
    glGenBuffers(2, m_VBOs);
    
    glBindVertexArray(m_VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::firstTriangle),
                 LEARN_OPEN_GL::firstTriangle,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(m_VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::secondTriangle),
                 LEARN_OPEN_GL::secondTriangle,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//with color
void drawTriangleWithColor::init()
{
//    _initShader(LEARN_OPEN_GL::vertexWithColorShaderSource, LEARN_OPEN_GL::framentWithColorShaderSource);
    _initShader("resources/shader/1_withColor.vs", "resources/shader/1_withColor.fs");
    _bindData();
}

void drawTriangleWithColor::_bindData()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    
    glBindVertexArray(m_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::verteciesWithColor),
                 LEARN_OPEN_GL::verteciesWithColor,
                 GL_STATIC_DRAW);
    
    // 顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawTriangleWithColor::draw()
{
    clearScreen();
    
//    glUseProgram(m_shaderProgram);
    m_pShader->use();
    
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawTriangleWithColor::clear()
{
    glDeleteBuffers(1, &m_VBO);
    glad_glDeleteVertexArrays(1, &m_VAO);
}
