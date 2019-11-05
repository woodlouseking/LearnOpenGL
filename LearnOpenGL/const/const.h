//
//  const.h
//  LearnOpenGL
//
//  Created by www on 2019/11/2.
//  Copyright © 2019年 woodlouse. All rights reserved.
//

#ifndef const_h
#define const_h

namespace LEARN_OPEN_GL {
    const int LOG_INFO_LEN = 1024;

    const int SCR_WIDTH = 800;
    const int SCR_HEIGHT = 600;
    const char SCR_TLE[] = "LearnOpenGL";
    
    
    // 一个三角形的顶点定义
    const float vertecies[] = {
        -0.5f, -0.5f, 0.0f, // 左下角
         0.5f, -0.5f, 0.0f, // 右下角
         0.0f,  0.5f, 0.0f  // 顶角
    };
    
    // 相邻三角形的顶点定义
    const float neighborVertecies[] = {
        -0.9f, -0.5f, 0.0f, // 左下角
         0.0f, -0.5f, 0.0f, // 右下角
        -0.5f,  0.5f, 0.0f,  // 顶角
        
        0.9f, -0.5f, 0.0f, // 左下角
        0.0f, -0.5f, 0.0f, // 右下角
        0.5f,  0.5f, 0.0f  // 顶角
    };
    
    // 矩形的顶点、索引定义
    const float verticesForRect[] = {
        //绘制一个矩形
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f, //左上角
        0.5f, -0.5f, 0.0f, // 右下角
        0.5f, 0.5f, 0.0f //右上角
    };
    const unsigned int indices[] = {
        0, 1, 2, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    //使用不同VAO VBO绘制的两个三角形定义
    const float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    const float secondTriangle[] = {
         0.9f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };

    static const char *vertexShaderSource = "#version 330 core\n"
                "layout (location=0) in vec3 aPos;\n"
                "void main(){\n"
                "       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                "}\n\0";
    
    static const char *fragmentShaderSource = "#version 330 core\n"
                "out vec4 fragColor;\n"
                "void main(){\n"
                "   fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                "}\n\0";
    
    // 定义顶点颜色
    // 一个三角形的顶点定义
    const float verteciesWithColor[] = {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// 左下角
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// 右下角
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f// 顶角
    };
    
    //着色器
    static const char* vertexWithColorShaderSource = "#version 330 core\n"
    "layout (location=0) in vec3 aPos;\n"
    "layout (location=1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos, 1.0f);\n"
    "   ourColor = aColor;\n"
    "}\0";

    static const char* framentWithColorShaderSource = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "in vec3 ourColor;\n"
    "void main(){\n"
    "   fragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";
    
}

#endif /* const_h */
