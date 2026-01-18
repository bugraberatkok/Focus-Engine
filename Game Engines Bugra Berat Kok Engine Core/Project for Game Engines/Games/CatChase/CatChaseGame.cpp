// CatChaseGame.cpp - Temizlenmiş hali

#include "CatChaseGame.h"
#include "TimeManager.h"
#include "PhysicsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

CatChaseGame::CatChaseGame()
    : cat(nullptr),
    gameTimer(60.0f),
    maxTime(60.0f),
    mouseSpawnTimer(0.0f),
    mouseSpawnInterval(2.0f),
    screenWidth(1280),
    screenHeight(720),
    gameActive(false),
    lastFinalScore(0),
    lastWasWin(false)
{
    srand(static_cast<unsigned>(time(nullptr)));
}

CatChaseGame::~CatChaseGame()
{
    Cleanup();
}

void CatChaseGame::Init(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    cat = new Cat(width / 2.0f, height / 2.0f);

    SpawnDog(50, 50);
    SpawnDog(width - 50.0f, 50);
    SpawnDog(50, height - 50.0f);
    SpawnDog(width - 50.0f, height - 50.0f);

    gameTimer = maxTime;
    mouseSpawnTimer = 0.0f;
    gameActive = true;

    GameManager::GetInstance().SetState(GameState::PLAYING);
}

void CatChaseGame::Update()
{
    if (!gameActive)
        return;

    float dt = TimeManager::GetInstance().GetDeltaTime();

    gameTimer -= dt;
    if (gameTimer <= 0.0f)
    {
        gameTimer = 0.0f;
        gameActive = false;
        lastFinalScore = GetScore();
        lastWasWin = true;
        GameManager::GetInstance().SetState(GameState::WIN);
        return;
    }

    mouseSpawnTimer += dt;
    if (mouseSpawnTimer >= mouseSpawnInterval)
    {
        mouseSpawnTimer = 0.0f;
        SpawnMouse();
    }

    if (cat)
    {
        float catCenterX = cat->GetRect().x + cat->GetRect().w / 2.0f;
        float catCenterY = cat->GetRect().y + cat->GetRect().h / 2.0f;

        for (Dog* dog : dogs)
        {
            if (dog)
                dog->SetTarget(catCenterX, catCenterY);
        }

        SeparateDogs();
    }

    for (auto it = mice.begin(); it != mice.end();)
    {
        Mouse* m = *it;

        if (!m)
        {
            it = mice.erase(it);
            continue;
        }

        if (m->IsOutOfBounds(screenWidth, screenHeight) || m->ShouldDelete())
        {
            ObjectManager::GetInstance().DestroyObject(m);
            it = mice.erase(it);
        }
        else
        {
            ++it;
        }
    }

    CheckCollisions();
}

void CatChaseGame::SeparateDogs()
{
    const float separationDistance = 40.0f;
    const float separationForce = 50.0f;
    const float dt = TimeManager::GetInstance().GetDeltaTime();

    float catCx = 0, catCy = 0;
    if (cat)
    {
        catCx = cat->GetRect().x + cat->GetRect().w * 0.5f;
        catCy = cat->GetRect().y + cat->GetRect().h * 0.5f;
    }

    for (size_t i = 0; i < dogs.size(); i++)
    {
        for (size_t j = i + 1; j < dogs.size(); j++)
        {
            Dog* A = dogs[i];
            Dog* B = dogs[j];
            if (!A || !B) continue;

            float ax = A->GetRect().x + A->GetRect().w * 0.5f;
            float ay = A->GetRect().y + A->GetRect().h * 0.5f;
            float bx = B->GetRect().x + B->GetRect().w * 0.5f;
            float by = B->GetRect().y + B->GetRect().h * 0.5f;

            float dx = bx - ax;
            float dy = by - ay;
            float d = std::sqrt(dx * dx + dy * dy);
            if (d < 0.001f) continue;

            if (d < separationDistance)
            {
                dx /= d; dy /= d;
                float t = (separationDistance - d) / separationDistance;

                float distAtoCat = std::sqrt((ax - catCx) * (ax - catCx) + (ay - catCy) * (ay - catCy));
                float distBtoCat = std::sqrt((bx - catCx) * (bx - catCx) + (by - catCy) * (by - catCy));
                float nearCat = std::min(distAtoCat, distBtoCat);

                float scale = nearCat / 60.0f;
                if (scale > 1.0f) scale = 1.0f;
                if (scale < 0.0f) scale = 0.0f;

                float push = t * separationForce * dt * scale;

                A->Nudge(-dx * push, -dy * push);
                B->Nudge(dx * push, dy * push);
            }
        }
    }
}

void CatChaseGame::CheckCollisions()
{
    if (!cat || !gameActive)
        return;

    PhysicsManager& physics = PhysicsManager::GetInstance();

    if (cat->IsCatching())
    {
        for (Mouse* mouse : mice)
        {
            if (!mouse) continue;

            if (physics.CheckCollision(cat->GetRect(), mouse->GetRect()))
            {
                cat->AddScore(10);
                mouse->MarkForDeletion();

                // ← SES EFEKTİ ÇAL
                SoundManager::GetInstance().PlaySound("bite_sound");
            }
        }
    }

    for (Dog* dog : dogs)
    {
        if (!dog) continue;

        if (physics.CheckCollision(cat->GetRect(), dog->GetRect()))
        {
            gameActive = false;
            lastFinalScore = cat->GetScore();
            lastWasWin = false;
            GameManager::GetInstance().SetState(GameState::GAME_OVER);
            return;
        }
    }
}

void CatChaseGame::SpawnMouse()
{
    float x, y, dirX, dirY;
    int edge = rand() % 4;

    switch (edge)
    {
    case 0:
        x = static_cast<float>(rand() % screenWidth);
        y = -50.0f;
        dirX = 0.0f;
        dirY = 1.0f;
        break;
    case 1:
        x = static_cast<float>(screenWidth + 50);
        y = static_cast<float>(rand() % screenHeight);
        dirX = -1.0f;
        dirY = 0.0f;
        break;
    case 2:
        x = static_cast<float>(rand() % screenWidth);
        y = static_cast<float>(screenHeight + 50);
        dirX = 0.0f;
        dirY = -1.0f;
        break;
    default:
        x = -50.0f;
        y = static_cast<float>(rand() % screenHeight);
        dirX = 1.0f;
        dirY = 0.0f;
        break;
    }

    mice.push_back(new Mouse(x, y, dirX, dirY));
}

void CatChaseGame::SpawnDog(float x, float y)
{
    dogs.push_back(new Dog(x, y));
}

void CatChaseGame::Cleanup()
{
    if (cat)
    {
        ObjectManager::GetInstance().DestroyObject(cat);
        cat = nullptr;
    }

    for (Mouse* m : mice)
    {
        if (m)
            ObjectManager::GetInstance().DestroyObject(m);
    }
    mice.clear();

    for (Dog* d : dogs)
    {
        if (d)
            ObjectManager::GetInstance().DestroyObject(d);
    }
    dogs.clear();
}

void CatChaseGame::Reset()
{
    Cleanup();
    Init(screenWidth, screenHeight);
}