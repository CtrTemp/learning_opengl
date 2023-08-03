// #version 330 core
// out vec4 FragColor;

// in VS_OUT {
//     vec3 FragPos;
//     vec3 Normal;
//     vec2 TexCoords;
// } fs_in;

// uniform sampler2D diffuseTexture;
// uniform samplerCube depthMap;

// uniform vec3 lightPos;
// uniform vec3 viewPos;

// uniform float far_plane;
// uniform bool shadows;

// float ShadowCalculation(vec3 fragPos)
// {
//     // get vector between fragment position and light position
//     vec3 fragToLight = fragPos - lightPos;
//     // ise the fragment to light vector to sample from the depth map    
//     float closestDepth = texture(depthMap, fragToLight).r;
//     // it is currently in linear range between [0,1], let's re-transform it back to original depth value
//     closestDepth *= far_plane;
//     // now get current linear depth as the length between the fragment and light position
//     float currentDepth = length(fragToLight);
//     // test for shadows
//     float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range
//     float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;        
//     // display closestDepth as debug (to visualize depth cubemap)
//     // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    

//     return shadow;
// }

// void main()
// {           
//     vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
//     vec3 normal = normalize(fs_in.Normal);
//     vec3 lightColor = vec3(0.3);
//     // ambient
//     vec3 ambient = 0.3 * lightColor;
//     // diffuse
//     vec3 lightDir = normalize(lightPos - fs_in.FragPos);
//     float diff = max(dot(lightDir, normal), 0.0);
//     vec3 diffuse = diff * lightColor;
//     // specular
//     vec3 viewDir = normalize(viewPos - fs_in.FragPos);
//     vec3 reflectDir = reflect(-lightDir, normal);
//     float spec = 0.0;
//     vec3 halfwayDir = normalize(lightDir + viewDir);  
//     spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
//     vec3 specular = spec * lightColor;    
//     // calculate shadow
//     float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;                      
//     vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

//     FragColor = vec4(lighting, 1.0);
// }
#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseTexture;   // 木地板纹理
uniform samplerCube depthMap;       // 从光源看过去，计算好的深度图

uniform vec3 lightPos;  // 光源位置
uniform vec3 viewPos;   // 相机位置

// 远平面位置（从光源位置看过去使用的远平面距离，用于从归一化的 depth map 中解码实际深度）
uniform float far_plane;
uniform bool shadows;       // 是否开启阴影效果（默认开启了）

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[](vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1), vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1), vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0), vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1), vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1));

float ShadowCalculation(vec3 fragPos) {
    // 从光源位置指向片段位置的向量
    vec3 fragToLight = fragPos - lightPos;
    // use the fragment to light vector to sample from the depth map    
    // float closestDepth = texture(depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    // closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    // 计算得到当前 fragment 到光源的距离
    float currentDepth = length(fragToLight);
    // 以下是 PCF(percentage closer filter) 计算
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);

    /*
        采样球半径
        这次我们以 fragment 位置为球心，围绕它进行采样，看深度是否大于光源看过去的最小深度（depth map中的值）
    diskRadius表示采样半径单位，以下的设置可以让观察者距离越远时采样半径越大，阴影也就越“软”。
        设置这个长度为20的矩阵减小了采样的复杂度，让我们只对那些较为分散，相互之间距离较远的样本点进行采样。可以
    在提升效率的同时保证“平滑阴影”的效果。
    */ 
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i) {
        // 归一化实际深度
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // 将归一化深度映射到实际深度
        if(currentDepth - bias > closestDepth) // 比较后确定该采样点是否在 shadow 下
            shadow += 1.0;
    }
    shadow /= float(samples); // 均值平滑阴影  

    return shadow;
}

void main() {
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * lightColor;
    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0);
}
