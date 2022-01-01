//
// Created by andreaporru on 30/12/21.
//
#include "Camera.h"

glm::mat4 Camera::getView(){
    return glm::lookAt(m_position, m_direction, m_up);
}
int Camera::init() {
    return CAMERA_INITED_TRUE;
}

void Camera::update(float delta) {
    // do nothing, for now
}


