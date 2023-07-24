#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normalMatrix;

void main() {
    TexCoords = aTexCoords;
    WorldPos = vec3(model * vec4(aPos, 1.0));
    // 这里出了问题，为什么在CPU端计算这个矩阵并传入会出问题
    // 是不是我的 setMat3 函数出错了（果然，，，）
    Normal = normalMatrix * aNormal;
    Normal = aNormal;   
    // // 上下两种写法都可，上面是从 CPU 传入，下面则是在 GPU 中做计算（上面做法更优）
    // mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    // Normal = normalize(vec3(vec4(normalMatrix * aNormal, 0.0)));

    gl_Position = projection * view * vec4(WorldPos, 1.0);
}