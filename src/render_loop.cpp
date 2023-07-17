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
    // 模板测试总是会通过，也就是无论如何以下的片段绘制都会被执行
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
    // 2nd. Render pass, now draw slightly scaled versions of the objects, this time disabling stencil writing.
    // Because stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are now not drawn, thus only drawing
    // the objects' size differences, making it look like borders.
    // 2、第二步，关闭模板写入和深度测试
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // GL_NOTEQUAL 表示当片段值与模板缓冲区中的值不相等的时候通过模板测试，并向模板中写1
    // glStencilMask(0x00);                 // 关闭模板写入 感觉这个根本没必要
    // glDisable(GL_DEPTH_TEST);            // 关闭深度测试 这个也没必要 （果然注释后没有什么差别）
    scene.shader["frame_shader"].use(); // 其次使用绘制边框的 shader 对物体进行第二次绘制
    float scale = 1.1f;

    // 以下绘制将会有如下的流程：
    /**
     * 1、将原来的CUBE扩大了一圈进行绘制
     * 2、此时这些被绘制部分片段的值应该被置为1
     * 3、以上的片段模板值会与模板缓冲区中的值进行比较，仅当二者不相等时才会被置为1
     * 4、也就是CUBE扩大的那一圈会被置为1，这就是边框部分
     * 5、而对于那些没有通过深度测试的，会被置为原来的值，所以原本扩大之前的CUBE还会被正确绘制，并保持遮挡关系。
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
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));     // it's a bit too big for our scene, so scale it down

    scene.shader["obj_shader"].setMat4("model", model);
    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);

    scene.model_obj.Draw(scene.shader["obj_shader"]);

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

void scene_skybox_demo_loop(Scene scene)
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

    glm::mat4 model = glm::mat4(1.0f);

    /****************************** 绘制模型 ******************************/
    // 选定shader
    scene.shader["model_shader"].use();
    scene.shader["model_shader"].setMat4("view", view);
    scene.shader["model_shader"].setMat4("projection", projection);
    scene.shader["model_shader"].setVec3("cameraPos", primary_cam.cameraPos); // 观察者方向
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));  // it's a bit too big for our scene, so scale it down

    scene.shader["model_shader"].setMat4("model", model);
    scene.model_obj.Draw(scene.shader["model_shader"]);

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

    /****************************** 绘制 SkyBox ******************************/
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    scene.shader["skybox_shader"].use();
    // 这句很有意思～
    view = glm::mat4(glm::mat3(glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp)));
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

    scene.model_obj.Draw(scene.shader["base_shader"]);

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

    scene.model_obj.Draw(scene.shader["base_shader"]);

    scene.shader["visual_norm_shader"].use();
    scene.shader["visual_norm_shader"].setMat4("model", model);
    scene.shader["visual_norm_shader"].setMat4("view", view);
    scene.shader["visual_norm_shader"].setMat4("projection", projection);

    scene.model_obj.Draw(scene.shader["visual_norm_shader"]);

    glBindVertexArray(0); // 解除 VAO 绑定
}
