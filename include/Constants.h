#pragma once

#include <raylib.h>

#include <array>
#include <cstdint>
#include <tuple>

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

#define MAKE_CONSTANT(NAME, VALUE) \
    constexpr static inline auto NAME = VALUE

MAKE_CONSTANT(WINDOW_SIZE, 768);

namespace Constants {
    MAKE_CONSTANT(window_title, "Raylib Minesweeper");
    MAKE_CONSTANT(main_bg_color, Color(50, 50, 50, 255));

    namespace Difficulty {
        MAKE_CONSTANT(segment_size, 3.5f);
    }  // namespace Difficulty

    namespace Texture {
        MAKE_CONSTANT(src_rect, Rectangle(0, 0, 28, 28));  // src texture size
        MAKE_CONSTANT(origin, Vector2{});
        MAKE_CONSTANT(rotation, 0.f);
    }  // namespace Texture

    namespace Mines_Colors {
        MAKE_CONSTANT(colors, std::to_array<Color>({BLANK, GREEN, BLUE, RED, PURPLE, MAGENTA}));
    }

    namespace Grid {
        MAKE_CONSTANT(active_params, std::tuple(PURPLE, 3.f));
        MAKE_CONSTANT(inactive_params, std::tuple(LIGHTGRAY, 1.f));
        MAKE_CONSTANT(revealed_color, DARKGRAY);
    }  // namespace Grid

    namespace Menu {
        MAKE_CONSTANT(title, "Minesweeper");
        MAKE_CONSTANT(title_font_sz, 52);
        /////////////////////////////////
        MAKE_CONSTANT(half_screen, (WINDOW_SIZE / 2));
        MAKE_CONSTANT(slider_w, (WINDOW_SIZE * 0.5f));
        MAKE_CONSTANT(slider_h, (WINDOW_SIZE * 0.05f));
        MAKE_CONSTANT(slider_rect, Rectangle((half_screen - slider_w / 2), half_screen - slider_h / 2, slider_w, slider_h));
        /////////////////////////////////
        MAKE_CONSTANT(bttn_w, (WINDOW_SIZE * 0.4f));
        MAKE_CONSTANT(bttn_h, (WINDOW_SIZE * 0.08f));
        MAKE_CONSTANT(bttn_rect, Rectangle((WINDOW_SIZE - bttn_w) / 2, WINDOW_SIZE - bttn_h * 2, bttn_w, bttn_h));
    }  // namespace Menu
}  // namespace Constants
#undef MAKE_CONSTANT