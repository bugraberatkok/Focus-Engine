#pragma once
#include <SDL.h>

struct AnimationState;

class BaseObject
{
protected:
    float posX, posY, rot;
    SDL_Texture* texture;

    SDL_Rect rect;
    SDL_Rect renderRect;

    int texW, texH;
    float scale;

    bool manualHitbox;
    int hitboxOffsetX;
    int hitboxOffsetY;

    AnimationState* animState;
    SDL_RendererFlip flip;

    // ← YENİ: Physics
    float velocityX;        // Yatay hız
    float velocityY;        // Dikey hız (gravity için)
    bool gravityAffected;   // Gravity etkisi var mı?

public:
    BaseObject();
    virtual ~BaseObject();

    virtual void Update() {}
    virtual void Render(SDL_Renderer* renderer);

    void SetPosition(float x, float y);
    void SetTexture(SDL_Texture* tex);
    void SetScale(float s);

    void SetAnimation(class Animation* anim);
    void PlayAnimation(class Animation* anim, bool restart = false);
    AnimationState* GetAnimationState() { return animState; }

    void SetFlip(SDL_RendererFlip f) { flip = f; }
    SDL_RendererFlip GetFlip() const { return flip; }

    const SDL_Rect& GetRect() const { return rect; }

    void SetCollisionRect(int w, int h)
    {
        rect.w = w;
        rect.h = h;
    }

    void SetCollisionOffset(int offsetX, int offsetY)
    {
        manualHitbox = true;
        hitboxOffsetX = offsetX;
        hitboxOffsetY = offsetY;
    }

    void SetCollisionCentered()
    {
        manualHitbox = false;
        hitboxOffsetX = 0;
        hitboxOffsetY = 0;
    }

    void UpdateRenderRect();

    // ← YENİ: Physics getters/setters
    void SetVelocity(float vx, float vy) { velocityX = vx; velocityY = vy; }
    void SetVelocityX(float vx) { velocityX = vx; }
    void SetVelocityY(float vy) { velocityY = vy; }
    float GetVelocityX() const { return velocityX; }
    float GetVelocityY() const { return velocityY; }

    void SetGravityAffected(bool affected) { gravityAffected = affected; }
    bool IsGravityAffected() const { return gravityAffected; }
};