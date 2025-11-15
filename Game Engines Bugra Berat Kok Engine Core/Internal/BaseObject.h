#pragma once
#include <SDL.h>

class BaseObject
{
protected:
    float posX, posY, rot;
    SDL_Texture* texture;
    SDL_Rect rect;

public:
    BaseObject();
    virtual ~BaseObject();

    virtual void Update() {}

    virtual void Render(SDL_Renderer* renderer);

    void SetPosition(float x, float y);

    void SetTexture(SDL_Texture* tex);

    const SDL_Rect& GetRect() const { return rect; }
};
