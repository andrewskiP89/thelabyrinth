//
// Created by andreaporru on 01/01/22.
//

#include "IOManager.h"

static const int GLFW_KEYS_TO_CHECK [4] = {
        GLFW_KEY_UP,
        GLFW_KEY_RIGHT,
        GLFW_KEY_DOWN,
        GLFW_KEY_LEFT
};

void CommandSubscriber::handleInput(const InputEvent &input , float delta) {}

void InputManager::init(Window &window) {
    m_window = window;
    m_mousePosition = m_oldMousePosition = m_window.getCenter();
    resetMouse();
    // initing commands
    m_commands[MOUSE_INPUT] = new Command();
    m_commands[ARROW_INPUT] = new Command();

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(m_window.m_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPos(m_window.m_window, m_window.getCenter().x, m_window.getCenter().y);
    // Hide the mouse and enable unlimited movement
    //glfwSetInputMode(m_window.m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();

}

void InputManager::resetMouse() {
    vec2i center = m_window.getCenter();
    // set mouse to the center
    glfwSetCursorPos(m_window.m_window, center.x, center.y);

}

void InputManager::handleInput(float delta) {
    // handling mouse position
    m_mousePosition = getMousePosition();
    InputEvent input;
    if(m_mousePosition != m_oldMousePosition){
        resetMouse();

        input.m_command = MOUSE_INPUT;
        input.m_Mouseposition = m_mousePosition;
        m_commands[MOUSE_INPUT]->execute(input, delta);
        m_oldMousePosition = m_mousePosition;
    }
    // handling keyboard mInput

    for(size_t key = 0; key <= KEY_LEFT; key++){

        if(glfwGetKey( m_window.m_window, GLFW_KEYS_TO_CHECK[key]) == GLFW_PRESS){

            input.m_command = ARROW_INPUT;
            input.m_key = key;
            input.m_isPressed = true;
            m_commands[ARROW_INPUT]->execute(input, delta);
        }
    }
    // we discard the event after processing
//   if(input != nullptr)
//        delete input;
}

vec2i InputManager::getMousePosition() const {
    double x, y;
    glfwGetCursorPos(m_window.m_window, &x, &y);
    vec2i mousePos = vec2i(floor(x), floor(y));
    return mousePos;
}

void InputManager::generateCommand() {

}

void InputManager::registerHandler(int command, CommandSubscriber *subscriber) {
    if(command <= ARROW_INPUT) {// @TODO find a best condition, which should not be changed upon command addition
        m_commands[command]->subscribe(subscriber);
    }
}

Command::Command() {
    m_subscribers = {};
}

void Command::subscribe(CommandSubscriber *subscriber) {
    m_subscribers.push_back(subscriber);
}

void Command::execute(const InputEvent &input, float delta) {
    for(auto sub : m_subscribers){
        sub->handleInput(input, delta);
    }
}

InputEvent::~InputEvent() {

}
