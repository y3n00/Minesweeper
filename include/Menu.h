#pragma once

#include "Constants.h"
#include "Difficulty.h"

class Menu {
   public:
    [[nodiscard]] Game_State show();
    [[nodiscard]] Game_State end_game(Game_State gs) const;
    [[nodiscard]] const Difficulty& get_difficulty() const noexcept;

   private:
    const Difficulty* diff = nullptr;
};
