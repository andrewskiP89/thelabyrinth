//
// Created by andreaporru on 01/01/22.
//

#ifndef THELABYRINTH_IOMANAGER_H
#define THELABYRINTH_IOMANAGER_H
#include "Libraries.h"
#include "StandardHeaders.h"
enum KeyBoard{ KEY_UP,
                 KEY_RIGhT,
                 KEY_DOWN,
                 KEY_LEFT
                };
enum Mouse{
    MOUSE_X,
    MOUSE_Y
};
struct InputInfo{

};

struct KeyBoardInput : InputInfo{
    size_t m_key;
    bool m_isPressed;
    bool m_isReleased;
};

struct MouseInput : InputInfo{
    bool m_isClick;
    glm::vec2 m_isPosition;
};
struct CommandSubscriber{
    virtual void handleInput(InputInfo* input);

};

struct Command {
    std::vector<CommandSubscriber*> m_subscribers;
    Command();
    void subscribe(CommandSubscriber *subscriber);
    virtual void execute(InputInfo *input);
};


struct InputManager{
    void handleInput(float delta);
};

Command::Command() {
    m_subscribers = {};
}

void Command::subscribe(CommandSubscriber *subscriber) {
    m_subscribers.push_back(subscriber);
}

void Command::execute(InputInfo *input) {
    for(auto sub : m_subscribers){
        sub->handleInput(input);
    }
}

#endif //THELABYRINTH_IOMANAGER_H
