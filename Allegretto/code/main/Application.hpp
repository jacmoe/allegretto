/*# This file is part of the
#  █████╗ ██╗     ██╗     ███████╗ ██████╗ ██████╗ ███████╗████████╗████████╗ ██████╗ 
# ██╔══██╗██║     ██║     ██╔════╝██╔════╝ ██╔══██╗██╔════╝╚══██╔══╝╚══██╔══╝██╔═══██╗
# ███████║██║     ██║     █████╗  ██║  ███╗██████╔╝█████╗     ██║      ██║   ██║   ██║
# ██╔══██║██║     ██║     ██╔══╝  ██║   ██║██╔══██╗██╔══╝     ██║      ██║   ██║   ██║
# ██║  ██║███████╗███████╗███████╗╚██████╔╝██║  ██║███████╗   ██║      ██║   ╚██████╔╝
# ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝   ╚═╝      ╚═╝    ╚═════╝ 
#   project
#
#   https://github.com/jacmoe/allegretto
#
#   (c) 2021 Jacob Moena
#
#   MIT License
#*/
#pragma once
#include <string>
#include <vector>
#include <memory>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include <spdlog/spdlog.h>

#include "utility/ALDeleter.hpp"


class Application
{
public:
    Application();
    virtual ~Application();

    bool init(const std::string title, int width, int height, float scale = 1.0f, const bool fullscreen = false);
    void run();

protected:
    virtual bool OnUserCreate() { return true; }
    virtual bool OnUserUpdate(double fDeltaTime) { return true; }
    virtual bool OnUserRender() { return true; }
    virtual bool OnUserDestroy() { return  true; }

    float m_scale;
    int m_width;
    int m_height;
    bool m_fullscreen;
    bool m_show_map;
    bool m_show_fps;
    float m_average_fps;

    std::string font_name;
    int font_size;

    std::unique_ptr<ALLEGRO_TIMER, utility::ALDeleter> m_timer;
    std::unique_ptr<ALLEGRO_EVENT_QUEUE, utility::ALDeleter> m_queue;
    std::unique_ptr<ALLEGRO_DISPLAY, utility::ALDeleter> m_display;
    std::unique_ptr<ALLEGRO_FONT, utility::ALDeleter> m_font;
    std::unique_ptr<ALLEGRO_BITMAP, utility::ALDeleter> m_display_buffer;
    ALLEGRO_LOCKED_REGION* m_screenlock;

private:
    std::string m_title;
    bool m_running;
    bool m_should_exit;

    ALLEGRO_EVENT m_event;

    void event();
    void render();
};
