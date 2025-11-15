#include "BaseObject.h"
#include "ObjectManager.h"

BaseObject::BaseObject()
    : posX(0), posY(0), rot(0), texture(nullptr) //object has two coordinates and rotation value. Texture will be provided by Sprite Manager
{
    rect = { 0, 0, 0, 0 };
    ObjectManager::GetInstance().AddObject(this);
}

BaseObject::~BaseObject()
{
    ObjectManager::GetInstance().RemoveObject(this);
}

void BaseObject::Render(SDL_Renderer* renderer) 
{
    if (texture) //if texture is not null
        SDL_RenderCopyEx(renderer, texture, nullptr, &rect, rot, nullptr, SDL_FLIP_NONE);
}

void BaseObject::SetPosition(float x, float y) //change the position of the object
{
    posX = x;
    posY = y;
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
}

void BaseObject::SetTexture(SDL_Texture* tex) //change the texture of the object
{
    texture = tex;
}
