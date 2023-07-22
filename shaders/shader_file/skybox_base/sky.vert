#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    gl_Position = projection * view * vec4(aPos, 1.0);
} 


// /*
//     使用这个方法可以让我们在渲染循环的最后对天空盒进行绘制
//     这个方法叫做“提前深度测试” Early-Z/Early Depth Testing
//     这样做的原由是：如果我们先渲染天空盒，那么屏幕中所有部分的 fragment 都会被绘制，
// 然而其他后绘制的物体必定遮挡天空盒，所以其实这部分被遮挡的天空盒的 fragment 是可以被
// 提前预知并取消绘制的，这样可以优化计算量。
// */ 
// #version 330 core
// layout (location = 0) in vec3 aPos;

// out vec3 TexCoords;

// uniform mat4 projection;
// uniform mat4 view;

// void main()
// {
//     TexCoords = aPos;
//     vec4 pos = projection * view * vec4(aPos, 1.0);
//     /*
//         （透视除法是在顶点着色器运行之后执行的）
//         通过这里将z分量设置成w进而达到 Early-Z 的效果，这是因为在透视除法阶段，gl_Position 的 xyz 分量
//     都会被除以 w ，于是这之后深度值为w/w一定会得到一个1.0f的值。而1.0f又对应着最大深度，所以对应的片段一定
//     会被抛弃掉。
//     */ 
//     gl_Position = pos.xyww; // 看好，这里不是xyzw，而是xyww！！！
// }  
