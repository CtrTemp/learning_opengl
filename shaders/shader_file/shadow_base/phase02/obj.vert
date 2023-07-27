#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix; // 这个是光源的变换阵 = light_projection * light_view

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));     // fragment 空间坐标
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;    // 防止不均等拉伸造成的法向量错误
    vs_out.TexCoords = aTexCoords;  // 纹理坐标直接传递即可
    // 将某个点应用光源变换阵，那么这个点的z坐标就是光源看过去该点的深度值（下面将转换到光源看过去的2D屏幕坐标）
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0); 
    // 相机位置看过去的2D空间坐标
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}