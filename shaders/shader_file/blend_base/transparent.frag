#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

// 从CPU端读入的纹理
uniform sampler2D box_texture;

void main() {
    FragColor = texture(box_texture, TexCoord);
}