
/*
    这个小节告诉我们 geometry shader 不但可以像上一个小节那样增添顶点，也可以像这个小节一样
对顶点的属性进行编辑。使其进行坐标变换（这里是平移操作）。
*/ 

#version 330 core
// 输入是 triangles 注意了这里并不是点数据！！
/*
    上一小节的困惑也就解决了，这里说明从 vertex shader 中读取是每三个顶点为一组读入，下面的
gs_in数组长度也就变成了3。且这三个顶点的顺序也决定了三角形三个顶点的绘制顺序（也就是正反面）。
*/ 
layout(triangles) in;
// 输出是三角形，且最多三个三角形
layout(triangle_strip, max_vertices = 3) out;

// 输出由上一小节的颜色属性变成了纹理坐标
in VS_OUT {
    vec2 texCoords;
} gs_in[]; // 由于读入的方式是 triangles 所以这里自然是一个长度为3的数组

out vec2 TexCoords; // 直接被赋值即可

uniform float time;

vec4 explode(vec4 position, vec3 normal) {
    float magnitude = 6.0; // 最大平移距离
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; // 顶点平移方向*距离
    // 向着面法向量的方向平移一段距离
    return position + vec4(direction, 0.0);
}

vec3 GetNormal() {
    // 根据三角形的两个边的叉承获取三角形的法向量！注意这里不能使用现有顶点向量的插值了。
    // 这里我们要的是面向量
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {
    vec3 normal = GetNormal();
    // 这里对 vertex shader 修改后的内置变量进行修改，将其变成 explode 之后的位置，传入到后面的光栅化阶段
    gl_Position = explode(gl_in[0].gl_Position, normal);
    TexCoords = gs_in[0].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normal);
    TexCoords = gs_in[1].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normal);
    TexCoords = gs_in[2].texCoords;
    EmitVertex();
    EndPrimitive();
}