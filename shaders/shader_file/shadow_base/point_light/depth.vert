#version 330 core
layout(location = 0) in vec3 aPos;

/*
    我们需要绘制6个面的深度图，也就是一个位置的光源要对某个顶点绘制6次得到6张深度图，
为了减小 draw call 的开销，这里我们仅仅将顶点做 model 变换得到其空间坐标，并在之后
借助 gemoetry shader 对每个顶点分别做6个方向的 view 和 projection 变换。
    最后将这些变换后的顶点统一传入 fragment shader ，从而只需一次 draw call 便
可以得到整个 Cube Map 所需要的 6 张深度图。
*/ 
uniform mat4 model;

void main() {
    gl_Position = model * vec4(aPos, 1.0);
}