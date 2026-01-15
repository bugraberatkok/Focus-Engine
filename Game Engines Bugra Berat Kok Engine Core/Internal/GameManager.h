#pragma once
#include "Singleton.h"

enum class GameState
{
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    WIN
};

class GameManager : public Singleton<GameManager>
{
    friend class Singleton<GameManager>;

private:
    GameManager();

    GameState currentState;

public:
    // State Management (sadece bu kadar!)
    void SetState(GameState newState) { currentState = newState; }
    GameState GetState() const { return currentState; }

    // Helper fonksiyonlar
    bool IsPlaying() const { return currentState == GameState::PLAYING; }
    bool IsPaused() const { return currentState == GameState::PAUSED; }
    bool IsGameOver() const { return currentState == GameState::GAME_OVER; }
    bool IsWin() const { return currentState == GameState::WIN; }
    bool IsMenu() const { return currentState == GameState::MENU; }
};