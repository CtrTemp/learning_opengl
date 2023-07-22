
## 光栅化渲染管线做了什么？如何做的

以下仅对我之前感到困惑的几个管线中的主要阶段进行通俗的解析



# · 初始化阶段/应用阶段

    这部分主要是将要渲染的场景准备好，在CPU创建完毕后将所需的数据导入到GPU中。

    模型顶点数据、 Shader Program 等一般会一次性导入到GPU的纹理内存/常量内存中
    渲染状态相关的数据，如：材质、纹理数据也会在这一阶段以 Uniform Buffer 的形式导入到GPU中，这部分一般也是一次性导入的。
    渲染状态相关的数据，如：变换矩阵等数据同样通过 Uniform Buffer 导入到 GPU ，不同的是它们在渲染循环中可能会被实时更新。

# · Tessellation 和 Geometry Shader 暂时省略
    在 Vulkan 中他被放在 Vertex Shader 阶段之前，在 OpenGL 中他在 Vertex Shader 之前？？（这里不确定）

# · Vertex Shader 顶点着色器做了什么

    （可编程）

    输入是什么？
        模型顶点数据，包括但不限于每个顶点的：空间坐标、颜色、纹理坐标
    操作是什么？
        对于每个输入的顶点数据，都会执行一次 Vertex Shader 程序，将顶点坐标从 世界坐标系 变换到 屏幕空间坐标系。
    输出是什么？
        变换到屏幕空间坐标系下的顶点数据。
    
    隐含操作？

    改变了什么内置变量？
        gl_Position?

# · Rasterization 光栅化阶段做了什么

    （不可编程，不可配置？）

    注：本阶段不一定是紧接着 Vertex Shader 的下一阶段

    输入是什么？
        顶点或组成 primitives/triagnles 的顶点组。
    操作是什么？
        1、对于每个输入的顶点组，将其构成 primitives ，并确定这个 primitives 能够在屏幕空间上覆盖哪些像素。
        2、对于已经确定覆盖的像素，我们称其为一个片段，即 fragment 。根据当前 fragment 所在 primitives 的顶点，使用质心坐标系
        插值出该 fragment 的所有信息。
    输出是什么？
        fragment 数据包。注：由于 fragment 数据实际上是顶点数据插值得到的，所以它默认具有顶点数据中的所有数据项，且命名相同。
    
    隐含操作？

    改变了什么内置变量？
        深度值？且是非线性映射得到的深度值？

# · Fragment Shader 片段着色器做了什么

    （可编程）

    注：本阶段一般是 Rasterization 紧接着的下一阶段

    输入是什么？
        fragment 数据包。
    操作是什么？
        遍历每个 fragment ，结合从 CPU 导入的“渲染状态”，计算当前片段应有的颜色。
    输出是什么？
        片段颜色值。
    
    隐含操作？

    改变了什么内置变量？


# · Stencil test 模板测试

    模板测试真的是在深度测试之前执行的么？？？按照配置来看是可疑的。


# · Depth test 深度测试
    较为明确了：执行完 Fragment Shader 之后，当前片段的深度值可以通过 gl_FragCoord.z 来进行访问，并且使用该值与早先在深度
    缓冲区中的深度值进行比较，根据 glDepthFunc 函数设置的比较参数决定当前片段是否被保留（一般默认是深度值较小的被留下），如果
    被保留，即通过深度测试，则使用当前的 gl_FragCoord.z 更新深度缓冲区中 [gl_FragCoord.x, gl_FragCoord.y] 处的值。

    然而我的问题是：如果只要深度更小就通过测试，那岂不是仅有离我们更近的片段被保留了下来？这样的话，如何渲染半透明表面后面的物体呢？

    果然如此，当深度测试和颜色混合同时开启，并且渲染不透明物体的时候，会发生一定的问题，解决的方式是：对于场景中的物体，优先绘制
    不透明的，且对于不透明物体内部的绘制，要以当前视角为准，从远及近进行绘制。


# · Color Blending 颜色混合阶段做了什么？

    （不可变成，可配置？）

    注：本阶段一般是 Fragment Shader 紧接着的下一阶段

    输入是什么？
        片段颜色值以及对应的深度信息、透明度信息。
    操作是什么？
        遍历每个 fragment 渲染结果 ，结合对应的深度、透明度信息，计算当前屏幕坐标位置处的像素颜色。
    输出是什么？
        像素颜色值（也就是最终渲染结果）

    隐含操作？

    改变了什么内置变量？





