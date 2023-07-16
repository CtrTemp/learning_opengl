#version 330 core

in vec2 TexCoord;
out vec4 FragColor;


// uniform sampler2D grass_texture;
uniform sampler2D transparent_texture;

void main()
{             
    vec4 texColor = texture(transparent_texture, TexCoord);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}