//
//  Model.hpp
//  LearnOpenGL
//
//  Created by www on 2020/1/7.
//  Copyright © 2020年 woodlouse. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include "shader.h"
#include <vector>
#include <string>
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model(string path);
    void Draw(LEARN_OPEN_GL::Shader shader);
    
private:
    vector<Mesh> meshes;
    string directory;
    
private:
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    GLint TextureFromFile(const char* path, string directory);
};

#endif /* Model_hpp */
