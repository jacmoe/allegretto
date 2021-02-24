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

    pixelator->fill(al_map_rgba(255, 0, 0, 255));

    pixelator->drawCircle(Vector2i(30, 30), 20, al_map_rgba(0, 0, 255, 255));

    return true;
}

bool Game::OnUserUpdate(double deltaTime)
{
    return true;
}

bool Game::OnUserRender()
{
    m_pixelator.get()->randomize();
    return true;
}

bool Game::OnUserDestroy()
{
    return true;
}
