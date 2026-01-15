#include "AnimationManager.h"
#include "SpriteManager.h"
#include <iostream>

AnimationManager::~AnimationManager()
{
    UnloadAll();
}

Animation* AnimationManager::CreateAnimation(
    const std::string& id,
    const std::string& texturePath,
    int frameWidth,
    int frameHeight,
    int frameCount,
    float frameDuration,
    bool loop)
{
    // Eğer bu ID zaten varsa, onu döndür
    auto it = animations.find(id);
    if (it != animations.end())
    {
        std::cout << "Animation already exists: " << id << std::endl;
        return it->second;
    }

    // Texture'ı yükle (SpriteManager kullan)
    SDL_Texture* texture = SpriteManager::GetInstance().LoadTexture(id, texturePath);

    if (!texture)
    {
        std::cerr << "Failed to load animation texture: " << texturePath << std::endl;
        return nullptr;
    }

    // Yeni animasyon oluştur
    Animation* anim = new Animation();
    anim->texture = texture;
    anim->frameDuration = frameDuration;
    anim->loop = loop;

    // Frame'leri hesapla (sprite sheet yatay dizilmiş)
    for (int i = 0; i < frameCount; i++)
    {
        SDL_Rect frame;
        frame.x = i * frameWidth;
        frame.y = 0;
        frame.w = frameWidth;
        frame.h = frameHeight;

        anim->frames.push_back(frame);
    }

    // Map'e ekle
    animations[id] = anim;

    std::cout << "Animation created: " << id
        << " (" << frameCount << " frames)" << std::endl;

    return anim;
}

Animation* AnimationManager::GetAnimation(const std::string& id) const
{
    auto it = animations.find(id);
    if (it != animations.end())
        return it->second;

    std::cerr << "Animation not found: " << id << std::endl;
    return nullptr;
}

void AnimationManager::UpdateAnimation(AnimationState& state, float deltaTime)
{
    if (!state.currentAnimation || !state.isPlaying)
        return;

    // Timer'ı artır
    state.frameTimer += deltaTime;

    // Frame süresini geçtiyse bir sonraki frame'e geç
    if (state.frameTimer >= state.currentAnimation->frameDuration)
    {
        state.frameTimer = 0.0f;
        state.currentFrame++;

        // Son frame'e ulaştıysak
        if (state.currentFrame >= state.currentAnimation->frames.size())
        {
            if (state.currentAnimation->loop)
            {
                // Loop varsa başa dön
                state.currentFrame = 0;
            }
            else
            {
                // Loop yoksa son frame'de kal
                state.currentFrame = state.currentAnimation->frames.size() - 1;
                state.isFinished = true;
                state.isPlaying = false;
            }
        }
    }
}

void AnimationManager::RenderAnimation(
    SDL_Renderer* renderer,
    const AnimationState& state,
    int x, int y,
    float scale,
    SDL_RendererFlip flip)
{
    if (!state.currentAnimation || !state.currentAnimation->texture)
        return;

    if (state.currentFrame < 0 ||
        state.currentFrame >= state.currentAnimation->frames.size())
        return;

    // Şu anki frame'i al
    const SDL_Rect& srcRect = state.currentAnimation->frames[state.currentFrame];

    // Hedef rect'i hesapla (scale uygula)
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = static_cast<int>(srcRect.w * scale);
    dstRect.h = static_cast<int>(srcRect.h * scale);

    // Çiz
    SDL_RenderCopyEx(
        renderer,
        state.currentAnimation->texture,
        &srcRect,  // Sprite sheet'ten hangi bölge
        &dstRect,  // Ekranda nereye
        0.0,       // Rotation
        nullptr,   // Rotation center
        flip       // Flip (SDL_FLIP_HORIZONTAL vs)
    );
}

void AnimationManager::UnloadAnimation(const std::string& id)
{
    auto it = animations.find(id);
    if (it != animations.end())
    {
        delete it->second;
        animations.erase(it);
    }
}

void AnimationManager::UnloadAll()
{
    for (auto& pair : animations)
    {
        delete pair.second;
    }
    animations.clear();
}