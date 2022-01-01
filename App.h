//
// Created by andreaporru on 28/12/21.
//

#ifndef THELABYRINTH_APP_H
#define THELABYRINTH_APP_H

#include "Renderer.h"
#include "Constants.h"

struct App{
    Window m_appWindow;
    int init();
    void run();
    void exit();
};
#endif //THELABYRINTH_APP_H
