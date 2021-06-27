#include "../Renderer/Window.h"

class UI {
public:
    static UI* Create(Window* window);
    ~UI();

    void Begin();
    void End();
private:
    explicit UI(Window* window);
    void Init(Window* window);
    static UI* instance;
    static Window* window;
};

