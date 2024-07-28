
#include "../include/Difficulty.h"

#include <raygui.h>

#include "../include/Constants.h"

constexpr auto Difficulty::get_difficulties() noexcept {
    return std::to_array<Difficulty>({
        {"Easy", 10, 10},
        {"Medium", 16, 40},
        {"Hard", 30, 99},
    });
}

constexpr Difficulty::Difficulty(const char* name, uint8_t w, uint8_t mines)
    : str(name), w(w), mines(mines) {}

const Difficulty* Difficulty::draw_slider(Rectangle rect) {
    using namespace Constants::Difficulty;
    static const auto diffs = get_difficulties();
    const auto slider_max = segment_size * diffs.size() - 1;

    static float slider_value = 0.0f;
    GuiSlider(rect, "Select difficulty", NULL, &slider_value, 0, slider_max);
    auto&& diff = diffs[static_cast<size_t>(slider_value / segment_size)];

    const auto& [x, y, w, h] = rect;
    const auto font_size = h * 0.5f;
    const auto [text_w, text_h] = MeasureTextEx(GetFontDefault(), diff.str, font_size, 1.f);
    const auto text_pos = Vector2{x + (w - text_w) / 2, y + (h - text_h) / 2};
    DrawTextEx(GetFontDefault(), diff.str, text_pos, font_size, 1.f, RAYWHITE);  // draw current difficulty on slider

    return &diff;
}
