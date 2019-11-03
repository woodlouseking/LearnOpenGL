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
    const float vertices[] = {
        -0.5f, -0.5f, 0.0f, // 左下角
        0.5f, -0.5f, 0.0f, // 右下角
        0.0f, 0.5f, 0.0f //顶角
    };
    const char *vertexShaderSource = "#version 330 core\n"
                "layout (location=0) in vec3 aPos;\n"
                "void main(){\n"
                "       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                "}\n\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                "out vec4 fragColor;\n"
                "void main(){\n"
                "   fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                "}\n\0";
}

#endif /* const_h */
