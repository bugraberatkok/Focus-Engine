#include "StartScene.h"

#include "UIManager.h"
#include "Button.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "InputManager.h"

StartScene::StartScene()
    : UISceneBase("Start")
{
}

void StartScene::OnEnter()
{
    // Menü state
    GameManager::GetInstance().SetState(GameState::MENU);

    // Bu scene'e girince önceki UI'ları temizle
    UIManager::GetInstance().RemoveAll();

    // Play butonu (ekran ortası)
    const int btnW = 260;
    const int btnH = 80;
    const int btnX = 1920 / 2 - btnW / 2;
    const int btnY = 1080 / 2 - btnH / 2;

    Button* playBtn = new Button("btn_play", btnX, btnY, btnW, btnH, "PLAY");

    // Tıklanınca Game scene'e geç
    playBtn->SetOnClick([]() {
        SceneManager::GetInstance().ChangeScene("Game");
        });

    UIManager::GetInstance().AddElement(playBtn);
}

void StartScene::OnExit()
{
    // Menü UI temizliği
    UIManager::GetInstance().RemoveAll();
}

void StartScene::Update()
{
    UIManager::GetInstance().Update();
}

void StartScene::Render(SDL_Renderer* renderer)
{
    // Basit koyu arkaplan
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_Rect bg{ 0,0,1920,1080 };
    SDL_RenderClear(renderer);

    // UI çiz
    UIManager::GetInstance().Render();
}

void StartScene::HandleInput()
{
    // Bu frame'de yakalanan SDL eventleri UI'ya dağıt
    const auto& events = InputManager::GetInstance().GetFrameEvents();

    for (const auto& e : events)
    {
        // UIManager parametreyi ref istiyor (non-const), kopyalayalım
        SDL_Event copy = e;
        UIManager::GetInstance().HandleEvent(copy);
    }

    // Frame eventleri tüketildi
    InputManager::GetInstance().ClearFrameEvents();
}
