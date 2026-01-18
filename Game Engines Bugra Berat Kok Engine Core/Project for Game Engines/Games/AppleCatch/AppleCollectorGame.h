#pragma once
#include "Player.h"
#include "Apple.h"
#include <vector>

class AppleCollectorGame
{
private:
    Player* player;
    std::vector<Apple*> apples;

    float gameTimer;
    float maxTime;
    float appleSpawnTimer;
    float appleSpawnInterval;
    int maxApplesOnScreen;
    int screenWidth;
    int screenHeight;
    bool gameActive;
    int lastFinalScore;

public:
    AppleCollectorGame();
    ~AppleCollectorGame();

    void Init(int width, int height);
    void Update();
    void CheckCollisions();
    void Cleanup();
    void Reset();

    void SpawnApple();

    Player* GetPlayer() const { return player; }
    int GetScore() const { return player ? player->GetScore() : 0; }
    float GetTimeRemaining() const { return gameTimer; }
    bool IsGameActive() const { return gameActive; }
    int GetLastFinalScore() const { return lastFinalScore; }

    void SetGameActive(bool active) { gameActive = active; }

    const std::vector<Apple*>& GetApples() const { return apples; }
};