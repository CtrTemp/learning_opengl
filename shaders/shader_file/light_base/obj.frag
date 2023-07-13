#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;

// uniform vec3 objectColor;
uniform vec3 lightColor;
// 光源位置 （这里只是点光源？）
uniform vec3 lightPos;
// 观察者方向
uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material; // 材质

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

void main() {   

    // ambient
    // vec3 ambient = lightColor * material.ambient;
    vec3 ambient = light.ambient * material.ambient;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = lightColor * (diff * material.diffuse);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = lightColor * (spec * material.specular);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);
}