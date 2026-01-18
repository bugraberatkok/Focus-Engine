#include "Player.h"
#include "AnimationManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include <cstdlib>
#include <iostream>

Player::Player(float x, float y)
    : Character(),
    currentColor(AppleColor::RED),
    colorChangeTimer(0.0f),
    colorChangeInterval(10.0f),
    score(0),
    movingLeft(false),
    movingRight(false),
    redLeftAnim(nullptr),
    redRightAnim(nullptr),
    greenLeftAnim(nullptr),
    greenRightAnim(nullptr),
    yellowLeftAnim(nullptr),
    yellowRightAnim(nullptr),
    purpleLeftAnim(nullptr),
    purpleRightAnim(nullptr)
{
    SetPosition(x, y);
    SetSpeed(300.0f);
    SetScale(4.5f);

    // Animasyonları yükle
    redLeftAnim = AnimationManager::GetInstance().GetAnimation("red_left");
    redRightAnim = AnimationManager::GetInstance().GetAnimation("red_right");
    greenLeftAnim = AnimationManager::GetInstance().GetAnimation("green_left");
    greenRightAnim = AnimationManager::GetInstance().GetAnimation("green_right");
    yellowLeftAnim = AnimationManager::GetInstance().GetAnimation("yellow_left");
    yellowRightAnim = AnimationManager::GetInstance().GetAnimation("yellow_right");
    purpleLeftAnim = AnimationManager::GetInstance().GetAnimation("purple_left");
    purpleRightAnim = AnimationManager::GetInstance().GetAnimation("purple_right");

    // Collision
    SetCollisionRect(80, 60);
    SetCollisionOffset(100,80);

    // Rastgele başlangıç rengi
    ChangeColorRandomly();

    std::cout << "Player created at (" << x << ", " << y << ")" << std::endl;
}

Player::~Player()
{
    std::cout << "Player destroyed. Final score: " << score << std::endl;
}

void Player::ChangeColorRandomly()
{
    int randomColor = rand() % 4;
    currentColor = static_cast<AppleColor>(randomColor);

    UpdateAnimation();

    std::cout << "Player color changed to: " << static_cast<int>(currentColor) << std::endl;
}

void Player::UpdateAnimation()
{
    Animation* targetAnim = nullptr;

    // Renk ve yöne göre animasyon seç
    switch (currentColor)
    {
    case AppleColor::RED:
        targetAnim = movingLeft ? redLeftAnim : redRightAnim;
        break;
    case AppleColor::GREEN:
        targetAnim = movingLeft ? greenLeftAnim : greenRightAnim;
        break;
    case AppleColor::YELLOW:
        targetAnim = movingLeft ? yellowLeftAnim : yellowRightAnim;
        break;
    case AppleColor::BLUE:
        targetAnim = movingLeft ? purpleLeftAnim : purpleRightAnim;
        break;
    }

    if (targetAnim)
        PlayAnimation(targetAnim);
}

void Player::Update()
{
    Character::Update();

    float dt = TimeManager::GetInstance().GetDeltaTime();
    InputManager& input = InputManager::GetInstance();

    // Renk değişim timer'ı
    colorChangeTimer += dt;
    if (colorChangeTimer >= colorChangeInterval)
    {
        colorChangeTimer = 0.0f;
        ChangeColorRandomly();
    }

    // Hareket
    bool wasMovingLeft = movingLeft;
    bool wasMovingRight = movingRight;

    movingLeft = false;
    movingRight = false;

    if (input.GetKey(SDL_SCANCODE_W) || input.GetKey(SDL_SCANCODE_UP))
    {
        posY -= speed * dt;
    }
    if (input.GetKey(SDL_SCANCODE_S) || input.GetKey(SDL_SCANCODE_DOWN))
    {
        posY += speed * dt;
    }
    if (input.GetKey(SDL_SCANCODE_A) || input.GetKey(SDL_SCANCODE_LEFT))
    {
        posX -= speed * dt;
        movingLeft = true;
    }
    if (input.GetKey(SDL_SCANCODE_D) || input.GetKey(SDL_SCANCODE_RIGHT))
    {
        posX += speed * dt;
        movingRight = true;
    }

    // Yön değişti mi kontrol et
    if (movingLeft != wasMovingLeft || movingRight != wasMovingRight)
    {
        UpdateAnimation();
    }

    // Ekran sınırları
    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    if (posX > 1920 - 80) posX = 1920 - 80;
    if (posY > 1080 - 80) posY = 1080 - 80;

    SetPosition(posX, posY);
}

void Player::Render(SDL_Renderer* renderer)
{
    Character::Render(renderer);

}