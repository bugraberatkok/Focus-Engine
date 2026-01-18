#include "Apple.h"
#include "SpriteManager.h"
#include "TimeManager.h"
#include <iostream>
#include <cstdlib>

Apple::Apple(float x, float y, AppleColor appleColor)
    : StaticObject(),
    color(appleColor),
    collected(false),
    lifeTimer(0.0f),
    maxLifeTime(4.0f + static_cast<float>(rand() % 2))  // 4-5 saniye arası
{
    SetPosition(x, y);
    SetScale(2.0f);
    SetPickup(true);
    SetCollision(false);

    // Renge göre sprite yükle
    std::string texturePath;
    std::string textureId;

    switch (color)
    {
    case AppleColor::RED:
        textureId = "apple_red";
        texturePath = "Media/Sprites/Apples/RedApple.png";
        break;
    case AppleColor::GREEN:
        textureId = "apple_green";
        texturePath = "Media/Sprites/Apples/GreenApple.png";
        break;
    case AppleColor::YELLOW:
        textureId = "apple_yellow";
        texturePath = "Media/Sprites/Apples/YellowApple.png";
        break;
    case AppleColor::BLUE:
        textureId = "apple_blue";
        texturePath = "Media/Sprites/Apples/PurpleApple.png";
        break;
    }

    SDL_Texture* tex = SpriteManager::GetInstance().LoadTexture(textureId, texturePath);
    SetTexture(tex);

    // Collision rect
    SetCollisionRect(24, 24);
    SetCollisionCentered();

    std::cout << "Apple spawned at (" << x << ", " << y << ") Color: "
        << static_cast<int>(color) << std::endl;
}

Apple::~Apple()
{
    std::cout << "Apple destroyed" << std::endl;
}

void Apple::Update()
{
    StaticObject::Update();

    // Ömür sayacı
    float dt = TimeManager::GetInstance().GetDeltaTime();
    lifeTimer += dt;
}

void Apple::Render(SDL_Renderer* renderer)
{
    if (!collected)
    {
        StaticObject::Render(renderer);
    }
}