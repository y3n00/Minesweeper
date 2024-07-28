#pragma once

#include <cstdint>

#include "Constants.h"

struct Cell {
    bool is_mine() const;
    bool is_revealed() const;
    bool is_flagged() const;
    void reveal();
    void toggle_flag();

    bool flagged = false, revealed = false;
    uint8_t mines_around = 0;
    Cell_Type type = Cell_Type::Normal;
};
