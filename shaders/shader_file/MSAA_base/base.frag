#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

void main() {

    FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    // FragColor = texture(texture_diffuse1, TexCoords);
}