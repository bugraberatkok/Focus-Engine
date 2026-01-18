#include "AppleCollectorGame.h"
#include "TimeManager.h"
#include "PhysicsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

AppleCollectorGame::AppleCollectorGame()
    : player(nullptr),
    gameTimer(80.0f),
    maxTime(80.0f),
    appleSpawnTimer(0.0f),
    appleSpawnInterval(2.0f),
    maxApplesOnScreen(8),
    screenWidth(1920),
    screenHeight(1080),
    gameActive(false),
    lastFinalScore(0)
{
    srand(static_cast<unsigned>(time(nullptr)));
}

AppleCollectorGame::~AppleCollectorGame()
{
    Cleanup();
}

void AppleCollectorGame::Init(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    // Create player at center
    player = new Player(width / 2.0f, height / 2.0f);

    gameTimer = maxTime;
    appleSpawnTimer = 0.0f;
    gameActive = true;

    // Spawn initial apples
    for (int i = 0; i < 4; i++)
    {
        SpawnApple();
    }

    GameManager::GetInstance().SetState(GameState::PLAYING);
}

void AppleCollectorGame::SpawnApple()
{
    if (apples.size() >= maxApplesOnScreen)
        return;

    // Random position with margins
    float x = 100.0f + static_cast<float>(rand() % (screenWidth - 200));
    float y = 100.0f + static_cast<float>(rand() % (screenHeight - 200));

    // Random color (0-3)
    AppleColor color = static_cast<AppleColor>(rand() % 4);

    apples.push_back(new Apple(x, y, color));
}

void AppleCollectorGame::Update()
{
    if (!gameActive)
        return;

    float dt = TimeManager::GetInstance().GetDeltaTime();

    // Game timer countdown
    gameTimer -= dt;
    if (gameTimer <= 0.0f)
    {
        gameTimer = 0.0f;
        gameActive = false;
        lastFinalScore = GetScore();
        GameManager::GetInstance().SetState(GameState::WIN);
        return;
    }

    // Apple spawning
    appleSpawnTimer += dt;
    if (appleSpawnTimer >= appleSpawnInterval)
    {
        appleSpawnTimer = 0.0f;
        SpawnApple();
    }

    // Remove collected or expired apples
    for (auto it = apples.begin(); it != apples.end();)
    {
        Apple* apple = *it;

        if (!apple || apple->IsCollected() || apple->ShouldDespawn())
        {
            if (apple)
                ObjectManager::GetInstance().DestroyObject(apple);
            it = apples.erase(it);
        }
        else
        {
            ++it;
        }
    }

    CheckCollisions();
}

void AppleCollectorGame::CheckCollisions()
{
    if (!player || !gameActive)
        return;

    PhysicsManager& physics = PhysicsManager::GetInstance();

    for (Apple* apple : apples)
    {
        if (!apple || apple->IsCollected())
            continue;

        if (physics.CheckCollision(player->GetRect(), apple->GetRect()))
        {
            // Check if colors match
            if (player->GetCurrentColor() == apple->GetColor())
            {
                // Correct color
                player->AddScore(10);
                std::cout << "+10 points! Score: " << player->GetScore() << std::endl;
            }
            else
            {
                // Wrong color
                player->SubtractScore(5);
                std::cout << "-5 points! Score: " << player->GetScore() << std::endl;
            }

            apple->Collect();
        }
    }
}

void AppleCollectorGame::Cleanup()
{
    if (player)
    {
        ObjectManager::GetInstance().DestroyObject(player);
        player = nullptr;
    }

    for (Apple* apple : apples)
    {
        if (apple)
            ObjectManager::GetInstance().DestroyObject(apple);
    }
    apples.clear();
}

void AppleCollectorGame::Reset()
{
    Cleanup();
    Init(screenWidth, screenHeight);
}