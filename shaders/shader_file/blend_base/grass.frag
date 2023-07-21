#version 330 core

in vec2 TexCoord;
out vec4 FragColor;


// uniform sampler2D grass_texture;
uniform sampler2D transparent_texture;

void main()
{             
    vec4 texColor = texture(transparent_texture, TexCoord);

    // alpha 不透明度低于0.1的就会被丢弃，相当于裁掉了贴图中 grass 外多余的部分
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}