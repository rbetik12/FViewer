#pragma once

#include "../Renderer/Window.h"

class Input {
public:
    static void Init(Window window);
    static void Update();
    static void Flush();
    static bool GetKeyDown(int keycode);
    static std::pair<float, float> GetMouseYawAndPitch();
    static void ToggleCursor(Window window);
    static void ToggleCursor(Window window, bool isOn);
private:
    static bool keys[1024];
    static float yaw;
    static float pitch;
    static float cursorX;
    static float cursorY;
    static bool firstFrame;
    static bool isCursor;
};

