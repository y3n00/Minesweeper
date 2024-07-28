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
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, Constants::window_title);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    Game_State game_state = Game_State::Menu;  // Game_Started;
    Menu menu;
    Mouse_Wrapper mouse;
    std::shared_ptr<MinesweeperGrid> grid;

    while (!WindowShouldClose()) {
        mouse.update();

        BeginDrawing();
        {
            ClearBackground(Constants::main_bg_color);

            switch (game_state) {
                case Game_State::Menu: {
                    game_state = menu.show();
                    break;
                }
                case Game_State::Game_Continued: {
                    if (!grid) {
                        using namespace Constants::Grid;
                        const auto& [w, mines, _] = menu.get_difficulty();
                        grid = std::make_shared<MinesweeperGrid>(w, mines);
                    }

                    const auto current_cell = grid->update_input(mouse);
                    const auto grid_status = grid->update_status();
                    switch (grid_status) {
                        case Grid_Status::Good:
                            grid->draw(current_cell);
                            break;
                        case Grid_Status::Bad:
                            game_state = Game_State::Game_Lost;
                            break;
                        case Grid_Status::Finished:
                            game_state = Game_State::Game_Won;
                            break;
                    }
                    break;
                }
                case Game_State::Game_Lost:
                case Game_State::Game_Won: {
                    game_state = menu.end_game(game_state);
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