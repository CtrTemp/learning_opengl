#version 330 core

in vec4 FragPos;            // fragment 空间坐标

uniform vec3 lightPos;      // 光源空间坐标
uniform float far_plane;    // 光源位置看过去的远平面距离，后面用于将 depth 归一化

/*
    为什么这里没有用正交投影那种方式去默认填充深度图的深度？？？
    原因在于当前 fragment shader 的数据来自于 geometry shader ，猜测是由于指定了 Cube Map 的
face Layer，所以 fragment shader 没有办法默认 使用 gl_Fragcoord.z 进行默认填充。所以只能采取
当前这种计算方式对每个 Cube Map 面的 depth Map 进行显式填充。
*/ 
void main() {
    // 3D空间中光源到 fragment 的实际距离
    float lightDistance = length(FragPos.xyz - lightPos);

    // 将实际距离归一化
    lightDistance = lightDistance / far_plane;

    // 显式指定填充 depth Map （cube map中的某一个面，在上一个 geometry shader 阶段被指定）
    gl_FragDepth = lightDistance;
}