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
    vec3 Normal;

    vec3 TangentLightPos;
    vec3 TangentViewPos;    // 切线空间中的观察点位置
    vec3 TangentFragPos;    // 切线空间中的片段位置（通过光栅化插值得到）
} fs_in;

// 材质参数
struct Material {
    sampler2D diffuseMap;
    sampler2D specularMap;
    sampler2D normalMap;
    sampler2D heightMap;
    float shininess;
};

uniform Material material; // 材质

uniform bool useNormalMap;
uniform bool useHeightMap;
uniform bool applyAmbientOcclusion;
uniform bool useAOMap;
uniform bool useMetallicMap;
uniform bool useRoughnessMap;

uniform vec3 viewPos;
uniform PointLight point_light;

uniform float heightScale;

// Height Map 计算最终 TexCoord
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir) { 
    // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * heightScale;
    vec2 deltaTexCoords = P / numLayers;

    // get initial values
    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = texture(material.heightMap, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue) {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(material.heightMap, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(material.heightMap, prevTexCoords).r - currentLayerDepth + layerDepth;

    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

// 点光源计算函数
vec3 CalcPointLight(PointLight light) {

    vec3 lightDir;
    vec3 viewDir;
    vec3 normal;
    vec2 finalTexCoord;

    if(useNormalMap) {
        lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
        viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
        if(useHeightMap) { // 仅当使能 NormalMap 时才允许使用 HeightMap
            finalTexCoord = ParallaxMapping(fs_in.TexCoords, viewDir);
            if(finalTexCoord.x > 1.0 || finalTexCoord.y > 1.0 || finalTexCoord.x < 0.0 || finalTexCoord.y < 0.0)
                discard;
        } else {
            finalTexCoord = fs_in.TexCoords;
        }
        normal = texture(material.normalMap, finalTexCoord).rgb;
        normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
    } else {
        lightDir = normalize(light.position - fs_in.FragPos);
        viewDir = normalize(viewPos - fs_in.FragPos);
        normal = normalize(fs_in.Normal);
        finalTexCoord = fs_in.TexCoords;
    }

    // 我们给过来的法线贴图是Direct-X坐标系下的，应用的是左手系，OpenGL用的是右手系
    // 所以每次我们都要对贴图进行上下旋转后再翻转，这解决了z和y轴，但x轴只能靠如下的翻转来处理
    normal.x = -normal.x;
        // finalTexCoord = fs_in.TexCoords;

    vec3 color = vec3(texture(material.diffuseMap, finalTexCoord));

    // 计算漫反射项强度（与平行光源计算一致）
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * color;

    // 计算环境光项强度
    vec3 ambient = point_light.ambient * color;

    // 计算镜面光项强度
    // vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir); // Blinn-Phong
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular;
    if(useMetallicMap) {
        specular = light.specular * spec * texture(material.specularMap, finalTexCoord).rgb;
    } else {
        specular = vec3(0.2) * spec;
    }

    // 计算衰减（点光源新增）：离得越远光强衰减效果越明显
    float distance = length(light.position - fs_in.FragPos); // 点光源与当前片段之间的距离
    // attenuation 表示衰减系数，以下分母的这部分其实就是一个多项式衰减项，用于模拟真实光线的能量衰减，目前只有0次～2次项
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // 最后将以上计算的值乘上衰减项并合并
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main() {

    vec3 result = CalcPointLight(point_light); // 结合光照后的结果

    FragColor = vec4(result, 1.0);

    // // offset texture coordinates with Parallax Mapping
    // vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    // vec2 texCoords = fs_in.TexCoords;

    // texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);
    // if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
    //     discard;

    // // obtain normal from normal map
    // vec3 normal = texture(material.normalMap, texCoords).rgb;
    // normal = normalize(normal * 2.0 - 1.0);   

    // // get diffuse color
    // vec3 color = texture(material.diffuseMap, texCoords).rgb;
    // // ambient
    // vec3 ambient = 0.1 * color;
    // // diffuse
    // vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    // float diff = max(dot(lightDir, normal), 0.0);
    // vec3 diffuse = diff * color;
    // // specular    
    // vec3 reflectDir = reflect(-lightDir, normal);
    // vec3 halfwayDir = normalize(lightDir + viewDir);
    // float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    // vec3 specular = vec3(0.2) * spec;
    // FragColor = vec4(ambient + diffuse + specular, 1.0);

}