#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
/*
    以下 CPU 端计算好的切线向量和副切线向量，通过顶点数据一并传入，其实二者只要一个就好
另一个可以和法向量N进行叉乘得出。
*/ 
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.TexCoords = aTexCoords;

    // 齐次变换，去除平移变换影响后的Model矩阵
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

    // 组装形成 TBN 矩阵
    mat3 TBN = transpose(mat3(T, B, N));

    // 以下的做法是将光源、摄像机、片段的位置通过 TBN 矩阵将其转换到了正确相对位置的世界空间坐标系下计算。
    // 注意，以上的 TBN 矩阵已经融合了 model 变换，且已经去除了平移带来的影响，只有旋转与缩放。
    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos = TBN * viewPos;
    vs_out.TangentFragPos = TBN * vs_out.FragPos;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}