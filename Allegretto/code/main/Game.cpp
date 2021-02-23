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
#include "main/Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnUserCreate()
{
    return true;
}

bool Game::OnUserUpdate(double deltaTime)
{
    return true;
}

bool Game::OnUserRender()
{
    m_screenlock = al_lock_bitmap(m_display_buffer.get(), ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    for (int x = 0; x < m_width; ++x)
    {
        uint8_t* ptr = (uint8_t*)m_screenlock->data + (4 * x);
        for (int y = 0; y < m_height; ++y)
        {
            r = rand() * 255;
            g = rand() * 255;
            b = rand() * 255;
            a = rand() * 255;
            *((uint32_t*)ptr) = (b | (g << 8) | (r << 16) | (a << 24));

            ptr += m_screenlock->pitch;
        }
    }
    al_unlock_bitmap(m_display_buffer.get());

    return true;
}

bool Game::OnUserDestroy()
{
    return true;
}
