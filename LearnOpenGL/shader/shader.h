//
//  shader.hpp
//  LearnOpenGL
//
//  Created by www on 2019/11/6.
//  Copyright © 2019年 woodlouse. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <stdio.h>
#include <string>

namespace LEARN_OPEN_GL {
    class Shader {
    public:
        unsigned int ID;
        Shader(const char *vertexPath, const char *fragmentPath);
        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, bool value) const;
        void setFloat(const std::string &name, float value) const;
    private:
        void checkCompileErrors(unsigned int shader, std::string type);
    };
}

#endif /* shader_hpp */