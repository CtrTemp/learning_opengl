
#version 330 core
// 三角形传入（三个顶点为一组进行传入）
layout(triangles) in;
// 线段传出，一次传出6个顶点也就是仨线段，对应三个顶点的法向量
layout(line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[]; // 同样是三个顶点的数组，这次传入的参数是顶点法向量

const float MAGNITUDE = 0.2; // 法向量长度（本义译为大小）

// 为何需要一个 projection 矩阵？ 为何不需要 view 矩阵
/*
    看了前面的 vertex shader 你就明白了。因为这里还需要我们在3D坐标空间进行
运算，所以前面帮我们乘了 view 和 model，但唯独不能乘 projection 矩阵，这
需要我们在完成顶点法向量的生成后，再一并乘以 projection 才行。
    （注意当前的 shader 只是用来画法向量的，并非那个画 model 的 shader ）
*/ 
uniform mat4 projection;  

// 为某一个顶点生成其法向量线段
void GenerateLine(int index) {
    /*
        （看清楚这里的 gl_in 和 gs_in ）
        注意，gl_in是内置变量，用于获取以上layou-in关键字端中传入的数据
    gl_in[index].gl_Position 获取的是传入顶点的位置。
    */ 
    // 顶点位置（顶点法向量起始位置）
    gl_Position = projection * gl_in[index].gl_Position; 
    EmitVertex();
    // 顶点位置+法向量长度（法向量结束位置）
    gl_Position = projection * (gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE); // 
    EmitVertex();
    EndPrimitive();
}

void main() {
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}