
// 适用于可视化顶点法向量
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec3 Normal; // normal 将被直接传入 fragment shader
out vec3 FragPos; // 当前 fragment 对应在场景中的位置
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoords = texCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}