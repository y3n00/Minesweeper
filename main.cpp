#define _CRT_SECURE_NO_WARNINGS
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <algorithm>
#include <format>
#include <numeric>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <vector>

#include "../my_headers/random.hpp"

//! todo implement count of mines around cell

constexpr static auto WINDOW_SIZE = 800;

enum class Game_State : uint8_t {
    Menu,
    Game,
};

enum class Cell_State : uint8_t {
    Normal_Hidden,
    Normal_Revealed,
    Flagged,
    Mine,
};

enum class Mouse_Action : uint8_t {
    None,
    Reveal,
    Flag,
};

struct Mouse_Wrapper {
    Mouse_Action action;
    Vector2 pos;
    inline void update() {
        pos = GetMousePosition();
        action = get_mouse_action();
    }

private:
    Mouse_Action get_mouse_action() const {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return Mouse_Action::Reveal;
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            return Mouse_Action::Flag;
        return Mouse_Action::None;
    }
};

struct Cell {
    bool is_mine() const { return state == Cell_State::Mine; }
    void toggle_flag() {
        if (state == Cell_State::Normal_Revealed)
            return;
        state = (state == Cell_State::Flagged ? Cell_State::Normal_Hidden : Cell_State::Flagged);
    }

    Cell_State state = Cell_State::Normal_Hidden;
    uint8_t mines_around = 0;
};

struct Menu {  // todo
    uint8_t selected_sz, selected_mines;

    void use() {
        constexpr static float rect_w = WINDOW_SIZE * 0.5, rect_h = WINDOW_SIZE * 0.1;

        // slider -> [txt, min, max, value]
        constexpr static auto min_grid_sz = 5, max_grid_size = 30;
        constexpr static auto mines_ratio_min = 0.1, mines_ratio_max = 0.9;

        float temp_sz, temp_mines_ratio;

        GuiSlider(Rectangle{}, std::format("Grid Size {}", min_grid_sz).c_str(), std::format("{}", max_grid_size).c_str(), &temp_sz, min_grid_sz, max_grid_size);
        GuiSlider(Rectangle{}, std::format("Mines Ratio {}", mines_ratio_min).c_str(), std::format("{}", mines_ratio_max).c_str(), &temp_mines_ratio, mines_ratio_min, mines_ratio_max);

        selected_sz = static_cast<uint8_t>(temp_sz);
        selected_mines = static_cast<uint8_t>(std::max<float>(1, temp_sz * temp_mines_ratio));
    }
};

class MinesweeperGrid {
    using Idx_Type = uint32_t;

public:
    MinesweeperGrid(Idx_Type num_cells, Idx_Type num_mines)
        : sq_size{ num_cells },
        cell_size{ static_cast<float>(WINDOW_SIZE) / sq_size } {
        const auto total_sz = num_cells * num_cells;
        static Random_t<Idx_Type> mines_rand;
        cells.resize(total_sz);

        std::set<Idx_Type> unique_poses;
        while (unique_poses.size() != num_mines)  // fill set of unique positions
            unique_poses.insert(mines_rand.get(0, total_sz));

        for (auto&& unique_idx : unique_poses)  // place bombs in this positions
            cells[unique_idx].state = Cell_State::Mine;
    }

    void draw(Idx_Type cell_idx) {
        for (Idx_Type y = 0; y < sq_size; ++y) {
            for (Idx_Type x = 0; x < sq_size; ++x) {
                const auto current_idx = y * sq_size + x;
                const auto is_selected_cell = current_idx == cell_idx;
                const auto rect = Rectangle(x * cell_size, y * cell_size, cell_size, cell_size);
                const auto color = is_selected_cell ? PURPLE : LIGHTGRAY;
                const auto thick = is_selected_cell ? 2.f : 1.f;
                DrawRectangleLinesEx(rect, thick, color);
#ifdef _DEBUG
                switch (cells[current_idx].state) {
                case Cell_State::Mine:
                    DrawText("M", rect.x + cell_size / 2 - 10, rect.y + cell_size / 2 - 10, 20, RED);
                    break;
                }
#endif
            }
        }
    }

    auto update(Mouse_Wrapper mouse) {
        const auto cell_idx = static_cast<Idx_Type>(mouse.pos.y / cell_size) * sq_size +
            static_cast<Idx_Type>(mouse.pos.x / cell_size);
        switch (mouse.action) {
        case Mouse_Action::Reveal:
            std::println("Reveal on {}", cell_idx);
            break;
        case Mouse_Action::Flag:
            std::println("Flag on {}", cell_idx);
            break;
        default:
            break;
        }
        return cell_idx;
    }

    ~MinesweeperGrid() noexcept = default;

private:
    Idx_Type sq_size;
    float cell_size;
    std::vector<Cell> cells;
};

int main() {
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Raylib Minesweeper");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    static Game_State game_state = Game_State::Game;
    std::unique_ptr<MinesweeperGrid> grid = std::make_unique<MinesweeperGrid>(25, 10);
    static Menu menu;
    static Mouse_Wrapper mouse;

    while (!WindowShouldClose()) {
        mouse.update();

        BeginDrawing();
        {
            ClearBackground(DARKGRAY);
            if (game_state == Game_State::Menu) {
            }
            else if (game_state == Game_State::Game) {
                if (!grid)
                    grid = std::make_unique<MinesweeperGrid>(menu.selected_sz, menu.selected_mines);
                const auto current_cell = grid->update(mouse);
                grid->draw(current_cell);
            }
        }
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}