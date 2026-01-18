#pragma once
#include "Cat.h"
#include "Mouse.h"
#include "Dog.h"
#include <vector>

class CatChaseGame
{
private:
    Cat* cat;
    std::vector<Mouse*> mice;
    std::vector<Dog*> dogs;

    float gameTimer;
    float maxTime;
    float mouseSpawnTimer;
    float mouseSpawnInterval;
    int screenWidth;
    int screenHeight;
    bool gameActive;
    int lastFinalScore;
    bool lastWasWin;

    void SeparateDogs();

public:
    CatChaseGame();
    ~CatChaseGame();

    void Init(int width, int height);
    void Update();
    void CheckCollisions();
    void Cleanup();
    void Reset();

    void SpawnMouse();
    void SpawnDog(float x, float y);

    Cat* GetCat() const { return cat; }
    int GetScore() const { return cat ? cat->GetScore() : 0; }
    float GetTimeRemaining() const { return gameTimer; }
    bool IsGameActive() const { return gameActive; }
    int GetLastFinalScore() const { return lastFinalScore; }
    bool WasLastWin() const { return lastWasWin; }

    void SetGameActive(bool active) { gameActive = active; }

    const std::vector<Mouse*>& GetMice() const { return mice; }
    const std::vector<Dog*>& GetDogs() const { return dogs; }
};