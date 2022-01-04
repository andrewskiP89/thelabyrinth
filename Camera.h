//
// Created by andreaporru on 30/12/21.
//

#ifndef THELABYRINTH_CAMERA_H
#define THELABYRINTH_CAMERA_H
#include "Libraries.h"
#include "StandardHeaders.h"

enum CameraInited {CAMERA_INITED_TRUE, CAMERA_INITED_FALSE};
struct Camera{
    glm::vec3 m_position    = glm::vec3(4, 3, 3); // camera position in world space
    glm::vec3 m_direction   = glm::vec3(0, 0, 0); // where camera's looking at
    glm::vec3 m_up          = glm::vec3(0, 1, 0); // head orientation
    glm::vec3 m_right       = glm::vec3(1, 0, 0); // camera right
    float m_hAngle = 3.14f; // this is pi, who really cares
    float m_vAngle = 0.0f;
    int init();
    glm::mat4 getView();
    void update(float delta);
};

#endif //THELABYRINTH_CAMERA_H
