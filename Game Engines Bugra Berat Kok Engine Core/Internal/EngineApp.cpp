#include "EngineApp.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Engine managers
#include "GameManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "PhysicsManager.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "BackgroundManager.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "CameraManager.h"

EngineApp::EngineApp(int w, int h, const std::string& t)
    : window(nullptr),
    renderer(nullptr),
    width(w),
    height(h),
    title(t),
    running(false)
{
}

EngineApp::~EngineApp()
{
    Shutdown();
}

bool EngineApp::Init()
{
    // =============================
    // SDL INIT (OS / HARDWARE)
    // =============================
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    TTF_Init();

    // =============================
    // WINDOW & RENDERER
    // =============================
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        std::cerr << "Window creation failed\n";
        return false;
    }

    renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer)
    {
        std::cerr << "Renderer creation failed\n";
        return false;
    }

    // =============================
// FULLSCREEN + LOGICAL SIZE
// =============================

   // fullscreen
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    // referans çözünürlük (tasarım çözünürlüğün)
    const int REF_W = 1920;
    const int REF_H = 1080;

    // koordinatları sabitle
    SDL_RenderSetLogicalSize(renderer, REF_W, REF_H);

    // integer scale kapalı (çünkü 1366x768 gibi ekranlarda küçültecek)
    SDL_RenderSetIntegerScale(renderer, SDL_FALSE);

    // keskinlik (pixel değilse 1 de deneyebilirsin)
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");



    // =============================
    // ENGINE MANAGERS
    // =============================
    InputManager::CreateSingleton();
    TimeManager::CreateSingleton();
    ObjectManager::CreateSingleton();
    PhysicsManager::CreateSingleton();
    SpriteManager::CreateSingleton();
    AnimationManager::CreateSingleton();
    SoundManager::CreateSingleton();
    TextManager::CreateSingleton();
    BackgroundManager::CreateSingleton();
    UIManager::CreateSingleton();
    SceneManager::CreateSingleton();
    CameraManager::CreateSingleton();
    GameManager::CreateSingleton();

    // Renderers
    ObjectManager::GetInstance().SetRenderer(renderer);
    SpriteManager::GetInstance().SetRenderer(renderer);
    AnimationManager::GetInstance().SetRenderer(renderer);
    TextManager::GetInstance().SetRenderer(renderer);
    BackgroundManager::GetInstance().SetRenderer(renderer);
    BackgroundManager::GetInstance().SetScreenSize(width, height);

    UIManager::GetInstance().SetRenderer(renderer);
    SceneManager::GetInstance().SetRenderer(renderer);
    CameraManager::GetInstance().SetScreenSize(width, height);

    // Init subsystems
    SoundManager::GetInstance().Init();
    TextManager::GetInstance().Init();

    // Reset delta time
    TimeManager::GetInstance().Update();

    running = true;
    return true;
}

void EngineApp::Run()
{
    SDL_Event event;

    while (running)
    {
        // =============================
        // EVENTS (OS INPUT)
        // =============================
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            InputManager::GetInstance().PushEvent(event);
        }

        // =============================
        // FRAME UPDATE
        // =============================
        TimeManager::GetInstance().Update();
        InputManager::GetInstance().Update();

        if (InputManager::GetInstance().GetKey(SDL_SCANCODE_ESCAPE))
            running = false;

        // =============================
        // SCENE PIPELINE
        // =============================
        SceneManager::GetInstance().HandleInput();
        SceneManager::GetInstance().Update();
        SceneManager::GetInstance().Render();

        SDL_RenderPresent(renderer);
    }
}

void EngineApp::Shutdown()
{
    if (!window && !renderer)
        return;

    SceneManager::DestroySingleton();
    UIManager::DestroySingleton();

    GameManager::DestroySingleton();
    CameraManager::DestroySingleton();
    BackgroundManager::DestroySingleton();
    TextManager::DestroySingleton();
    SoundManager::DestroySingleton();
    AnimationManager::DestroySingleton();
    SpriteManager::DestroySingleton();
    PhysicsManager::DestroySingleton();
    ObjectManager::DestroySingleton();
    TimeManager::DestroySingleton();
    InputManager::DestroySingleton();

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}