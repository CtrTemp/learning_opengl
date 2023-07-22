// single color house
// #version 330 core
// layout (points) in;
// layout (triangle_strip, max_vertices = 5) out;

// void build_house(vec4 position)
// {    
//     gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:bottom-left
//     EmitVertex();   
//     gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:bottom-right
//     EmitVertex();
//     gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:top-left
//     EmitVertex();
//     gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:top-right
//     EmitVertex();
//     gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:top
//     EmitVertex();
//     EndPrimitive();
// }

// void main() {    
//     build_house(gl_in[0].gl_Position);
// }  

// multi-color house

#version 330 core
// 声明 geometry shader 的输入的图元类型是点（但还可能是其他的类型么？）
layout(points) in; 
// 声明 geometry shader 的输出的图元类型是三角形
// max_vertices 指定最多输出5个顶点，多出来的将被抛弃掉
/*
    但这里传入到下个流程中的点的链接顺序是怎样被确定的呢？我尝试了面剔除
发现面都是正面，这是正确的，但顶点的顺序是如何确定的？
    这里又没有给出顶点的index，那么这个五边形是如何拆成三个三角形的，这让人
有点感觉奇怪。
*/ 
layout(triangle_strip, max_vertices = 5) out;

// 输入是上一个 vertex shader 阶段传过来的顶点数据，且只有一个颜色值
// 这里我们不需要知道她的位置坐标
in VS_OUT {
    vec3 color;
} gs_in[]; // 接受一个数组，但其实我们每次只传了一个顶点过来
// （这里思考如何每次传多个顶点过来呢？）

out vec3 fColor;

/*
    geometry shader 接收来自 vertex shader 的数据，将顶点进行扩充，再以另外一种形式
将顶点数据交付给后面的光栅化阶段。
    这里指定了顺序，但如何连接的却没有说明。五边形如何拆分为三个三角形的？
*/ 
void build_house(vec4 position) {
    fColor = gs_in[0].color; // gs_in[0] since there's only one input vertex
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:bottom-left   
    EmitVertex(); // 为当前的 primitive 添加一个顶点进行组装
    gl_Position = position + vec4(0.2, -0.2, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.2, 0.2, 0.0, 0.0);    // 3:top-left
    EmitVertex();
    gl_Position = position + vec4(0.2, 0.2, 0.0, 0.0);    // 4:top-right
    // EmitVertex(); // 可以尝试少一个 veretex
    gl_Position = position + vec4(0.0, 0.4, 0.0, 0.0);    // 5:top
    fColor = vec3(1.0, 1.0, 1.0); // 加上这个相当于给最后一个顶点赋予了一个硬编码颜色
    EmitVertex();
    EndPrimitive(); // 顶点添加完毕，将 primitive 直接传递给下一个阶段
}

void main() {
    build_house(gl_in[0].gl_Position);
}