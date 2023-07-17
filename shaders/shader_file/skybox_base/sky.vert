// #version 330 core
// layout (location = 0) in vec3 aPos;

// out vec3 TexCoords;

// uniform mat4 projection;
// uniform mat4 view;

// void main()
// {
//     TexCoords = aPos;
//     gl_Position = projection * view * vec4(aPos, 1.0);
// } 


// 思考：为什么上面那个不行？？？
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww; // 看好，这里不是xyzw，而是xyww！！！
}  
