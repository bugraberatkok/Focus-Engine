#include <iostream>
#include "EngineApp.h"
#include "AnimationManager.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "SoundManager.h"  // ← EKLE
#include "CatChaseGame.h"
#include "StartScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

int main(int argc, char* argv[])
{
    // Pencere ve Oyun içi çözünürlük AYNI.
    // Stretch yok, pikseller 1:1.
    EngineApp app(1920, 1080, "Cat Chase");

    if (!app.Init()) return -1;

    // Animasyonlar
    AnimationManager::GetInstance().CreateAnimation("cat_walk", "Media/Sprites/CatWalk.png", 48, 48, 6, 0.1f, true);
    AnimationManager::GetInstance().CreateAnimation("cat_attack", "Media/Sprites/CatAttack.png", 48, 48, 4, 0.1f, false);
    AnimationManager::GetInstance().CreateAnimation("cat_idle", "Media/Sprites/CatIdle.png", 48, 48, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("mouse_walk", "Media/Sprites/RatWalk.png", 32, 32, 4, 0.1f, true);
    AnimationManager::GetInstance().CreateAnimation("mouse_death", "Media/Sprites/RatDeath.png", 32, 32, 4, 0.1f, false);
    AnimationManager::GetInstance().CreateAnimation("dog_walk", "Media/Sprites/DogWalk.png", 48, 48, 6, 0.1f, true);
    AnimationManager::GetInstance().CreateAnimation("dog_idle", "Media/Sprites/DogIdle.png", 48, 48, 4, 0.15f, true);

    // Font
    TextManager::GetInstance().LoadFont("main_font", "Media/Fonts/Roboto/static/Roboto-Regular.ttf", 32);

    // ← MÜZİK + SES EFEKTLERİ
    SoundManager::GetInstance().Init();
    SoundManager::GetInstance().LoadMusic("game_music", "Media/Sounds/BackgroundMusic.mp3");  // veya .ogg
    SoundManager::GetInstance().LoadSound("bite_sound", "Media/Sounds/CatSoundEffect.wav");
    SoundManager::GetInstance().SetMusicVolume(0.3f);  // %30 volume
    SoundManager::GetInstance().SetSFXVolume(0.5f);    // %50 volume

    static CatChaseGame sharedGame;

    SceneManager::GetInstance().AddScene("Start", new StartScene());
    SceneManager::GetInstance().AddScene("Game", new GameScene(WINDOW_WIDTH, WINDOW_HEIGHT, &sharedGame));
    SceneManager::GetInstance().AddScene("GameOver", new GameOverScene(WINDOW_WIDTH, WINDOW_HEIGHT, &sharedGame));

    SceneManager::GetInstance().ChangeScene("Start");
    SceneManager::GetInstance().Update();

    app.Run();
    app.Shutdown();
    return 0;
}