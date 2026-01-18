#pragma once
#include "GameSceneBase.h"

class CatChaseGame;

class GameScene : public GameSceneBase
{
private:
    int screenW;
    int screenH;
    CatChaseGame* game;
    bool initialized;

public:
    GameScene(int w, int h, CatChaseGame* gameRef);

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void HandleInput() override;
};