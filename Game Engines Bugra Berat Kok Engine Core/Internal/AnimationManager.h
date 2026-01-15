#pragma once
#include "Singleton.h"
#include <SDL.h>
#include <string>
#include <map>
#include <vector>

// Bir animasyon tanımı
struct Animation
{
    SDL_Texture* texture;           // Sprite sheet texture'ı
    std::vector<SDL_Rect> frames;   // Her frame'in sprite sheet içindeki koordinatları
    float frameDuration;            // Her frame kaç saniye gösterilecek
    bool loop;                      // Animasyon döngüye girecek mi?

    Animation() : texture(nullptr), frameDuration(0.1f), loop(true) {}
};

// Bir objenin animasyon durumu
struct AnimationState
{
    Animation* currentAnimation;
    int currentFrame;
    float frameTimer;
    bool isPlaying;
    bool isFinished;

    AnimationState()
        : currentAnimation(nullptr),
        currentFrame(0),
        frameTimer(0.0f),
        isPlaying(true),
        isFinished(false)
    {
    }
};

class AnimationManager : public Singleton<AnimationManager>
{
    friend class Singleton<AnimationManager>;

private:
    AnimationManager() {}
    ~AnimationManager();

    SDL_Renderer* renderer;
    std::map<std::string, Animation*> animations;

public:
    void SetRenderer(SDL_Renderer* r) { renderer = r; }

    // Sprite sheet'ten animasyon oluştur
    Animation* CreateAnimation(
        const std::string& id,              // "cat_walk"
        const std::string& texturePath,     // "Media/cat_walk.png"
        int frameWidth,                     // 48
        int frameHeight,                    // 48
        int frameCount,                     // 6
        float frameDuration = 0.1f,         // Her frame 0.1 saniye
        bool loop = true                    // Döngüye girsin mi
    );

    Animation* GetAnimation(const std::string& id) const;

    // Animasyon state'ini güncelle (deltaTime ile)
    void UpdateAnimation(AnimationState& state, float deltaTime);

    // Animasyonu ekrana çiz
    void RenderAnimation(
        SDL_Renderer* renderer,
        const AnimationState& state,
        int x, int y,
        float scale = 1.0f,
        SDL_RendererFlip flip = SDL_FLIP_NONE
    );

    void UnloadAnimation(const std::string& id);
    void UnloadAll();
};