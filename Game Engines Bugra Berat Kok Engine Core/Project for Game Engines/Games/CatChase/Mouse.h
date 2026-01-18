#pragma once
#include "Character.h"

class Mouse : public Character
{
private:
    float dirX, dirY;
    bool shouldDelete;

public:
    Mouse(float x, float y, float dirX, float dirY);
    ~Mouse();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

    bool IsOutOfBounds(int screenWidth, int screenHeight) const;

    void MarkForDeletion() { shouldDelete = true; }
    bool ShouldDelete() const { return shouldDelete; }
};