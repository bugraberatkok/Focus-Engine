#include "AppleGameScene.h"
#include "AppleCollectorGame.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "TextManager.h"
#include <iostream>

AppleGameScene::AppleGameScene(int w, int h, AppleCollectorGame* gameRef)
    : GameSceneBase("AppleGame"),
    screenW(w),
    screenH(h),
    game(gameRef),
    initialized(false)
{
    std::cout << "==== AppleGameScene Constructor ====" << std::endl;

    // Set tilemap spec - SceneManager will load it automatically
    TilemapSpec spec;
    spec.enabled = true;
    spec.tilesetPath = "Media/Tilemap/Tileset/WorldTiles_Atlas.png";
    spec.groundCsvPath = "Media/Tilemap/Maps/AppleMap.csv";  // ✅ CatChase'in haritası
    spec.tileSize = 16;
    spec.mapW = 120;
    spec.mapH = 68;

    std::cout << "Tilemap spec set:" << std::endl;
    std::cout << "  Enabled: " << spec.enabled << std::endl;
    std::cout << "  Tileset: " << spec.tilesetPath << std::endl;
    std::cout << "  CSV: " << spec.groundCsvPath << std::endl;
    std::cout << "  Tile size: " << spec.tileSize << std::endl;
    std::cout << "  Map size: " << spec.mapW << "x" << spec.mapH << std::endl;

    SetTilemapSpec(spec);

    std::cout << "SetTilemapSpec called" << std::endl;
    std::cout << "====================================" << std::endl;
}

void AppleGameScene::OnEnter()
{
    std::cout << "==== AppleGameScene::OnEnter ====" << std::endl;

    GameManager::GetInstance().SetState(GameState::PLAYING);

    if (!initialized)
    {
        game->Init(screenW, screenH);
        initialized = true;
    }
    else
    {
        game->Reset();
    }

    game->SetGameActive(true);
    SoundManager::GetInstance().PlayMusic("game_music", -1);

    // ✅ DEBUG: Tilemap kontrolü
    std::cout << "Checking tilemap after scene enter..." << std::endl;
    TileMap* map = SceneManager::GetInstance().GetActiveMap();
    if (map)
    {
        std::cout << "SUCCESS: Map loaded!" << std::endl;
        std::cout << "Map size: " << map->GetMapWidth() << "x" << map->GetMapHeight() << std::endl;
    }
    else
    {
        std::cout << "ERROR: Map is NULL after scene enter!" << std::endl;
    }
    std::cout << "=================================" << std::endl;
}

void AppleGameScene::OnExit()
{
    game->Cleanup();
    SoundManager::GetInstance().StopMusic();
}

void AppleGameScene::Update()
{
    if (game->IsGameActive())
    {
        game->Update();
        ObjectManager::GetInstance().Update();
    }

    GameState st = GameManager::GetInstance().GetState();
    if (st == GameState::WIN)
    {
        SceneManager::GetInstance().ChangeScene("GameOver");
    }
}

void AppleGameScene::Render(SDL_Renderer* renderer)
{

    // Tilemap render
    TileMap* map = SceneManager::GetInstance().GetActiveMap();
    if (map)
    {
        map->Render(renderer);
    }

    // Objects
    ObjectManager::GetInstance().RenderAll();

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);  // Siyah, %70 opak
    SDL_Rect hudBg = { 10, 10, 300, 160 };
    SDL_RenderFillRect(renderer, &hudBg);
    // HUD
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color yellow = { 255, 255, 0, 255 };

    std::string scoreText = "Score: " + std::to_string(game->GetScore());
    TextManager::GetInstance().RenderText(scoreText, "main_font", 30, 30, white);

    int timeLeft = static_cast<int>(game->GetTimeRemaining());
    std::string timeText = "Time: " + std::to_string(timeLeft) + "s";
    TextManager::GetInstance().RenderText(timeText, "main_font", 30, 80, white);

    if (game->GetPlayer())
    {
        float colorTimer = game->GetPlayer()->GetColorChangeTimer();
        float colorInterval = game->GetPlayer()->GetColorChangeInterval();
        int colorTimeLeft = static_cast<int>(colorInterval - colorTimer);
        std::string colorText = "Color Change: " + std::to_string(colorTimeLeft) + "s";
        TextManager::GetInstance().RenderText(colorText, "main_font", 30, 130, yellow);
    }
}

void AppleGameScene::HandleInput()
{
    InputManager::GetInstance().ClearFrameEvents();
}