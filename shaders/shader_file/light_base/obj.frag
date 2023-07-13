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
    float shininess;
};
uniform Material material; // 材质

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff; // spotlight 参数（聚光灯光源/束状光源）光源打开的半角
    float outerCutOff; // 聚光灯平滑边缘
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // 以下是点光源参数
    float constant; // 光线衰减常数项
    float linear;   // 光线衰减二次项
    float quadratic;// 光线衰减三次项
};
uniform Light light;

void main() {

    // /********************************* 平行光源效果 *********************************/ 
    // // 平行光源是没有衰减的，无限远处的光照
    // // ambient
    // vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)); // 环境光也设为贴图值

    // // diffuse 
    // vec3 norm = normalize(Normal);
    // // vec3 lightDir = normalize(lightPos - FragPos);
    // vec3 lightDir = normalize(-light.direction); // 现在我们使用平行光，不再需要一个特定的光源物体
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // 贴图表示漫反射项

    // // specular
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // // vec3 specular = vec3(0.0f);
    // // vec3 specular = light.specular * (spec * material.specular);
    // vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // vec3 result = ambient + diffuse + specular;
    // color = vec4(result, 1.0);

    // /********************************* 点光源效果 *********************************/ 
    // // ambient
    // vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)); // 环境光也设为贴图值

    // // diffuse 
    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(lightPos - FragPos);
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // 贴图表示漫反射项

    // // specular
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // // 计算关于点光源的衰减 （但问题是这样不会一同影响平行光源么？～）
    // // 显然是受到了影响的，，，
    // float distance = length(lightPos - FragPos);
    // float attenuation = 1.0 / (light.constant + light.linear * distance +
    //     light.quadratic * (distance * distance));

    // ambient *= attenuation;
    // diffuse *= attenuation;
    // specular *= attenuation;

    // vec3 result = ambient + diffuse + specular;
    // color = vec4(result, 1.0);

    /********************************* 聚光灯效果 *********************************/ 
    vec3 lightDir = normalize(light.position - FragPos);

    float theta = dot(lightDir, normalize(-light.direction));

    float epsilon = light.cutOff - light.outerCutOff; // 平滑过渡边缘宽度
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 

        // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)); // 环境光也设为贴图值

        // diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // 贴图表示漫反射项

        // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

        // 计算关于点光源的衰减 （但问题是这样不会一同影响平行光源么？～）
        // 显然是受到了影响的，，，
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
        light.quadratic * (distance * distance));
        // 距离衰减
    diffuse *= attenuation;
    specular *= attenuation;
        // 平滑边缘过渡
    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);

}