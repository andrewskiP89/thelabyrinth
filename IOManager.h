//
// Created by andreaporru on 01/01/22.
//

#ifndef THELABYRINTH_IOMANAGER_H
#define THELABYRINTH_IOMANAGER_H
#include "Libraries.h"
#include "StandardHeaders.h"
#include "Renderer.h"
#include "Camera.h"

enum KeyBoard{ KEY_UP,
                 KEY_RIGHT,
                 KEY_DOWN,
                 KEY_LEFT
                };

enum Mouse{
    MOUSE_X,
    MOUSE_Y
};

enum Commands{
    MOUSE_INPUT,
    ARROW_INPUT
};
struct InputEvent{
    ~InputEvent();
    int m_command;
    size_t m_key;
    bool m_isPressed;
    bool m_isReleased;
    int m_button;
    bool isClick;
    glm::vec2 m_Mouseposition;
};

//struct KeyBoardInput : InputEvent{
////    size_t m_key;
////    bool m_isPressed;
////    bool m_isReleased;
//};

//struct MouseInput : InputEvent{
//    bool m_isClick;
//    int m_button;
//    glm::vec2 m_mouseSpeed;
//};
struct CommandSubscriber{
    virtual void handleInput(const InputEvent &input, float delta);
};

struct Command {
    // subscribers can be added or removed, such a gun
    // or a usable item
    std::vector<CommandSubscriber*> m_subscribers;
    Command();
    void subscribe(CommandSubscriber *subscriber);
    virtual void execute(const InputEvent &input, float delta);
};

struct InputManager{
    Command *m_commands[ARROW_INPUT + 1];
    vec2i m_mousePosition;
    vec2i m_oldMousePosition; // needed?
    Window m_window;
    InputEvent m_currentEvent;
    void init(Window &window);
    void registerHandler(int command, CommandSubscriber * subscriber);
    void handleInput(float delta);
    void generateCommand();
    vec2i getMousePosition() const;

    void resetMouse();
};

#endif //THELABYRINTH_IOMANAGER_H
