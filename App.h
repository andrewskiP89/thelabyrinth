//
// Created by andreaporru on 28/12/21.
//

#ifndef THELABYRINTH_APP_H
#define THELABYRINTH_APP_H

#include "Renderer.h"
#include "IOManager.h"
#include "Constants.h"

#define MOUSE_SPEED 0.08f
#define CAMERA_SPEED 1.5f
struct CameraInputHandler : CommandSubscriber {
    CameraInputHandler(Camera &camera);
    vec2i m_screenCenter;
    Camera &m_camera;
    void handleInput(const InputEvent &input, float delta) override;
};

struct App{
    Window m_appWindow;
    InputManager m_inputManager;
    int init();
    void run();
    void update(float delta);
    void exit();

};
static Window const GetWindow();
#endif //THELABYRINTH_APP_H
