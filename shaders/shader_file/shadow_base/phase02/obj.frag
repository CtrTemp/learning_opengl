#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

// // 版本01：最基本的简单版本
// float ShadowCalculation(vec4 fragPosLightSpace) {
//     // perform perspective divide
//     vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // 除以 w 代表归一化
//     // transform to [0,1] range
//     projCoords = projCoords * 0.5 + 0.5; // 从 [-1,1] 映射到 [0,1] 这是为了与 depthMap 中保持一致 
//     // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
//     // 从深度图中取得从光源看过去该点最小的深度值
//     float closestDepth = texture(shadowMap, projCoords.xy).r; 
//     // get depth of current fragment from light's perspective
//     // 在深度图中获取当前点从光源看过去实际的深度值
//     float currentDepth = projCoords.z;
    

//     float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;


//     return shadow;
// }

// // 版本02：解决阴影纹路失真的问题（就是在本该没有阴影的地方存在很多黑线，这个叫做阴影失真）
// /**
//     问题解释：
//     首先，projCoords可以看作是一个连续的值
//     那么 currentDepth 就是一个连续的值
//     但由于depthMap/shadowMap的分辨率是有限的，这导致：多个不同的 projCoords.xy 采样 shadowMap得到的可能是同一个值
//     于是 closestDepth 实际上是一个与 depthMap/shadowMap 的分辨率有关的离散值
//     那么 closestDepth 再与 currentDepth 进行比较时，就可能导致一个连续的 currentDepth 对应同一个 closestDepth进行比较
//     这就会使得比较的值有一部分可能是大于的，一部分是小于的，于是就有了本应没有阴影的区域变成一部分有阴影，一部分没有阴影的效果
// **/ 
// float ShadowCalculation(vec4 fragPosLightSpace) {
//     // perform perspective divide
//     vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // 除以 w 代表归一化
//     // transform to [0,1] range
//     projCoords = projCoords * 0.5 + 0.5;
//     float closestDepth = texture(shadowMap, projCoords.xy).r; // 从光源来看，当前点对应的最小深度值 
//     float currentDepth = projCoords.z; // 从相机来看，当前点实际深度值

//     // 通过添加一个简单的容错偏移来解决阴影失真
//     // float bias = 0.005;
//     // 偏移优化：当光线和当前平面的交角越大的时候，应该给i一个更大的偏移，反之小偏移
//     // 你可以画图试一试，确实如此，并且我们将最小最大偏移限制在[0.005, 0.05]之间
//     vec3 lightDir = normalize(lightPos - fs_in.FragPos);
//     float bias = max(0.05 * (1.0 - dot(fs_in.Normal, lightDir)), 0.005);
//     float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

//     // if(projCoords.z > 1.0)
//     //     shadow = 0.0;

//     return shadow;
// }

// // 版本03：
// /**
//     问题解释：悬浮偏移失真，仔细观察贴近地面的那个立方体的角落处，发现影子的位置有一定的偏差，就好像箱子浮空了一样。
// 如果你尝试将这个偏移硬编码成0.05将会发现偏移其实非常明显。它有一个比较有意思的称呼叫做 Peter Panning～ 其实就是
// 将“彼·潘”用作了动词，表示他会悬空的这一现象。
//     其实这种现象出现的根本原因就是你设置的bias偏移。
//     这里我们通过面剔除解决，使用物体的背面来计算 depth Map 可以解决大部分这方面的问题。
// **/ 
// float ShadowCalculation(vec4 fragPosLightSpace) {
//     // perform perspective divide
//     vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // 除以 w 代表归一化
//     // transform to [0,1] range
//     projCoords = projCoords * 0.5 + 0.5;
//     float closestDepth = texture(shadowMap, projCoords.xy).r; // 从光源来看，当前点对应的最小深度值 
//     float currentDepth = projCoords.z; // 从相机来看，当前点实际深度值
    
//     vec3 lightDir = normalize(lightPos - fs_in.FragPos);
//     float bias = max(0.05 * (1.0 - dot(fs_in.Normal, lightDir)), 0.005);
//     float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

//     // if(projCoords.z > 1.0)
//     //     shadow = 0.0;

//     return shadow;
// }

// // 版本04：
// /**
//     问题解释：光照有一个区域，超出该区域就成为了阴影；这个区域实际上代表着深度贴图的大小，这个贴图投影到了地板上。
// 发生这种情况的原因是我们之前将深度贴图的环绕方式设置成了GL_REPEAT。我们宁可让所有超出深度贴图的坐标的深度范围是1.0，
// 这样超出的坐标将永远不在阴影之中。我们可以储存一个边框颜色，然后把深度贴图的纹理环绕选项设置为GL_CLAMP_TO_BORDER
//     但这样也不足以解决问题：仍有一部分是黑暗区域。那里的坐标超出了光的正交视锥的远平面。你可以看到这片黑色区域总
// 是出现在光源视锥的极远处。你可以进行测试，将光锥的远平面设为很远，现象消失了。但这不会更本层面上解决问题，为了简单
// 解决这个问题，只需要在projCoords.z > 1.0的时候将shadow值直接设为0即可。
// **/ 
// float ShadowCalculation(vec4 fragPosLightSpace) {
//     // perform perspective divide
//     vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // 除以 w 代表归一化
//     // transform to [0,1] range
//     projCoords = projCoords * 0.5 + 0.5;
//     float closestDepth = texture(shadowMap, projCoords.xy).r; // 从光源来看，当前点对应的最小深度值 
//     float currentDepth = projCoords.z; // 从相机来看，当前点实际深度值

//     vec3 lightDir = normalize(lightPos - fs_in.FragPos);
//     float bias = max(0.05 * (1.0 - dot(fs_in.Normal, lightDir)), 0.005);
//     float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

//     if(projCoords.z > 1.0)
//         shadow = 0.0;

//     return shadow;
// }

// 版本05：
/**
    问题解释：由于深度图的分辨率有限，可知还是会有很多不同的坐标位置处的片段采样深度图后，得到相同的深度值，这就
使得阴影被渲染出的“分辨率”很低，尤其是在相对较远位置处，画出来的阴影就是一个个方格的拼凑，产生锯齿边缘。

    解决方案：PCF（percentage-closer filtering）
    核心思想是从深度贴图中多次采样，每一次采样的纹理坐标都稍有不同。每个独立的样本可能在也可能不再阴影中。所有的
次生结果接着结合在一起，进行平均化，我们就得到了柔和阴影。
**/ 
float ShadowCalculation(vec4 fragPosLightSpace) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // 除以 w 代表归一化
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r; // 从光源来看，当前点对应的最小深度值 
    float currentDepth = projCoords.z; // 从相机来看，当前点实际深度值
    // PCF
    float shadow = 0.0;
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(fs_in.Normal, lightDir)), 0.005);

    /*
        这个textureSize返回一个给定采样器纹理的0级mipmap的vec2类型的宽和高，这样 texelSize.x 和 texelSize.y 
    其实就是单位纹素在0～1空间的长度步进值。也就是下文中偏移采样的移动最小单元。
    */ 
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0); 
    // 深度图当前位置3*3的宫格内采样
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; // 采样点的深度
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;  // 累加shadow
        }
    }
    shadow /= 9.0; // 求平均得到软阴影（严格来讲其实这并不能算作是软阴影，，，软阴影的定义并非如此）

    if(projCoords.z > 1.0)
        shadow = 0.0;

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
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0);
}