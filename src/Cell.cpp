#include "../include/Cell.h"

bool Cell::is_mine() const { return type == Cell_Type::Mine; }
bool Cell::is_revealed() const { return revealed; }
bool Cell::is_flagged() const { return flagged; }
void Cell::reveal() { revealed = true; }
void Cell::toggle_flag() {
    if (!revealed)
        flagged = !flagged;
}
