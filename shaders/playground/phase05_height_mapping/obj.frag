#version 330 core
out vec4 FragColor;

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

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    PointLight TangentLight;  // 切线空间中的光源位置
    vec3 TangentViewPos;    // 切线空间中的观察点位置
    vec3 TangentFragPos;    // 切线空间中的片段位置（通过光栅化插值得到）
} fs_in;

// 材质参数
struct Material {
    sampler2D diffuseMap;
    sampler2D normalMap;
    float shininess;
};

uniform Material material; // 材质

// 点光源计算函数
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

    vec3 lightDir = normalize(light.position - fs_in.TangentFragPos);

    vec3 color = vec3(texture(material.diffuseMap, fs_in.TexCoords));

    // 计算漫反射项强度（与平行光源计算一致）
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, fs_in.TexCoords));

    // 计算镜面光项强度
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir); // Blinn-Phong
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = vec3(0.2) * spec;

    // 计算环境光项强度
    vec3 ambient = fs_in.TangentLight.ambient * color;

    // 计算衰减（点光源新增）：离得越远光强衰减效果越明显
    float distance = length(light.position - fragPos); // 点光源与当前片段之间的距离
    // attenuation 表示衰减系数，以下分母的这部分其实就是一个多项式衰减项，用于模拟真实光线的能量衰减，目前只有0次～2次项
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // 最后将以上计算的值乘上衰减项并合并
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main() {           

    // 从法线贴图中获取当前 fragment 对应的法线方向
    vec3 normal = texture(material.normalMap, fs_in.TexCoords).rgb;
    // 将法线映射到-1～1空间后归一化，也就是在切线空间的法向量，这一步是为啥？没理解
    // 之前有提到过这种映射么?
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space

    // normal = vec3(0.0, 0.0, 1.0); // 加上这句取消法线贴图

    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);

    vec3 result = CalcPointLight(fs_in.TangentLight, normal, fs_in.FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}