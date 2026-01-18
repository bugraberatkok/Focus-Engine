#include "AppleStartScene.h"
#include "UIManager.h"
#include "Button.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "TextManager.h"

AppleStartScene::AppleStartScene()
    : UISceneBase("AppleStart")
{
}

void AppleStartScene::OnEnter()
{
    GameManager::GetInstance().SetState(GameState::MENU);
    UIManager::GetInstance().RemoveAll();

    // START button (center screen)
    Button* playBtn = new Button("btn_play", 810, 500, 300, 80, "START");
    playBtn->SetOnClick([]() {
        SceneManager::GetInstance().ChangeScene("AppleGame");
        });

    UIManager::GetInstance().AddElement(playBtn);
}

void AppleStartScene::OnExit()
{
    UIManager::GetInstance().RemoveAll();
}

void AppleStartScene::Update()
{
    UIManager::GetInstance().Update();
}

void AppleStartScene::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = { 255, 255, 255, 255 };

    // Title
    std::string title = "APPLE COLLECTOR";
    int tw, th;
    TextManager::GetInstance().GetTextSize(title, "main_font", tw, th);
    TextManager::GetInstance().RenderText(title, "main_font", 960 - tw / 2, 300, white);

    UIManager::GetInstance().Render();
}

void AppleStartScene::HandleInput()
{
    const auto& events = InputManager::GetInstance().GetFrameEvents();
    for (const auto& e : events)
    {
        SDL_Event copy = e;
        UIManager::GetInstance().HandleEvent(copy);
    }
    InputManager::GetInstance().ClearFrameEvents();
}