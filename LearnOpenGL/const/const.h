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
    const int KEY_STATS_LEN = 1024; //按键状态
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

    // 纹理矩形
    // 矩形的顶点、索引定义
    const float verticesForRectWithTex[] = {
            //位置               颜色               纹理坐标
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,//左上角
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,// 右下角
        0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f//右上角
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
    
    // 定义顶点颜色
    // 一个三角形的顶点定义
    const float verteciesWithColor[] = {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// 左下角
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// 右下角
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f// 顶角
    };

    // 定义一个立方体的顶点
    const float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
}

#endif /* const_h */
