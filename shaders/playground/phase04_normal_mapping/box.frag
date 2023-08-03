#version 330 core
out vec4 color;


// 材质参数
struct Material {
    sampler2D diffuseMap;
    sampler2D specularMap;
    float shininess;
};

// 点光源参数
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

// 观察者方向
uniform vec3 viewPos;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform Material material; // 材质

uniform PointLight point_light;

// 点光源计算函数
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // 计算漫反射项强度（与平行光源计算一致）
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, fs_in.TexCoords));

    // 计算镜面反射项强度（与平行光源计算一致）
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specularMap, fs_in.TexCoords).rgb;

    // 计算环境光项强度（与平行光源计算一致）
    vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, fs_in.TexCoords));

    // 计算衰减（点光源新增）：离得越远光强衰减效果越明显
    float distance = length(light.position - fragPos); // 点光源与当前片段之间的距离
    // attenuation 表示衰减系数，以下分母的这部分其实就是一个多项式衰减项，用于模拟真实光线的能量衰减，目前只有0次～2次项
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // 最后将以上计算的值乘上衰减项并合并
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
    // return fragPos;
}

// 对于光源的shader比较简单，无论光源实际上是什么颜色，我们这里都统一使用一个白色来指定光源颜色
void main() {

    // norm 是当前片段的空间法向量
    vec3 norm = normalize(fs_in.Normal);
    // viewDir 是观察方向，从当前片段的空间坐标指向摄像机坐标
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    vec3 result = CalcPointLight(point_light, norm, fs_in.FragPos, viewDir); // 结合光照后的结果

    color = vec4(result, 1.0);
}