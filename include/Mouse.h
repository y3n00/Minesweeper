#pragma once

#include "Constants.h"

struct Mouse_Wrapper {
    void update();

    Mouse_Action action;
    Vector2 pos;
};