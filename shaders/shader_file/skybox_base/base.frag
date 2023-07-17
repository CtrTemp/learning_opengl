// #version 330 core

// in vec2 TexCoord;
// out vec4 FragColor;

// // 从CPU端读入的纹理
// uniform sampler2D box_texture;

// void main() {
//     FragColor = texture(box_texture, TexCoord);
// }

// environment mapping
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

// 从CPU端读入的纹理
uniform vec3 cameraPos;
uniform samplerCube cubemapTexture;

void main() {
    // // pure reflect (mental)
    // vec3 I = normalize(Position - cameraPos);
    // vec3 R = reflect(I, normalize(Normal));
    // FragColor = vec4(texture(cubemapTexture, R).rgb, 1.0);

    // pure refrect (glass)
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(Position - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);
    FragColor = vec4(texture(cubemapTexture, R).rgb, 1.0);
}