#pragma once

#include <raylib.h>

#include <array>
#include <cstdint>
#include <tuple>

constexpr static inline auto WINDOW_SIZE = 768;

using Enum_t = uint8_t;
enum class Cell_Type : Enum_t {
    Normal,
    Mine,
};

enum class Texture_ID : Enum_t {
    Flag,
    Mine
};

enum class Grid_Status : Enum_t {
    Good,
    Bad,
    Finished
};

enum class Mouse_Action : Enum_t {
    None,
    Reveal,
    Toggle_Flag,
};

enum class Game_State : Enum_t {
    Menu,
    Game_Started,
    Game_Lost,
    Game_Won,
};

#define CONSTANT(NAME, VALUE) \
    constexpr inline auto NAME = VALUE

namespace Constants {
    namespace Difficulty {
        CONSTANT(segment_size, 3.5f);
    }  // namespace Difficulty

    namespace Texture {
        CONSTANT(src_rect, Rectangle(0, 0, 28, 28));  // src texture size
        CONSTANT(origin, Vector2{});
        CONSTANT(rotation, 0.f);
    }  // namespace Texture

    namespace Mines_Colors {
        CONSTANT(colors, std::to_array<Color>({BLANK, GREEN, BLUE, RED, PURPLE, MAGENTA}));
    }

    namespace Grid {
        CONSTANT(active_params, std::tuple(PURPLE, 3.f));
        CONSTANT(inactive_params, std::tuple(LIGHTGRAY, 1.f));
        CONSTANT(revealed_color, DARKGRAY);
    }  // namespace Grid

    namespace Menu {
        CONSTANT(title, "Minesweeper");
        CONSTANT(title_font_sz, 52);
        /////////////////////////////////
        CONSTANT(half_screen, (WINDOW_SIZE / 2));
        CONSTANT(slider_w, (WINDOW_SIZE * 0.5f));
        CONSTANT(slider_h, (WINDOW_SIZE * 0.05f));
        CONSTANT(slider_rect, Rectangle((half_screen - slider_w / 2), half_screen - slider_h / 2, slider_w, slider_h));
        /////////////////////////////////
        CONSTANT(bttn_w, (WINDOW_SIZE * 0.4f));
        CONSTANT(bttn_h, (WINDOW_SIZE * 0.08f));
        CONSTANT(bttn_rect, Rectangle((WINDOW_SIZE - bttn_w) / 2, WINDOW_SIZE - bttn_h * 2, bttn_w, bttn_h));
    }  // namespace Menu
}  // namespace Constants
#undef CONSTANT