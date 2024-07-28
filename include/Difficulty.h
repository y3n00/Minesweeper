#pragma once

#include <raylib.h>

#include <cstdint>

struct Difficulty {
   private:
    [[nodiscard]] constexpr static auto get_difficulties() noexcept;

   public:
    constexpr Difficulty(const char* name, uint8_t w, uint8_t mines);
    [[nodiscard]] static const Difficulty* draw_slider(Rectangle rect);

    uint8_t w, mines;
    const char* str;
};