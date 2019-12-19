#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

//材质属性定义
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    
    float shininess;
};
uniform Material material;

struct Light
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    // Ambient
    vec3 ambient = light.diffuse * vec3(texture(material.diffuse, TexCoords));
    
    //Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 speclular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    //Attenuation 衰减
    float distance = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear*distance + light.quadratic*(distance*distance));
    
    vec3 result = ambient*attenuation + diffuse*attenuation + speclular*attenuation;
    color = vec4(result, 1.0f);
}
