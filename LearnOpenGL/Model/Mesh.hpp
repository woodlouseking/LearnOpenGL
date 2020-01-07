//
//  Mesh.hpp
//  LearnOpenGL
//
//  Created by www on 2020/1/3.
//  Copyright © 2020年 woodlouse. All rights reserved.
//

#pragma onece

#ifndef Mesh_hpp
#define Mesh_hpp

#include <string>
#include <vector>
#include <GL/glew.h>
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "shader.h"

using namespace std;


struct Vertex {
    glm::vec3 Position; // 位置
    glm::vec3 Normal; // 法向量
    glm::vec2 TexCoords; // 纹理坐标
};

struct Texture {
    GLuint id;
    string type;
    string path;
};

class Mesh {
public:
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
    
    void Draw(LEARN_OPEN_GL::Shader &shader);
    
public:
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    
private:
    void setupMesh();
    
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    
};

#endif /* Mesh_hpp */
