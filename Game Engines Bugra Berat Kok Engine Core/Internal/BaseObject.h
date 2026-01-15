#pragma once
#include <SDL.h>

// Forward declaration
struct AnimationState;

class BaseObject
{
protected:
    float posX, posY, rot;
    SDL_Texture* texture;
    SDL_Rect rect;

    int texW, texH;
    float scale;

    // Animasyon desteği (opsiyonel)
    AnimationState* animState;
    SDL_RendererFlip flip;  // Sprite yönü (sağa/sola bakma için)

public:
    BaseObject();
    virtual ~BaseObject();

    virtual void Update() {}
    virtual void Render(SDL_Renderer* renderer);

    void SetPosition(float x, float y);
    void SetTexture(SDL_Texture* tex);
    void SetScale(float s);

    // Animasyon fonksiyonları
    void SetAnimation(class Animation* anim);
    void PlayAnimation(class Animation* anim, bool restart = false);
    AnimationState* GetAnimationState() { return animState; }

    // Flip kontrolü (sağa/sola bakma)
    void SetFlip(SDL_RendererFlip f) { flip = f; }
    SDL_RendererFlip GetFlip() const { return flip; }

    const SDL_Rect& GetRect() const { return rect; }
};