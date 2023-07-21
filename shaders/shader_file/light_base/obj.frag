#version 330 core
out vec4 color;

// 输入的是经过 Rasterization 阶段插值后得到的每个 fragment 的数据包

in vec3 Normal;     // fragment 对应的法向量
in vec3 FragPos;    // fragment 对应的空间位置
in vec2 TexCoords;  // fragment 对应的纹理坐标

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

// 这次我们将光打散成不同类型的光源

// 平行光源
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

// 平行光计算函数
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    // 对平行光方向取反，这是由于我们要计算它和法向量的夹角，它应该是一个锐角
    vec3 lightDir = normalize(-light.direction); 

    // 计算漫反射强度
    /*
        diff 是一个衰减项，可见当光照方向和当前面的法向量夹角越小这个系数越大，这从侧面说明了直射的平行光
    将会使得平面吸收更多的光照，对于漫反射光也就更有可能辐射出个更多的光，这是合理的。
    */ 
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // 计算镜面反射项强度
    /*
        reflectDir 是反射光方向，从片段位置指向放射光方向
        spec 是反射光光强衰减项，其中的点乘可以直观表现：当反射方向与观测方向更加接近时，该值越大。后面的
    material.shininess项越大表示高光效果越明显，同时高光覆盖区域越小。
        注意这里我们还没有引入半程向量，所以点乘的结果可能会因为夹角为钝角而变成负数，所以使用max函数限制
    其最小为0。在这里可以看出，我们仍使用的是 Phong 光照模型。
    */ 
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // 计算环境光项强度 
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // 合并各个光照分量
    return (ambient + diffuse + specular);
}

// 点光源
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4  // 当前场景总共定义四个点光源
uniform PointLight pointLights[NR_POINT_LIGHTS];

// 点光源计算函数
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // 计算漫反射项强度（与平行光源计算一致）
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // 计算镜面反射项强度（与平行光源计算一致）
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // 计算环境光项强度（与平行光源计算一致）
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

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

// 聚光灯光源
struct SpotLight {
    vec3 position;
    vec3 direction;
    // 聚光灯光束内径半角（在此光椎内有统一的最大光强）
    float cutOff;      
    // 聚光灯光束外径半角（在此光椎与内径光椎之间有一段柔和过渡，此光椎外完全不受该光源影响）
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotLight;
// 聚光灯光源计算函数.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // 计算漫反射项强度（与平行光源计算一致）
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // 计算镜面反射项强度（与平行光源计算一致）
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // 计算环境光项强度（与平行光源计算一致）
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // 聚光效果衰减项计算
    /*
        theta 是当前片段位置与聚光灯光源连线 和 聚光灯方向夹角 的余弦值，用它可以判断当前片段是否处于聚光灯光源的光椎内
        epsilon 是光椎内经和外径过渡段柔光区域的角度
        intensity 表示针对聚光灯光源的衰减项，可见使用clamp函数，即当前角度超过外径则取得minVal，内经以内会使得 theta
    与 light.outerCutOff 的插值大于 epsilon ，于是取得 maxVal 。二者之间就是一个线性的柔和过渡区。
    */ 
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // 计算距离衰减（与点光源计算一致）
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    // 衰减项纳入考虑，并合并总光源强度
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

float LinearizeDepth(float depth) {
    float near = 0.1;
    float far = 100.0;
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * near) / (far + near - z * (far - near));
}

void main() {

    // properties
    // norm 是当前片段的空间法向量
    vec3 norm = normalize(Normal);
    // viewDir 是观察方向，从当前片段的空间坐标指向摄像机坐标
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    } 
    // phase 3: Spot light
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    color = vec4(result, 1.0);

    // // gl_FragCoord 是内置变量，说明当前片段的位置信息
    // // 直接这样输出可以看到所有的方块无论远近基本上都是白的，只有在离得很近的时候才变为黑灰
    // // 这说明了内置的深度测试是非线性的，而且在距离很近的时候是曲率较大的，保证了在近处具有更高的深度测试精度
    // color = vec4(vec3(gl_FragCoord.z), 1.0);

    // // 以下我们可以将深度测试还原为线性，再来看一下
    // float depth = LinearizeDepth(gl_FragCoord.z);
    // color = vec4(vec3(depth), 1.0);

}