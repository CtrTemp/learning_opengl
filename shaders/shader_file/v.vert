
// 开头总是要声明版本
#version 330 core

// 接下来声明要输入以及输出的变量
/**
    注意我们能声明的顶点属性是有上限的，一般由硬件决定！
OpenGL确保至少有16个4分量的顶点属性可以使用。～这个最大
限度可以在CPU端打印输出，进行check。
    （不过以上的16个4分量在大部分情况下是绝对够用的）
*/

/*
    vertex shader 中关于顶点数据的输入这部分较为特殊。这是因为其顶点数据是从CPU
一次性导入的，所以可以将这部分数据视为一个整体的数据包（包含很多顶点），
    在CPU端通过指明VBO的stride，来确定每个顶点数据包的大小，并正确分割，将顶点数据包传输
到GPU的vertex shader端，也就是这里。我们用layout关键字表示这种被分割解析的数据。
    而vertex shader又要对每个数据包内部进行进一步解析，通过 loaction 字段来确定
数据包内部的各个属性（attribute）与数据包头位置的偏移（offset）。
*/
// 简单来说，layout表示它是由CPU统一传输，并分割而来的数据包
// 并使用 location 字段指明数据包各项属性的内部偏移量。
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

out vec3 ourColorFromVert;

// 最终是main函数，这个函数将被每一个并行单元执行一次
// 函数中将处理输入的变量，并将最终的计算结果赋值到输出变量

void main() {
  gl_Position = vec4(aPos, 1.0);
  ourColorFromVert = aCol;
}