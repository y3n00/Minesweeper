#pragma once

#include <set>
#include <vector>

#include "Cell.h"
#include "Mouse.h"

class MinesweeperGrid {
    using Num_Type = uint32_t;

   public:
    MinesweeperGrid(Num_Type width, Num_Type mines_num);
    [[nodiscard]] Num_Type update_input(Mouse_Wrapper mouse);
    [[nodiscard]] Grid_Status update_status();
    void draw(Num_Type cell_idx);
    ~MinesweeperGrid() noexcept = default;

   private:
    [[nodiscard]] inline std::array<Num_Type, 2> pos_from_idx(Num_Type idx) const noexcept;
    [[nodiscard]] inline Num_Type idx_from_pos(Vector2 pos) const noexcept;
    inline void loop_over_neighbors(Num_Type idx, auto&& Func) noexcept;
    inline void reveal_cell(Num_Type idx);

    Num_Type sz;
    float cell_size;
    std::set<Num_Type> mines;
    std::vector<Cell> cells;
};