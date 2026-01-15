#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Engine Managers
#include "Singleton.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "PhysicsManager.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "BackgroundManager.h"

// Test için basit bir karakter
#include "Character.h"
#include "StaticObject.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

// Test karakteri
class TestCharacter : public Character
{
public:
    TestCharacter(float x, float y)
    {
        SetPosition(x, y);
        SetScale(2.0f);
        SetSpeed(200.0f);

        // Test için basit texture (sonra animasyon ekleriz)
        SDL_Texture* tex = SpriteManager::GetInstance().LoadTexture(
            "test_char",
            "Media/test.png"  // Basit bir 32x32 sprite koy
        );
        SetTexture(tex);
    }

    void Update() override
    {
        Character::Update();

        float dt = TimeManager::GetInstance().GetDeltaTime();
        InputManager& input = InputManager::GetInstance();

        // Hareket
        bool moving = false;

        if (input.GetKey(SDL_SCANCODE_UP))
        {
            posY -= speed * dt;
            moving = true;
        }
        if (input.GetKey(SDL_SCANCODE_DOWN))
        {
            posY += speed * dt;
            moving = true;
        }
        if (input.GetKey(SDL_SCANCODE_LEFT))
        {
            posX -= speed * dt;
            SetFacingRight(false);
            moving = true;
        }
        if (input.GetKey(SDL_SCANCODE_RIGHT))
        {
            posX += speed * dt;
            SetFacingRight(true);
            moving = true;
        }

        // Pozisyonu güncelle
        rect.x = static_cast<int>(posX);
        rect.y = static_cast<int>(posY);

        // State güncelle
        if (moving)
            SetState(CharacterState::WALKING);
        else
            SetState(CharacterState::IDLE);
    }
};

// Test statik obje
class TestObstacle : public StaticObject
{
public:
    TestObstacle(float x, float y)
    {
        SetPosition(x, y);
        SetScale(1.5f);
        SetCollision(true);

        SDL_Texture* tex = SpriteManager::GetInstance().LoadTexture(
            "test_obstacle",
            "Media/obstacle.png"
        );
        SetTexture(tex);
    }
};

int main(int argc, char* argv[])
{
    std::cout << "========================================\n";
    std::cout << "    GAME ENGINE TEST\n";
    std::cout << "========================================\n";

    // SDL Başlatma
    std::cout << "\n[1/10] Initializing SDL...\n";
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL FAILED: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "✓ SDL initialized\n";

    // SDL_image
    std::cout << "\n[2/10] Initializing SDL_image...\n";
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init FAILED: " << IMG_GetError() << std::endl;
        return 1;
    }
    std::cout << "✓ SDL_image initialized\n";

    // SDL_mixer
    std::cout << "\n[3/10] Initializing SDL_mixer...\n";
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
        std::cerr << "Mix_Init FAILED: " << Mix_GetError() << std::endl;
        return 1;
    }
    std::cout << "✓ SDL_mixer initialized\n";

    // SDL_ttf
    std::cout << "\n[4/10] Initializing SDL_ttf...\n";
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init FAILED: " << TTF_GetError() << std::endl;
        return 1;
    }
    std::cout << "✓ SDL_ttf initialized\n";

    // Window
    std::cout << "\n[5/10] Creating window...\n";
    SDL_Window* window = SDL_CreateWindow(
        "Game Engine Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window creation FAILED: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "✓ Window created (" << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << ")\n";

    // Renderer
    std::cout << "\n[6/10] Creating renderer...\n";
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "Renderer creation FAILED: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "✓ Renderer created\n";

    // Engine Singletons
    std::cout << "\n[7/10] Creating engine singletons...\n";
    InputManager::CreateSingleton();
    ObjectManager::CreateSingleton();
    PhysicsManager::CreateSingleton();
    SpriteManager::CreateSingleton();
    TimeManager::CreateSingleton();
    AnimationManager::CreateSingleton();
    GameManager::CreateSingleton();
    SoundManager::CreateSingleton();
    TextManager::CreateSingleton();
    SceneManager::CreateSingleton();
    UIManager::CreateSingleton();
    BackgroundManager::CreateSingleton();
    std::cout << "✓ All singletons created\n";

    // Renderer'ları set et
    std::cout << "\n[8/10] Setting renderers...\n";
    ObjectManager::GetInstance().SetRenderer(renderer);
    SpriteManager::GetInstance().SetRenderer(renderer);
    AnimationManager::GetInstance().SetRenderer(renderer);
    TextManager::GetInstance().SetRenderer(renderer);
    SceneManager::GetInstance().SetRenderer(renderer);
    UIManager::GetInstance().SetRenderer(renderer);
    BackgroundManager::GetInstance().SetRenderer(renderer);
    BackgroundManager::GetInstance().SetScreenSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "✓ Renderers set\n";

    // Sub-system init
    std::cout << "\n[9/10] Initializing sub-systems...\n";
    SoundManager::GetInstance().Init();
    TextManager::GetInstance().Init();
    std::cout << "✓ Sub-systems initialized\n";

    // Test objeleri oluştur
    std::cout << "\n[10/10] Creating test objects...\n";

    // NOT: Gerçek sprite yoksa test çalışmayabilir
    // Media klasöründe test.png ve obstacle.png olmalı
    // Yoksa sadece konsol çıktılarına bak

    TestCharacter* testChar = new TestCharacter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    TestObstacle* testObs = new TestObstacle(300, 300);

    std::cout << "✓ Test objects created\n";

    // TimeManager başlat
    TimeManager::GetInstance().Update();

    std::cout << "\n========================================\n";
    std::cout << "ENGINE TEST STARTED!\n";
    std::cout << "========================================\n";
    std::cout << "Controls:\n";
    std::cout << "  Arrow Keys - Move character\n";
    std::cout << "  ESC - Quit\n";
    std::cout << "========================================\n\n";

    // Main loop
    bool running = true;
    SDL_Event event;
    int frameCount = 0;

    while (running)
    {
        // Events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            UIManager::GetInstance().HandleEvent(event);
        }

        // Update
        TimeManager::GetInstance().Update();
        InputManager::GetInstance().Update();

        if (InputManager::GetInstance().GetKey(SDL_SCANCODE_ESCAPE))
            running = false;

        ObjectManager::GetInstance().Update();
        GameManager::GetInstance().SetState(GameState::PLAYING);

        // Render
        SDL_SetRenderDrawColor(renderer, 50, 150, 50, 255);
        SDL_RenderClear(renderer);

        BackgroundManager::GetInstance().Render();
        ObjectManager::GetInstance().RenderAll();

        // FPS counter
        frameCount++;
        if (frameCount % 60 == 0)
        {
            std::cout << "Engine running... Frame: " << frameCount
                << " | FPS: ~" << (int)(1.0f / TimeManager::GetInstance().GetDeltaTime())
                << std::endl;
        }

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    std::cout << "\n========================================\n";
    std::cout << "Shutting down engine...\n";
    std::cout << "========================================\n";

    delete testChar;
    delete testObs;

    BackgroundManager::DestroySingleton();
    UIManager::DestroySingleton();
    SceneManager::DestroySingleton();
    TextManager::DestroySingleton();
    SoundManager::DestroySingleton();
    GameManager::DestroySingleton();
    AnimationManager::DestroySingleton();
    TimeManager::DestroySingleton();
    SpriteManager::DestroySingleton();
    PhysicsManager::DestroySingleton();
    ObjectManager::DestroySingleton();
    InputManager::DestroySingleton();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    std::cout << "\n✓ Engine shut down successfully!\n";
    std::cout << "========================================\n";

    return 0;
}