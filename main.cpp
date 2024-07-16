#define _CRT_SECURE_NO_WARNINGS
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <algorithm>
#include <format>
#include <future>
#include <numeric>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <vector>

#include "random.hpp"
#include "timer.hpp"

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

enum class Grid_Status {
    Good,
    Bad,
    Finished
};

struct Mouse_Wrapper {
    Mouse_Action action;
    Vector2 pos;
    inline void update() {
        pos = GetMousePosition();
        action = []() -> Mouse_Action {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                return Mouse_Action::Reveal;
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
                return Mouse_Action::Toggle_Flag;
            return Mouse_Action::None;
        }();
    }
};

struct Cell {  // TODO: REFACTOR
    inline bool is_mine() const { return type == Cell_Type::Mine; }
    inline bool is_revealed() const { return revealed; }
    inline bool is_flagged() const { return flagged; }

    inline auto toggle_flag() {
        if (!revealed)
            flagged != flagged;
    }
    inline auto reveal() {
        if (type == Cell_Type::Mine)
            return false;
        return (revealed = true);
    }
    Cell_Type type = Cell_Type::Normal;
    uint8_t mines_around = 0;
    bool flagged = false, revealed = false;
};

struct Menu {  // TODO
    uint8_t selected_sz, selected_mines;

    inline auto show() {
        constexpr static auto label = "Minesweeper";
        constexpr static auto font_sz = 52;  // PISYAT DWA!
        static const auto label_sz = MeasureTextEx(GetFontDefault(), label, font_sz, 1.f);
        DrawText(label, (WINDOW_SIZE - label_sz.x) / 2, WINDOW_SIZE * 0.15, font_sz, RAYWHITE);

        static VALUE values[] = {
            {"Grid Size", 5, 30},
            {"Mines Ratio", 0.1f, 0.9f},
        };

        constexpr static auto half_screen = WINDOW_SIZE / 2.f,
                              rect_w = WINDOW_SIZE * 0.5f,
                              rect_h = WINDOW_SIZE * 0.05f,
                              padding = 15.f;

        for (auto&& [idx, v] : values | std::views::enumerate) {
            v.slider(Rectangle{
                .x = (half_screen - rect_w / 2),
                .y = half_screen - rect_h / 2 + (rect_h + padding) * idx,
                .width = rect_w,
                .height = rect_h,
            });
        }

        const auto& [sz, ratio] = std::tuple(values[0].get_value(), values[1].get_value());
        selected_sz = static_cast<uint8_t>(sz);
        selected_mines = static_cast<uint8_t>(sz * ratio);

        constexpr static auto bttn_w = WINDOW_SIZE * 0.4f, bttn_h = WINDOW_SIZE * 0.08f;
        constexpr static auto play_bttn_rect = Rectangle{(WINDOW_SIZE - bttn_w) / 2, WINDOW_SIZE - bttn_h * 2, bttn_w, bttn_h};

        return GuiButton(play_bttn_rect, "PLAY") ? Game_State::Game_Started : Game_State::Menu;
    }
    inline auto win(auto&& timer) {}  //! TODO
    inline auto lose() {}             //! TODO

   private:
    struct VALUE {
        using Value_t = float;

        Value_t value{};
        const Value_t min, max;
        const std::string txt;

        constexpr VALUE(std::string_view txt, float min, float max)
            : txt{txt}, min{min}, max{max} {}

        void slider(Rectangle rect) {
            GuiSlider(rect, txt.c_str(), NULL, &value, min, max);
            const auto fmt = (value < 1.f ? std::format("{0:.2f}", value) : std::format("{0}x{0}", (int)value));
            DrawText(fmt.c_str(), rect.x + 10, rect.y + 10, 20, RAYWHITE);
        }

        constexpr Value_t get_value() const { return value; }
    };
};

class MinesweeperGrid {
    using Idx_Type = uint32_t;

   public:
    MinesweeperGrid(Idx_Type num_cells, Idx_Type num_mines)
        : sq_size{num_cells}, cell_size{static_cast<float>(WINDOW_SIZE) / sq_size} {
        const auto total_sz = num_cells * num_cells;
        static Random_t<Idx_Type> mines_rand;
        cells.resize(total_sz);

        while (mines.size() != num_mines)  // fill set of unique positions
            mines.insert(mines_rand.get(0, total_sz - 1));

        for (auto&& unique : mines) {
            cells[unique].type = Cell_Type::Mine;

            const auto [x, y] = pos_from_idx(unique);
            for (int dy = -1; dy <= 1; ++dy) {  // count mines around
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0)  // mine itself
                        continue;

                    const auto abs_x = x + dx, abs_y = y + dy;
                    if (abs_x < 0 || abs_x >= sq_size || abs_y < 0 || abs_y >= sq_size)
                        continue;
                    ++cells[abs_y * sq_size + abs_x].mines_around;
                }
            }
        }
        grid_time.start();
    }

    auto update_input(Mouse_Wrapper mouse) {  //! TODO: rewrite
        const auto cell_idx = idx_from_mouse_pos(mouse.pos);
        switch (mouse.action) {
            case Mouse_Action::Reveal:
                break;
            case Mouse_Action::Toggle_Flag:
                break;
            default:
                break;
        }
        return cell_idx;
    }

    auto update_status() {
        auto status = Grid_Status::Good;
        auto check_1 = std::async(std::launch::async, std::ranges::all_of, mines, [&](auto&& m_idx) -> bool { return cells[m_idx].type == Cell_Type::Flagged; });
        auto check_2 = std::async(std::launch::async, std::ranges::any_of, mines, [&](auto&& m_idx) -> bool { return cells[m_idx].type == Cell_Type::Normal_Revealed; });

        if (status == Grid_Status::Finished) {
            grid_time.stop();
        }
        return status;  //! TODO
    }

    void draw(Idx_Type cell_idx) {  // TODO: REFACTOR
        for (auto&& [idx, cell] : cells | std::views::enumerate) {
            const auto [x, y] = pos_from_idx(idx);
            const auto rect = Rectangle(x * cell_size, y * cell_size, cell_size, cell_size);
            const auto [color, thick] = (idx == cell_idx ? std::tuple(PURPLE, 3.f) : std::tuple(LIGHTGRAY, 1.f));  // highlight cell under mouse
            DrawRectangleLinesEx(rect, thick, color);

            if (cell.is_revealed()) {
            } else if (cell.is_flagged()) {
            }
#ifdef _DEBUG
            switch (cell.type) {
                case Cell_Type::Mine:
                    DrawText("M", rect.x + cell_size / 2 - 10, rect.y + cell_size / 2 - 10, 20, RED);
                    break;
                default:
                    if (const auto& mines_around = cell.mines_around; mines_around > 0)
                        DrawText(TextFormat("%d", mines_around), rect.x + cell_size / 2 - 10, rect.y + cell_size / 2 - 10, 20, GREEN);
                    break;
            }
#endif
        }
    }

    inline auto get_time() const {
        return grid_time.get_duration();
    }

    ~MinesweeperGrid() noexcept = default;

   private:
    inline std::array<Idx_Type, 2> pos_from_idx(Idx_Type idx) const noexcept {
        return std::to_array({idx % sq_size, idx / sq_size});
    }
    inline Idx_Type idx_from_mouse_pos(Vector2 pos) const noexcept {
        return static_cast<Idx_Type>(pos.y / cell_size) * sq_size + static_cast<Idx_Type>(pos.x / cell_size);
    }

    Idx_Type sq_size;
    float cell_size;
    Timer<Measurements::s> grid_time;
    std::set<Idx_Type> mines;
    std::vector<Cell> cells;
};

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Raylib Minesweeper");
    // SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    static Game_State game_state;  // = Game_State::Game_Started;
    static Menu menu;
    static Mouse_Wrapper mouse;
    std::unique_ptr<MinesweeperGrid> grid = std::make_unique<MinesweeperGrid>(10, 10);

    while (!WindowShouldClose()) {
        mouse.update();

        BeginDrawing();
        {
            ClearBackground(DARKGRAY);

            switch (game_state) {  // TODO: REFACTOR
                case Game_State::Menu: {
                    menu.show();
                    break;
                }
                case Game_State::Game_Started: {
                    if (!grid) {
                        grid = std::make_unique<MinesweeperGrid>(menu.selected_sz, menu.selected_mines);
                    }

                    const auto current_cell = grid->update_input(mouse);
                    const auto grid_status = grid->update_status();

                    switch (grid_status) {
                        case Grid_Status::Bad:
                            game_state = Game_State::Game_Lost;
                            break;
                        case Grid_Status::Finished:
                            game_state = Game_State::Game_Won;
                            break;
                        case Grid_Status::Good:
                        default:
                            break;
                    }
                    grid->draw(current_cell);
                    break;
                }
                case Game_State::Game_Won: {
                    menu.win(grid->get_time());
                    break;
                }
                case Game_State::Game_Lost: {
                    menu.lose();
                    break;
                }
                default: {
                    std::unreachable();
                }
            }
        }
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}