#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal; // normal 将被直接传入 fragment shader
out vec3 FragPos; // 当前 fragment 对应在场景中的位置

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{    
    gl_Position = projection * view * model * vec4(position, 1.0f);
    FragPos = vec3(model * vec4(position, 1.0f));
    // Normal = normal; // 这个无法动态更新
    Normal = mat3(transpose(inverse(model))) * normal;  // 可以实时动态更新
}