#include "BaseObject.h"
#include "ObjectManager.h"
#include "AnimationManager.h"
#include "TimeManager.h"
#include <SDL.h>

BaseObject::BaseObject()
    : posX(0.0f), posY(0.0f), rot(0.0f),
    texture(nullptr),
    texW(0), texH(0),
    scale(1.0f),
    animState(nullptr),
    flip(SDL_FLIP_NONE)
{
    rect = { 0, 0, 0, 0 };
    ObjectManager::GetInstance().AddObject(this);
}

BaseObject::~BaseObject()
{
    // Animasyon state'ini temizle
    if (animState)
    {
        delete animState;
        animState = nullptr;
    }

    ObjectManager::GetInstance().RemoveObject(this);
}

void BaseObject::Render(SDL_Renderer* renderer)
{
    // Önce animasyon varsa onu çiz
    if (animState && animState->currentAnimation)
    {
        AnimationManager::GetInstance().RenderAnimation(
            renderer,
            *animState,
            rect.x,
            rect.y,
            scale,
            flip
        );
    }
    // Animasyon yoksa eski texture sistemini kullan
    else if (texture && rect.w > 0 && rect.h > 0)
    {
        SDL_RenderCopyEx(renderer, texture, nullptr, &rect, rot, nullptr, flip);
    }
}

void BaseObject::SetPosition(float x, float y)
{
    posX = x;
    posY = y;
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
}

void BaseObject::SetTexture(SDL_Texture* tex)
{
    texture = tex;

    if (texture)
    {
        if (SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH) != 0)
        {
            SDL_Log("SDL_QueryTexture error: %s", SDL_GetError());
            texW = texH = 0;
        }

        if (texW > 0 && texH > 0)
        {
            rect.w = static_cast<int>(texW * scale);
            rect.h = static_cast<int>(texH * scale);
        }
    }
    else
    {
        SDL_Log("SetTexture: texture is nullptr");
        texW = texH = 0;
        rect.w = rect.h = 0;
    }
}

void BaseObject::SetScale(float s)
{
    scale = s;

    // Eğer animasyon varsa, animasyonun frame boyutunu kullan
    if (animState && animState->currentAnimation &&
        !animState->currentAnimation->frames.empty())
    {
        const SDL_Rect& frame = animState->currentAnimation->frames[0];
        rect.w = static_cast<int>(frame.w * scale);
        rect.h = static_cast<int>(frame.h * scale);
    }
    // Animasyon yoksa texture boyutunu kullan
    else if (texW > 0 && texH > 0)
    {
        rect.w = static_cast<int>(texW * scale);
        rect.h = static_cast<int>(texH * scale);
    }
}

void BaseObject::SetAnimation(Animation* anim)
{
    if (!anim)
        return;

    // İlk defa animasyon state oluştur
    if (!animState)
    {
        animState = new AnimationState();
    }

    animState->currentAnimation = anim;
    animState->currentFrame = 0;
    animState->frameTimer = 0.0f;
    animState->isPlaying = true;
    animState->isFinished = false;

    // Rect boyutunu animasyon frame'ine göre ayarla
    if (!anim->frames.empty())
    {
        const SDL_Rect& frame = anim->frames[0];
        rect.w = static_cast<int>(frame.w * scale);
        rect.h = static_cast<int>(frame.h * scale);
    }
}

void BaseObject::PlayAnimation(Animation* anim, bool restart)
{
    if (!anim)
        return;

    // Eğer aynı animasyon çalışıyorsa ve restart false ise, bir şey yapma
    if (animState &&
        animState->currentAnimation == anim &&
        animState->isPlaying &&
        !restart)
    {
        return;
    }

    SetAnimation(anim);
}