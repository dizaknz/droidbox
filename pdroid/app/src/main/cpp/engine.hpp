#ifndef _PADDLE_DROID_ENGINE_HPP
#define _PADDLE_DROID_ENGINE_HPP

#include <android_native_app_glue.h>

#include "log.hpp"
#include "display.hpp"
#include "blocks.hpp"

class Engine {
    private:
	    android_app *m_app;
        Display m_display;
        /*
        float m_touchX;
        float m_touchY;
        float m_playerX;
        float m_playerY;
        float m_ballX;
        float m_ballY;
        float m_ballVelocityX;
        float m_ballVelocityY;
	    bool m_touchIsDown;
        */
        bool m_active;
        Blocks m_blocks;

    public:
        Engine(android_app *app) : m_app{app} {};
        int Init();
        void InitBlocks();
        void Close();
        bool Active();
};

bool Engine::Active() {
    return m_active;
}

int Engine::Init() {
    int ret = m_display.Init(m_app);
    if (ret != 0) {
        return ret;
    }
    InitBlocks();
    m_active = true;

    return ret;
}

void Engine::InitBlocks() {
    // randomize
    // m_blocks.Clear();
    // m_blocks.Init(x1, y1, x2, y2, width, height, gap);
}

void Engine::Close() {
    m_display.Close();
}

#endif
