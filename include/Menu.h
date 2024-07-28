#pragma once

#include "Constants.h"
#include "Difficulty.h"

class Menu {
   public:
    Game_State show();
    Game_State end_game(Game_State gs) const;
    const Difficulty& get_difficulty() const noexcept;

   private:
    const Difficulty* diff = nullptr;
};
