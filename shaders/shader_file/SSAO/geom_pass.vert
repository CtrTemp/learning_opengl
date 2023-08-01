#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform bool invertedNormals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 viewPos = view * model * vec4(aPos, 1.0);
    FragPos = viewPos.xyz;  // 还有就是这里为什么 FragPos 成了相机位置？？？
    TexCoords = aTexCoords;


    // mat3 normalMatrix = transpose(inverse(mat3(model))); // 去除 平移操作带来的影响
    mat3 normalMatrix = transpose(inverse(mat3(view * model))); // （这里为什么要引入 view 矩阵？）
    Normal = normalMatrix * (invertedNormals ? -aNormal : aNormal);
    
    gl_Position = projection * viewPos;
}