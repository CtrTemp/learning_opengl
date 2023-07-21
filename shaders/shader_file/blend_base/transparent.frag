#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

// 从CPU端读入的纹理
uniform sampler2D box_texture;

void main() {
    /*
        开启了 Color Blending 之后，当前颜色缓冲区中的颜色会默认与当前 fragment color 进行混合
    如果我们开启了深度测试，则仅当我们从远及近绘制透明物体时才会进行正确的颜色混合，否则先绘制近处的物体
    会导致远处的物体叠加部分被抛弃掉，这样就无法得到正确的渲染结果了
    */ 
    FragColor = texture(box_texture, TexCoord);
}