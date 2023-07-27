#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
    /*
        lightSpaceMatrix 是从平行光源看向场景的投影变换矩阵乘积，相当于 projection * view 
    不仅仅在当前生成这张深度图有用，后面在绘制真实场景时还要用到，所以为了方便这里将乘积统一传入。
    */  
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}