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



    //std::unique_ptr<ALLEGRO_TIMER, utility::ALDeleter> timer;
    //std::unique_ptr<ALLEGRO_EVENT_QUEUE, utility::ALDeleter> queue;
    //std::unique_ptr<ALLEGRO_DISPLAY, utility::ALDeleter> disp;
    //std::unique_ptr<ALLEGRO_FONT, utility::ALDeleter> font;
    //std::unique_ptr<ALLEGRO_BITMAP, utility::ALDeleter> mysha;

    //timer.reset(al_create_timer(1.0 / 30.0));
    //if (!timer.get())
    //{
    //    printf("couldn't initialize timer\n");
    //    return 1;
    //}

    //queue.reset(al_create_event_queue());
    //if (!queue.get())
    //{
    //    printf("couldn't initialize queue\n");
    //    return 1;
    //}

    //disp.reset(al_create_display(640, 480));
    //if (!disp.get())
    //{
    //    printf("couldn't initialize display\n");
    //    return 1;
    //}

    //font.reset(al_create_builtin_font());
    //if (!font.get())
    //{
    //    printf("couldn't initialize font\n");
    //    return 1;
    //}

    //if (!al_init_image_addon())
    //{
    //    printf("couldn't initialize image addon\n");
    //    return 1;
    //}

    //mysha.reset(al_load_bitmap("assets/textures/mysha.png"));
    //if (!mysha.get())
    //{
    //    printf("couldn't load mysha\n");
    //    return 1;
    //}

    //al_register_event_source(queue.get(), al_get_keyboard_event_source());
    //al_register_event_source(queue.get(), al_get_display_event_source(disp.get()));
    //al_register_event_source(queue.get(), al_get_timer_event_source(timer.get()));

    //bool done = false;
    //bool redraw = true;
    //ALLEGRO_EVENT event;

    //al_start_timer(timer.get());
    //while (1)
    //{
    //    al_wait_for_event(queue.get(), &event);

    //    switch (event.type)
    //    {
    //    case ALLEGRO_EVENT_TIMER:
    //        // game logic goes here.
    //        redraw = true;
    //        break;

    //    case ALLEGRO_EVENT_KEY_DOWN:
    //    case ALLEGRO_EVENT_DISPLAY_CLOSE:
    //        done = true;
    //        break;
    //    }

    //    if (done)
    //        break;

    //    if (redraw && al_is_event_queue_empty(queue.get()))
    //    {
    //        al_clear_to_color(al_map_rgb(0, 0, 0));
    //        al_draw_text(font.get(), al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
    //        al_draw_bitmap(mysha.get(), 100, 100, 0);
    //        al_flip_display();

    //        redraw = false;
    //    }
    //}

    ////al_destroy_bitmap(mysha);
    ////al_destroy_font(font);
    ////al_destroy_display(disp);
    ////al_destroy_timer(timer);
    ////al_destroy_event_queue(queue);

    Game game;

    if (game.init("Allegretto", 320, 200, 2, false))
    {
        game.run();
    }

    utility::closeConsoleWindow();

    return 0;
}
