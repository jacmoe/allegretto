#include <stdio.h>
#include <memory>
#include <filesystem>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "utility/utils.hpp"
#include "utility/dbg_console.hpp"
#include "main/Game.hpp"


void setup_working_directory()
{
    // Get executable path
    std::string path = std::filesystem::current_path().generic_string();
    // Remove the build directory, so that we land on appropriate directory for asset loading
    std::vector<std::string> strList;
    strList.push_back("/build/code");
    strList.push_back("/vsbuild/code");
    strList.push_back("Release");
    strList.push_back("RelWithDebInfo");
    strList.push_back("Debug");
    utility::eraseSubStrings(path, strList);
    // Set a proper working directory
    std::filesystem::current_path(path);
}

void setup_logging()
{
    std::shared_ptr<spdlog::logger> m_pxllogger;

    std::string logfile_name = "log/pxllog.txt";

    // Remove old log file
    if (std::filesystem::exists(logfile_name))
    {
        std::remove(logfile_name.c_str());
    }

    // Create console sink and file sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfile_name, true);
    spdlog::sinks_init_list sink_list = { file_sink, console_sink };
    // Make the logger use both the console and the file sink
    m_pxllogger = std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({ console_sink, file_sink }));
    // Set the standard logger so that we can use it freely everywhere
    spdlog::set_default_logger(m_pxllogger);
    // Set the format pattern - [Loglevel] [Function] [Line] message
    spdlog::set_pattern("[%l] [%!] [line %#] %v");
}

int main(int argc, char** argv)
{
    setup_working_directory();
    utility::createConsoleWindow();
    setup_logging();

    SPDLOG_INFO("PixelWolf initializing.");

    Game game;

    if (game.init("Allegretto", 320, 200, 2, false))
    {
        game.run();
    }

    utility::closeConsoleWindow();

    return 0;
}
