#pragma once
#include "Character.h"

class Cat : public Character
{
private:
    bool isCatching;
    int score;

public:
    Cat(float x, float y);
    ~Cat();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

    bool IsCatching() const { return isCatching; }

    void AddScore(int points) { score += points; }
    int GetScore() const { return score; }
};