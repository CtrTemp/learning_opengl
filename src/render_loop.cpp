#include "render_loop.h"


void multi_rotating_cube_demo_loop(Scene scene)
{
    // set clear frame color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    // 选定shader
    scene.shader.use();
    // 以下使用两种方式从CPU端告知GPU端设置的Uniform Buffer编号
    glUniform1i(glGetUniformLocation(scene.shader.ID, "ourTextureFromCPU"), 0); // set it manually
    scene.shader.setInt("ourTextureFromCPU_ano", 1);

    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    // 定义 MVP 变换阵并导入shader
    // Model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    
    glm::mat4 view;
    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(scene.shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int viewLoc = glGetUniformLocation(scene.shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]); 
    unsigned int projectionLoc = glGetUniformLocation(scene.shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // 通过 uniform buffer 向GPU传递一个渐变的颜色值
    GLfloat timeValue = glfwGetTime();
    GLfloat greenValue = sin(timeValue) / 2 + 0.5;
    GLint vertexColorLocation = glGetUniformLocation(scene.shader.ID, "ourColorFromCPU");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


    // texture 值
    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, scene.textures[0]);
    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, scene.textures[1]);

    
    glBindVertexArray(scene.VAO);

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
        unsigned int modelLoc = glGetUniformLocation(scene.shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
