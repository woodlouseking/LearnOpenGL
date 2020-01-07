//
//  Mesh.cpp
//  LearnOpenGL
//
//  Created by www on 2020/1/3.
//  Copyright © 2020年 woodlouse. All rights reserved.
//

#include "Mesh.hpp"
#include <sstream>

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    
    this->setupMesh();
}

void Mesh::Draw(LEARN_OPEN_GL::Shader &shader)
{
    // Bind appropriate textures
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    
    for(GLuint i=0; i<this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
        // Retrieve texture number
        stringstream ss;
        string number;
        string name = this->textures[i].type;
        if (name == "texture_diffuse") {
            ss << diffuseNr++;
        } else if (name == "texture_specular") {
            ss << specularNr++;
        }
        number = ss.str();
        // Now set the sampler to the correct texture unit
        glUniform1f(glGetUniformLocation(shader.ID, (name+number).c_str()), i);
        // And finally bind the texture
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
    
    //Also set each mesh's shininess property to a default value
    glUniform1f(glGetUniformLocation(shader.ID, "material.shiness"), 16.0f);
    
    //Draw Mesh
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    // Always good practice to set everything back to defaults once configured.
    for(GLuint i=0; i<this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Mesh::setupMesh()
{
    // Create buffers/arrays
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    
    glBindVertexArray(this->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 this->vertices.size()*sizeof(Vertex),
                 &this->vertices[0],
                 GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 this->indices.size()*sizeof(GLuint),
                 &this->indices[0],
                 GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    
    glBindVertexArray(0);
}


