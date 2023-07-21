#version 330 core
// 顶点数据包
layout (location = 0) in vec3 position;     // 空间坐标
layout (location = 1) in vec3 normal;       // 空间法向量
layout (location = 2) in vec2 texCoords;    // 纹理坐标

out vec3 Normal;    // normal 将被直接传入 fragment shader
out vec3 FragPos;   // 片段位置
out vec2 TexCoords; // 输入的顶点纹理坐标直接输出到下一阶段

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{    
    /*
        为和我们需要片段位置？
        gl_Position 得到的是当前顶点从 3D 空间转换到屏幕空间后的坐标，然而对于一个光照场景，由于需要计算空间中的光
    与物体的相互作用，所以这时候我们还需要在 fragment shader 阶段保留片段的空间位置信息。
        由于只有 model 矩阵影响物体在 3D 空间中的位置，所以对于 FragPos 的计算只需要乘以 model 矩阵即可。
        注意虽然我们这里的命名是 FragPos ，但我们这里在 Vertex Shader 中实际操作的对象仍然是顶点坐标数据。这样命名
    是由于后面 rasterizaion 阶段的插值操作会自动将其插值为 fragment 对应的坐标。为了后面不产生误导，就这样命名了。
    */ 
    FragPos = vec3(model * vec4(position, 1.0));
    /*
        我们暂时不去考虑以下的计算式，只需要知道的是：它将解决非等比例缩放造成的法线不垂直于表面的失真问题。
    */ 
    Normal = mat3(transpose(inverse(model))) * normal;  
    TexCoords = texCoords; // 输入的顶点纹理坐标直接输出到下一阶段 
    
    // gl_Position 作为内置变量将直接传入 fragment shader
    gl_Position = projection * view * vec4(FragPos, 1.0);
}