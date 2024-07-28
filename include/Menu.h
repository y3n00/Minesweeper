#pragma once

#include "Constants.h"
#include "Difficulty.h"

class Menu {
   private:
    const Difficulty* diff = nullptr;

   public:
    Game_State show();
    void lose();
    void win(const auto& timer) {}
    const Difficulty& get_diff() const noexcept;
};
