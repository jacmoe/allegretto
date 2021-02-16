/*# This file is part of the
# ██████╗ ██╗  ██╗██╗     ██╗    ██╗ ██████╗ ██╗     ███████╗
# ██╔══██╗╚██╗██╔╝██║     ██║    ██║██╔═══██╗██║     ██╔════╝
# ██████╔╝ ╚███╔╝ ██║     ██║ █╗ ██║██║   ██║██║     █████╗  
# ██╔═══╝  ██╔██╗ ██║     ██║███╗██║██║   ██║██║     ██╔══╝  
# ██║     ██╔╝ ██╗███████╗╚███╔███╔╝╚██████╔╝███████╗██║     
# ╚═╝     ╚═╝  ╚═╝╚══════╝ ╚══╝╚══╝  ╚═════╝ ╚══════╝╚═╝     
#   project
#
#   https://github.com/jacmoe/pxlwolf
#
#   (c) 2020 - 2021 Jacob Moena
#
#   MIT License
#*/
#include "Application.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

Application::Application()
    : m_scale(0)
    , m_width(0)
    , m_height(0)
    , m_fullscreen(false)
    , m_show_map(false)
    , m_title("")
    , m_running(false)
    , m_show_fps(false)
    , m_should_exit(false)
    , font_name("assets/fonts/MedievalSharp-Bold.ttf")
    , font_size(12)
{}

Application::~Application()
{
    SPDLOG_INFO("PixelWolf shutdown.");
}

bool Application::init(const std::string title, int width, int height, float scale, const bool fullscreen)
{
    m_width = width;
    m_height = height;
    m_scale = scale;
    m_title = title;
    m_fullscreen = fullscreen;

    if (!al_init())
    {
        SPDLOG_ERROR("Couldn't initialize allegro");
        return false;
    }

    if (!al_install_keyboard())
    {
        SPDLOG_ERROR("Couldn't initialize keyboard");
        return false;
    }

    m_timer.reset(al_create_timer(1.0 / 30.0));
    if (!m_timer.get())
    {
        printf("couldn't initialize timer\n");
        return 1;
    }

    m_queue.reset(al_create_event_queue());
    if (!m_queue.get())
    {
        printf("couldn't initialize queue\n");
        return 1;
    }

    m_display.reset(al_create_display(m_width, m_height));
    if (!m_display.get())
    {
        printf("couldn't initialize display\n");
        return 1;
    }

    m_font.reset(al_create_builtin_font());
    if (!m_font.get())
    {
        printf("couldn't initialize font\n");
        return 1;
    }

    if (!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return 1;
    }

    m_mysha.reset(al_load_bitmap("assets/textures/mysha.png"));
    if (!m_mysha.get())
    {
        printf("couldn't load mysha\n");
        return 1;
    }

    al_register_event_source(m_queue.get(), al_get_keyboard_event_source());
    al_register_event_source(m_queue.get(), al_get_display_event_source(m_display.get()));
    al_register_event_source(m_queue.get(), al_get_timer_event_source(m_timer.get()));

    SPDLOG_INFO("PixelWolf initialized.");
    return true;
}

void Application::run()
{
    bool done = false;
    bool redraw = true;

    al_start_timer(m_timer.get());
    while (1)
    {
        al_wait_for_event(m_queue.get(), &m_event);

        switch (m_event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // game logic goes here.
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(m_queue.get()))
        {
            render();
            redraw = false;
        }
    }
}

void Application::event()
{
}

void Application::render()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(m_font.get(), al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
    al_draw_bitmap(m_mysha.get(), 100, 100, 0);
    al_flip_display();
}
