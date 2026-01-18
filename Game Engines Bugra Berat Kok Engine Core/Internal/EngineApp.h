#pragma once
#include <string>

// Forward declarations (oyun SDL bilmesin diye)
struct SDL_Window;
struct SDL_Renderer;

/*
    EngineApp
    ----------
    - OS / hardware wrapper
    - SDL lifecycle owner
    - Main loop runner
    - Oyun içermez, sadece engine’i çalıştırır
*/
class EngineApp
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int width;
    int height;
    std::string title;

    bool running;

public:
    EngineApp(int w, int h, const std::string& title);
    ~EngineApp();

    bool Init();   // SDL + managers + renderer
    void Run();    // main loop
    void Shutdown();

    SDL_Renderer* GetRenderer() const { return renderer; }
};