#pragma once

#include <cstdint>
#include <raylib.h>

struct Difficulty {
   private:
    constexpr static auto get_difficulties() noexcept;

   public:
    constexpr Difficulty(const char* name, uint8_t w, uint8_t h, uint8_t mines);
    static const Difficulty* draw_slider(Rectangle rect);

    const char* str;
    uint8_t w, h, mines;
};