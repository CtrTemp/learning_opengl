#version 330 core

// 从 Vertex Shader 读入的数据
in vec3 ourColorFromVert;
in vec2 TexCoord;
// 使用out关键字来说明这是 fragment shader 最终输出的变量，代表像素值
out vec4 FragColor;

/*
    uniform buffer 也就是从CPU端传到GPU端 shader 的变量，它有些不同：它是全局的
这意味着：
    1、uniform
变量在每个shader中都是独一无二的，可以被着色器函数（也就是下面的main函数）
    2、无论将uniform buffer设置为什么值， uniform
buffer都会一直保有这个数据直到被更新 或者程序结束。

    如果你声明了一个uniform
buffer却从来没在GLSL中用过，则在编译阶段它就会被去除。
*/

// 声明一个从CPU传来的全局变量
// 注意这里只是声明，如果CPU不传，则它就是空的
uniform vec4 ourColorFromCPU;

// 从CPU端读入的纹理
uniform sampler2D ourTextureFromCPU;
uniform sampler2D ourTextureFromCPU_ano;

// 这里我们没有进行任何计算，直接将其输出的颜色写死。
// 因为没有计算，所以也不需要输入，可以看到这里没有 in 关键字变量
void main() {
  // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // 直接给定一个确定的颜色值
  // FragColor = ourColorFromCPU; // 将颜色输出为从CPU端读入的数据
  // FragColor = vec4(ourColorFromVert, 1.0f); // 将颜色输出为从 Vertex Shader
  // 后级读入的数据
  // 从 texture 中读入数据，以插值的方式计算像素值
  // texture 函数详解？做了什么？插值的方式是什么？
  // FragColor = texture(ourTextureFromCPU, TexCoord);
  //   // 可以进行颜色混叠
    // FragColor = texture(ourTextureFromCPU, TexCoord) * ourColorFromCPU;
//   FragColor =
//       texture(ourTextureFromCPU, TexCoord) * vec4(ourColorFromVert, 1.0f);
  // 多纹理混叠

    FragColor = mix(texture(ourTextureFromCPU, TexCoord),
                    texture(ourTextureFromCPU_ano, TexCoord), 0.5);
}