#include "GameOverScene.h"

#include "UIManager.h"
#include "Button.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TextManager.h"
#include "CatChaseGame.h"

GameOverScene::GameOverScene(int w, int h, CatChaseGame* gameRef)
    : UISceneBase("GameOver"),
    game(gameRef),
    screenW(w),
    screenH(h)
{
}

void GameOverScene::OnEnter()
{
    UIManager::GetInstance().RemoveAll();

    const int btnW = 260;
    const int btnH = 80;
    const int btnX = screenW / 2 - btnW / 2;
    const int btnY = screenH / 2 + 40;

    Button* retryBtn = new Button("btn_retry", btnX, btnY, btnW, btnH, "RETRY");

    retryBtn->SetOnClick([]() {
        SceneManager::GetInstance().ChangeScene("Game");
        });

    UIManager::GetInstance().AddElement(retryBtn);
}

void GameOverScene::OnExit()
{
    UIManager::GetInstance().RemoveAll();
}

void GameOverScene::Update()
{
    UIManager::GetInstance().Update();
}

void GameOverScene::Render(SDL_Renderer* renderer)
{
    // karartılmış arkaplan
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect bg{ 0,0,screenW,screenH };
    SDL_RenderClear(renderer);

    // panel
    SDL_Rect panel = {
        screenW / 2 - 260,
        screenH / 2 - 160,
        520,
        260
    };

    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 240);
    SDL_RenderFillRect(renderer, &panel);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderDrawRect(renderer, &panel);

    // başlık
    const bool win = game && game->WasLastWin();
    const int score = game ? game->GetLastFinalScore() : 0;

    std::string title = win ? "YOU WIN!" : "GAME OVER";
    std::string scoreText = "Score: " + std::to_string(score);

    SDL_Color white = { 255, 255, 255, 255 };

    int tw, th;

    TextManager::GetInstance().GetTextSize(title, "main_font", tw, th);
    TextManager::GetInstance().RenderText(
        title,
        "main_font",
        screenW / 2 - tw / 2,
        screenH / 2 - 120,
        white
    );

    TextManager::GetInstance().GetTextSize(scoreText, "main_font", tw, th);
    TextManager::GetInstance().RenderText(
        scoreText,
        "main_font",
        screenW / 2 - tw / 2,
        screenH / 2 - 70,
        white
    );

    UIManager::GetInstance().Render();
}

void GameOverScene::HandleInput()
{
    const auto& events = InputManager::GetInstance().GetFrameEvents();

    for (const auto& e : events)
    {
        SDL_Event copy = e;
        UIManager::GetInstance().HandleEvent(copy);
    }

    InputManager::GetInstance().ClearFrameEvents();
}
