//
// Created by andreaporru on 28/12/21.
//
#include "App.h"

int App::init() {
    if(m_appWindow.init() != INITED_TRUE){
        return -1;
    }
    return 0;
}

void App::run() {
    while(!m_appWindow.quitting()){
        float delta;
        m_appWindow.update(delta);
        m_appWindow.display();
    }
}

void App::exit() {
    m_appWindow.exit();
}
