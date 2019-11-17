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
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

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
    clearScreen();
    
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
    clearScreen();
    
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
    clearScreen();
    
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
    clearScreen();
    
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
