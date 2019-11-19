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
#include "shader.h"
#include "glm.hpp"

class renderTexture;
class userInput;

class render{
public:
    render():m_pShader(NULL){};
    
    //初始化
    virtual void init() = 0;
    // 渲染
    virtual void draw() = 0;
    //清理
    virtual void clear() = 0;
    
    //设置处理用户输入的对象
    virtual void setInputHandler(userInput *inputHandler){}
    
    virtual ~render() {
        if (m_pShader) {
            delete m_pShader;
            m_pShader = NULL;
        }
    };

protected:
    virtual void _initShader(const char *vertexShaderSource = "resources/shader/0_common.vs", const char *fragmentShaderSource="resources/shader/0_common.fs");
    virtual void clearScreen();

protected:
    //封装后的的shader
    LEARN_OPEN_GL::Shader *m_pShader;
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

// 绘制带纹理的矩形
class drawRectanleWithTex : public render{
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
    
    renderTexture *m_pTex;
};


// 绘制两个纹理的矩形
class drawRectanleWithTwoTex : public render{
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
    
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};


// 绘制两个纹理的矩形 使用GLM库进行矩阵相关的运算
class drawRectanleWithGLM : public render{
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
    
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};

// 3d图形
class draw3D_0 : public render{
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
    
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};

//3D cube
class draw3D_cube : public render{
public:
    void init() override;
    void draw() override;
    void clear() override;
private:
    void _bindData();
private:
    GLuint m_VAO;
    GLuint m_VBO;
    
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};

//3D cube
class draw3D_moreCube : public render{
public:
    void init() override;
    void draw() override;
    void clear() override;
private:
    void _bindData();
private:
    GLuint m_VAO;
    GLuint m_VBO;
    
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};

// 摄像机自旋转
class draw3DCubeWithAutogyrationCamera : public render{
public:
    void init() override;
    void draw() override;
    void clear() override;
private:
    void _bindData();
private:
    GLuint m_VAO;
    GLuint m_VBO;
    
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};

// 手动控制摄像机
class manualCamera : public render{
public:
    void init() override;
    void draw() override;
    void clear() override;
private:
    void _bindData();
private:
    GLuint m_VAO;
    GLuint m_VBO;
    
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
    
    //定义LookAt函数参数
    glm::vec3 m_cameraPos; //摄像机位置
    glm::vec3 m_cameraFront; // 摄像机前方
    glm::vec3 m_cameraUp; // 摄像机上方
    
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
    
    //设置处理用户输入的对象
    void setInputHandler(userInput *inputHandler){
        m_pInputHandler = inputHandler;
    }
    
private:
    void _bindData();
private:
    GLuint m_VAO;
    GLuint m_VBO;
    userInput *m_pInputHandler;
};

#endif /* my_render_h */
