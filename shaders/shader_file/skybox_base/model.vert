
// // 开头总是要声明版本
// #version 330 core

// layout(location = 0) in vec3 position;
// layout(location = 1) in vec3 color;
// layout(location = 2) in vec2 textCoord;

// // MVP 变换阵
// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

// // 当前来看对于 color 和 textCoord 直接向下传入到 fragment shader 即可
// out vec2 TexCoord;

// void main() {
//     gl_Position = projection * view * model * vec4(position, 1.0);
//     TexCoord = textCoord;
// }



// environment mapping

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(Position, 1.0);
}  