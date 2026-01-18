#include "GameScene.h"
#include "CatChaseGame.h"
#include "ObjectManager.h"
#include "BackgroundManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"  
#include "TextManager.h"  

GameScene::GameScene(int w, int h, CatChaseGame* gameRef)
    : GameSceneBase("Game"), screenW(w), screenH(h), game(gameRef), initialized(false)
{
    TilemapSpec spec;
    spec.enabled = true;
    spec.tilesetPath = "Media/Tilemap/tileset/WorldTiles_Atlas.png";
    spec.groundCsvPath = "Media/Tilemap/maps/map_Ground.csv";
    spec.tileSize = 16;
    spec.mapW = 120;
    spec.mapH = 68;
    SetTilemapSpec(spec);
}

void GameScene::OnEnter()
{
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

    // ← MÜZİK BAŞLAT
    SoundManager::GetInstance().PlayMusic("game_music", -1);  // -1 = sonsuz loop
}

void GameScene::OnExit()
{
    game->Cleanup();

    // ← MÜZİK DURDUR
    SoundManager::GetInstance().StopMusic();
}

void GameScene::Update()
{
    if (game->IsGameActive())
    {
        game->Update();
        ObjectManager::GetInstance().Update();
        game->CheckCollisions();
    }

    GameState st = GameManager::GetInstance().GetState();
    if (st == GameState::GAME_OVER || st == GameState::WIN)
    {
        SceneManager::GetInstance().ChangeScene("GameOver");
    }
}

void GameScene::Render(SDL_Renderer* renderer)
{
    ObjectManager::GetInstance().RenderAll();

    // ← SCORE + TIMER GÖSTER (Sol üst)
    SDL_Color white = { 255, 255, 255, 255 };

    std::string scoreText = "Score: " + std::to_string(game->GetScore());
    TextManager::GetInstance().RenderText(scoreText, "main_font", 30, 30, white);

    int timeLeft = static_cast<int>(game->GetTimeRemaining());
    std::string timeText = "Time: " + std::to_string(timeLeft) + "s";
    TextManager::GetInstance().RenderText(timeText, "main_font", 30, 80, white);
}

void GameScene::HandleInput()
{
    InputManager::GetInstance().ClearFrameEvents();
}