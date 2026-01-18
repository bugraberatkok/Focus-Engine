#include <iostream>
#include "EngineApp.h"
#include "AnimationManager.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "AppleCollectorGame.h"
#include "AppleStartScene.h"
#include "AppleGameScene.h"
#include "AppleGameOverScene.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

int main(int argc, char* argv[])
{
    EngineApp app(WINDOW_WIDTH, WINDOW_HEIGHT, "Apple Collector");

    if (!app.Init())
        return -1;

    // Player animations (256x32, 64x32 per frame, 4 frames horizontal)
    AnimationManager::GetInstance().CreateAnimation("red_left", "Media/Sprites/Players/RedLeft.png", 64, 32, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("red_right", "Media/Sprites/Players/RedRight.png", 64, 32, 4, 0.15f, true);

    AnimationManager::GetInstance().CreateAnimation("green_left", "Media/Sprites/Players/GreenLeft.png", 64, 32, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("green_right", "Media/Sprites/Players/GreenRight.png", 64, 32, 4, 0.15f, true);

    AnimationManager::GetInstance().CreateAnimation("yellow_left", "Media/Sprites/Players/YellowLeft.png", 64, 32, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("yellow_right", "Media/Sprites/Players/YellowRight.png", 64, 32, 4, 0.15f, true);

    AnimationManager::GetInstance().CreateAnimation("purple_left", "Media/Sprites/Players/PurpleLeft.png", 64, 32, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("purple_right", "Media/Sprites/Players/PurpleRight.png", 64, 32, 4, 0.15f, true);

    // Apple sprites
    SpriteManager::GetInstance().LoadTexture("apple_red", "Media/Sprites/Apples/RedApple.png");
    SpriteManager::GetInstance().LoadTexture("apple_green", "Media/Sprites/Apples/GreenApple.png");
    SpriteManager::GetInstance().LoadTexture("apple_yellow", "Media/Sprites/Apples/YellowApple.png");
    SpriteManager::GetInstance().LoadTexture("apple_blue", "Media/Sprites/Apples/PurpleApple.png");

    // Font
    TextManager::GetInstance().LoadFont("main_font", "Media/Fonts/Roboto/static/Roboto-Regular.ttf", 32);

    // Sound
    SoundManager::GetInstance().Init();
    SoundManager::GetInstance().LoadMusic("game_music", "Media/Audio/bgMusic.mp3");
    SoundManager::GetInstance().SetMusicVolume(0.3f);

    // Game instance
    static AppleCollectorGame appleGame;

    // Scenes
    SceneManager::GetInstance().AddScene("AppleStart", new AppleStartScene());
    SceneManager::GetInstance().AddScene("AppleGame", new AppleGameScene(WINDOW_WIDTH, WINDOW_HEIGHT, &appleGame));
    SceneManager::GetInstance().AddScene("GameOver", new AppleGameOverScene(WINDOW_WIDTH, WINDOW_HEIGHT, &appleGame));

    SceneManager::GetInstance().ChangeScene("AppleStart");
    SceneManager::GetInstance().Update();

    app.Run();
    app.Shutdown();

    return 0;
}