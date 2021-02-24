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

#include <allegro5/allegro5.h>
#include <string>
#include <vector>
#include <unordered_map>

struct Vector2i
{
    int x;
    int y;

    Vector2i(int x, int y);
    Vector2i() = default;
};

struct IntRect
{
    int left;
    int top;
    int width;
    int height;

    IntRect() = default;
    IntRect(int left, int top, int width, int height);
};

class Pixelator
{
public:
    Pixelator();

    void setSize(const Vector2i size);
    void setSize(const std::string& name, const Vector2i size);

    // Pixels
    void setPixel(unsigned int x, unsigned int y, const ALLEGRO_COLOR& color);
    void setPixel(const std::string& name, unsigned int x, unsigned int y, const ALLEGRO_COLOR& color);
    ALLEGRO_COLOR getPixel(unsigned int x, unsigned int y) const;
    ALLEGRO_COLOR getPixel(const std::string& name, unsigned int x, unsigned int y) const;
    const uint8_t* getPixelsPtr() const;
    const uint8_t* getPixelsPtr(const std::string& name) const;

    void drawColumn(unsigned int x, unsigned int y, unsigned int height, const ALLEGRO_COLOR& color);
    void drawColumn(const std::string& name, unsigned int x, unsigned int y, unsigned int height, const ALLEGRO_COLOR& color);
    void drawRow(unsigned int x, unsigned int y, unsigned int length, const ALLEGRO_COLOR& color);
    void drawRect(const IntRect rect, const ALLEGRO_COLOR& color);
    void drawFilledRect(const IntRect& rect, const ALLEGRO_COLOR& color);
    void drawFilledRect(const std::string& name, const IntRect& rect, const ALLEGRO_COLOR& color);
    void drawLine(const Vector2i& start, const Vector2i& end, const ALLEGRO_COLOR& color);
    void drawCircle(const Vector2i& coord, const int radius, const ALLEGRO_COLOR& color);

    void fill(ALLEGRO_COLOR color);
    void randomize();
    void clear();
    void clear(const std::string& name);

    // Buffers
    bool addBuffer(const std::string name);
    bool removeBuffer(const std::string name);
    void setActiveBuffer(const std::string name);
    const std::string getActiveBuffer() { return m_current_buffer; }
    unsigned int getNumberOfBuffers() const { return static_cast<unsigned int>(m_buffers.size()); }

    bool swapBuffer(const std::string name);

    // copy pixels from a source
    void copy(const std::string name, unsigned int x = 0, unsigned int y = 0, bool applyAlpha = false);
    void copy(const std::string name, unsigned int destX, unsigned int destY, const IntRect& sourceRect, bool applyAlpha = false);
    //void copy(const sf::Image& source, unsigned int destX, unsigned int destY, const IntRect& sourceRect, bool applyAlpha = false);
    void copy(const uint8_t* source_pixels, const Vector2i buffer_size, unsigned int destX, unsigned int destY, const IntRect& sourceRect, bool applyAlpha = false);

    // get the size (width and height) of a buffer
    IntRect getSize() { return getSize(m_current_buffer); }
    IntRect getSize(const std::string name);

private:
    std::string m_current_buffer;
    std::unordered_map<std::string, unsigned int> m_buffer_map;

    // buffers
    struct Buffer
    {
        Vector2i size;
        std::vector<uint8_t> pixels;
    };
    std::vector<Buffer> m_buffers;

};
