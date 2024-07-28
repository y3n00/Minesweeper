#include "../include/Mouse.h"

void Mouse_Wrapper::update() {
    pos = GetMousePosition();
    action = []() -> Mouse_Action {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return Mouse_Action::Reveal;
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            return Mouse_Action::Toggle_Flag;
        return Mouse_Action::None;
    }();
}