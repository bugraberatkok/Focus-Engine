#pragma once
#include "Character.h"
#include "Apple.h"

class Player : public Character
{
private:
    AppleColor currentColor;
    float colorChangeTimer;
    float colorChangeInterval;
    int score;
    bool movingLeft;
    bool movingRight;

    // Her renk için 2 animasyon (left + right)
    Animation* redLeftAnim;
    Animation* redRightAnim;
    Animation* greenLeftAnim;
    Animation* greenRightAnim;
    Animation* yellowLeftAnim;
    Animation* yellowRightAnim;
    Animation* purpleLeftAnim;
    Animation* purpleRightAnim;

    void ChangeColorRandomly();
    void UpdateAnimation();

public:
    Player(float x, float y);
    ~Player();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

    AppleColor GetCurrentColor() const { return currentColor; }

    void AddScore(int points) { score += points; }
    void SubtractScore(int points) { score -= points; }
    int GetScore() const { return score; }

    float GetColorChangeTimer() const { return colorChangeTimer; }
    float GetColorChangeInterval() const { return colorChangeInterval; }
};