#include "../include/Grid.h"

#include <raylib.h>

#include <algorithm>
#include <array>
#include <queue>
#include <ranges>

#include "../include/random.hpp"

#include "../textures/bytes.h"

static inline auto get_texture(Texture_ID texture_id) {
    static const auto mem_flag = LoadImageFromMemory(".png", flag_png.data(), flag_png.size());
    static const auto mem_mine= LoadImageFromMemory(".png", mine_png.data(), mine_png.size());

    static const auto flag = LoadTextureFromImage(mem_flag);
    static const auto mine = LoadTextureFromImage(mem_mine);

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
    using namespace Constants::Texture;
    const auto& [x, y, sz, _] = params;
    const auto new_sz = sz * 0.5f;

    const auto offset = (sz - new_sz) / 2;
    const auto dst_rect = Rectangle{x + offset, y + offset, new_sz, new_sz};

    DrawTexturePro(get_texture(texture_id), src_rect, dst_rect, origin, rotation, WHITE);
}

static auto draw_mines_around(uint32_t mines_count, Rectangle params) {
    using namespace Constants::Mines_Colors;
    const auto& [x, y, sz, _] = params;
    const auto font_sz = sz * 0.7f;

    const auto as_str = std::to_string(mines_count);
    const auto text_width = MeasureText(as_str.c_str(), font_sz);
    const auto half_sz = sz / 2.f, half_font_sz = font_sz / 2.f, half_text_width = text_width / 2.f;

    DrawText(as_str.c_str(), x + half_sz - half_text_width, y + half_sz - half_font_sz, font_sz, colors[mines_count]);
}

MinesweeperGrid::MinesweeperGrid(Num_Type size, Num_Type mines_num)
    : sz{size}, cell_size{WINDOW_SIZE / (float)sz} {
    const auto total_sz = sz * sz;

    static Random_t<Num_Type> mines_rand;
    cells.resize(total_sz);

    while (mines.size() != mines_num)  // fill set of unique positions
        mines.insert(mines_rand.get(0, total_sz - 1));

    for (auto&& unique : mines) {
        cells[unique].type = Cell_Type::Mine;
        loop_over_neighbors(unique, [](Cell& cell) { ++cell.mines_around; });
    }
}

MinesweeperGrid::Num_Type MinesweeperGrid::update_input(Mouse_Wrapper mouse) {
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

Grid_Status MinesweeperGrid::update_status() {
    auto&& revealed = cells | std::views::filter([](auto&& cell) -> bool { return cell.is_revealed(); });
    const auto revealed_sz = std::ranges::distance(revealed.begin(), revealed.end());
    auto&& flagged = [this](auto&& cell_idx) { return cells[cell_idx].is_flagged(); };

    if (std::ranges::any_of(revealed, [](auto&& cell) { return cell.is_mine(); }))  // if any mine is revealed
        return Grid_Status::Bad;
    else if (cells.size() - revealed_sz == mines.size() || std::ranges::all_of(mines, flagged))
        return Grid_Status::Finished;

    return Grid_Status::Good;
}

void MinesweeperGrid::draw(Num_Type cell_idx) {
    using namespace Constants::Grid;

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

inline std::array<MinesweeperGrid::Num_Type, 2> MinesweeperGrid::pos_from_idx(MinesweeperGrid::Num_Type idx) const noexcept {
    return std::to_array({idx % sz, idx / sz});
}

inline MinesweeperGrid::Num_Type MinesweeperGrid::idx_from_pos(Vector2 pos) const noexcept {
    using namespace Constants::Grid;

    const auto [x, y] = pos;
    const auto calc_idx = static_cast<Num_Type>(y / cell_size) * sz + static_cast<Num_Type>(x / cell_size);
    return std::clamp<Num_Type>(calc_idx, 0, cells.size() - 1);
}

inline void MinesweeperGrid::loop_over_neighbors(Num_Type idx, auto&& Func) noexcept {
    const auto [x, y] = pos_from_idx(idx);
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0)
                continue;

            const auto abs_x = x + dx, abs_y = y + dy;
            if (abs_x < 0 || abs_x >= sz || abs_y < 0 || abs_y >= sz)
                continue;
            Func(cells[abs_y * sz + abs_x]);
        }
    }
}

inline void MinesweeperGrid::reveal_cell(Num_Type idx) {
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
