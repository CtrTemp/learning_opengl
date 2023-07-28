#include "render_loop.h"

void multi_rotating_cube_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 定义 MVP 变换阵 中的 view 和 project 变换阵一般是不变的，可以预先定义并设置
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    // 箱子坐标与定义
    vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, scene.textures["transparent_texture"]);

    /****************************** 绘制箱子 ******************************/
    // 选定shader
    scene.shader["base_shader"].use();
    scene.shader["base_shader"].setMat4("view", view);
    scene.shader["base_shader"].setMat4("projection", projection);
    // texture 值
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["box_texture"]);

    glBindVertexArray(scene.VAO["base_vao"]); // 绑定 VAO
    for (unsigned int i = 0; i < cubePositions.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        // 静态 cube
        // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        // 动态 cube
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        scene.shader["base_shader"].setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_TRIANGLES, 12, 24);
    }
    glBindVertexArray(0); // 解绑 VAO

    /****************************** 绘制草丛 ******************************/

    // 选定shader
    scene.shader["grass_shader"].use();
    scene.shader["grass_shader"].setMat4("view", view);
    scene.shader["grass_shader"].setMat4("projection", projection);
    // texture 值
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["grass_texture"]);

    glBindVertexArray(scene.VAO["base_vao"]); // 绑定 VAO
    for (unsigned int i = 0; i < cubePositions.size() / 2; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        scene.shader["grass_shader"].setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 6, 6);
    }
    glBindVertexArray(0); // 解绑 VAO

    /****************************** 绘制半透明 ******************************/

    // 选定shader
    scene.shader["transparent_shader"].use();
    scene.shader["transparent_shader"].setMat4("view", view);
    scene.shader["transparent_shader"].setMat4("projection", projection);
    // texture 值
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["transparent_texture"]);

    glBindVertexArray(scene.VAO["base_vao"]); // 绑定 VAO
    for (unsigned int i = 5; i < cubePositions.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        scene.shader["transparent_shader"].setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0); // 解绑 VAO
}

void scene_light_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制（如果使能了模板缓冲，必须在绘制循环开始前将其清空）
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // 定义 MVP 变换阵
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    /******************************** 绘制物体 ********************************/

    // 先将 view 和 projection 两个矩阵导入 shader

    scene.shader["frame_shader"].use(); // 以下对 frame shader 进行配置
    scene.shader["frame_shader"].setMat4("view", view);
    scene.shader["frame_shader"].setMat4("projection", projection);

    scene.shader["obj_shader"].use(); // 以下对 obj shader 进行配置
    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);

    // 根摄像机一同移动的聚光灯光源
    scene.shader["obj_shader"].setVec3("spotLight.position", primary_cam.cameraPos);
    scene.shader["obj_shader"].setVec3("spotLight.direction", primary_cam.cameraFront);
    // 观察者位置（相机位置）
    scene.shader["obj_shader"].setVec3("viewPos", primary_cam.cameraPos);

    // 绘制多个物体对象
    std::vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    scene.shader["obj_shader"].use(); // 首先使用正常的 shader 对物体进行一次绘制

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["viking_texture"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["frame_texture"]);
    // 1、第一步，开启模板写入，并设置
    // 模板测试总是会通过，也就是无论如何以下的片段绘制都会被执行，并且被绘制的片段将会默认向模板缓冲区中写1
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    // 允许模板缓冲区写入，根据最开始创建场景时的设置，通过模板/深度测试的片段会向模板缓冲区的对应位置写1
    // 也就是执行完以下的绘制后，所有画CUBE的位置的模板值将被置为1,其他位置是0
    glStencilMask(0xFF);

    glBindVertexArray(scene.VAO["obj_vao"]); // 绑定VAO准备开始渲染物体
    for (int i = 0; i < cubePositions.size(); i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        // 动态 cube （静态CUBE直接注销这句即可）
        float angel = 20.0f * (i + 1);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angel), glm::vec3(0.5f, 1.0f, 0.0f));
        // // 旋转特定角度
        // model = glm::rotate(model, 1 * glm::radians(angel), glm::vec3(1.0f, 0.3f, 0.5f));
        scene.shader["obj_shader"].setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0); // 解绑 VAO
    // 绘制完之后，模板缓冲区已经被更新完毕了

    // == =============
    // 2、第二步，关闭模板写入和深度测试
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // GL_NOTEQUAL 表示当片段值与模板缓冲区中的值不相等的时候通过模板测试，并向模板中写1
    // glStencilMask(0x00);                 // 关闭模板写入 感觉这个根本没必要
    // glDisable(GL_DEPTH_TEST);            // 关闭深度测试 这个也没必要 （果然注释后没有什么差别）
    scene.shader["frame_shader"].use(); // 其次使用绘制边框的 shader 对物体进行第二次绘制
    float scale = 1.05f;

    // 以下绘制将会有如下的流程：
    /**
     * 1、将原来的CUBE扩大了一圈进行绘制；
     * 2、此时由于我们关闭了模板的写入，所以模板缓冲区不会被更新；
     * 3、当绘制时，进行模板测试，仅当不为1时才会通过模板测试进行绘制；
     * 4、也就是上一个在缩放之前的区域永远不会被绘制，仅不为1的区域也就是因为被放大多出来的那一圈边框会通过模板测试；
     * 5、由于这阶段的绘制关闭了深度测试，又因为我们绘制的是纯色边框，后绘制的叠加到先绘制的图形上并不影响。
     * */

    // 使用另一个片段着色器绘制
    glBindVertexArray(scene.VAO["obj_vao"]); // 绑定VAO准备开始渲染物体
    for (int i = 0; i < cubePositions.size(); i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::scale(model, glm::vec3(scale));
        // 动态 cube （静态CUBE直接注销这句即可）
        float angel = 20.0f * (i + 1);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angel), glm::vec3(0.5f, 1.0f, 0.0f));
        // // 旋转特定角度
        // model = glm::rotate(model, 1 * glm::radians(angel), glm::vec3(1.0f, 0.3f, 0.5f));
        scene.shader["frame_shader"].setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0); // 解绑 VAO

    // 以下就是恢复为初始状态 （这是为了后面的其他绘制部分能够正确绘制遮挡关系，比如下面对于光源的绘制）
    glStencilMask(0xFF);               // 允许模板写入
    glStencilFunc(GL_ALWAYS, 0, 0xFF); // 总是通过模板测试，并且将通过的部分写0
    glEnable(GL_DEPTH_TEST);           // 开启深度测试

    // /******************************** 绘制点光源 ********************************/
    std::vector<glm::vec3> pointLightPositions = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)};
    // 首先应该切换到光源对应的shader
    scene.shader["light_shader"].use(); // 以下对 light shader 进行配置

    glBindVertexArray(scene.VAO["light_vao"]); // 绑定 VAO
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);

    for (int i = 0; i < pointLightPositions.size(); i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.25f));
        // 动态 cube （静态CUBE直接注销这句即可）
        float angel = 50.0f;
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angel), glm::vec3(0.5f, 1.0f, 0.0f));
        // // 旋转特定角度
        // model = glm::rotate(model, 1 * glm::radians(angel), glm::vec3(1.0f, 0.3f, 0.5f));
        scene.shader["light_shader"].setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0); // 解除 VAO 绑定
}

void scene_load_model_demo_loop(Scene scene)
{
    // 模型绘制
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // don't forget to enable shader before setting uniforms
    scene.shader["obj_shader"].use();

    // 根摄像机一同移动的聚光灯光源
    scene.shader["obj_shader"].setVec3("spotLight.position", primary_cam.cameraPos);
    scene.shader["obj_shader"].setVec3("spotLight.direction", primary_cam.cameraFront);
    // 观察者位置传入
    scene.shader["obj_shader"].setVec3("viewPos", primary_cam.cameraPos);

    // view/projection transformations
    // 定义 MVP 变换阵并导入shader
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));  // it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    scene.shader["obj_shader"].setMat4("model", model);
    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);

    scene.model_obj["backpack"].Draw(scene.shader["obj_shader"]);

    glBindVertexArray(0); // 解绑 VAO

    /******************************** 绘制点光源 ********************************/
    std::vector<glm::vec3> pointLightPositions = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)};
    // 首先应该切换到光源对应的shader

    glBindVertexArray(scene.VAO["base_vao"]); // 绑定 VAO
    scene.shader["light_shader"].use();       // 以下对 light shader 进行配置
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);

    for (int i = 0; i < pointLightPositions.size(); i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.25f));
        // 动态 cube （静态CUBE直接注销这句即可）
        float angel = 50.0f;
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angel), glm::vec3(0.5f, 1.0f, 0.0f));
        // // 旋转特定角度
        // model = glm::rotate(model, 1 * glm::radians(angel), glm::vec3(1.0f, 0.3f, 0.5f));
        scene.shader["light_shader"].setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0); // 解除 VAO 绑定
}

void framebuffer_test_loop(Scene scene)
{
    /**
     *  改变窗口的默认 frame buffer 的绑定，将其绑定到我们创建的 Frame Buffer Object
     * 之后我们的渲染指令操作的结果都将被绘制到该FBO的颜色附件上。
     * */
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["base_fbo"]);
    glEnable(GL_DEPTH_TEST); // 这里我们使能深度测试针对的是我们创建的FBO

    // make sure we clear the framebuffer's content
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 定义 MVP 变换阵 中的 view 和 project 变换阵一般是不变的，可以预先定义并设置
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    // 箱子坐标与定义
    vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    /****************************** 绘制箱子 ******************************/
    // 选定shader
    scene.shader["base_shader"].use();
    scene.shader["base_shader"].setMat4("view", view);
    scene.shader["base_shader"].setMat4("projection", projection);
    // texture 值
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["box_texture"]);

    glBindVertexArray(scene.VAO["base_vao"]); // 绑定 VAO
    for (unsigned int i = 0; i < cubePositions.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        // 静态 cube
        // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        // 动态 cube
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        scene.shader["base_shader"].setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0); // 解绑 VAO

    /**
     *  切换回窗口默认的Frame Buffer
     * */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    /**
     *  失能窗口默认 Frame Buffer 的深度测试，所以后被绘制的总会被呈现在窗口的最前面。
     * 于是我们下一步绘制我们创建的FBO的中的纹理时，它总能被呈现在窗口。
     *  不过由于我们的这个demo没有绘制其他的东西，只有这一个窗口纹理，所以说是不是失能
     * 深度测试好像也没有多大的关系，，，但是情况好像和预想的不一样，下面这句不能注销
     * */
    glDisable(GL_DEPTH_TEST);
    // 清空当前的 Frame Buffer 设为全白
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);

    // 切换专门绘制 texture 平面图的 shader
    scene.shader["frame_shader"].use();
    glBindVertexArray(scene.VAO["frame_vao"]); // 绑定对应 VAO
    // glBindTexture(GL_TEXTURE_2D, scene.textures["screenTexture"]); // use the color attachment texture as the texture of the quad plane

    // 激活 texture 值
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["screenTexture"]);
    glDrawArrays(GL_TRIANGLES, 0, 36); // 绘制 texture

    // 这样做的好处是方便我们进行一些有趣的图像后处理

    glBindVertexArray(0); // 解绑 VAO
}

void scene_skybox_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 定义 MVP 变换阵 中的 view 和 project 变换阵一般是不变的，可以预先定义并设置
    glm::mat4 view;
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    // /****************************** 绘制 SkyBox 注意这个应该优先进行绘制******************************/
    // glDepthMask(GL_FALSE);
    // // glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    // scene.shader["skybox_shader"].use();
    // // 这句很有意思～ mat4 转为 mat3 这使得model变换中的平移操作对当前的天空盒不产生影响，天空盒永远无限远
    // view = glm::mat4(glm::mat3(glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp)));
    // projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);
    // scene.shader["skybox_shader"].setMat4("view", view);
    // scene.shader["skybox_shader"].setMat4("projection", projection);
    // // ... set view and projection matrix
    // glBindVertexArray(scene.VAO["skybox_vao"]);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["cubemapTexture"]);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // // glDepthFunc(GL_LESS); // set depth function back to default
    // glDepthMask(GL_TRUE);

    // glBindVertexArray(0); // 解绑 VAO

    /****************************** 绘制模型 ******************************/

    // 注意这里要重新设置 view 和 projection 矩阵
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    // 选定shader
    scene.shader["model_shader"].use();
    scene.shader["model_shader"].setMat4("view", view);
    scene.shader["model_shader"].setMat4("projection", projection);
    scene.shader["model_shader"].setVec3("cameraPos", primary_cam.cameraPos); // 观察者方向
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));  // it's a bit too big for our scene, so scale it down

    scene.shader["model_shader"].setMat4("model", model);
    scene.model_obj["back_pack"].Draw(scene.shader["model_shader"]);

    /****************************** 绘制箱子 ******************************/
    // 箱子坐标与定义
    vector<glm::vec3> cubePositions = {
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};
    // 选定shader
    scene.shader["base_shader"].use();
    scene.shader["base_shader"].setMat4("view", view);
    scene.shader["base_shader"].setMat4("projection", projection);
    scene.shader["base_shader"].setVec3("cameraPos", primary_cam.cameraPos); // 观察者方向

    glBindVertexArray(scene.VAO["base_vao"]); // 绑定 VAO
    // texture 值
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["cubemapTexture"]);

    for (unsigned int i = 0; i < cubePositions.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * (i + 1);
        // // 静态 cube
        // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        // 动态 cube
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
        scene.shader["base_shader"].setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0); // 解绑 VAO

    /****************************** 绘制 SkyBox 注意这个应该优先进行绘制******************************/
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    scene.shader["skybox_shader"].use();
    // 这句很有意思～ mat4 转为 mat3 这使得model变换中的平移操作对当前的天空盒不产生影响，天空盒永远无限远
    view = glm::mat4(glm::mat3(glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp)));
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);
    scene.shader["skybox_shader"].setMat4("view", view);
    scene.shader["skybox_shader"].setMat4("projection", projection);
    // ... set view and projection matrix
    glBindVertexArray(scene.VAO["skybox_vao"]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["cubemapTexture"]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS); // set depth function back to default

    glBindVertexArray(0); // 解绑 VAO
}

void scene_geometry_shader_demo_loop(Scene scene)
{

    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 选定shader
    // scene.shader["base_shader"].use();
    scene.shader["house_shader"].use();
    glBindVertexArray(scene.VAO["base_vao"]); // 绑定 VAO
    glDrawArrays(GL_POINTS, 0, 4);

    glBindVertexArray(0); // 解绑 VAO
}

void scene_explode_model_demo_loop(Scene scene)
{
    // 模型绘制
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // don't forget to enable shader before setting uniforms
    scene.shader["base_shader"].use();

    // 根摄像机一同移动的聚光灯光源
    scene.shader["base_shader"].setVec3("spotLight.position", primary_cam.cameraPos);
    scene.shader["base_shader"].setVec3("spotLight.direction", primary_cam.cameraFront);
    // 观察者位置传入
    scene.shader["base_shader"].setVec3("viewPos", primary_cam.cameraPos);

    // view/projection transformations
    // 定义 MVP 变换阵并导入shader
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));     // it's a bit too big for our scene, so scale it down

    scene.shader["base_shader"].setMat4("model", model);
    scene.shader["base_shader"].setMat4("view", view);
    scene.shader["base_shader"].setMat4("projection", projection);
    scene.shader["base_shader"].setFloat("time", glfwGetTime()); // 爆炸分离的效果

    scene.model_obj["backpack"].Draw(scene.shader["base_shader"]);

    glBindVertexArray(0); // 解除 VAO 绑定
}

void scene_visualize_model_normal_loop(Scene scene)
{
    // 模型绘制
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 定义 MVP 变换阵并导入shader
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));     // it's a bit too big for our scene, so scale it down

    scene.shader["base_shader"].use();
    scene.shader["base_shader"].setMat4("model", model);
    scene.shader["base_shader"].setMat4("view", view);
    scene.shader["base_shader"].setMat4("projection", projection);

    scene.model_obj["backpack"].Draw(scene.shader["base_shader"]);

    scene.shader["visual_norm_shader"].use();
    scene.shader["visual_norm_shader"].setMat4("model", model);
    scene.shader["visual_norm_shader"].setMat4("view", view);
    scene.shader["visual_norm_shader"].setMat4("projection", projection);

    scene.model_obj["backpack"].Draw(scene.shader["visual_norm_shader"]);

    glBindVertexArray(0); // 解除 VAO 绑定
}

void rendering_instance_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 由于要绘制100个贴片，所以之类将其偏移量进行填充
    glm::vec2 translations[100];
    int index = 0;
    float offset = 0.1f;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }

    // 选定shader
    scene.shader["base_shader"].use();
    for (unsigned int i = 0; i < 100; i++)
    {
        scene.shader["base_shader"].setVec2(("offsets[" + std::to_string(i) + "]"), translations[i]);
    }

    // 一句指令绘制所有的方框，而非重复执行很多次指令
    glBindVertexArray(scene.VAO["base_vao"]);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

    glBindVertexArray(0); // 解绑 VAO
}

void rendering_instance_demo_loop_opt(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 选定shader
    scene.shader["base_shader"].use();

    // 一句指令绘制所有的方框，而非重复执行很多次指令
    glBindVertexArray(scene.VAO["base_vao"]);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

    glBindVertexArray(0); // 解绑 VAO
}

void planet_demo_loop(Scene scene)
{

    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 选定shader
    // view/projection transformations
    // 定义 MVP 变换阵并导入shader
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 1000.0f);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));     // it's a bit too big for our scene, so scale it down

    // Draw the planet
    scene.shader["base_shader"].use();

    scene.shader["base_shader"].setMat4("model", model);
    scene.shader["base_shader"].setMat4("view", view);
    scene.shader["base_shader"].setMat4("projection", projection);
    scene.model_obj["mars"].Draw(scene.shader["base_shader"]);

    // Draw the meteorities
    scene.shader["asteroid_shader"].use();
    scene.shader["asteroid_shader"].setMat4("view", view);
    scene.shader["asteroid_shader"].setMat4("projection", projection);
    scene.shader["asteroid_shader"].setInt("texture_diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.model_obj["rock"].textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
    for (unsigned int i = 0; i < scene.model_obj["rock"].meshes.size(); i++)
    {
        glBindVertexArray(scene.model_obj["rock"].meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(scene.model_obj["rock"].meshes[i].indices.size()), GL_UNSIGNED_INT, 0, 5000);
        glBindVertexArray(0);
    }
}

void MSAA_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // view/projection transformations
    // 定义 MVP 变换阵并导入shader
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 1000.0f);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));     // it's a bit too big for our scene, so scale it down

    // Draw the planet
    scene.shader["base_shader"].use();

    scene.shader["base_shader"].setMat4("model", model);
    scene.shader["base_shader"].setMat4("view", view);
    scene.shader["base_shader"].setMat4("projection", projection);

    glBindVertexArray(scene.VAO["base_vao"]); // 绑定 VAO
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0); // 解绑 VAO
}

void offscreen_MSAA_loop(Scene scene)
{
    // render
    // ------
    // 第一步：绑定 MSAA_FBO 我们将把图像写入 MSAA 对应的 FBO
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["MSAA_fbo"]);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // view/projection transformations
    // 定义 MVP 变换阵并导入shader
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 1000.0f);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);

    // set transformation matrices
    scene.shader["base_shader"].use();
    scene.shader["base_shader"].setMat4("model", model);
    scene.shader["base_shader"].setMat4("view", view);
    scene.shader["base_shader"].setMat4("projection", projection);

    // 在 MSAA 的 FBO 中绘制，产生的结果将被导入到 MSAA_FBO 的超采样颜色附件中
    glBindVertexArray(scene.VAO["base_vao"]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // 之后是呈现到屏幕的部分，这里我们指定：以下渲染操作的读取源为 MSAA 的 FBO；且应该直接输出/写图像到屏幕
    glBindFramebuffer(GL_READ_FRAMEBUFFER, scene.FBO["MSAA_fbo"]);         // 从哪里读取
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, scene.FBO["intermediate_fbo"]); // 向哪里输出
    /**
     *  这次我们将 MSAA 渲染生成的数据输送到中间层 FBO 中，可以在它这里进行一次预处理。注意：实际上我们是将
     * 数据输送到了 intermediate_fbo 的颜色附件上，其实就是绑定在它上面的 screenTexture 。执行完下面的数据
     * 输送语句后 screenTexture 将被填充
     * */
    glBlitFramebuffer(0, 0, primary_cam.frame_width, primary_cam.frame_height, 0, 0, primary_cam.frame_width, primary_cam.frame_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // 切换绑定，先切换到屏幕默认 FBO ，对其清屏
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); // 取消深度测试，从而使得后面绘制到屏幕上的 screenTexture 可以完全被显示。

    /**
     *  可以直接绘制，将 screenTexture 中的内容呈现在屏幕上。也可以使用这个 shader 进行对 screenTexture 的后处理，
     * 得到一些图片处理后的结果。（如灰度图、模糊）
     * */
    scene.shader["quad_shader"].use();
    glBindVertexArray(scene.VAO["quad_vao"]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["screenTexture"]); // use the now resolved color attachment as the quad's texture
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void offscreen_MSAA_loop_ano(Scene scene)
{
    // render
    // ------
    // 第一步：绑定 MSAA_FBO 我们将把图像写入 MSAA 对应的 FBO
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["MSAA_fbo"]);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // view/projection transformations
    // 定义 MVP 变换阵并导入shader
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 1000.0f);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);

    // set transformation matrices
    scene.shader["base_shader"].use();
    scene.shader["base_shader"].setMat4("model", model);
    scene.shader["base_shader"].setMat4("view", view);
    scene.shader["base_shader"].setMat4("projection", projection);

    // 在 MSAA 的 FBO 中绘制，产生的结果将被导入到 MSAA_FBO 的超采样颜色附件中
    glBindVertexArray(scene.VAO["base_vao"]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    /*
        首先这里的一个问题就是，为什么渲染命令执行后再配置的 FBO 中的 src 和 dst，而且还能有正确显示效果。
    这是由于我们应该明确渲染到 FBO 的颜色附件和展示到屏幕显示是两回事。上面的 Draw Call 仅仅是向 GPU 传递
    绘制命令，而如何展示到屏幕是用下面的语句进行配置的。
        glBindFramebuffer 可以使用如之前的形式，将第一项配置为 GL_FRAMEBUFFER 从而使得 FrameBuffer
    的读取和输出是同一个 FBO。
        而以下这种形式可以使用 GL_READ_FRAMEBUFFER 决定 FBO 的数据来源，使用 GL_DRAW_FRAMEBUFFER 决定
    FBO 的数据流向。
    */

    // 之后是呈现到屏幕的部分，这里我们指定：以下渲染操作的读取源为 MSAA 的 FBO；且应该直接输出/写图像到屏幕
    glBindFramebuffer(GL_READ_FRAMEBUFFER, scene.FBO["MSAA_fbo"]); // 从哪里读取
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);                     // 向哪里输出
    /**
     *  制定好以上规则后，便使用以下的 glBlitFramebuffer 函数将数据从 src 导入到 dst 中。
     * 在这里我们直接将数据输出到了屏幕默认的 Frame Buffer 中，于是就直接被呈现到屏幕了。
     * */
    glBlitFramebuffer(0, 0, primary_cam.frame_width, primary_cam.frame_height, 0, 0, primary_cam.frame_width, primary_cam.frame_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void blinn_phong_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 定义 MVP 变换阵
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    /******************************** 绘制物体 ********************************/

    // 先将 view 和 projection 两个矩阵导入 shader

    scene.shader["obj_shader"].use(); // 以下对 obj shader 进行配置
    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);

    // 观察者位置（相机位置）
    scene.shader["obj_shader"].setVec3("viewPos", primary_cam.cameraPos);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["floor_texture"]);

    glBindVertexArray(scene.VAO["obj_vao"]); // 绑定VAO准备开始渲染物体

    model = glm::mat4(1.0f);

    // // 动态 cube （静态CUBE直接注销这句即可）
    // float angel = 20.0f * (i + 1);
    // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angel), glm::vec3(0.5f, 1.0f, 0.0f));
    // // 旋转特定角度
    // model = glm::rotate(model, 1 * glm::radians(angel), glm::vec3(1.0f, 0.3f, 0.5f));
    scene.shader["obj_shader"].setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0); // 解除 VAO 绑定
}

void shadow_mapping_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /***********************************************************************************************/
    // 定义 MVP 变换阵
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    /******************************** 绘制物体 ********************************/

    // 先将 view 和 projection 两个矩阵导入 shader

    scene.shader["plane_shader"].use(); // 以下对 obj shader 进行配置
    scene.shader["plane_shader"].setMat4("view", view);
    scene.shader["plane_shader"].setMat4("projection", projection);

    // 观察者位置（相机位置）
    scene.shader["plane_shader"].setVec3("viewPos", primary_cam.cameraPos);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["floor_texture"]);

    glBindVertexArray(scene.VAO["plane_vao"]); // 绑定VAO准备开始渲染物体

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0); // 解除 VAO 绑定

    /****************************** 绘制箱子 ******************************/
    // 箱子坐标与定义
    vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};
    // 选定shader
    scene.shader["cube_shader"].use();
    scene.shader["cube_shader"].setMat4("view", view);
    scene.shader["cube_shader"].setMat4("projection", projection);
    // texture 值
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["floor_texture"]);

    glBindVertexArray(scene.VAO["cube_vao"]); // 绑定 VAO
    for (unsigned int i = 0; i < cubePositions.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        cubePositions[i].y += 3;
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * (i + 1);
        // 静态 cube
        // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        // 动态 cube
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
        scene.shader["cube_shader"].setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0); // 解绑 VAO
}

void switch_shadow_mapping_demo_loop(Scene scene)
{
    /***********************************************************************************************/

    /****************************** 绘制深度图 ******************************/
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightPos(-2.0f, 4.0f, -1.0f); // 这个之后要修改,改成平行光效果

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 7.5f;
    // 由于是平行光源，所以这里使用的是正交投影，定义左右宽度和上下高度，以及前后平面距离
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));

    lightSpaceMatrix = lightProjection * lightView;
    // 这里使用 depth_shader 从光源的视角看过去，渲染场景，注意光源的位置是固定的，
    // 所以该深度图中我们通过操纵摄像机引起的场景交互是无效的
    scene.shader["depth_shader"].use();
    scene.shader["depth_shader"].setMat4("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, 1600, 900);                               // 注意使用的分辨率应该和创建的深度/模板缓冲区附件一致
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["depth_fbo"]); // 切换绑定，接下来的操作将渲染到深度图 FBO 上
    glClear(GL_DEPTH_BUFFER_BIT);
    /**
     *  渲染深度图。绘制过程使用 depth shader 。
     *  翻看这个 shader program 中的 fragmet shader 我们会发现其 main 函数中没有做任何事情。
     * 这是因为我们没有对当前的 FBO 设置颜色缓冲区，也不需要对颜色进行绘制。我们只需要填充其 depth buffer 。
     * 而 depth buffer 是在 fragment shader 中默认进行比较并填充的。
     *  所以该阶段实际上只需要一个 vertex shader！执行完这个函数后，depth buffer 被默认填充，也就是
     * 它对应的深度纹理 depthMap 被填充。下一个阶段我们将会可视化这个深度缓冲区，也就是把 depthMap 用另一个
     * shader 画出来。
     * */
    renderScene(scene.shader["depth_shader"], scene.VAO["plane_vao"]);

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // 切换回窗口默认的 Frame Buffer
    // 切换回摄像机窗口大小，因为接下来我们要向屏幕进行绘制了
    glViewport(0, 0, primary_cam.frame_width, primary_cam.frame_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清空屏幕默认 FBO 的颜色缓冲区以及深度缓冲区

    // 使用另一个 shader 将已经被填充好的 depthMap 绘制出来。达到可视化深度缓冲的效果
    scene.shader["quad_shader"].use(); // 切换回用于渲染FBO纹理的shader
    // 下面这两个参数用于将默认的非线性深度值还原为线性深度值，这需要我们直到最远平面、最近平面到1～0的映射
    scene.shader["quad_shader"].setFloat("near_plane", near_plane);
    scene.shader["quad_shader"].setFloat("far_plane", far_plane);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["depthMap"]); // 激活纹理
    renderQuad();                                             // 渲染这个texture并且铺满屏幕
    /**
     *  这里额外提一句，看起来这个效果不是很真实，貌似是被拉长了。这是由于我们设置的depthMap与摄像机窗口的分辨率
     * 不一致导致的。可以试着将其统一再查看其效果。（但好像没用？？这是为啥？？我们看到的真的是真实的深度缓冲么）
     * */
}

void switch_shadow_mapping_demo_loop_p2(Scene scene)
{
    /***********************************************************************************************/

    /****************************** 绘制深度图 ******************************/
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightPos(-2.0f, 4.1f, -1.0f);

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 7.5f;
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));

    lightSpaceMatrix = lightProjection * lightView;
    // 第一步：还是从光源的角度看过去，以正交投影的方式绘制深度图
    scene.shader["depth_shader"].use();
    scene.shader["depth_shader"].setMat4("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, 1024, 1024);
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["depth_fbo"]);
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["floor_texture"]);

    // 版本03：优化：剔除正面以解决绝大部分的 peter panning 问题，具体的问题描述在对应的 shader 文件中
    // （不过我这样设置后，好像情况也没什么太大改观，，，）
    glCullFace(GL_FRONT);
    /**
     *  执行完这步后，深度图将被渲染到 depth_fbo 的深度/模板缓冲区附件中，也就是 depthMap 这个 texture 被填充。
     * */
    renderScene(scene.shader["depth_shader"], scene.VAO["plane_vao"]);
    glCullFace(GL_BACK); // 不要忘记设回原先的culling face

    // 绑定到窗口默认的 FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // 重置窗口长宽
    glViewport(0, 0, primary_cam.frame_width, primary_cam.frame_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 第二步：正常绘制场景，将其渲染到屏幕，这里为和能渲染出阴影，主要是 shader 通过计算并对比深度值做到的
    // 以下是正常 camera 视角下的 MVP 变换阵设置
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);
    scene.shader["obj_shader"].use();

    scene.shader["obj_shader"].setMat4("projection", projection);
    scene.shader["obj_shader"].setMat4("view", view);
    // set light uniforms
    scene.shader["obj_shader"].setVec3("viewPos", primary_cam.cameraPos);
    scene.shader["obj_shader"].setVec3("lightPos", lightPos);
    scene.shader["obj_shader"].setMat4("lightSpaceMatrix", lightSpaceMatrix);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["woodTexture"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["depthMap"]); // 注意这里的 depthMap 是第一步生成的
    renderScene(scene.shader["obj_shader"], scene.VAO["plane_vao"]);
}

#pragma region

// renders the 3D scene
// --------------------
void renderScene(Shader &shader, unsigned int VAO)
{
    // floor
    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // cubes
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader.setMat4("model", model);
    renderCube();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader.setMat4("model", model);
    renderCube();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.25));
    shader.setMat4("model", model);
    renderCube();
}

// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;
void renderCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
            1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // bottom-right
            1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  // top-left
            // front face
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
            -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
            -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top-left
            -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
            -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
                                                                // right face
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
            1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // top-right
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    // bottom-left
            // bottom face
            -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // top-left
            1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
            1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
            -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
            -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
            1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // top-right
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
            -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f   // bottom-left
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,
            1.0f,
            0.0f,
            0.0f,
            1.0f,
            -1.0f,
            -1.0f,
            0.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            0.0f,
            1.0f,
            1.0f,
            1.0f,
            -1.0f,
            0.0f,
            1.0f,
            0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

#pragma endregion

bool shadows = true;
bool shadowsKeyPressed = false;

void point_light_source_shadow_mapping_demo_loop(Scene scene)
{
    /***********************************************************************************************/

    /****************************** 绘制深度图 ******************************/

    // 点光源定位
    glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
    // 光源位置随着时间进行移动
    lightPos.z = static_cast<float>(sin(glfwGetTime() * 1.5) * 4.5);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float near_plane = 1.0f;
    float far_plane = 25.0f;

    // 点光源 projection 矩阵
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)1024 / (float)1024, near_plane, far_plane);

    // 点光源 view 矩阵（6个面）
    std::vector<glm::mat4> shadowTransforms;
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

    // 第一步：还是从光源的角度看过去，以透视投影的方式绘制深度图

    glViewport(0, 0, 1024, 1024);
    glBindFramebuffer(GL_FRAMEBUFFER, scene.FBO["depth_fbo"]);
    glClear(GL_DEPTH_BUFFER_BIT);

    scene.shader["depth_shader"].use();
    for (unsigned int i = 0; i < 6; ++i)
    {
        scene.shader["depth_shader"].setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
    }
    scene.shader["depth_shader"].setFloat("far_plane", far_plane);
    scene.shader["depth_shader"].setVec3("lightPos", lightPos);
    /**
     *  使用 depth shader 绘制一遍场景，深度图将被更新到你创建并绑定在 depth fbo 深度附件中的纹理中。
     * */
    renderScene_point_light(scene.shader["depth_shader"]);

    // 绑定回窗口默认的 FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // 重置窗口长宽
    glViewport(0, 0, primary_cam.frame_width, primary_cam.frame_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 第二步：正常绘制场景，将其渲染到屏幕，这里为什么能渲染出阴影，主要是 shader 通过计算并对比深度值做到的
    // 以下是正常 camera 视角下的 MVP 变换阵设置
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    // 定向看光源
    view = glm::lookAt(primary_cam.cameraPos, lightPos, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);
    scene.shader["obj_shader"].use();
    scene.shader["obj_shader"].setMat4("projection", projection);
    scene.shader["obj_shader"].setMat4("view", view);
    // set light uniforms
    scene.shader["obj_shader"].setVec3("viewPos", primary_cam.cameraPos);
    scene.shader["obj_shader"].setVec3("lightPos", lightPos);

    scene.shader["obj_shader"].setInt("shadows", shadows); // enable/disable shadows by pressing 'SPACE'
    scene.shader["obj_shader"].setFloat("far_plane", far_plane);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["diffuseTexture"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["depthCubemap"]);
    renderScene_point_light(scene.shader["obj_shader"]);

    /******************************* 绘制光源 *******************************/
    scene.shader["light_shader"].use();
    scene.shader["light_shader"].setMat4("projection", projection);
    scene.shader["light_shader"].setMat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    /**
     *  这里重新说一下模型变换的顺序。 M_model = M_t * M_r * M_s;
     *  可见应用顺序依次为 translate rotate scale
     *  其实 rotate 和 scale 的顺序是无关的，因为二者都是齐次变换，
     *  只要它们都放在 translate 这种非齐次变换之前就可以。
     * */
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.05));
    scene.shader["light_shader"].setMat4("model", model);
    renderSphere();
}

#pragma region

// renders the 3D scene
// --------------------
void renderScene_point_light(Shader &shader)
{
    // room cube
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(5.0f));
    shader.setMat4("model", model);
    glDisable(GL_CULL_FACE);             // note that we disable culling here since we render 'inside' the cube instead of the usual 'outside' which throws off the normal culling methods.
    shader.setInt("reverse_normals", 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
    renderCube_point_light();
    shader.setInt("reverse_normals", 0); // and of course disable it
    glEnable(GL_CULL_FACE);
    // cubes
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(4.0f, -3.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader.setMat4("model", model);
    renderCube_point_light();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 3.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.75f));
    shader.setMat4("model", model);
    renderCube_point_light();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader.setMat4("model", model);
    renderCube_point_light();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
    model = glm::scale(model, glm::vec3(0.5f));
    shader.setMat4("model", model);
    renderCube_point_light();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.75f));
    shader.setMat4("model", model);
    renderCube_point_light();
}

// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int cubeVAO_point_light = 0;
unsigned int cubeVBO_point_light = 0;
void renderCube_point_light()
{
    // initialize (if necessary)
    if (cubeVAO_point_light == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
            1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // bottom-right
            1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // top-right
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  // top-left
            // front face
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top-right
            -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
            -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top-left
            -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
            -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // top-right
                                                                // right face
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
            1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // top-right
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom-right
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // top-left
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    // bottom-left
            // bottom face
            -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // top-left
            1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
            1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom-left
            -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
            -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
            1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // top-right
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
            -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f   // bottom-left
        };
        glGenVertexArrays(1, &cubeVAO_point_light);
        glGenBuffers(1, &cubeVBO_point_light);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO_point_light);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO_point_light);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO_point_light);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

#pragma endregion

void simple_normal_mapping_demo_loop(Scene scene)
{
    glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 定义 MVP 变换阵
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);
    // model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));

    /******************************** 绘制物体 ********************************/

    // 先将 view 和 projection 两个矩阵导入 shader

    scene.shader["obj_shader"].use(); // 以下对 obj shader 进行配置
    scene.shader["obj_shader"].setMat4("model", model);
    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);

    // 观察者位置（相机位置）
    scene.shader["obj_shader"].setVec3("viewPos", primary_cam.cameraPos);
    scene.shader["obj_shader"].setVec3("lightPos", lightPos);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["diffuseMap"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["normalMap"]);
    renderQuad_Normal();

    // render light source
    scene.shader["light_shader"].use(); // 以下对 light shader 进行配置
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.1f));
    scene.shader["light_shader"].setMat4("model", model);
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);
    renderSphere();

    glBindVertexArray(0); // 解除 VAO 绑定
}

void simple_height_mapping_demo_loop(Scene scene)
{
    glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 定义 MVP 变换阵
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);
    // model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));

    /******************************** 绘制物体 ********************************/

    // 先将 view 和 projection 两个矩阵导入 shader

    scene.shader["obj_shader"].use(); // 以下对 obj shader 进行配置
    scene.shader["obj_shader"].setMat4("model", model);
    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);

    // 观察者位置（相机位置）
    scene.shader["obj_shader"].setVec3("viewPos", primary_cam.cameraPos);
    scene.shader["obj_shader"].setVec3("lightPos", lightPos);

    float heightScale = 0.1f;                                        // 调整深度/高度范围
    scene.shader["obj_shader"].setFloat("heightScale", heightScale); // adjust with Q and E keys

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["diffuseMap"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["normalMap"]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, scene.textures["heightMap"]);
    renderQuad_Normal();

    // render light source
    scene.shader["light_shader"].use(); // 以下对 light shader 进行配置
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.1f));
    scene.shader["light_shader"].setMat4("model", model);
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);
    renderSphere();

    glBindVertexArray(0); // 解除 VAO 绑定
}

#pragma region
// renders a 1x1 quad in NDC with manually calculated tangent vectors
// ------------------------------------------------------------------
unsigned int quadVAO_Normal = 0;
unsigned int quadVBO_Normal;
void renderQuad_Normal()
{
    if (quadVAO_Normal == 0)
    {
        // positions
        glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
        glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
        glm::vec3 pos3(1.0f, -1.0f, 0.0f);
        glm::vec3 pos4(1.0f, 1.0f, 0.0f);
        // texture coordinates
        glm::vec2 uv1(0.0f, 1.0f);
        glm::vec2 uv2(0.0f, 0.0f);
        glm::vec2 uv3(1.0f, 0.0f);
        glm::vec2 uv4(1.0f, 1.0f);
        // normal vector
        glm::vec3 nm(0.0f, 0.0f, 1.0f);

        /**
         *  预设平面中两个三角形的 切线向量 和 副切线向量 我们在CPU端进行TBN的计算，并将对应坐标轴的向量
         * 随顶点数据传入GPU。
         * */
        glm::vec3 tangent1, bitangent1;
        glm::vec3 tangent2, bitangent2;
        // 对第一个三角形进行计算
        // ----------

        /**
         *  先得到三角形的任意两条边，再根据以下的公式解方程组
         *
         *  edge1 = deltaU1*T + deltaV1*B
         *  edge2 = deltaU2*T + deltaV2*B
         *
         *  deltaU1 + deltaU2 = 1.0
         *  deltaV1 + deltaV2 = 1.0
         *
         *  deltaUV1 对应法线贴图 edge1 的斜边向量
         *  deltaUV2 对应法线贴图 edge2 的斜边向量
         *
         *  最终解矩阵可以优化成以下的形式，中间推导略过
         * */
        glm::vec3 edge1 = pos2 - pos1;
        glm::vec3 edge2 = pos3 - pos1;
        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        tangent1 = glm::normalize(tangent1);

        bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        bitangent1 = glm::normalize(bitangent1);

        // triangle 2
        // ----------
        edge1 = pos3 - pos1;
        edge2 = pos4 - pos1;
        deltaUV1 = uv3 - uv1;
        deltaUV2 = uv4 - uv1;

        f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        tangent2 = glm::normalize(tangent2);

        bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        bitangent2 = glm::normalize(bitangent2);

        float quadVertices[] = {
            // positions            // normal         // texcoords  // tangent                          // bitangent
            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
            pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
            pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z};
        // configure plane VAO
        glGenVertexArrays(1, &quadVAO_Normal);
        glGenBuffers(1, &quadVBO_Normal);
        glBindVertexArray(quadVAO_Normal);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO_Normal);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)(8 * sizeof(float)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)(11 * sizeof(float)));
    }
    glBindVertexArray(quadVAO_Normal);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

#pragma endregion

void PBR_light_base_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // lights
    // ------
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f, 10.0f, 10.0f),
        glm::vec3(10.0f, 10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3(10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)};
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    // initialize static shader uniforms before rendering
    // --------------------------------------------------

    // 定义 MVP 变换阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setMat4("projection", projection);
    scene.shader["pbr_shader"].setMat4("view", view);
    scene.shader["pbr_shader"].setVec3("camPos", primary_cam.cameraPos);

    // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
    glm::mat4 model = glm::mat4(1.0f);
    for (int row = 0; row < nrRows; ++row)
    {
        scene.shader["pbr_shader"].setFloat("metallic", (float)row / (float)nrRows);
        // cout << "(float)row / (float)nrRows = " << (float)row / (float)nrRows << endl;
        for (int col = 0; col < nrColumns; ++col)
        {
            // we clamp the roughness to 0.05 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
            // on direct lighting.
            scene.shader["pbr_shader"].setFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));
            // cout << "glm::clamp((float)col / (float)nrColumns = " << glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f) << endl;

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(
                                              (col - (nrColumns / 2)) * spacing,
                                              (row - (nrRows / 2)) * spacing,
                                              0.0f));
            scene.shader["pbr_shader"].setMat4("model", model);
            scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            renderSphere();
        }
        // throw std::runtime_error("haha");
    }

    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
    {
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        scene.shader["pbr_shader"].setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        scene.shader["pbr_shader"].setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, newPos);
        model = glm::scale(model, glm::vec3(0.5f));
        scene.shader["pbr_shader"].setMat4("model", model);
        scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderSphere();
    }
}

void PBR_light_textured_demo_loop(Scene scene)
{

    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // lights
    // ------
    glm::vec3 lightPositions[] = {
        glm::vec3(0.0f, 0.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(150.0f, 150.0f, 150.0f),
    };
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    // initialize static shader uniforms before rendering
    // --------------------------------------------------

    // 定义 MVP 变换阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setMat4("projection", projection);
    scene.shader["pbr_shader"].setMat4("view", view);
    scene.shader["pbr_shader"].setVec3("camPos", primary_cam.cameraPos);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["albedoMap"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["normalMap"]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, scene.textures["metallicMap"]);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, scene.textures["roughnessMap"]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, scene.textures["aoMap"]);

    // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
    glm::mat4 model = glm::mat4(1.0f);
    for (int row = 0; row < nrRows; ++row)
    {
        scene.shader["pbr_shader"].setFloat("metallic", (float)row / (float)nrRows);
        // cout << "(float)row / (float)nrRows = " << (float)row / (float)nrRows << endl;
        for (int col = 0; col < nrColumns; ++col)
        {
            // we clamp the roughness to 0.05 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
            // on direct lighting.
            scene.shader["pbr_shader"].setFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));
            // cout << "glm::clamp((float)col / (float)nrColumns = " << glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f) << endl;

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(
                                              (col - (nrColumns / 2)) * spacing,
                                              (row - (nrRows / 2)) * spacing,
                                              0.0f));
            scene.shader["pbr_shader"].setMat4("model", model);
            scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            renderSphere();
        }
        // throw std::runtime_error("haha");
    }

    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
    {
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        scene.shader["pbr_shader"].setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        scene.shader["pbr_shader"].setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, newPos);
        model = glm::scale(model, glm::vec3(0.5f));
        scene.shader["pbr_shader"].setMat4("model", model);
        scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderSphere();
    }
}

#pragma region

// renders (and builds at first invocation) a sphere
// -------------------------------------------------
unsigned int sphereVAO = 0;
unsigned int indexCount;
void renderSphere()
{
    if (sphereVAO == 0)
    {
        glGenVertexArrays(1, &sphereVAO);

        unsigned int vbo, ebo;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359f;
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = static_cast<unsigned int>(indices.size());

        std::vector<float> data;
        for (unsigned int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
        }
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        unsigned int stride = (3 + 2 + 3) * sizeof(float);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)(6 * sizeof(float)));
    }

    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}

#pragma endregion

void PBR_IBL_diffuse_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // lights
    // ------
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f, 10.0f, 10.0f),
        glm::vec3(10.0f, 10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3(10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)};
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    // initialize static shader uniforms before rendering
    // --------------------------------------------------

    // 定义 MVP 变换阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("projection", projection);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setMat4("projection", projection);
    scene.shader["pbr_shader"].setMat4("view", view);
    scene.shader["pbr_shader"].setVec3("camPos", primary_cam.cameraPos);

    // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
    glm::mat4 model = glm::mat4(1.0f);
    for (int row = 0; row < nrRows; ++row)
    {
        scene.shader["pbr_shader"].setFloat("metallic", (float)row / (float)nrRows);
        for (int col = 0; col < nrColumns; ++col)
        {
            // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
            // on direct lighting.
            scene.shader["pbr_shader"].setFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(
                                              (float)(col - (nrColumns / 2)) * spacing,
                                              (float)(row - (nrRows / 2)) * spacing,
                                              -2.0f));
            scene.shader["pbr_shader"].setMat4("model", model);
            scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            renderSphere();
        }
    }
    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
    {
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        scene.shader["pbr_shader"].setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        scene.shader["pbr_shader"].setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, newPos);
        model = glm::scale(model, glm::vec3(0.5f));
        scene.shader["pbr_shader"].setMat4("model", model);
        scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderSphere();
    }

    /****************************** 绘制 skybox ******************************/
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    // render skybox (render as last to prevent overdraw)
    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["envCubemap"]);
    renderCube();
    glDepthFunc(GL_LESS);
}

void PBR_IBL_diffuse_demo_loop_p2(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // lights
    // ------
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f, 10.0f, 10.0f),
        glm::vec3(10.0f, 10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3(10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)};
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    // initialize static shader uniforms before rendering
    // --------------------------------------------------

    // 定义 MVP 变换阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("projection", projection);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setMat4("projection", projection);
    scene.shader["pbr_shader"].setMat4("view", view);
    scene.shader["pbr_shader"].setVec3("camPos", primary_cam.cameraPos);

    // bind pre-computed IBL data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["irradianceMap"]);

    // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
    glm::mat4 model = glm::mat4(1.0f);
    for (int row = 0; row < nrRows; ++row)
    {
        scene.shader["pbr_shader"].setFloat("metallic", (float)row / (float)nrRows);
        for (int col = 0; col < nrColumns; ++col)
        {
            // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
            // on direct lighting.
            scene.shader["pbr_shader"].setFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(
                                              (float)(col - (nrColumns / 2)) * spacing,
                                              (float)(row - (nrRows / 2)) * spacing,
                                              -2.0f));
            scene.shader["pbr_shader"].setMat4("model", model);
            scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            renderSphere();
        }
    }
    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
    {
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        scene.shader["pbr_shader"].setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        scene.shader["pbr_shader"].setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, newPos);
        model = glm::scale(model, glm::vec3(0.5f));
        scene.shader["pbr_shader"].setMat4("model", model);
        scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderSphere();
    }

    /****************************** 绘制 skybox ******************************/
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    // render skybox (render as last to prevent overdraw)
    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["envCubemap"]);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["irradianceMap"]);
    renderCube();
    glDepthFunc(GL_LESS);
}

void PBR_IBL_diffuse_demo_loop_ano(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // lights
    // ------
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f, 10.0f, 10.0f),
        glm::vec3(10.0f, 10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3(10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)};
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    // initialize static shader uniforms before rendering
    // --------------------------------------------------

    // 定义 MVP 变换阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("projection", projection);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setMat4("projection", projection);
    scene.shader["pbr_shader"].setMat4("view", view);
    scene.shader["pbr_shader"].setVec3("camPos", primary_cam.cameraPos);

    // bind pre-computed IBL data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["irradianceMap"]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["albedoMap"]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, scene.textures["normalMap"]);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, scene.textures["metallicMap"]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, scene.textures["roughnessMap"]);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, scene.textures["aoMap"]);

    // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
    glm::mat4 model = glm::mat4(1.0f);
    for (int row = 0; row < nrRows; ++row)
    {
        scene.shader["pbr_shader"].setFloat("metallic", (float)row / (float)nrRows);
        // cout << "(float)row / (float)nrRows = " << (float)row / (float)nrRows << endl;
        for (int col = 0; col < nrColumns; ++col)
        {
            // we clamp the roughness to 0.05 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
            // on direct lighting.
            scene.shader["pbr_shader"].setFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));
            // cout << "glm::clamp((float)col / (float)nrColumns = " << glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f) << endl;

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(
                                              (col - (nrColumns / 2)) * spacing,
                                              (row - (nrRows / 2)) * spacing,
                                              0.0f));
            scene.shader["pbr_shader"].setMat4("model", model);
            scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            renderSphere();
        }
        // throw std::runtime_error("haha");
    }

    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
    {
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        scene.shader["pbr_shader"].setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        scene.shader["pbr_shader"].setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, newPos);
        model = glm::scale(model, glm::vec3(0.5f));
        scene.shader["pbr_shader"].setMat4("model", model);
        scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderSphere();
    }

    /****************************** 绘制 skybox ******************************/
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    // render skybox (render as last to prevent overdraw)
    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["envCubemap"]);
    renderCube();
    glDepthFunc(GL_LESS);
}

void PBR_IBL_specular_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // lights
    // ------
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f, 10.0f, 10.0f),
        glm::vec3(10.0f, 10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3(10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)};
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    // initialize static shader uniforms before rendering
    // --------------------------------------------------

    // 定义 MVP 变换阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("projection", projection);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setMat4("projection", projection);
    scene.shader["pbr_shader"].setMat4("view", view);
    scene.shader["pbr_shader"].setVec3("camPos", primary_cam.cameraPos);

    // bind pre-computed IBL data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["irradianceMap"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["prefilterMap"]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, scene.textures["brdfLUTTexture"]);

    // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
    glm::mat4 model = glm::mat4(1.0f);
    for (int row = 0; row < nrRows; ++row)
    {
        scene.shader["pbr_shader"].setFloat("metallic", (float)row / (float)nrRows);
        for (int col = 0; col < nrColumns; ++col)
        {
            // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
            // on direct lighting.
            scene.shader["pbr_shader"].setFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(
                                              (float)(col - (nrColumns / 2)) * spacing,
                                              (float)(row - (nrRows / 2)) * spacing,
                                              -2.0f));
            scene.shader["pbr_shader"].setMat4("model", model);
            scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            renderSphere();
        }
    }
    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
    {
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        scene.shader["pbr_shader"].setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        scene.shader["pbr_shader"].setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, newPos);
        model = glm::scale(model, glm::vec3(0.5f));
        scene.shader["pbr_shader"].setMat4("model", model);
        scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderSphere();
    }

    /****************************** 绘制 skybox ******************************/
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    // render skybox (render as last to prevent overdraw)
    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["envCubemap"]);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["irradianceMap"]); // display irradiance map
    // glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["prefilterMap"]); // display prefilter map
    renderCube();
    glDepthFunc(GL_LESS);
}

void PBR_IBL_textured_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // lights
    // ------
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f, 10.0f, 10.0f),
        glm::vec3(10.0f, 10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3(10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 00.0f, 00.0f),
        glm::vec3(00.0f, 300.0f, 00.0f),
        glm::vec3(00.0f, 00.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)};
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    // initialize static shader uniforms before rendering
    // --------------------------------------------------

    // 定义 MVP 变换阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    glm::mat4 model = glm::mat4(1.0f);

    scene.shader["light_shader"].use();
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("projection", projection);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setMat4("projection", projection);
    scene.shader["pbr_shader"].setMat4("view", view);
    scene.shader["pbr_shader"].setVec3("camPos", primary_cam.cameraPos);

    // bind pre-computed IBL data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["irradianceMap"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["prefilterMap"]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, scene.textures["brdfLUTTexture"]);

    // rusted iron
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, scene.textures["ironAlbedoMap"]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, scene.textures["ironNormalMap"]);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, scene.textures["ironMetallicMap"]);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, scene.textures["ironRoughnessMap"]);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, scene.textures["ironAOMap"]);

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
    model = glm::translate(model, glm::vec3(-1.0, 0.0, 2.0));
    scene.shader["pbr_shader"].setMat4("model", model);
    scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
    renderSphere();

    // gold
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, scene.textures["goldAlbedoMap"]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, scene.textures["goldNormalMap"]);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, scene.textures["goldMetallicMap"]);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, scene.textures["goldRoughnessMap"]);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, scene.textures["goldAOMap"]);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0, -1.0, 2.0));
    scene.shader["pbr_shader"].setMat4("model", model);
    scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
    renderSphere();

    // wall
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, scene.textures["wallAlbedoMap"]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, scene.textures["wallNormalMap"]);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, scene.textures["wallMetallicMap"]);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, scene.textures["wallRoughnessMap"]);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, scene.textures["wallAOMap"]);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    scene.shader["pbr_shader"].setMat4("model", model);
    scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
    renderSphere();

    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
    {
        scene.shader["pbr_shader"].use();
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        scene.shader["pbr_shader"].setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        scene.shader["pbr_shader"].setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

        scene.shader["light_shader"].use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, newPos);
        model = glm::scale(model, glm::vec3(0.15f));
        scene.shader["light_shader"].setMat4("model", model);
        scene.shader["light_shader"].setVec3("lightColor", lightColors[i]);
        // scene.shader["light_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderSphere();
    }

    /****************************** 绘制 skybox ******************************/
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    // render skybox (render as last to prevent overdraw)
    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["envCubemap"]);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["irradianceMap"]); // display irradiance map
    // glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["prefilterMap"]); // display prefilter map
    renderCube();
    glDepthFunc(GL_LESS);
}

void PBR_IBL_model_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // lights
    // ------
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f, 10.0f, 10.0f),
        glm::vec3(10.0f, 10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3(10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 00.0f, 00.0f),
        glm::vec3(00.0f, 300.0f, 00.0f),
        glm::vec3(00.0f, 00.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)};

    // initialize static shader uniforms before rendering
    // --------------------------------------------------

    // 定义 MVP 变换阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    glm::mat4 model = glm::mat4(1.0f);

    scene.shader["light_shader"].use();
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);

    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("projection", projection);

    scene.shader["pbr_shader"].use();
    scene.shader["pbr_shader"].setMat4("projection", projection);
    scene.shader["pbr_shader"].setMat4("view", view);
    scene.shader["pbr_shader"].setVec3("camPos", primary_cam.cameraPos);

    // bind pre-computed IBL data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["irradianceMap"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["prefilterMap"]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, scene.textures["brdfLUTTexture"]);

    // rusted gun
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, scene.textures["gunAlbedoMap"]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, scene.textures["gunNormalMap"]);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, scene.textures["gunMetallicMap"]);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, scene.textures["gunRoughnessMap"]);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, scene.textures["gunAOMap"]);

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    model = glm::translate(model, glm::vec3(0.0, 0.0, 2.0));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    scene.shader["pbr_shader"].setMat4("model", model);
    scene.shader["pbr_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
    // renderSphere();
    scene.model_obj["gun"].Draw(scene.shader["pbr_shader"]);

    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
    {
        scene.shader["pbr_shader"].use();
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        scene.shader["pbr_shader"].setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        scene.shader["pbr_shader"].setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

        scene.shader["light_shader"].use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, newPos);
        model = glm::scale(model, glm::vec3(0.15f));
        scene.shader["light_shader"].setMat4("model", model);
        scene.shader["light_shader"].setVec3("lightColor", lightColors[i]);
        // scene.shader["light_shader"].setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderSphere();
    }

    /****************************** 绘制 skybox ******************************/
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    // render skybox (render as last to prevent overdraw)
    scene.shader["background_shader"].use();
    scene.shader["background_shader"].setMat4("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["envCubemap"]);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["irradianceMap"]); // display irradiance map
    // glBindTexture(GL_TEXTURE_CUBE_MAP, scene.textures["prefilterMap"]); // display prefilter map
    renderCube();
    glDepthFunc(GL_LESS);
}
