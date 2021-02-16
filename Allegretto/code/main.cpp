#include <stdio.h>
#include <memory>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "utility/ALDeleter.hpp"

int main(int argc, char** argv)
{
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return 1;
    }

    if (!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        return 1;
    }

    std::unique_ptr<ALLEGRO_TIMER, utility::ALDeleter> timer;
    std::unique_ptr<ALLEGRO_EVENT_QUEUE, utility::ALDeleter> queue;
    std::unique_ptr<ALLEGRO_DISPLAY, utility::ALDeleter> disp;
    std::unique_ptr<ALLEGRO_FONT, utility::ALDeleter> font;
    std::unique_ptr<ALLEGRO_BITMAP, utility::ALDeleter> mysha;

    timer.reset(al_create_timer(1.0 / 30.0));
    if (!timer.get())
    {
        printf("couldn't initialize timer\n");
        return 1;
    }

    queue.reset(al_create_event_queue());
    if (!queue.get())
    {
        printf("couldn't initialize queue\n");
        return 1;
    }

    disp.reset(al_create_display(640, 480));
    if (!disp.get())
    {
        printf("couldn't initialize display\n");
        return 1;
    }

    font.reset(al_create_builtin_font());
    if (!font.get())
    {
        printf("couldn't initialize font\n");
        return 1;
    }

    if (!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return 1;
    }

    mysha.reset(al_load_bitmap("assets/textures/mysha.png"));
    if (!mysha.get())
    {
        printf("couldn't load mysha\n");
        return 1;
    }

    al_register_event_source(queue.get(), al_get_keyboard_event_source());
    al_register_event_source(queue.get(), al_get_display_event_source(disp.get()));
    al_register_event_source(queue.get(), al_get_timer_event_source(timer.get()));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer.get());
    while (1)
    {
        al_wait_for_event(queue.get(), &event);

        switch (event.type)
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

        if (redraw && al_is_event_queue_empty(queue.get()))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font.get(), al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
            al_draw_bitmap(mysha.get(), 100, 100, 0);
            al_flip_display();

            redraw = false;
        }
    }

    //al_destroy_bitmap(mysha);
    //al_destroy_font(font);
    //al_destroy_display(disp);
    //al_destroy_timer(timer);
    //al_destroy_event_queue(queue);

    return 0;
}
