//
//  render.h
//  LearnOpenGL
//
//  Created by www on 2019/11/5.
//  Copyright © 2019年 woodlouse. All rights reserved.
//

#ifndef my_render_h
#define my_render_h

#include "const.h"

class render{
public:
    //初始化
    virtual void init() = 0;
    // 渲染
    virtual void draw() = 0;
    //清理
    virtual void clear() = 0;

    virtual ~render() {};

protected:
    virtual void _initShader(const char *vertexShaderSource = LEARN_OPEN_GL::vertexShaderSource, const char *fragmentShaderSource=LEARN_OPEN_GL::fragmentShaderSource);
    virtual void clearScreen();

protected:
    GLuint m_shaderProgram;
};

//绘制三角形
class drawTriangle : public render {
public:
    void init() override;
    void draw() override;
    void clear() override;
private:
    void _bindData();
private:
    GLuint m_VAO;
    GLuint m_VBO;
};


//绘制两个相邻的三角形
class neighborTriangle : public render
{
public:
    void init() override;
    void draw() override;
    void clear() override;
private:
    void _bindData();
    
private:
    GLuint m_VAO;
    GLuint m_VBO;
};


//使用索引绘制矩形
class drawRectangleByIndex : public render{
public:
    void init() override;
    void draw() override;
    void clear() override;
private:
    void _bindData();
    
private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};

//使用不同的VAO VBO绘制两个三角形
class twoTriangleByDifferentAB : public render {
public:
    void init() override;
    void draw() override;
    void clear() override;

private:
    void _bindData();

private:
    GLuint m_VAOs[2];
    GLuint m_VBOs[2];
};

//绘制三角形（顶点颜色在顶点数组中）
class drawTriangleWithColor : public render {
public:
    void init() override;
    void draw() override;
    void clear() override;
    
private:
    void _bindData();
private:
    GLuint m_VAO;
    GLuint m_VBO;
};

#endif /* my_render_h */
