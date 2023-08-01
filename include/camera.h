#ifndef CAMERA_H
#define CAMERA_H

#include "global_include.h"

class Camera
{
public:
    Camera()
    {
        fov = 45.0f;
        frame_width = 1600;
        frame_height = 900;
        yaw = -90.0f;
        pitch = 0.0f;

        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        worldDown = glm::vec3(0.0f, -1.0f, 0.0f);
    }

    Camera(float f, unsigned int w, unsigned int h, float y, float p)
    {
        fov = f;
        frame_width = w;
        frame_height = h;
        yaw = y;
        pitch = p;

        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        worldDown = glm::vec3(0.0f, -1.0f, 0.0f);
    }

public:
    // 应该有一个函数是通过当前的 viewPos 和 cameraFront 来更新摄像机当前欧拉角
    void update_cam_pos();

public:
    float fov;
    unsigned int frame_width;
    unsigned int frame_height;

    float yaw;
    float pitch;
    // float roll;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 worldUp;
    glm::vec3 worldDown;
};

// 声明相机全局变量
extern Camera primary_cam;

#endif