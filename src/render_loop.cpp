#include "render_loop.h"

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

// renders a 1x1 quad in NDC with manually calculated tangent vectors
// ------------------------------------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
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

        float quadVertices[] = {
            // positions            // normal         // texcoords
            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y,
            pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y,

            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y,
            pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y};
        // configure plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

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

void playground_demo_loop_p1_simple(Scene scene)
{

    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vector<glm::vec3> cube_pos{
        {0.0f, 1.01f, 0.0f}};

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    scene.shader["obj_shader"].use();
    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);

    model = glm::mat4(1.0f);
    model = glm::translate(model, cube_pos[0]);
    scene.shader["obj_shader"].setMat4("model", model);
    scene.shader["obj_shader"].setVec3("baseColor", {1.0f, 0.0f, 0.0f});
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["box_tex"]);
    renderCube();

    model = glm::mat4(1.0f);
    // model = glm::translate(model, cube_pos[0]);
    model = glm::scale(model, glm::vec3(5.0f));
    model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scene.shader["obj_shader"].setMat4("model", model);
    scene.shader["obj_shader"].setVec3("baseColor", {0.0f, 1.0f, 0.0f});
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["floor_tex"]);
    renderQuad();
}

void playground_demo_loop_p2_texture(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vector<glm::vec3> cube_pos{
        {0.0f, 1.01f, 0.0f}};

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    scene.shader["obj_shader"].use();
    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);

    model = glm::mat4(1.0f);
    model = glm::translate(model, cube_pos[0]);
    scene.shader["obj_shader"].setMat4("model", model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["box_tex"]);
    renderCube();

    model = glm::mat4(1.0f);
    // model = glm::translate(model, cube_pos[0]);
    model = glm::scale(model, glm::vec3(5.0f));
    model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scene.shader["obj_shader"].setMat4("model", model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["floor_tex"]);
    renderQuad();
}

void playground_demo_loop_p3_light_source(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // MVP Matrix
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    // Object configuration
    const float attenuation_constant = 1.0f;
    const float attenuation_linear = 0.09f;
    const float attenuation_quadratic = 0.0032f;
    vector<glm::vec3> light_pos{
        {0.0f, 1.0f, 2.5f}};
    vector<glm::vec3> light_color{
        {1.0f, 1.0f, 1.0f}};
    vector<glm::vec3> light_ambient{
        {0.05f, 0.05f, 0.05f}};

    vector<glm::vec3> cube_pos{
        {0.0f, 1.01f, 0.0f}};

    scene.shader["obj_shader"].use();
    scene.shader["obj_shader"].setMat4("view", view);
    scene.shader["obj_shader"].setMat4("projection", projection);
    scene.shader["obj_shader"].setVec3("viewPos", primary_cam.cameraPos);

    scene.shader["obj_shader"].setFloat("material.shininess", scene.mat_shininess);

    scene.shader["obj_shader"].setVec3("pointLights[0].position", light_pos[0]);
    scene.shader["obj_shader"].setVec3("pointLights[0].ambient", light_ambient[0] * scene.mat_ambient);
    scene.shader["obj_shader"].setVec3("pointLights[0].diffuse", light_color[0]);
    scene.shader["obj_shader"].setVec3("pointLights[0].specular", light_color[0]);

    scene.shader["obj_shader"].setFloat("pointLights[0].constant", attenuation_constant);
    scene.shader["obj_shader"].setFloat("pointLights[0].linear", attenuation_linear);
    scene.shader["obj_shader"].setFloat("pointLights[0].quadratic", attenuation_quadratic);

    /**************************************** Render Object ****************************************/

    model = glm::mat4(1.0f);
    model = glm::translate(model, cube_pos[0]);
    scene.shader["obj_shader"].setMat4("model", model);
    scene.shader["obj_shader"].setFloat("reverseNormal", 1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["box_tex"]);
    renderCube();

    /**************************************** Render Ground ****************************************/

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(5.0f));
    model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scene.shader["obj_shader"].setMat4("model", model);
    scene.shader["obj_shader"].setFloat("reverseNormal", -1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["floor_tex"]);
    renderQuad();

    /************************************* Render Light Source *************************************/
    scene.shader["light_shader"].use();
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);

    model = glm::mat4(1.0f);
    model = glm::translate(model, light_pos[0]);
    model = glm::scale(model, glm::vec3(0.1f));
    model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scene.shader["light_shader"].setMat4("model", model);
    scene.shader["light_shader"].setVec3("lightColor", light_color[0]);
    renderSphere();
}

void playground_demo_loop_p4_normal_mapping(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // MVP Matrix
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    // Object configuration
    const float attenuation_constant = 1.0f;
    const float attenuation_linear = 0.09f;
    const float attenuation_quadratic = 0.0032f;
    vector<glm::vec3> light_pos{
        {0.0f, 1.0f, 2.5f}};
    vector<glm::vec3> light_color{
        {1.0f, 1.0f, 1.0f}};
    vector<glm::vec3> light_ambient{
        {0.05f, 0.05f, 0.05f}};

    vector<glm::vec3> cube_pos{
        {0.0f, 1.01f, 0.0f}};

    /**************************************** Render Box ****************************************/

    scene.shader["box_shader"].use();
    scene.shader["box_shader"].setMat4("view", view);
    scene.shader["box_shader"].setMat4("projection", projection);
    scene.shader["box_shader"].setVec3("viewPos", primary_cam.cameraPos);

    scene.shader["box_shader"].setFloat("material.shininess", scene.mat_shininess);

    scene.shader["box_shader"].setVec3("point_light.position", light_pos[0]);
    scene.shader["box_shader"].setVec3("point_light.ambient", light_ambient[0] * scene.mat_ambient);
    scene.shader["box_shader"].setVec3("point_light.diffuse", light_color[0]);
    scene.shader["box_shader"].setVec3("point_light.specular", light_color[0]);

    scene.shader["box_shader"].setFloat("point_light.constant", attenuation_constant);
    scene.shader["box_shader"].setFloat("point_light.linear", attenuation_linear);
    scene.shader["box_shader"].setFloat("point_light.quadratic", attenuation_quadratic);

    model = glm::mat4(1.0f);
    model = glm::translate(model, cube_pos[0]);
    scene.shader["box_shader"].setMat4("model", model);
    scene.shader["box_shader"].setFloat("reverseNormal", 1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["box_diffuse_tex"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["box_specular_tex"]);
    renderCube();

    /**************************************** Render Ground ****************************************/

    scene.shader["plane_shader"].use();
    scene.shader["plane_shader"].setMat4("view", view);
    scene.shader["plane_shader"].setMat4("projection", projection);
    scene.shader["plane_shader"].setVec3("viewPos", primary_cam.cameraPos);

    scene.shader["plane_shader"].setFloat("material.shininess", scene.mat_shininess);

    scene.shader["plane_shader"].setVec3("point_light.position", light_pos[0]);
    scene.shader["plane_shader"].setVec3("point_light.ambient", light_ambient[0] * scene.mat_ambient);
    scene.shader["plane_shader"].setVec3("point_light.diffuse", light_color[0]);
    scene.shader["plane_shader"].setVec3("point_light.specular", light_color[0]);

    scene.shader["plane_shader"].setFloat("point_light.constant", attenuation_constant);
    scene.shader["plane_shader"].setFloat("point_light.linear", attenuation_linear);
    scene.shader["plane_shader"].setFloat("point_light.quadratic", attenuation_quadratic);

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(5.0f));
    model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scene.shader["plane_shader"].setMat4("model", model);
    scene.shader["plane_shader"].setFloat("reverseNormal", -1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["plane_diffuse_tex"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["plane_normal_tex"]);
    renderQuad_Normal();

    /************************************* Render Light Source *************************************/
    scene.shader["light_shader"].use();
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);

    model = glm::mat4(1.0f);
    model = glm::translate(model, light_pos[0]);
    model = glm::scale(model, glm::vec3(0.1f));
    model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scene.shader["light_shader"].setMat4("model", model);
    scene.shader["light_shader"].setVec3("lightColor", light_color[0]);
    renderSphere();
}

void playground_demo_loop_p5_height_mapping(Scene scene)
{
    // set clear frame color
    glClearColor(scene.background.r, scene.background.g, scene.background.b, scene.background.a);
    glEnable(GL_DEPTH_TEST); // 使能深度测试，这样可以正确绘制遮挡关系
    // 每轮循环都要清空深度缓存和颜色缓存，从而正确绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // MVP Matrix
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(primary_cam.cameraPos, primary_cam.cameraPos + primary_cam.cameraFront, primary_cam.cameraUp);
    projection = glm::perspective(glm::radians(primary_cam.fov), (float)primary_cam.frame_width / (float)primary_cam.frame_height, 0.1f, 100.0f);

    // Object configuration
    const float attenuation_constant = 1.0f;
    const float attenuation_linear = 0.09f;
    const float attenuation_quadratic = 0.0032f;
    vector<glm::vec3> light_pos{
        {0.0f, 1.0f, 2.5f}};
    vector<glm::vec3> light_color{
        {1.0f, 1.0f, 1.0f}};
    vector<glm::vec3> light_ambient{
        {0.05f, 0.05f, 0.05f}};

    vector<glm::vec3> cube_pos{
        {0.0f, 1.01f, 0.0f}};

    /**************************************** Render Box ****************************************/

    scene.shader["box_shader"].use();
    scene.shader["box_shader"].setMat4("view", view);
    scene.shader["box_shader"].setMat4("projection", projection);
    scene.shader["box_shader"].setVec3("viewPos", primary_cam.cameraPos);

    scene.shader["box_shader"].setFloat("material.shininess", scene.mat_shininess);

    scene.shader["box_shader"].setVec3("point_light.position", light_pos[0]);
    scene.shader["box_shader"].setVec3("point_light.ambient", light_ambient[0] * scene.mat_ambient);
    scene.shader["box_shader"].setVec3("point_light.diffuse", light_color[0]);
    scene.shader["box_shader"].setVec3("point_light.specular", light_color[0]);

    scene.shader["box_shader"].setFloat("point_light.constant", attenuation_constant);
    scene.shader["box_shader"].setFloat("point_light.linear", attenuation_linear);
    scene.shader["box_shader"].setFloat("point_light.quadratic", attenuation_quadratic);

    model = glm::mat4(1.0f);
    model = glm::translate(model, cube_pos[0]);
    scene.shader["box_shader"].setMat4("model", model);
    scene.shader["box_shader"].setFloat("reverseNormal", 1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["box_diffuse_tex"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["box_specular_tex"]);
    renderCube();

    /**************************************** Render Ground ****************************************/

    scene.shader["plane_shader"].use();
    scene.shader["plane_shader"].setMat4("view", view);
    scene.shader["plane_shader"].setMat4("projection", projection);
    scene.shader["plane_shader"].setVec3("viewPos", primary_cam.cameraPos);

    scene.shader["plane_shader"].setFloat("material.shininess", scene.mat_shininess);

    scene.shader["plane_shader"].setVec3("point_light.position", light_pos[0]);
    scene.shader["plane_shader"].setVec3("point_light.ambient", light_ambient[0] * scene.mat_ambient);
    scene.shader["plane_shader"].setVec3("point_light.diffuse", light_color[0]);
    scene.shader["plane_shader"].setVec3("point_light.specular", light_color[0]);

    scene.shader["plane_shader"].setFloat("point_light.constant", attenuation_constant);
    scene.shader["plane_shader"].setFloat("point_light.linear", attenuation_linear);
    scene.shader["plane_shader"].setFloat("point_light.quadratic", attenuation_quadratic);

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(5.0f));
    model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scene.shader["plane_shader"].setMat4("model", model);
    scene.shader["plane_shader"].setFloat("reverseNormal", -1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene.textures["plane_diffuse_tex"]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene.textures["plane_normal_tex"]);
    renderQuad_Normal();

    /************************************* Render Light Source *************************************/
    scene.shader["light_shader"].use();
    scene.shader["light_shader"].setMat4("view", view);
    scene.shader["light_shader"].setMat4("projection", projection);

    model = glm::mat4(1.0f);
    model = glm::translate(model, light_pos[0]);
    model = glm::scale(model, glm::vec3(0.1f));
    model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scene.shader["light_shader"].setMat4("model", model);
    scene.shader["light_shader"].setVec3("lightColor", light_color[0]);
    renderSphere();
}

