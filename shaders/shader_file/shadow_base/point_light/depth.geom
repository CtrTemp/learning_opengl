

/*
    !!! 特别注意：
    使用 geometry shader 为 Cube Map 6个面生成三角形副本并进行一次渲染得到结果的方式，并不一定
比渲染6次（提交6次 draw call）拥有更高的效率～
*/ 


#version 330 core
// 每三个顶点为一组传入 geometry shader
layout(triangles) in;
/*
    输出为 triangle，并且最多输出18个顶点，也就是6个三角形这里指的就是将一个三角形分别向
光源的6个方向进行投影变换。
*/ 
layout(triangle_strip, max_vertices = 18) out;

/*
    shadowMatrices 中的每一个值代表从光源看向 Cube 某个方向的变换阵 projection * view。
其中的 projection 矩阵均相同。只是 view 矩阵有变化。
*/ 
uniform mat4 shadowMatrices[6];

/*
    fragment 的空间坐标，根据顶点输入直接传递到 fragment shader 即可。
    值的注意的是，每次 EmitVertex() 操作都将会向 fragment shader 传入一个 FragPos。
这是一定的，因为绘制每个深度图都要所有的顶点坐标，即使在某些方向的深度图这些顶点会被抛弃掉。
所以每个顶点坐标都被重复了6次并传入了每个方向的绘制 shader。
*/ 
out vec4 FragPos;

void main() {
    for(int face = 0; face < 6; ++face) // 遍历 Cube Map 的每个面
    {
        /*
            gl_Layer ： 内建变量，仅当我们当前的 shader 使用并激活了 Cube Map 纹理时有效。
            如果不指定 gl_Layer，则所有顶点数据将会默认输入到管线的下一阶段。而指定 gl_Layer 后，
        shader program 会根据指定的 index 将图形绘制到 Cube Map 的指定面。
        */ 
        gl_Layer = face;
        for(int i = 0; i < 3; ++i)  // 遍历传入三角形的每个顶点
        {
            FragPos = gl_in[i].gl_Position; // 顶点空间坐标
            gl_Position = shadowMatrices[face] * FragPos; // 顶点从光源方向看过去的二维屏幕投影
            EmitVertex();
        }
        EndPrimitive();
    }
}