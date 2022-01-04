//
// Created by andreaporru on 28/12/21.
//
#include "App.h"


int App::init() {
    if(m_appWindow.init() != INITED_TRUE){
        return -1;
    }
    m_inputManager.init(m_appWindow);
    //Camera camera = m_appWindow.getCamera();
    // creating a command handler for moving camera by mouse and keyboard
    CameraInputHandler *cHandler = new CameraInputHandler(m_appWindow.getCamera());
    cHandler->m_screenCenter = m_appWindow.getCenter();
    m_inputManager.registerHandler(MOUSE_INPUT, cHandler);
    m_inputManager.registerHandler(ARROW_INPUT, cHandler);
    return 0;
}

void App::run() {
    // initing the window
    double lastTime = glfwGetTime();
    while(!m_appWindow.quitting()){
        float currentTime = glfwGetTime();
        float delta = float(currentTime - lastTime);
        m_inputManager.handleInput(delta);
        m_appWindow.update(delta);
        m_appWindow.display();

        glfwPollEvents();

        lastTime = currentTime;
    }
    // initing the io manager
    m_inputManager.init(m_appWindow);
}

void App::update(float delta){
    m_appWindow.update(delta);
}

void App::exit() {
    m_appWindow.exit();
}

CameraInputHandler::CameraInputHandler(Camera &camera) : m_camera(camera) {
    //m_camera = camera;
}

void CameraInputHandler::handleInput(const InputEvent &input, float delta) {
    std::cout << "Updating the camera\n";
    if(input.m_command == MOUSE_INPUT){
        // computing direction of the camera
        float hAngle, vAngle;
        vec2i cPosition = input.m_Mouseposition;
        m_camera.m_hAngle += MOUSE_SPEED * float(m_screenCenter.x - cPosition.x);
        m_camera.m_vAngle += MOUSE_SPEED * float(m_screenCenter.y - cPosition.y);
        // converting shperical to carthesian
        m_camera.m_direction = glm::vec3(
                    cos(m_camera.m_vAngle)  * sin(m_camera.m_hAngle),
                    sin(m_camera.m_vAngle),
                    cos(m_camera.m_vAngle) * cos(m_camera.m_hAngle)
                );
        // calculating the right vector to get the up direction
        m_camera.m_right = glm::vec3(
                sin(m_camera.m_hAngle - 3.14f/2.0f),
                0,
                cos(m_camera.m_hAngle - 3.14f/2.0f)
        );
        m_camera.m_up = glm::cross(m_camera.m_right,m_camera.m_direction);

    }else if(input.m_command == ARROW_INPUT){
        switch (input.m_key) {
            case KEY_UP:
                m_camera.m_position += m_camera.m_direction * delta * CAMERA_SPEED;
                break;
            case KEY_RIGHT:
                m_camera.m_position += m_camera.m_right * delta * CAMERA_SPEED;
                break;
            case KEY_DOWN:
                m_camera.m_position -= m_camera.m_direction * delta * CAMERA_SPEED;
                break;
            case KEY_LEFT:
                m_camera.m_position -= m_camera.m_right * delta * CAMERA_SPEED;
                break;
            default:
                break;
        }
    }
}

