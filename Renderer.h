//
// Created by andreaporru on 28/12/21.
//

#ifndef THELABYRINTH_RENDERER_H
#define THELABYRINTH_RENDERER_H

#include "Libraries.h"
#include "StandardHeaders.h"
#include "Constants.h"
#include "ShadersManager.h"
#include "Camera.h"
#include "Shapes.h"


enum INIT_STATUS {INITED_FALSE, INITED_TRUE};

struct Window{
    Camera m_camera;
    GLFWwindow* m_window;
    int init();
    void update(float delta);
    void display();
    bool quitting() const;
    void exit() const;
    vec2i const getCenter();
    Camera& getCamera();
    glm::mat4 getProjection(bool ortho = false);
};
#endif //THELABYRINTH_RENDERER_H
