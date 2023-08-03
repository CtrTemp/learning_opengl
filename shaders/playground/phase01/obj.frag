#version 330 core
out vec4 color;

uniform vec3 baseColor;

// 对于光源的shader比较简单，无论光源实际上是什么颜色，我们这里都统一使用一个白色来指定光源颜色
void main() {
    color = vec4(baseColor, 1.0);
}