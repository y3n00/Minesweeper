#include "../include/Menu.h"

#include <raygui.h>

#include "../include/Constants.h"
const Difficulty& Menu::get_diff() const noexcept { return *diff; }

void Menu::lose() {}

Game_State Menu::show() {
    using namespace Constants::Menu;

    static const auto title_sz = MeasureTextEx(GetFontDefault(), title, title_font_sz, 1.f);
    DrawText(title, (WINDOW_SIZE - title_sz.x) / 2, WINDOW_SIZE * 0.15, title_font_sz, RAYWHITE);

    this->diff = Difficulty::draw_slider(slider_rect);

    return GuiButton(bttn_rect, "PLAY") ? Game_State::Game_Started : Game_State::Menu;
}
