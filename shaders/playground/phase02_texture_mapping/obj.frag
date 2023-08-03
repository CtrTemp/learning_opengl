#version 330 core
out vec4 color;

// uniform vec3 baseColor;
uniform sampler2D tex;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

// 对于光源的shader比较简单，无论光源实际上是什么颜色，我们这里都统一使用一个白色来指定光源颜色
void main() {
    vec3 tex_color = texture(tex, fs_in.TexCoords).rgb;

    color = vec4(tex_color, 1.0);
}