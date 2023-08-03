#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform bool reverse_normals;

void main() {
    // 传递空间坐标
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    // 外部作为“房间”的Cube，我们将其内部的面视为“外表面”
    if(reverse_normals)
        vs_out.Normal = transpose(inverse(mat3(model))) * (-1.0 * aNormal);
    else
        vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    // 直接传递纹理坐标
    vs_out.TexCoords = aTexCoords; 
    // 投影到摄像机看过去的2D屏幕空间
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
