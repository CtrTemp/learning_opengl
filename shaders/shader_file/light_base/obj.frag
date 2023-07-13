#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords; // 使用纹理贴图的形式表示漫反射表面

// uniform vec3 objectColor;
// uniform vec3 lightColor;
// 光源位置 （这里只是点光源？）
uniform vec3 lightPos;
// 观察者方向
uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    // vec3 specular;
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
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)); // 环境光也设为贴图值


    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // 贴图表示漫反射项

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = vec3(0.0f);
    // vec3 specular = light.specular * (spec * material.specular);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);

    //     // Ambient
    // vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  	
    // // Diffuse 
    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  
    
    // // Specular
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);  
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
        
    // color = vec4(ambient + diffuse + specular, 1.0f);  
}