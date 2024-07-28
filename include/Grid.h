#pragma once

#include <set>
#include <vector>

#include "Cell.h"
#include "Mouse.h"
#include "timer.hpp"

class MinesweeperGrid {
    using Num_Type = uint32_t;

   public:
    MinesweeperGrid(Num_Type width, Num_Type height, Num_Type mines_num);
    Num_Type update_input(Mouse_Wrapper mouse);
    Grid_Status update_status();
    void draw(Num_Type cell_idx);
    inline auto get_time() const { return grid_timer.get_duration(); }
    ~MinesweeperGrid() noexcept = default;

   private:
    inline std::array<Num_Type, 2> pos_from_idx(Num_Type idx) const noexcept;
    inline Num_Type idx_from_pos(Vector2 pos) const noexcept;
    inline void loop_over_neighbors(Num_Type idx, auto&& Func) noexcept;
    inline void reveal_cell(Num_Type idx);

    Num_Type width, height;
    float cell_size;
    Timer<Measurements::s> grid_timer;
    std::set<Num_Type> mines;
    std::vector<Cell> cells;
};