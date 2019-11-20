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
#include "renderTexture.h"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
#include "userInput.h"

render::render():
m_pShader(NULL),
m_deltaTime(0.0),
m_lastFrameTime(0.0) {
    
}

//渲染入口
void render::Rendering()
{
    //一些公共处理：计算帧间隔
    GLfloat currentTime = glfwGetTime();
    m_deltaTime = currentTime - m_lastFrameTime;
    m_lastFrameTime = currentTime;
    
    clearScreen();
    
    //子类实现
    draw();
}

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
 ** 使用h索引绘制带纹理的矩形，纹理的处理暂且在main函数中
 */
void drawRectanleWithTex::init()
{
    _initShader("resources/shader/4_1_tex.vs", "resources/shader/4_1_tex.fs");
    _bindData();
    //设置渲染图片
    m_pTex = new renderTexture("resources/textures/container.jpg", GL_RGB);
}

//绑定数据
void drawRectanleWithTex::_bindData()
{
    // 生成对象
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    
    // 绑定
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    
    //拷贝数据
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::verticesForRectWithTex),
                 LEARN_OPEN_GL::verticesForRectWithTex,
                 GL_STATIC_DRAW);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::indices),
                 LEARN_OPEN_GL::indices,
                 GL_STATIC_DRAW);
    
    // 绑定数据
    // 位置数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //颜色数据
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //坐标数据
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawRectanleWithTex::draw()
{
    
    m_pShader->use();
    
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawRectanleWithTex::clear()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    if (m_pTex) {
        delete m_pTex;
        m_pTex = NULL;
    }
}

/*
 ** 使用两个纹理图片的渲染
 */
void drawRectanleWithTwoTex::init()
{
    _initShader("resources/shader/4_1_tex.vs", "resources/shader/4_1_2tex.fs");
    _bindData();
    m_pTex1 = new renderTexture("resources/textures/container.jpg", GL_RGB);
    m_pTex2 = new renderTexture("resources/textures/awesomeface.png", GL_RGBA);
    
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
    m_pShader->setInt("texture2", 1);
}

void drawRectanleWithTwoTex::_bindData()
{
    // 生成对象
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    
    // 绑定
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    
    //拷贝数据
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::verticesForRectWithTex),
                 LEARN_OPEN_GL::verticesForRectWithTex,
                 GL_STATIC_DRAW);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::indices),
                 LEARN_OPEN_GL::indices,
                 GL_STATIC_DRAW);
    
    // 绑定数据
    // 位置数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //颜色数据
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //坐标数据
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawRectanleWithTwoTex::draw()
{
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pTex1->textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pTex2->textureId);
    
    m_pShader->use();
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawRectanleWithTwoTex::clear()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    if (m_pTex1) {
        delete m_pTex1;
        m_pTex1 = NULL;
    }
    if (m_pTex2) {
        delete m_pTex2;
        m_pTex2 = NULL;
    }
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

/*
 ** 进行矩阵变幻
 */
void drawRectanleWithGLM::init()
{
    _initShader("resources/shader/4_1_texglm.vs", "resources/shader/4_1_2tex.fs");
    _bindData();
    m_pTex1 = new renderTexture("resources/textures/container.jpg", GL_RGB);
    m_pTex2 = new renderTexture("resources/textures/awesomeface.png", GL_RGBA);
    
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
    m_pShader->setInt("texture2", 1);
    
    glm::mat4 trans(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    
    unsigned int loc = glGetUniformLocation(m_pShader->ID, "transform");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(trans));
}

void drawRectanleWithGLM::_bindData()
{
    // 生成对象
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    
    // 绑定
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    
    //拷贝数据
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::verticesForRectWithTex),
                 LEARN_OPEN_GL::verticesForRectWithTex,
                 GL_STATIC_DRAW);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::indices),
                 LEARN_OPEN_GL::indices,
                 GL_STATIC_DRAW);
    
    // 绑定数据
    // 位置数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //颜色数据
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //坐标数据
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawRectanleWithGLM::draw()
{
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pTex1->textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pTex2->textureId);
    
    m_pShader->use();
    
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawRectanleWithGLM::clear()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    if (m_pTex1) {
        delete m_pTex1;
        m_pTex1 = NULL;
    }
    if (m_pTex2) {
        delete m_pTex2;
        m_pTex2 = NULL;
    }
}

/*
 ** 3D图形渲染
 */
void draw3D_0::init()
{
    _initShader("resources/shader/5_1_3D.vs", "resources/shader/5_1_3D.fs");
    _bindData();
    m_pTex1 = new renderTexture("resources/textures/container.jpg", GL_RGB);
    m_pTex2 = new renderTexture("resources/textures/awesomeface.png", GL_RGBA);
    
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
    m_pShader->setInt("texture2", 1);
}

void draw3D_0::_bindData()
{
    // 生成对象
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    
    // 绑定
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    
    //拷贝数据
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::verticesForRectWithTex),
                 LEARN_OPEN_GL::verticesForRectWithTex,
                 GL_STATIC_DRAW);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::indices),
                 LEARN_OPEN_GL::indices,
                 GL_STATIC_DRAW);
    
    // 绑定数据
    // 位置数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //颜色数据
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //坐标数据
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    //设置变换矩阵
    // 模型矩阵
    glm::mat4 model(1.0);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    //观察矩阵
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    
    //投影矩阵
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f),
                                  float(LEARN_OPEN_GL::SCR_WIDTH/LEARN_OPEN_GL::SCR_HEIGHT),
                                  0.1f,
                                  100.0f);
    
    //传入顶点着色器
    m_pShader->use();
    GLuint locModel = glGetUniformLocation(m_pShader->ID, "model");
    glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
    
    GLuint locView = glGetUniformLocation(m_pShader->ID, "view");
    glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));
    
    GLuint locProjection = glGetUniformLocation(m_pShader->ID, "projection");
    glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(projection));
    
}

void draw3D_0::draw()
{
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pTex1->textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pTex2->textureId);
    
    m_pShader->use();
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void draw3D_0::clear()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    if (m_pTex1) {
        delete m_pTex1;
        m_pTex1 = NULL;
    }
    if (m_pTex2) {
        delete m_pTex2;
        m_pTex2 = NULL;
    }
}


/*
 ** 3D cube
 */
void draw3D_cube::init()
{
    _initShader("resources/shader/5_2_cube.vs", "resources/shader/5_2_cube.fs");
    _bindData();
    m_pTex1 = new renderTexture("resources/textures/container.jpg", GL_RGB);
    m_pTex2 = new renderTexture("resources/textures/awesomeface.png", GL_RGBA);
    
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
    m_pShader->setInt("texture2", 1);
    
    //开启Z缓冲
    glEnable(GL_DEPTH_TEST);
}

void draw3D_cube::_bindData()
{
    // 生成对象
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    
    // 绑定
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    //拷贝数据
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::cubeVertices),
                 LEARN_OPEN_GL::cubeVertices,
                 GL_STATIC_DRAW);
    
    // 绑定数据
    // 位置数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //坐标数据
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw3D_cube::draw()
{
    
    //清除深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pTex1->textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pTex2->textureId);
    
    m_pShader->use();
    
    //设置变换矩阵
    // 模型矩阵
    glm::mat4 model(1.0);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
    
    //观察矩阵
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    
    //投影矩阵
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f),
                                  float(LEARN_OPEN_GL::SCR_WIDTH/LEARN_OPEN_GL::SCR_HEIGHT),
                                  0.1f,
                                  100.0f);
    
    //传入顶点着色器
    GLuint locModel = glGetUniformLocation(m_pShader->ID, "model");
    glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
    
    GLuint locView = glGetUniformLocation(m_pShader->ID, "view");
    glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));
    
    GLuint locProjection = glGetUniformLocation(m_pShader->ID, "projection");
    glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(projection));
    
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void draw3D_cube::clear()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    
    if (m_pTex1) {
        delete m_pTex1;
        m_pTex1 = NULL;
    }
    if (m_pTex2) {
        delete m_pTex2;
        m_pTex2 = NULL;
    }
}


/*
 ** 3D 10个cube
 */
void draw3D_moreCube::init()
{
    _initShader("resources/shader/5_2_cube.vs", "resources/shader/5_2_cube.fs");
    _bindData();
    m_pTex1 = new renderTexture("resources/textures/container.jpg", GL_RGB);
    m_pTex2 = new renderTexture("resources/textures/awesomeface.png", GL_RGBA);
    
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
    m_pShader->setInt("texture2", 1);
    
    //开启Z缓冲
    glEnable(GL_DEPTH_TEST);
}

void draw3D_moreCube::_bindData()
{
    // 生成对象
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    
    // 绑定
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    //拷贝数据
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::cubeVertices),
                 LEARN_OPEN_GL::cubeVertices,
                 GL_STATIC_DRAW);
    
    // 绑定数据
    // 位置数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //坐标数据
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //设置变换矩阵
    //观察矩阵
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    
    //投影矩阵
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f),
                                  float(LEARN_OPEN_GL::SCR_WIDTH/LEARN_OPEN_GL::SCR_HEIGHT),
                                  0.1f,
                                  100.0f);
    
    //传入顶点着色器
    m_pShader->use();
    GLuint locView = glGetUniformLocation(m_pShader->ID, "view");
    glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));
    
    GLuint locProjection = glGetUniformLocation(m_pShader->ID, "projection");
    glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(projection));
    
}

void draw3D_moreCube::draw()
{
    
    //清除深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pTex1->textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pTex2->textureId);
    
    m_pShader->use();
    
    //不同的世界坐标
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    glBindVertexArray(m_VAO);
    
    // 模型矩阵
    for(int i=0; i<10; i++) {
        glm::mat4 model(1.0);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
        GLuint locModel = glGetUniformLocation(m_pShader->ID, "model");
        glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void draw3D_moreCube::clear()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    
    if (m_pTex1) {
        delete m_pTex1;
        m_pTex1 = NULL;
    }
    if (m_pTex2) {
        delete m_pTex2;
        m_pTex2 = NULL;
    }
}

/*
 ** 3D Camera旋转
 */
void draw3DCubeWithAutogyrationCamera::init()
{
    _initShader("resources/shader/5_2_cube.vs", "resources/shader/5_2_cube.fs");
    _bindData();
    m_pTex1 = new renderTexture("resources/textures/container.jpg", GL_RGB);
    m_pTex2 = new renderTexture("resources/textures/awesomeface.png", GL_RGBA);
    
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
    m_pShader->setInt("texture2", 1);
    
    //开启Z缓冲
    glEnable(GL_DEPTH_TEST);
}

void draw3DCubeWithAutogyrationCamera::_bindData()
{
    // 生成对象
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    
    // 绑定
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    //拷贝数据
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::cubeVertices),
                 LEARN_OPEN_GL::cubeVertices,
                 GL_STATIC_DRAW);
    
    // 绑定数据
    // 位置数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //坐标数据
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //设置变换矩阵
    //投影矩阵
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f),
                                  float(LEARN_OPEN_GL::SCR_WIDTH/LEARN_OPEN_GL::SCR_HEIGHT),
                                  0.1f,
                                  100.0f);
    
    //传入顶点着色器
    m_pShader->use();
    GLuint locProjection = glGetUniformLocation(m_pShader->ID, "projection");
    glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(projection));
    
}

void draw3DCubeWithAutogyrationCamera::draw()
{
    float currentFrame = glfwGetTime();
    
    
    //清除深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pTex1->textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pTex2->textureId);
    
    m_pShader->use();
    
    //不同的世界坐标
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    glBindVertexArray(m_VAO);
    
    //观察矩阵/旋转矩阵转起来
    GLfloat radius = 10.0f;
    GLfloat camX = sin(glfwGetTime()) * radius;
    GLfloat camZ = cos(glfwGetTime()) * radius;
    
    glm::mat4 view(1.0f);
    view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
    
    GLuint locView = glGetUniformLocation(m_pShader->ID, "view");
    glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));
    
    // 模型矩阵
    for(int i=0; i<10; i++) {
        glm::mat4 model(1.0);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.5f));
        GLuint locModel = glGetUniformLocation(m_pShader->ID, "model");
        glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void draw3DCubeWithAutogyrationCamera::clear()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    
    if (m_pTex1) {
        delete m_pTex1;
        m_pTex1 = NULL;
    }
    if (m_pTex2) {
        delete m_pTex2;
        m_pTex2 = NULL;
    }
}

/*
 ** 3D 手动控制Camera
 */
void manualCamera::init()
{
    //初始化摄像机位置
    m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    
    _initShader("resources/shader/5_2_cube.vs", "resources/shader/5_2_cube.fs");
    _bindData();
    m_pTex1 = new renderTexture("resources/textures/container.jpg", GL_RGB);
    m_pTex2 = new renderTexture("resources/textures/awesomeface.png", GL_RGBA);
    
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
    m_pShader->setInt("texture2", 1);
    
    //开启Z缓冲
    glEnable(GL_DEPTH_TEST);
}

void manualCamera::_bindData()
{
    // 生成对象
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    
    // 绑定
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    //拷贝数据
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(LEARN_OPEN_GL::cubeVertices),
                 LEARN_OPEN_GL::cubeVertices,
                 GL_STATIC_DRAW);
    
    // 绑定数据
    // 位置数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //坐标数据
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //设置变换矩阵
    //投影矩阵
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f),
                                  float(LEARN_OPEN_GL::SCR_WIDTH/LEARN_OPEN_GL::SCR_HEIGHT),
                                  0.1f,
                                  100.0f);
    
    //传入顶点着色器
    m_pShader->use();
    GLuint locProjection = glGetUniformLocation(m_pShader->ID, "projection");
    glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(projection));
    
}

void manualCamera::draw()
{
    
    //清除深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pTex1->textureId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pTex2->textureId);
    
    m_pShader->use();
    
    //不同的世界坐标
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    glBindVertexArray(m_VAO);
    
    checkInput();
    
    //观察矩阵/旋转矩阵转起来
    glm::mat4 view = glm::lookAt(m_cameraPos, m_cameraPos+m_cameraFront, m_cameraUp);
    
    GLuint locView = glGetUniformLocation(m_pShader->ID, "view");
    glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));
    
    // 模型矩阵
    for(int i=0; i<10; i++) {
        glm::mat4 model(1.0);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.5f));
        GLuint locModel = glGetUniformLocation(m_pShader->ID, "model");
        glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void manualCamera::checkInput()
{
    if(!m_pInputHandler) {
        return;
    }
    float speed = 5.0f * m_deltaTime;
    if (m_pInputHandler->isPress(GLFW_KEY_W)) {
        m_cameraPos += speed * m_cameraFront;
    } else if(m_pInputHandler->isPress(GLFW_KEY_S)) {
        m_cameraPos -= speed * m_cameraFront;
    } else if(m_pInputHandler->isPress(GLFW_KEY_A)) {
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
    } else if(m_pInputHandler->isPress(GLFW_KEY_D)) {
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
    }
}

void manualCamera::clear()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    
    if (m_pTex1) {
        delete m_pTex1;
        m_pTex1 = NULL;
    }
    if (m_pTex2) {
        delete m_pTex2;
        m_pTex2 = NULL;
    }
}
