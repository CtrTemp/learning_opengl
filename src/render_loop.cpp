#include "render_loop.h"

void multi_rotating_cube_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 选定shader
    scene.shader["base_shader"].use();
    unsigned int shader_id = scene.shader["base_shader"].ID;
    // 以下使用两种方式从CPU端告知GPU端设置的Uniform Buffer编号
    glUniform1i(glGetUniformLocation(shader_id, "ourTextureFromCPU"), 0); // set it manually
    scene.shader["base_shader"].setInt("ourTextureFromCPU_ano", 1);

    // 定义 MVP 变换阵并导入shader
    // Model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(shader_id, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int viewLoc = glGetUniformLocation(shader_id, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    unsigned int projectionLoc = glGetUniformLocation(shader_id, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // 通过 uniform buffer 向GPU传递一个渐变的颜色值
    GLfloat timeValue = glfwGetTime();
    GLfloat greenValue = sin(timeValue) / 2 + 0.5;
    GLint vertexColorLocation = glGetUniformLocation(shader_id, "ourColorFromCPU");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    // texture 值
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["statue_texture"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["viking_texture"]);

    glBindVertexArray(scene.VAO["base_vao"]);

    // 我们可以绘制更多的CUBE
    glm::vec3 cubePositions[] = {
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

    // 绘制更多的 CUBE
    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        // 静态 cube
        // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        // 动态 cube
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        unsigned int modelLoc = glGetUniformLocation(shader_id, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void scene_light_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 定义 MVP 变换阵
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view;
    glm::mat4 projection = glm::mat4(1.0f);

    // 定义物体位置和光源位置 （现在只考虑单一光源）
    glm::vec3 objPos = {0.0f, 0.0f, 0.0f};
    glm::vec3 lightPos = {1.2f, 1.0f, 2.0f};

    /******************************** 绘制光物体 ********************************/
    scene.shader["obj_shader"].use(); // 以下对 obj shader 进行配置

    scene.shader["obj_shader"].setVec3("lightPos", lightPos);
    scene.shader["obj_shader"].setVec3("light.position", primary_cam.cameraPos);
    scene.shader["obj_shader"].setVec3("light.direction", primary_cam.cameraFront);
    scene.shader["obj_shader"].setVec3("viewPos", primary_cam.cameraPos);

    // 设置 MVP 变换阵并导入shader

    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["viking_texture"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["frame_texture"]);

    glBindVertexArray(scene.VAO["obj_vao"]);

    // 绘制物体对象（顶点已经被默认摆放到了正确的位置，所以物体可以直接进行绘制）

    // 我们可以绘制更多的CUBE
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

    for (int i = 0; i < cubePositions.size(); i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        // 动态 cube （静态CUBE直接注销这句即可）
        float angel = 20.0f * (i + 1);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angel), glm::vec3(0.5f, 1.0f, 0.0f));
        // // 旋转特定角度
        // model = glm::rotate(model, 1 * glm::radians(angel), glm::vec3(1.0f, 0.3f, 0.5f));
        scene.shader["obj_shader"].setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0); // 解绑 VAO

    // /******************************** 绘制光源 ********************************/
    // 首先应该切换到光源对应的shader
    scene.shader["light_shader"].use(); // 以下对 light shader 进行配置

    glBindVertexArray(scene.VAO["light_vao"]); // 绑定 VAO
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.25f));
    // 动态 cube （静态CUBE直接注销这句即可）
    // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    // 旋转特定角度
    model = glm::rotate(model, 1 * glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    scene.shader["light_shader"].setMat4("model", model);
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0); // 解除 VAO 绑定
}