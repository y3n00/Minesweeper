#define _CRT_SECURE_NO_WARNINGS
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <algorithm>
#include <cassert>
#include <format>
#include <numeric>
#include <print>
#include <queue>
#include <ranges>
#include <set>
#include <string>
#include <vector>

#include "random.hpp"
#include "timer.hpp"

// todo list :
// menu win and lose windows

constexpr static auto WINDOW_SIZE = 800;

enum class Game_State : uint8_t {
    Menu,
    Game_Started,
    Game_Lost,
    Game_Won,
};

enum class Cell_Type : uint8_t {
    Normal,
    Mine,
};

enum class Mouse_Action : uint8_t {
    None,
    Reveal,
    Toggle_Flag,
};

enum class Grid_Status : uint8_t {
    Good,
    Bad,
    Finished
};

enum class Texture_ID : uint8_t {
    Flag,
    Mine
};

static inline auto get_texture(Texture_ID texture_id) {
    static const auto flag = LoadTexture("textures/flag.png");
    static const auto mine = LoadTexture("textures/mine.png");

    switch (texture_id) {
        case Texture_ID::Flag:
            return flag;
        case Texture_ID::Mine:
            return mine;
        default:
            std::unreachable();
    }
}

static auto draw_texture(Texture_ID texture_id, Rectangle params) {
    constexpr static auto src_rect = Rectangle{0, 0, 28, 28};  // src texture size
    constexpr static auto origin = Vector2{};
    constexpr static auto rotation = 0.f;

    const auto& [x, y, sz, _] = params;
    const auto new_sz = sz * 0.5f;

    const auto offset = (sz - new_sz) / 2;
    const auto dst_rect = Rectangle{x + offset, y + offset, new_sz, new_sz};

    DrawTexturePro(get_texture(texture_id), src_rect, dst_rect, origin, rotation, WHITE);
}

static auto draw_mines_around(uint32_t mines_count, Rectangle params) {
    constexpr static auto colors = std::to_array<Color>({BLANK, GREEN, BLUE, RED, PURPLE, MAGENTA});
    const auto& [x, y, sz, _] = params;
    const auto font_sz = sz * 0.8f;

    const auto as_str = std::to_string(mines_count);
    const auto text_width = MeasureText(as_str.c_str(), font_sz);
    const auto half_sz = sz / 2.f, half_font_sz = font_sz / 2.f, half_text_width = text_width / 2.f;

    DrawText(as_str.c_str(), x + half_sz - half_text_width, y + half_sz - half_font_sz, font_sz, colors[mines_count]);
}

struct Mouse_Wrapper {
    inline auto update() {
        pos = GetMousePosition();
        action = []() -> Mouse_Action {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                return Mouse_Action::Reveal;
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
                return Mouse_Action::Toggle_Flag;
            return Mouse_Action::None;
        }();
    }

    Mouse_Action action;
    Vector2 pos;
};

struct Cell {  // TODO: REFACTOR
    inline auto is_mine() const { return type == Cell_Type::Mine; }
    inline auto is_revealed() const { return revealed; }
    inline auto is_flagged() const { return flagged; }

    inline auto reveal() { revealed = true; }
    inline auto toggle_flag() {
        if (!revealed)
            flagged = !flagged;
    }

    bool flagged = false, revealed = false;
    uint8_t mines_around = 0;
    Cell_Type type = Cell_Type::Normal;
    Texture2D texture;
};

class Menu {
   private:
    struct Difficulty {
       private:
        constexpr static auto get_difficulties() noexcept {
            return std::to_array<Difficulty>({
                {"Easy", 10, 10, 10},
                {"Medium", 16, 16, 40},
                {"Hard", 30, 16, 99},
            });
        }

       public:
        const char* str;
        uint8_t w, h, mines;

        Difficulty() = default;

        constexpr Difficulty(const char* name, uint8_t w, uint8_t h, uint8_t mines)
            : str(name), w(w), h(h), mines(mines) {}

        static auto draw_slider(Rectangle rect) {
            constexpr static auto single_segment_range = 3.5f;
            static const auto diffs = get_difficulties();
            const auto slider_max = single_segment_range * diffs.size() - 1;

            static float slider_value = 0.0f;
            GuiSlider(rect, "Select difficulty", NULL, &slider_value, 0, slider_max);
            auto&& diff = diffs[static_cast<size_t>(slider_value / single_segment_range)];

            const auto& [x, y, w, h] = rect;
            const auto font_size = h * 0.5f;
            const auto [text_w, text_h] = MeasureTextEx(GetFontDefault(), diff.str, font_size, 1.f);
            const auto text_pos = Vector2{x + (w - text_w) / 2, y + (h - text_h) / 2};
            DrawTextEx(GetFontDefault(), diff.str, text_pos, font_size, 1.f, RAYWHITE);  // draw current difficulty on slider

            return &diff;
        }
    };

    const Difficulty* diff = nullptr;

   public:
    inline auto show() {
        constexpr static auto title = "Minesweeper";
        constexpr static auto title_font_sz = 52;
        static const auto title_sz = MeasureTextEx(GetFontDefault(), title, title_font_sz, 1.f);
        DrawText(title, (WINDOW_SIZE - title_sz.x) / 2, WINDOW_SIZE * 0.15, title_font_sz, RAYWHITE);

        constexpr static auto half_screen = WINDOW_SIZE / 2.f,
                              rect_w = WINDOW_SIZE * 0.5f,
                              rect_h = WINDOW_SIZE * 0.05f;

        constexpr static auto slider_rect = Rectangle{(half_screen - rect_w / 2), half_screen - rect_h / 2, rect_w, rect_h};
        this->diff = Difficulty::draw_slider(slider_rect);

        constexpr static auto bttn_w = WINDOW_SIZE * 0.4f, bttn_h = WINDOW_SIZE * 0.08f;
        constexpr static auto play_bttn_rect = Rectangle{(WINDOW_SIZE - bttn_w) / 2, WINDOW_SIZE - bttn_h * 2, bttn_w, bttn_h};

        return GuiButton(play_bttn_rect, "PLAY") ? Game_State::Game_Started : Game_State::Menu;
    }

    inline auto win(const auto& timer) {}

    inline auto lose() {}

    const auto& get_diff() const noexcept { return *diff; }
};

class MinesweeperGrid {
    using Num_Type = uint32_t;

   public:
    MinesweeperGrid(Num_Type width, Num_Type height, Num_Type mines_num)
        : width{width}, height{height}, cell_size{static_cast<float>(WINDOW_SIZE) / std::max(width, height)} {
        const auto total_sz = width * height;

        static Random_t<Num_Type> mines_rand;
        cells.resize(total_sz);

        while (mines.size() != mines_num)  // fill set of unique positions
            mines.insert(mines_rand.get(0, total_sz - 1));

        for (auto&& unique : mines) {
            cells[unique].type = Cell_Type::Mine;
            loop_over_neighbors(unique, [](Cell& cell) { ++cell.mines_around; });
        }
        grid_timer.start();
    }

    auto update_input(Mouse_Wrapper mouse) {
        const auto idx = idx_from_pos(mouse.pos);
        auto& selected_cell = cells[idx];
        switch (mouse.action) {
            case Mouse_Action::Reveal:
                reveal_cell(idx);
                break;
            case Mouse_Action::Toggle_Flag:
                selected_cell.toggle_flag();
                break;
            case Mouse_Action::None:
                break;
            default:
                std::unreachable();
        }
        return idx;
    }

    auto update_status() {
        auto&& revealed = cells | std::views::filter([](auto&& cell) -> bool { return cell.is_revealed(); });
        const auto revealed_sz = std::ranges::distance(revealed.begin(), revealed.end());
        auto&& flagged = [this](auto&& cell_idx) { return cells[cell_idx].is_flagged(); };

        if (std::ranges::any_of(revealed, [](auto&& cell) { return cell.is_mine(); }))  // if any mine is revealed
            return Grid_Status::Bad;

        if (cells.size() - revealed_sz == mines.size() || std::ranges::all_of(mines, flagged)) {
            grid_timer.stop();
            return Grid_Status::Finished;
        }

        return Grid_Status::Good;
    }

    auto draw(Num_Type cell_idx) {
        constexpr static auto active_params = std::tuple(PURPLE, 3.f), inactive_params = std::tuple(LIGHTGRAY, 1.f);
        constexpr static auto revealed_color = DARKGRAY;

        for (auto&& [idx, cell] : cells | std::views::enumerate) {
            const auto [x, y] = pos_from_idx(idx);
            const auto rect = Rectangle(x * cell_size, y * cell_size, cell_size, cell_size);

            if (cell.is_revealed()) {
                DrawRectangleRec(rect, revealed_color);

                switch (cell.type) {
                    case Cell_Type::Mine:
                        draw_texture(Texture_ID::Mine, rect);
                        break;
                    case Cell_Type::Normal:
                        draw_mines_around(cell.mines_around, rect);
                        break;
                    default:
                        std::unreachable();
                }
            } else {
                const auto& [color, thick] = (idx == cell_idx ? active_params : inactive_params);
                DrawRectangleLinesEx(rect, thick, color);

                if (cell.is_flagged())
                    draw_texture(Texture_ID::Flag, rect);
            }
        }
    }

    inline auto get_time() const { return grid_timer.get_duration(); }

    ~MinesweeperGrid() noexcept = default;

   private:
    inline std::array<Num_Type, 2> pos_from_idx(Num_Type idx) const noexcept {
        return std::to_array({idx % width, idx / width});
    }

    inline Num_Type idx_from_pos(Vector2 pos) const noexcept {
        const auto [x, y] = pos;
        const auto calc_idx = static_cast<Num_Type>(y / cell_size) * width + static_cast<Num_Type>(x / cell_size);
        return std::clamp<Num_Type>(calc_idx, 0, cells.size() - 1);
    }

    inline void loop_over_neighbors(Num_Type idx, auto&& Func) noexcept {
        const auto [x, y] = pos_from_idx(idx);
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0)
                    continue;

                const auto abs_x = x + dx, abs_y = y + dy;
                if (abs_x < 0 || abs_x >= width || abs_y < 0 || abs_y >= height)
                    continue;
                Func(cells[abs_y * width + abs_x]);
            }
        }
    }

    void reveal_cell(Num_Type idx) {
        if (cells[idx].is_revealed())
            return;

        std::queue<Num_Type> to_reveal;
        to_reveal.push(idx);

        while (!to_reveal.empty()) {
            const auto current_idx = to_reveal.front();
            to_reveal.pop();

            auto& current_cell = cells[current_idx];
            current_cell.reveal();

            if (current_cell.mines_around == 0) {
                loop_over_neighbors(current_idx, [&](Cell& cell) {
                    const auto neighbor_idx = &cell - &cells[0];
                    if (!cell.is_mine() && !cell.is_revealed())
                        to_reveal.push(neighbor_idx);
                });
            }
        }
    }

    Num_Type width, height;
    float cell_size;
    Timer<Measurements::s> grid_timer;
    std::set<Num_Type> mines;
    std::vector<Cell> cells;
};

int main() {
#ifndef _NDEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Raylib Minesweeper");
    // SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    static Game_State game_state;  // = Game_State::Game_Started;
    static Menu menu;
    static Mouse_Wrapper mouse;
    std::shared_ptr<MinesweeperGrid> grid;

    constexpr static auto bg_color = Color(50, 50, 50, 255);
    while (!WindowShouldClose()) {
        mouse.update();

        BeginDrawing();
        {
            ClearBackground(bg_color);

            switch (game_state) {
                case Game_State::Menu: {
                    game_state = menu.show();
                    break;
                }
                case Game_State::Game_Started: {
                    if (!grid) {
                        const auto& [_, w, h, mines] = menu.get_diff();
                        grid = std::make_shared<MinesweeperGrid>(w, h, mines);
                    }

                    const auto current_cell = grid->update_input(mouse);

                    switch (grid->update_status()) {
                        case Grid_Status::Bad:
                            game_state = Game_State::Game_Lost;
                            break;
                        case Grid_Status::Finished:
                            game_state = Game_State::Game_Won;
                            break;
                        case Grid_Status::Good:
                            break;
                        default:
                            std::unreachable();
                    }
                    grid->draw(current_cell);
                    break;
                }
                case Game_State::Game_Won: {
                    menu.win(grid->get_time());
                    grid.reset();
                    break;
                }
                case Game_State::Game_Lost: {
                    menu.lose();
                    grid.reset();
                    break;
                }
                default:
                    std::unreachable();
            }
        }
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}