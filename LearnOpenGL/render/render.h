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
#include "userInput.h"
#include "Camera.h"
#include "Model.hpp"

class renderTexture;

class render{
public:
    render();
    
    //初始化
    virtual void init() = 0;
    //渲染入口
    void Rendering();
    
    //清理
    virtual void clear() = 0;
    
    virtual ~render() {
        if (m_pShader) {
            delete m_pShader;
            m_pShader = NULL;
        }
    };
    
    Camera* getCamera() {
        return m_pCamera;
    }

protected:
    // 渲染
    virtual void draw() = 0;
    
    virtual void _initShader(const char *vertexShaderSource = "resources/shader/0_common.vs", const char *fragmentShaderSource="resources/shader/0_common.fs");
    virtual void clearScreen();

protected:
    //封装后的的shader
    LEARN_OPEN_GL::Shader *m_pShader;
    
    //渲染时间的计算
    float m_deltaTime;
    float m_lastFrameTime; //上一帧时间
    
    //摄像机
    Camera *m_pCamera;
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


// 光照
class lightColor : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();
    
private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    // 光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
};

//环境光照
class AmbientLight : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();
    
private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    // 光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
};

// 漫反射光照
class DiffuseLighting : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();

private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
    
};

// 漫反射光照
class ReflectLighting : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();

private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
};

// 移动光源
class MoveLight : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();

private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
};

// 应用材质
class UseMaterial : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();

private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
};

// 应用材质、光属性
class UseMaterialLight : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();

private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
};

// 随机光颜色
class UseRandomLight : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();

private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
};

// 漫反射贴图
class DiffuseTexture : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();
    
private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
    renderTexture *m_pTex;
};


// 镜面贴图
class SpecularTexture : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();
    
private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};


// 定向光
class DirectionalLight : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();
    
private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};

// 点光、衰减
class AttenuationLight : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();
    
private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};

// 手电筒光照
class FlashLight : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();
    
private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};

// 多光源
class MultiLight : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void _bindData();
    
private:
    GLuint m_objectVAO;
    GLuint m_objectVBO;
    
    GLuint m_ligthVAO;
    
    //光照着色器
    LEARN_OPEN_GL::Shader *m_pLightShader;
    renderTexture *m_pTex1;
    renderTexture *m_pTex2;
};


class Model;

// 模型渲染
class ModelRender : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    Model *m_pModel;
    
};

// 模板测试
class StencilTestRender : public render
{
public:
    void init() override;
    void clear() override;
    
protected:
    void draw() override;
    
private:
    void bindData();
    
private:
    // 箱子属性
    GLuint m_cubeVAO;
    GLuint m_cubeVBO;
    
    // 地板属性
    GLuint m_planeVAO;
    GLuint m_planeVBO;
    
    // 纹理
    renderTexture *m_pCubeTexture; // 箱子纹理
    renderTexture *m_pFloorTexture; // 地板纹理
    
    // 着色器
    LEARN_OPEN_GL::Shader *m_singleColorShader; // 单色着色器
};

#endif /* my_render_h */
