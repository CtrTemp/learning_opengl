#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D floor_texture;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material; // 材质

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
    vec3 lightDir = normalize(-light.direction);
    // 计算漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);
    // 计算镜面反射强度
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并各个光照分量
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.TexCoords));
    return (ambient + diffuse + specular);
}

void main() {
    // bool blinn = false;
    // // blinn = true;
    // vec3 color = texture(floor_texture, fs_in.TexCoords).rgb;
    // // ambient
    // vec3 ambient = 0.05 * color;
    // // diffuse
    // vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    // vec3 normal = normalize(fs_in.Normal);
    // float diff = max(dot(lightDir, normal), 0.0);
    // vec3 diffuse = diff * color;
    // // specular
    // vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = 0.0;
    // if(blinn) {
    //     vec3 halfwayDir = normalize(lightDir + viewDir);
    //     spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    // } else {
    //     vec3 reflectDir = reflect(-lightDir, normal);
    //     spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    // }
    // vec3 specular = vec3(0.3) * spec; // assuming bright white light color
    // FragColor = vec4(ambient + diffuse + specular, 1.0);

    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    

    FragColor = vec4(result, 1.0);

}