#define _CRT_SECURE_NO_WARNINGS
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <memory>

#include "include/Constants.h"
#include "include/Grid.h"
#include "include/Menu.h"
#include "include/Mouse.h"

int main() {
#ifndef _NDEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Raylib Minesweeper");
    // SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    Game_State game_state = Game_State::Menu; //Game_Started;
    Menu menu;
    Mouse_Wrapper mouse;
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