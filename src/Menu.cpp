#include "../include/Menu.h"

#include <raygui.h>

#include <format>

#include "../include/Constants.h"

const Difficulty& Menu::get_difficulty() const noexcept { return *diff; }

Game_State Menu::show() {
    using namespace Constants::Menu;

    static const auto title_sz = MeasureTextEx(GetFontDefault(), title, title_font_sz, 1.f);
    DrawText(title, (WINDOW_SIZE - title_sz.x) / 2, WINDOW_SIZE * 0.15, title_font_sz, RAYWHITE);

    this->diff = Difficulty::draw_slider(slider_rect);

    return GuiButton(bttn_rect, "PLAY") ? Game_State::Game_Continued : Game_State::Menu;
}

Game_State Menu::end_game(Game_State gs) const {
    using namespace Constants::Menu;

    const auto title = std::format("Game {}!", (gs == Game_State::Game_Won ? "won" : "over"));
    const auto title_sz = MeasureTextEx(GetFontDefault(), title.c_str(), title_font_sz, 1.f);
    DrawText(title.c_str(), (WINDOW_SIZE - title_sz.x) / 2, WINDOW_SIZE * 0.15, title_font_sz, RAYWHITE);

    return GuiButton(bttn_rect, "BACK TO MENU") ? Game_State::Menu : gs;
}
