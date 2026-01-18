#pragma once
#include "UISceneBase.h"

class AppleStartScene : public UISceneBase
{
public:
    AppleStartScene();

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void HandleInput() override;
};