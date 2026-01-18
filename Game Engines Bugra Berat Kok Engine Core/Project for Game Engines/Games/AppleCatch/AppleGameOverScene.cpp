#include "AppleGameOverScene.h"
#include "AppleCollectorGame.h"
#include "UIManager.h"
#include "Button.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TextManager.h"

AppleGameOverScene::AppleGameOverScene(int w, int h, AppleCollectorGame* gameRef)
    : UISceneBase("AppleGameOver"),
    game(gameRef),
    screenW(w),
    screenH(h)
{
}

void AppleGameOverScene::OnEnter()
{
    UIManager::GetInstance().RemoveAll();

    // RETRY button
    Button* retryBtn = new Button("btn_retry", 810, 600, 300, 80, "RETRY");
    retryBtn->SetOnClick([]() {
        SceneManager::GetInstance().ChangeScene("AppleGame");
        });

    UIManager::GetInstance().AddElement(retryBtn);
}

void AppleGameOverScene::OnExit()
{
    UIManager::GetInstance().RemoveAll();
}

void AppleGameOverScene::Update()
{
    UIManager::GetInstance().Update();
}

void AppleGameOverScene::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    const int score = game ? game->GetLastFinalScore() : 0;

    std::string title = "TIME'S UP!";
    std::string scoreText = "Final Score: " + std::to_string(score);

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color yellow = { 255, 255, 0, 255 };

    int tw, th;

    // Title
    TextManager::GetInstance().GetTextSize(title, "main_font", tw, th);
    TextManager::GetInstance().RenderText(title, "main_font", 960 - tw / 2, 300, white);

    // Score
    TextManager::GetInstance().GetTextSize(scoreText, "main_font", tw, th);
    TextManager::GetInstance().RenderText(scoreText, "main_font", 960 - tw / 2, 400, yellow);

    UIManager::GetInstance().Render();
}

void AppleGameOverScene::HandleInput()
{
    const auto& events = InputManager::GetInstance().GetFrameEvents();
    for (const auto& e : events)
    {
        SDL_Event copy = e;
        UIManager::GetInstance().HandleEvent(copy);
    }
    InputManager::GetInstance().ClearFrameEvents();
}