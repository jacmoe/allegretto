# This file is part of the
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
#
cmake_minimum_required(VERSION 3.7)

project(allegretto)

set(CMAKE_CXX_STANDARD 17)

set(3RD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Allegretto/3rdparty)
set(SPDLOG_INCLUDE_DIR ${3RD_PARTY_DIR}/spdlog/include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Allegro5 REQUIRED)

include_directories(
    ${ALLEGRO_INCLUDE_DIR}
    ${SPDLOG_INCLUDE_DIR}
    ./Allegretto/code
    ./Allegretto/code/main
    ./Allegretto/code/components
    ./Allegretto/code/systems
    ./Allegretto/code/utility
)

add_subdirectory(./Allegretto/code)
