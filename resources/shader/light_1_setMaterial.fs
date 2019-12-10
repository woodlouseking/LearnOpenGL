#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

//材质属性定义
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    // Ambient
    vec3 ambient = lightColor * material.ambient;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = lightColor * (diff * material.diffuse);
    
    //Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 speclular = lightColor * (spec * material.specular);
    
    vec3 result = ambient + diffuse + speclular;
    color = vec4(result, 1.0f);
}
