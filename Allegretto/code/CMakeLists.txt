# This file is part of the
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
#
set(TARGET_NAME allegretto)

set(main
    ./main/Application.cpp
    ./main/Application.hpp
    ./main/Game.cpp
    ./main/Game.hpp
    ./main/Pixelator.cpp
    ./main/Pixelator.hpp
)

set(utility
    ./utility/dbg_console.cpp
    ./utility/dbg_console.hpp
    ./utility/ALDeleter.hpp
    ./utility/utils.cpp
    ./utility/utils.hpp
)

add_executable(${TARGET_NAME}
    ./main.cpp
    ${main}
    ${utility}
)

target_link_libraries(${TARGET_NAME} ${ALLEGRO_LIBRARIES})

