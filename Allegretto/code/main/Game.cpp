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
    Pixelator* pixelator = m_pixelator.get();

    pixelator->fill(al_map_rgba(255, 255, 0, 255));
    //pixelator->randomize();

    pixelator->drawCircle(Vector2i(20, 20), 20, al_map_rgba(255, 0, 0, 255));

    return true;
}

bool Game::OnUserUpdate(double deltaTime)
{
    return true;
}

bool Game::OnUserRender()
{
    m_screenlock = al_lock_bitmap(m_display_buffer.get(), ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            ALLEGRO_COLOR color = m_pixelator.get()->getPixel(x, y);
            al_put_pixel(x, y, color);
        }
    }
    al_unlock_bitmap(m_display_buffer.get());

    return true;
}

bool Game::OnUserDestroy()
{
    return true;
}
