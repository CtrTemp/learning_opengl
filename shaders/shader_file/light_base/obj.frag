#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
// 光源位置 （这里只是点光源？）
uniform vec3 lightPos;
// 观察者方向
uniform vec3 viewPos;

void main()
{
    float ambientStrength = 0.15f;
    vec3 ambient = ambientStrength * lightColor;

    // 光照方向
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // 漫反射光
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 镜面反射光
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128); // 通过调节最后一个参数来确定高光项的表现力
    vec3 specular = specularStrength * spec * lightColor;   

    // 最终合成结果
    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0f);
}