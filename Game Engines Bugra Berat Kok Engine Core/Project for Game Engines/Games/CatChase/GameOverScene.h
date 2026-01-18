#pragma once
#include "UISceneBase.h"

class CatChaseGame;

class GameOverScene : public UISceneBase
{
private:
    CatChaseGame* game;   // oyun tarafı (engine değil)

    int screenW;
    int screenH;

public:
    GameOverScene(int w, int h, CatChaseGame* gameRef);

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void HandleInput() override;
};
